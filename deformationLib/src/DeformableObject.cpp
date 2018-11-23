#include "DeformableObject.h"

DeformableObject::DeformableObject(Mesh3D _mesh)
{
    // initialize the list of particles 
    // set the rest positions for the particle system 
    // loop over the vertex positions and create a list of particles 
    for(int i = 0; i < _mesh.getNumberOfVertex(); ++i)
    {
       m_listOfParticles.emplace_back(Particle(_mesh.getVertexPositions()[i], 1.0f)); 
    }

    // calculate original center of mass 
    calculateCOM();
    // calculate the original relative positions 
    calculateQ();
    // calculate symmetric matrix = constant 
    calculateA_qq();
}
/// ---------------------------------------------------------
void DeformableObject::initialize(Mesh3D _mesh)
{
    // initialize the list of particles 
    // set the rest positions for the particle system 
    // loop over the vertex positions and create a list of particles 
    for(int i = 0; i < _mesh.getNumberOfVertex(); ++i)
    {
       m_listOfParticles.emplace_back(Particle(_mesh.getVertexPositions()[i], 1.0f)); 
    }

    // calculate original center of mass 
    calculateCOM();
    // calculate the original relative positions 
    calculateQ();
    // calculate symmetric matrix = constant 
    calculateA_qq();
}
/// ---------------------------------------------------------
void DeformableObject::setListOfParticles(Mesh3D _mesh)
{
    for(int i=0; i < _mesh.getNumberOfVertex(); ++i)
    {
        m_listOfParticles.emplace_back(Particle(_mesh.getVertexPositions()[i],1.0f));
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
glm::vec3 DeformableObject::getCurrentCOM()
{
    return m_currentCenterOfMass; 
}
/// ---------------------------------------------------------
glm::mat3 DeformableObject::getA_qq()
{
    return m_Aqq; 
}
/// ---------------------------------------------------------
glm::mat3 DeformableObject::getA_pq()
{
    return m_Apq;
}
/// ---------------------------------------------------------
void DeformableObject::update(float _timeStep, float _stiffness)
{

    setCurrentPos(_timeStep);
    calculateCOM(false);
    calculateA_pq();
    calculateR();
    calculateGoalPos();

    for(auto& part : m_listOfParticles)
    {
        part.update(_timeStep, _stiffness);
    }
}
/// ---------------------------------------------------------
void DeformableObject::calculateCOM(bool _isCurrent)
{
    float sumMass = 0.0f; 
    glm::vec3 sumPos{0.0f};
    for(auto& part : m_listOfParticles)
    {
        sumMass += part.getMass();
        sumPos += part.getMass() * ((_isCurrent) ? part.getInitPosition() : part.getCurrentPosition());
    }
    ((_isCurrent) ? m_originalCenterOfMass : m_currentCenterOfMass) = sumPos/sumMass; 
}
/// ---------------------------------------------------------
void DeformableObject::calculateQ()
{
    for(auto& part: m_listOfParticles)
    {
        part.setQ(part.getInitPosition() - m_originalCenterOfMass);
    }
}
/// ---------------------------------------------------------
void DeformableObject::calculateP()
{
    for(auto& part : m_listOfParticles)
    {
        part.setP(part.getCurrentPosition() - m_currentCenterOfMass);
    }
}
/// ---------------------------------------------------------
void DeformableObject::calculateA_qq()
{
    // sum of (mass * q_i * (q_i)^T)
    // 3 x 1 * 1 x 3 = 3 x 3  
    // row * column
    // creates a matrix 
    std::vector<Particle> list = m_listOfParticles;
    
    for(auto& part : m_listOfParticles)
    {
        m_Aqq += part.getMass() * glm::outerProduct(part.getQ(), part.getQ());        
    }

    m_Aqq = glm::inverse(m_Aqq);
}
/// ---------------------------------------------------------
void DeformableObject::calculateA_pq()
{
    // sum of (mass * p_i * (q_i)^T)
    // 3 x 1 * 3 * 1 = 3x3 
    // Treats the first parameter c as a column vector and the second parameter r as a row vector and does a linear algebraic matrix multiply c * r.
    for(auto& part : m_listOfParticles)
    {
        m_Apq += part.getMass() * glm::outerProduct(part.getQ(), part.getP());
    }
}
/// ---------------------------------------------------------
void DeformableObject::calculateR()
{
    // might use eigen as a library
    glm::mat3 S = glm::transpose(m_Apq) * m_Apq; 
    // convert to an eigen matrix
    Eigen::Map<Eigen::Matrix<float, 3, 3, Eigen::RowMajor>> Seig(&S[0][0]);
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix<float, 3, 3, Eigen::RowMajor>> Seigsq(Seig);
    Eigen::Matrix<float, 3,3, Eigen::RowMajor> S_inverse = Seigsq.operatorInverseSqrt();
    // convert the S_inverse to glm 
    glm::mat3 S_inverseGlm;
    for(int i=0; i < 3; ++i)
    {
        for(int j=0; j < 3; ++j)
        {
            S_inverseGlm[i][j] = S_inverse(i,j);
        }
    }
    // calculated R - do tests
    m_R = m_Apq * S_inverseGlm;
}
// in other code temp_position = currentPosition;
/// ---------------------------------------------------------
void DeformableObject::calculateGoalPos()
{
   for(auto& part : m_listOfParticles)
   {
       glm::vec3 temp = m_R * (part.getInitPosition() - m_originalCenterOfMass ) + m_currentCenterOfMass;
       part.setGoalPosition(temp);
   }
}
/// ---------------------------------------------------------
void DeformableObject::setCurrentPos(float _timeStep)
{
    for(auto& part : m_listOfParticles)
    {
        glm::vec3 temp_vel = part.getVelocity() + (part.getForce() * _timeStep)/part.getMass();
        glm::vec3 temp_pos = part.getCurrentPosition() + temp_vel;
        part.setCurrentPosition(temp_pos);
    }
}
