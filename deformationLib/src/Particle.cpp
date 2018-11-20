#include "Particle.h"

float Particle::getMass()
{
	return m_mass;
}
//----------------------------------------------------------------------
float Particle::getRadius()
{
    return m_radius; 
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
glm::vec3 Particle::getAcceleration()
{
    return m_acceleration;
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
void Particle::setMass(float _mass)
{
	m_mass = _mass;
}
//----------------------------------------------------------------------
void Particle::setRadius(float _radius)
{
    m_radius = _radius; 
}
//---------------------------------------------------------------------
void Particle::setInitPosition(glm::vec3 _initPosition)
{
	m_initPosition = _initPosition;
}
//----------------------------------------------------------------------
void Particle::setCurrentPosition(glm::vec3 _currentPosition)
{
	m_currentPosition = _currentPosition;
}
//---------------------------------------------------------------------
void Particle::setGoalPosition(glm::vec3 _goalPosition)
{
	m_goalPosition = _goalPosition;
}
//---------------------------------------------------------------------
void Particle::setVelocity(glm::vec3 _velocity)
{
	m_velocity = _velocity;
}
//----------------------------------------------------------------------
void Particle::setAcceleration(glm::vec3 _acceleration)
{
    m_acceleration = _acceleration;
}
//---------------------------------------------------------------------
void Particle::setQ(glm::vec3 _q)
{
    m_q = _q;
}
//---------------------------------------------------------------------
void Particle::setP(glm::vec3 _p)
{
    m_p = _p; 
}
//---------------------------------------------------------------------
void Particle::reset()
{
    m_initPosition = glm::vec3{0.0f};
    m_mass = 1.0f; 
    m_radius = 1.0f;
    m_currentPosition = glm::vec3{0.0f};
    m_goalPosition = glm::vec3{0.0f};
    m_velocity = glm::vec3{0.0f};
}
//---------------------------------------------------------------------
void Particle::update(float _timeStep)
{
    // gravity or external forces can be added to velocity 
    // if velocity and acceleration is the same for each particle it will move 
    // as a solid object 
    // gravity = _timeStep * f_ext / m_i <- gravity acts upon every particle 
    m_velocity += m_acceleration * _timeStep; 
    m_currentPosition += m_velocity * _timeStep;     
}
