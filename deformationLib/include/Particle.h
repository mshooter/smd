/// @file Particle.h
#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "glm/glm.hpp"
#include <iostream>
#include <vector>
#include <Eigen/Dense>
/// \author Moira Shooter
/// \version 1.0
/// \date 17 November 2018

/// \Revision history: \n

/// \class Particle
/// \brief class that represent a particle, that has a rest position, mass  
/// \todo 

class Particle
{
    public:
        /// ---------------------------------------------------------
        /// @uild default constructor 
        /// ---------------------------------------------------------
        Particle() = default;
        /// ---------------------------------------------------------
        /// @build constructor
        /// @param[_in] _initPos : initial position of the particle
        /// ---------------------------------------------------------
        Particle(glm::vec3 _originalPositions, glm::vec3 _vel);
        /// ---------------------------------------------------------
        /// @default copy constructor 
        /// ---------------------------------------------------------
        Particle(const Particle&) = default;
        /// ---------------------------------------------------------
        /// @build default copy assignment operator
        /// ---------------------------------------------------------
        Particle& operator=(const Particle&) = default;
        /// ---------------------------------------------------------
        /// @build  default move constructor
        /// ---------------------------------------------------------
        Particle(Particle&&) = default; 
        /// ---------------------------------------------------------
        /// @build default move assignment opeartor 
        /// ---------------------------------------------------------
        Particle& operator=(Particle&&) = default;
        /// ---------------------------------------------------------
        /// @default  deconstrutor 
        /// ---------------------------------------------------------
        ~Particle() = default;
        /// ---------------------------------------------------------
        /// @build get mass of the particle
        /// ---------------------------------------------------------
        float getMass();
        /// ---------------------------------------------------------
        /// @build get the initial position of the particle
        /// ---------------------------------------------------------
        glm::vec3 getInitPosition();
        /// ---------------------------------------------------------
        /// @build get the current position of the particle 
        /// ---------------------------------------------------------
        glm::vec3 getCurrentPosition();
        /// ---------------------------------------------------------
        /// @build get the goal position of tha particle
        /// ---------------------------------------------------------
        glm::vec3 getGoalPosition();
        /// ---------------------------------------------------------
        /// @build get the velocity of the particle 
        /// ---------------------------------------------------------
        glm::vec3 getVelocity();
        /// ---------------------------------------------------------
        /// @build get the original relative pos of the particle 
        /// ---------------------------------------------------------
        glm::vec3 getQ();
        /// ---------------------------------------------------------
        /// @build get the current relative pos  of the particle 
        /// ---------------------------------------------------------
        glm::vec3 getP();
        /// ---------------------------------------------------------
        /// @build get external force  
        /// ---------------------------------------------------------
        glm::vec3 getForce();
        /// ---------------------------------------------------------
        /// @build set the mass of the particle 
        /// @param[_in] _mass : the mass you want to set the particle
        /// ---------------------------------------------------------
        void setMass(float _mass);
        /// ---------------------------------------------------------
        /// @build set the intial position of the particle
        /// @param[_in] _initPosition : the initial position 
        /// ---------------------------------------------------------
        void setInitPosition(glm::vec3 _initPosition);
        /// ---------------------------------------------------------
        /// @build set the current position 
        /// @param[_in] _currentPosition : the current position 
        /// ---------------------------------------------------------
        void setCurrentPosition(glm::vec3 _currentPosition);
        /// ---------------------------------------------------------
        /// @build set goal position of the particle 
        /// @param[_in] _goalPosition : set the goal position
        /// ---------------------------------------------------------
        void setGoalPosition(glm::vec3 _goalPosition);
        /// ---------------------------------------------------------
        /// @build set the velocity of the particle 
        /// @param[_in] _velocity : the velocity of the particle 
        /// ---------------------------------------------------------
        void setVelocity(glm::vec3 _velocity);
        /// ---------------------------------------------------------
        /// @build set original relative coordinate, q
        /// ---------------------------------------------------------
        void setQ(glm::vec3 _q);
        /// ---------------------------------------------------------
        /// @build set current relative coordinate, p 
        /// ---------------------------------------------------------
        void setP(glm::vec3 _p);
        /// ---------------------------------------------------------
        /// @build set force  
        /// ---------------------------------------------------------
        void setForce(glm::vec3 _force);
        /// ---------------------------------------------------------
        /// @build update force method for individial method
        /// @param[_in] _timeStep : the time for a 'frame'
        /// ---------------------------------------------------------
        void updateForces(float _timeStep, std::vector<float> _impuls);       
        /// ---------------------------------------------------------
        /// @build update velocity method for individial method
        /// @param[_in] _timeStep : the time for a 'frame'
        /// ---------------------------------------------------------
        void updateVelocity(float _timeStep);       
        /// ---------------------------------------------------------
        /// @build update position method for individial method
        /// @param[_in] _timeStep : the time for a 'frame'
        /// ---------------------------------------------------------
        void updatePosition(float _timeStep);       
        /// ---------------------------------------------------------
        /// @build update method for individial method
        /// @param[_in] _timeStep : the time for a 'frame'
        /// @param[_in] _stiffness : stiffness of the deformable object
        /// ---------------------------------------------------------
        void shapeMatchUpdate(float _timeStep, float _stiffness, float _bounciness);
        void setQTilde(Eigen::VectorXf _qtilde);
        Eigen::VectorXf getQTilde();
    private:
        /// ---------------------------------------------------------
        /// @build initial position of the particle
        /// ---------------------------------------------------------
        glm::vec3 m_initPosition; 
        /// ---------------------------------------------------------
        /// @build the value of gravity 
        /// ---------------------------------------------------------
        glm::vec3 m_gravity; 
        /// ---------------------------------------------------------
        /// @build the mass of the particle 
        /// ---------------------------------------------------------
        float m_mass;
        /// ---------------------------------------------------------
        /// @build the current position of the particle 
        /// ---------------------------------------------------------
        glm::vec3 m_currentPosition; 
        /// ---------------------------------------------------------
        /// @build the goal position of the particle 
        /// ---------------------------------------------------------
        glm::vec3 m_goalPosition;
        /// ---------------------------------------------------------
        /// @build  velocity of the particle
        /// ---------------------------------------------------------
        glm::vec3 m_velocity; 
        /// ---------------------------------------------------------
        /// @build  inital relative coordinate, q
        /// ---------------------------------------------------------
        glm::vec3 m_q; 
        /// ---------------------------------------------------------
        /// @build  current relative coordinate, p 
        /// ---------------------------------------------------------
        glm::vec3 m_p;
        /// ---------------------------------------------------------
        /// @build  force of the particle   
        /// ---------------------------------------------------------
        glm::vec3 m_force;
        Eigen::VectorXf m_qTilde=Eigen::VectorXf(9);
};
#endif // _PARTICLE_H_
