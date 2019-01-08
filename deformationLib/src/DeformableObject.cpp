#include "DeformableObject.h"
#include <cmath>
#include <math.h>
DeformableObject::DeformableObject(std::vector<glm::vec3> _originalPositions, glm::vec3 _vel)
{
    m_mode = 0;
    m_Aqq = glm::mat3(0.0f);
    // reset all attributes
    for(unsigned int i = 0 ; i < _originalPositions.size(); ++i)
    {
        m_listOfParticles.emplace_back(Particle(_originalPositions[i], _vel));
    }
    // original center of mass
    m_originalCenterOfMass = computeCOM();
    // calculate the q 
    for(auto& particle : m_listOfParticles)
    {
        particle.setQ(particle.getInitPosition()-m_originalCenterOfMass);
    }
    // calculate Aqq and Aqq_tilde
    for(auto& particle : m_listOfParticles)
    {
        m_Aqq += particle.getMass() * glm::outerProduct(particle.getQ(), particle.getQ());
    }
    // inverse of m_Aqq
    m_Aqq = glm::inverse(m_Aqq);
    // calculate qtilde
    for(auto& particle : m_listOfParticles)
    {
        float x = particle.getQ().x;
        float y = particle.getQ().y;
        float z = particle.getQ().z;
        Eigen::VectorXf q = Eigen::VectorXf(9,1);
        q << x, y, z, x * x, y * y, z * z, x * y, y * z, z * x;
        particle.setQTilde(q);
    }
    // m_Aqq
    for(auto& particle : m_listOfParticles)
    {
        auto q = particle.getQTilde();
        m_AqqTilde += (q * q.transpose()) * particle.getMass();
    }
    Eigen::HouseholderQR<Eigen::MatrixXf> qr;
    qr.compute(m_AqqTilde);
    m_AqqTilde = qr.solve(Eigen::MatrixXf::Identity(9,9));
}
// ---------------------------------------------------------
std::vector<Particle> DeformableObject::getListOfParticles()
{
    return m_listOfParticles;
}
/// ---------------------------------------------------------
glm::vec3 DeformableObject::getOriginalCOM()
{
    return m_originalCenterOfMass;
}
/// ---------------------------------------------------------
void DeformableObject::update(float _timeStep, std::vector<float> _impuls)
{
    for(auto& part : m_listOfParticles)
    {
        part.updateForces(_timeStep, _impuls);
        part.updateVelocity(_timeStep);
        part.updatePosition(_timeStep);
    }
}
/// ---------------------------------------------------------
void DeformableObject::shapematching(float _timeStep, float _stiffness, float _bounciness)
{
    m_Apq = glm::mat3(0.0f);
    m_ApqTilde = Eigen::MatrixXf::Zero(3,9);
    glm::vec3 centerOfMass; 
    centerOfMass = computeCOM();
    // calculate P current original positions 
    for(auto& particle : m_listOfParticles)
    {
        particle.setP(particle.getCurrentPosition() - centerOfMass);
        
    }
    float det = 0;
    Eigen::MatrixXf identity = Eigen::MatrixXf::Identity(9,9);
    Eigen::Vector3f g; 
    if(m_mode != DeformationMode::Quadratic)
    {
            for(auto& particle : m_listOfParticles)
            {
                m_Apq += particle.getMass() * glm::outerProduct(particle.getP(), particle.getQ());
            }
            m_R = calculateR();
    }
    switch(m_mode)
    {
        case DeformationMode::Basic:
            // set goal positions
            for(auto& particle : m_listOfParticles)
            {
                particle.setGoalPosition(m_R * (particle.getInitPosition() - m_originalCenterOfMass) + centerOfMass);
            }
            break;
        case DeformationMode::Linear:
            // calculate linear matrix 
            m_A = m_Apq * m_Aqq;   
            det = glm::determinant(m_A);
            // scale A to ensure det(A) = 1
            m_A /= pow(det > 0.1f ? det :  0.1f, 1.0/3.0f); 
            // set goal positions
            for(auto& particle : m_listOfParticles)
            {
                particle.setGoalPosition((m_beta * m_A + (1.0f-m_beta) * m_R) * (particle.getInitPosition() - m_originalCenterOfMass) + centerOfMass);
            }
            break;
        case DeformationMode::Quadratic:
            // calculate matrices
            for(auto& particle : m_listOfParticles)
            {
                // outerproduct needs to be swapped for quadratic
                m_Apq += particle.getMass() * glm::outerProduct(particle.getQ(), particle.getP());
                Eigen::Vector3f p({particle.getP().x, particle.getP().y, particle.getP().z});
                m_ApqTilde += particle.getMass() * (p * particle.getQTilde().transpose());
            }
            // calculata ATilde
            m_ATilde = m_ApqTilde * m_AqqTilde;
            // calculate R 
            m_R = calculateR();
            // RTilde
            // scale factor
            for(int i=0; i<3;++i)
            {
                for(int j=0; j<3; ++j)
                {
                    m_RTilde(i,j) = m_R[i][j];
                    identity(i,j) = m_ATilde(i,j);
                }
            }
            // scale
            det = identity.determinant();
            identity /= pow(det > .1f?det:0.1f,1.0/9.0f);
            // convert back to 3x9 matrix 
            for(int i=0; i<3; ++i)
            {
                for(int j=0; j<3; ++j)
                {
                    m_ATilde(i,j) = identity(i,j);
                }
            }
            // set goal positions 
            for(auto& particle : m_listOfParticles)
            {
                g = (m_beta * m_ATilde + (1.0f - m_beta) * m_RTilde)* particle.getQTilde();
                particle.setGoalPosition(glm::vec3(g(0), g(1), g(2)) + centerOfMass);
            }
            break;
        default: 
            std::cout<<"Error, there is no mode"<<std::endl;
    }
    // add shape mathcing by translatinjg poositions towards goal positions
    for(auto& particle : m_listOfParticles)
    {
        particle.shapeMatchUpdate(_timeStep, _stiffness, _bounciness);
    }
}
/// ---------------------------------------------------------
int DeformableObject::getMode()
{
    return m_mode;
}
/// ---------------------------------------------------------
void DeformableObject::setMode(int _mode)
{
    m_mode = std::move(_mode);
}
/// ---------------------------------------------------------
void DeformableObject::setBeta(float _beta)
{
    m_beta = std::move(_beta);
}
/// ---------------------------------------------------------
glm::vec3 DeformableObject::computeCOM()
{
    glm::vec3 com{0.0f, 0.0f, 0.0f};
    float massSum{0.0f};
    for(auto& particle : m_listOfParticles)
    {
        com += particle.getCurrentPosition() * particle.getMass();
        massSum += particle.getMass();
    }
    return (com/massSum);
}
/// ---------------------------------------------------------
glm::mat3 DeformableObject::calculateR()
{
    // might use eigen as a library
    glm::mat3 S = glm::transpose(m_Apq) * m_Apq; 
    // convert to an eigen matrix
    Eigen::Map<Eigen::Matrix<float, 3, 3, Eigen::RowMajor>> Seig(&S[0][0]);
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix<float, 3, 3, Eigen::RowMajor>> Seigsq(Seig);
    Eigen::Matrix<float, 3,3, Eigen::RowMajor> S_inverse = Seigsq.operatorInverseSqrt();
    //convert the S_inverse to glm 
    glm::mat3 S_inverseGlm(0.0f);
    for(int i=0; i < 3; ++i)
    {
        for(int j=0; j < 3; ++j)
        {
            S_inverseGlm[i][j] = S_inverse(i,j);
        }
    }
    // calculated R - do tests
    return  m_Apq * S_inverseGlm;
}
/// ---------------------------------------------------------
void DeformableObject::setParameters(float _mass)
{
    for(auto& part : m_listOfParticles)
    {
        part.setMass(_mass);
    }
}
/// ---------------------------------------------------------
glm::mat3 DeformableObject::getAqq()
{
    return m_Aqq;
}
/// ---------------------------------------------------------
