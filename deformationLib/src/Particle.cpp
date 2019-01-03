#include "Particle.h"

Particle::Particle(glm::vec3 _originalPositions)
{   
    m_mass = 1.0f;
    m_initPosition = _originalPositions;
    m_currentPosition = _originalPositions; 
    m_goalPosition = _originalPositions; 
    m_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    m_force = glm::vec3(0.0f, 0.0f, 0.0f);
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
void Particle::updateForces(float _timeStep)
{
    // update force
    m_force = glm::vec3(0.0f, -9.81f, 0.0f) * m_mass;
    // add collision
    if(m_currentPosition.y <= 0 )
    {
        m_velocity *= - 0.5f;
        m_currentPosition.y = 0.1f; 
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
        m_currentPosition.y = 0.1f;
    }
}
//---------------------------------------------------------------------
void Particle::shapeMatchUpdate(float _timeStep, float _stiffness)
{
    // set velocity elasticity
    m_velocity += _stiffness * (m_goalPosition - m_currentPosition) / _timeStep; 
    m_currentPosition += _stiffness * (m_goalPosition - m_currentPosition);
}
