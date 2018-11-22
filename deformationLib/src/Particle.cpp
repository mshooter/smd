#include "Particle.h"

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
	m_initPosition = std:;move(_initPosition);
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
void Particle::reset()
{
    m_initPosition = glm::vec3{0.0f};
    m_mass = 1.0f; 
    m_currentPosition = glm::vec3{0.0f};
    m_goalPosition = glm::vec3{0.0f};
    m_velocity = glm::vec3{0.0f};
}
//---------------------------------------------------------------------
void Particle::update(float _timeStep, float _stiffness)
{
    // basic algorithm
    m_velocity += _stiffness *( m_goalPosition - m_currentPosition ) / _timeStep + (_timeStep / m_mass) * m_force; 
    m_currentPosition += _timeStep * m_velocity;
}
