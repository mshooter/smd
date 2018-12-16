#include "DeformableObject.h"
#include <cmath>
/// ---------------------------------------------------------
DeformableObject::DeformableObject(std::vector<glm::vec3> _originalPositions, int _mode, float _linearParam)
{
    m_mode = _mode;
    m_linearParam = _linearParam;
    // reset all attributes
    for(unsigned int i = 0 ; i < _originalPositions.size(); ++i)
    {
        m_listOfParticles.emplace_back(Particle(_originalPositions[i]));
    }
    // original center of mass
    m_originalCenterOfMass = computeCOM();
    for(auto& particle : m_listOfParticles)
    {
        m_Aqq += particle.getMass() * glm::outerProduct(particle.getQ(), particle.getQ());
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
        part.update(_timeStep);
    }
}
/// ---------------------------------------------------------
void DeformableObject::shapematching(float _timeStep, float _stiffness)
{
    glm::vec3 centerOfMass; 
    centerOfMass = computeCOM();
    for(auto& particle : m_listOfParticles)
    {
        particle.setQ(particle.getCurrentPosition() - centerOfMass);
        particle.setP(particle.getInitPosition() - m_originalCenterOfMass);
        
    }
    // calculate matrices
    for(auto& particle : m_listOfParticles)
    {
        m_Apq += particle.getMass() * glm::outerProduct(particle.getQ(), particle.getP());
    }
    // calculate R 
    m_R = calculateR();
    // if rotaton has reflection, reflect back
//  if(glm::determinant(m_R) < 0)
//  {
//      m_R[0][2] = -m_R[0][2];
//      m_R[1][2] = -m_R[1][2];
//      m_R[2][2] = -m_R[1][2];
//  }
    // compute target positions for rigid transform 
    for(auto& particle : m_listOfParticles)
    {
        // don't forget te rotational matrix
        // basic mode
        if(m_mode == DeformationMode::Basic)
            particle.setGoalPosition(m_R * (particle.getInitPosition() - m_originalCenterOfMass) + centerOfMass);
        if(m_mode == DeformationMode::Linear)
            // linear mode
            m_A = m_Apq * glm::inverse(m_Aqq);
            float detA = glm::determinant(m_A);
            float cbrt = std::cbrt(detA);
            cbrt = (detA < 0) ? -cbrt : cbrt; 
            m_A /= cbrt;
            // calculate A matrix 
            particle.setGoalPosition((m_linearParam*m_A + (1-m_linearParam)*m_R)* (particle.getInitPosition() - m_originalCenterOfMass) + centerOfMass);
        if(m_mode == DeformationMode::Quadratic)
            particle.setGoalPosition(centerOfMass);
    }
    // add shape mathcing by translatinjg poositions towards goal positions
    for(auto& particle : m_listOfParticles)
    {
        particle.shapeMatchUpdate(_timeStep, _stiffness);
    }
}
/// ---------------------------------------------------------
glm::vec3 DeformableObject::computeCOM()
{
    glm::vec3 com{0.0f};
    float massSum = 0.0f;
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
    return m_Apq * S_inverseGlm;
}
