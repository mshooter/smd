#include "Particle.h"

Particle::Particle(glm::vec3 _originalPositions, glm::vec3 _vel)
{   
    m_initPosition = _originalPositions;
    m_currentPosition = _originalPositions; 
    m_goalPosition = _originalPositions; 
    m_velocity = _vel;
    m_force = glm::vec3(0.0f, 0.0f, 0.0f);
    m_mass = 1.0f;
}
//----------------------------------------------------------------------
float Particle::getMass()
{
	return m_mass;
}
//----------------------------------------------------------------------
glm::vec3 Particle::getInitPosition()
{
	return m_initPosition;
}
//----------------------------------------------------------------------
glm::vec3 Particle::getCurrentPosition()
{
	return m_currentPosition; 
}
//----------------------------------------------------------------------
glm::vec3 Particle::getGoalPosition()
{	
	return m_goalPosition;
}
//----------------------------------------------------------------------
glm::vec3 Particle::getVelocity()
{
	return m_velocity;
}
//----------------------------------------------------------------------
glm::vec3 Particle::getQ()
{
    return m_q;
}
//----------------------------------------------------------------------
glm::vec3 Particle::getP()
{
    return m_p;
}
//----------------------------------------------------------------------
glm::vec3 Particle::getForce()
{
    return m_force;
}
//----------------------------------------------------------------------
void Particle::setMass(float _mass)
{
	m_mass = std::move(_mass);
}
//---------------------------------------------------------------------
void Particle::setInitPosition(glm::vec3 _initPosition)
{
	m_initPosition = std::move(_initPosition);
}
//----------------------------------------------------------------------
void Particle::setCurrentPosition(glm::vec3 _currentPosition)
{
	m_currentPosition = std::move(_currentPosition);
}
//---------------------------------------------------------------------
void Particle::setGoalPosition(glm::vec3 _goalPosition)
{
	m_goalPosition = std::move(_goalPosition);
}
//---------------------------------------------------------------------
void Particle::setVelocity(glm::vec3 _velocity)
{
	m_velocity = std::move(_velocity);
}
//---------------------------------------------------------------------
void Particle::setQ(glm::vec3 _q)
{
    m_q = std::move(_q);
}
//---------------------------------------------------------------------
void Particle::setP(glm::vec3 _p)
{
    m_p = std::move(_p); 
}
//---------------------------------------------------------------------
void Particle::setForce(glm::vec3 _force)
{
    m_force = std::move(_force);
}
//---------------------------------------------------------------------
void Particle::setGravity(glm::vec3 _gravity)
{
    m_gravity = std::move(_gravity);
}
//---------------------------------------------------------------------
void Particle::updateForces(float _timeStep)
{
    // update force total force
    // gravity 
    m_force = glm::vec3(0.0f, -9.8f, 0.0f) * m_mass;
    // add collision
    if(m_currentPosition.y <= 0)
    {
//        m_velocity *= - 0.5f;
        glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 deltaV = m_velocity - glm::vec3(0.0f, 0.0f, 0.0f); 
        glm::vec3 composant = normal * glm::dot(normal, deltaV); 
        glm::vec3 collisionImp = -(0.2f+1.0f) * normal * glm::dot(normal, deltaV) * m_mass;
        glm::vec3 frictionImp = -0.2f * (deltaV - composant) * m_mass;
        m_force += (collisionImp + frictionImp) / _timeStep;
        // add other forces together
        m_currentPosition.y = 0.01f; 
    }

}
//---------------------------------------------------------------------
void Particle::updateVelocity(float _timeStep)
{
    // update velocity 
    m_velocity += m_force / m_mass * _timeStep;
    m_force = glm::vec3(0,0,0);
}
//---------------------------------------------------------------------
void Particle::updatePosition(float _timeStep)
{
    // update position 
    m_currentPosition += _timeStep * m_velocity;
    // update position 
    if(m_currentPosition.y <= 0)
    {
        m_currentPosition.y = 0.01f;
    }
}
//---------------------------------------------------------------------
void Particle::shapeMatchUpdate(float _timeStep, float _stiffness)
{
    // set velocity elasticity
    m_velocity +=  0.5f * _stiffness * (m_goalPosition - m_currentPosition) / _timeStep; 
    m_currentPosition += _stiffness * (m_goalPosition - m_currentPosition);
}
//---------------------------------------------------------------------
void Particle::setQtilde(arma::mat _qtilde)
{
    m_qtilde = std::move(_qtilde);
}
//---------------------------------------------------------------------
arma::mat Particle::getQtilde()
{
    return m_qtilde;
}
