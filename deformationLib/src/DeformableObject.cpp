#include "DeformableObject.h"
#include <cmath>
#include <math.h>

DeformableObject::DeformableObject(std::vector<glm::vec3> _originalPositions, glm::vec3 _vel)
{
    m_mode = 0;
    m_Aqq = glm::mat3(0.0f);
    m_AqqTilde = Eigen::MatrixXf::Zero(9,9);
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
    if(glm::determinant(m_AqqTilde) == 0)
    {
        m_AqqTilde = 
    }
    m_AqqTilde = m_AqqTilde.inverse();
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
void DeformableObject::update(float _timeStep)
{
    for(auto& part : m_listOfParticles)
    {
        part.updateForces(_timeStep);
        part.updateVelocity(_timeStep);
        part.updatePosition(_timeStep);
    }
}
/// ---------------------------------------------------------
void DeformableObject::shapematching(float _timeStep, float _stiffness)
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
    // calculate matrices
    for(auto& particle : m_listOfParticles)
    {
        // this was wrong all the time
        // outerproduct checks now
        m_Apq += particle.getMass() * glm::outerProduct(particle.getP(), particle.getQ());
        Eigen::Vector3f p({particle.getP().x, particle.getP().y, particle.getP().z});
        m_ApqTilde += particle.getMass() * (p * particle.getQTilde().transpose());
    }
    // calculate R 
    m_R = calculateR();
//   if(glm::determinant(m_R) < 0)
//   {
//       m_R[0][2] = -m_R[0][2];
//   	m_R[1][2] = -m_R[1][2];
//   	m_R[2][2] = -m_R[2][2];
//   }
    // basic mode
    float det = 0;
    Eigen::MatrixXf identity = Eigen::MatrixXf::Identity(9,9);
    Eigen::MatrixXf temp = Eigen::MatrixXf::Zero(3,9);
    Eigen::Vector3f g; 
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
            m_A /= pow(det > 0.1f ? det : 0.1f, 1.0/3.0f); 
            // set goal positions
            for(auto& particle : m_listOfParticles)
            {
                particle.setGoalPosition((m_beta * m_A + (1.0f-m_beta) * m_R) * (particle.getInitPosition() - m_originalCenterOfMass) + centerOfMass);
            }
            break;
        case DeformationMode::Quadratic:

            m_RTilde(0,0) = m_R[0][0];
            m_RTilde(0,1) = m_R[0][1];
            m_RTilde(0,2) = m_R[0][2];
            
            m_RTilde(1,0) = m_R[1][0];
            m_RTilde(1,1) = m_R[1][1];
            m_RTilde(1,2) = m_R[1][2];

            m_RTilde(2,0) = m_R[2][0];
            m_RTilde(2,1) = m_R[2][1];
            m_RTilde(2,2) = m_R[2][2];
            
            m_ATilde = m_ApqTilde * m_AqqTilde;

            identity(0,0) = m_ATilde(0,0);
            identity(0,1) = m_ATilde(0,1);
            identity(0,2) = m_ATilde(0,2);

            identity(1,0) = m_ATilde(1,0);
            identity(1,1) = m_ATilde(1,1);
            identity(1,2) = m_ATilde(1,2);

            identity(2,0) = m_ATilde(2,0);
            identity(2,1) = m_ATilde(2,1);
            identity(2,2) = m_ATilde(2,2);
            
            det = identity.determinant();
            identity /= pow(det>0.1f?det:0.1f,1.0/9.0f);
            m_ATilde(0,0) = identity(0,0);
            m_ATilde(0,1) = identity(0,1);
            m_ATilde(0,2) = identity(0,2);

            m_ATilde(1,0) = identity(1,0);
            m_ATilde(1,1) = identity(1,1);
            m_ATilde(1,2) = identity(1,2);

            m_ATilde(2,0) = identity(2,0);
            m_ATilde(2,1) = identity(2,1);
            m_ATilde(2,2) = identity(2,2);

            temp = (m_beta * m_ATilde + (1.0f - m_beta) * m_RTilde);
            for(auto& particle : m_listOfParticles)
            {
                g = temp * particle.getQTilde();
                particle.setGoalPosition(glm::vec3(g(0), g(1), g(2)) + centerOfMass);
            }
            break;
        default: 
            std::cout<<"Error, there is no mode"<<std::endl;
    }
    // add shape mathcing by translatinjg poositions towards goal positions
    for(auto& particle : m_listOfParticles)
    {
        particle.shapeMatchUpdate(_timeStep, _stiffness);
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
