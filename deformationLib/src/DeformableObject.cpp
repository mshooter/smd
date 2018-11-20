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
void DeformableObject::update(float _timeStep)
{
    // update the particle step
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
    glm::mat3 S_inverse = glm::sqrt(S);
    m_R = m_Apq * S_inverse;
}
