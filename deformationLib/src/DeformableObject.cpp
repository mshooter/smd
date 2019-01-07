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
    if(m_AqqTilde.determinant() ==0)
    {
        m_AqqTilde = Eigen::MatrixXf::Identity(9,9);
    }
    else
    {
        m_AqqTilde = m_AqqTilde.inverse();
    }
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
    if(glm::determinant(m_R) < 0)
    {
        m_R[0][2] = -m_R[0][2];
		m_R[1][2] = -m_R[1][2];
		m_R[2][2] = -m_R[2][2];
    }
    // basic mode
    float det = 0;
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
            // ATilde
            m_ATilde = m_ApqTilde * m_AqqTilde;
            m_RTilde(0,0) = m_R[0][0];
            m_RTilde(0,1) = m_R[0][1];
            m_RTilde(0,2) = m_R[0][2];
            
            m_RTilde(1,0) = m_R[1][0];
            m_RTilde(1,1) = m_R[1][1];
            m_RTilde(1,2) = m_R[1][2];

            m_RTilde(2,0) = m_R[2][0];
            m_RTilde(2,1) = m_R[2][1];
            m_RTilde(2,2) = m_R[2][2];

            m_AR = (m_beta * m_ATilde + (1.0f-m_beta) * m_RTilde);
           
            m_ARA(0,0) = m_AR(0,0);
            m_ARA(0,1) = m_AR(0,1);
            m_ARA(0,2) = m_AR(0,2);

            m_ARA(1,0) = m_AR(1,0);
            m_ARA(1,1) = m_AR(1,1);
            m_ARA(1,2) = m_AR(1,2);

            m_ARA(2,0) = m_AR(2,0);
            m_ARA(2,1) = m_AR(2,1);
            m_ARA(2,2) = m_AR(2,2);
            
            m_ARQ(0,0) = m_AR(0,0+3);
            m_ARQ(0,1) = m_AR(0,1+3);
            m_ARQ(0,2) = m_AR(0,2+3);

            m_ARQ(1,0) = m_AR(1,0+3);
            m_ARQ(1,1) = m_AR(1,1+3);
            m_ARQ(1,2) = m_AR(1,2+3);

            m_ARQ(2,0) = m_AR(2,0+3);
            m_ARQ(2,1) = m_AR(2,1+3);
            m_ARQ(2,2) = m_AR(2,2+3);

            m_ARM(0,0) = m_AR(0,0+6);
            m_ARM(0,1) = m_AR(0,1+6);
            m_ARM(0,2) = m_AR(0,2+6);

            m_ARM(1,0) = m_AR(1,0+6);
            m_ARM(1,1) = m_AR(1,1+6);
            m_ARM(1,2) = m_AR(1,2+6);

            m_ARM(2,0) = m_AR(2,0+6);
            m_ARM(2,1) = m_AR(2,1+6);
            m_ARM(2,2) = m_AR(2,2+6);
           
            det = m_ARA.determinant();
            m_ARA /= pow(det> 0.1f ? det : 0.1f, 1.0f/3.0f);

            for(int i=0; i<3; ++i)
            {
                for(int j=0; j<3; ++j)
                {
                    m_ARAgl[i][j] = m_ARA(i,j);
                    m_ARQgl[i][j] = m_ARQ(j,i);
                    m_ARMgl[i][j] = m_ARM(i,j);
                }
            }
            for(auto& particle : m_listOfParticles)
            {
                auto x = particle.getInitPosition() - m_originalCenterOfMass;
                glm::vec3 linear = m_ARAgl * (x);
                glm::vec3 quadratic = m_ARQgl * glm::vec3(x.x * x.x, x.y*x.y, x.z*x.z);
                glm::vec3 mixed = m_ARMgl * glm::vec3(x.x * x.y, x.y*x.z, x.z*x.x);
                
                particle.setGoalPosition((linear + quadratic + mixed) + centerOfMass);
                
            }
          //  // RTilde
          //for(int i=0; i < 3; ++i)
          //{
          //    for(int j=0; j < 3; ++j)
          //    {
          //        m_RTilde(i,j) = m_R[i][j];
          //    }
          //}
            // scale ATilde 
          // for(int i=0; i<3; ++i)
          // {
          //     for(int j=0; j<9; ++j)
          //     {
          //         identity(i,j) = m_ATilde(i,j);
          //     }
          // }
            // det 
          //  det = identity.determinant();
          //  m_ATilde /= pow(det > 0.1f ? det : 0.1f, 1.0/9.0f);
            // formula
          //  for(auto& particle : m_listOfParticles)
        //{
         //       g = (m_beta * m_ATilde + (1.0f - m_beta) * m_RTilde) * particle.getQTilde();
         //       particle.setGoalPosition(glm::vec3(g(0), g(1), g(2)) + centerOfMass);
           //}
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
