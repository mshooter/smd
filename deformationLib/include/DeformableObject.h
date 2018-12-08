/// @file DeformableObject.h 
#ifndef _DEFORMALEOBJECT_H_
#define _DEFORMALEOBJECT_H_

#include <vector>
#include <Eigen/Dense>
#include "Particle.h"
/// \author Moira Shooter
/// \version 1.0
/// \date 17 November 2018

/// \Revision history: \n

/// \class DeformableObject
/// \brief class that represent a mesh 
/// \todo the particle system with the update function 

class DeformableObject
{
    public:
        /// ---------------------------------------------------------
        /// @build default constructor
        /// ---------------------------------------------------------
        DeformableObject() = default; 
        /// ---------------------------------------------------------
        /// @build constructor that sets the particle system initial
        /// state
        /// ---------------------------------------------------------
        DeformableObject(std::vector<glm::vec3> _originalPositions);
        /// ---------------------------------------------------------
        /// @build copy constructor 
        /// ---------------------------------------------------------
        DeformableObject(const DeformableObject&) = default;
        /// ---------------------------------------------------------
        /// @build default copy assignment operator
        /// ---------------------------------------------------------
        DeformableObject& operator=(const DeformableObject&) = default;
        /// ---------------------------------------------------------
        /// @build default move constructor
        /// ---------------------------------------------------------
        DeformableObject(DeformableObject&&) = default; 
        /// ---------------------------------------------------------
        /// @build default move assignment operator
        /// ---------------------------------------------------------
        DeformableObject& operator=(DeformableObject&&) = default; 
        /// ---------------------------------------------------------
        /// @build default deconstructor 
        /// ---------------------------------------------------------
        ~DeformableObject() = default;
        /// ---------------------------------------------------------
        /// @build get the particle list 
        /// ---------------------------------------------------------
        std::vector<Particle> getListOfParticles();
        /// ---------------------------------------------------------
        /// @build get original center of mass
        /// ---------------------------------------------------------
        glm::vec3 getOriginalCOM();
        /// ---------------------------------------------------------
        /// @build get current center of mass
        /// ---------------------------------------------------------
        glm::vec3 getCurrentCOM();
        /// ---------------------------------------------------------
        /// @build get A_pq
        /// ---------------------------------------------------------
        glm::mat3 getA_pq();
        /// ---------------------------------------------------------
        /// @build update function
        /// @param[_in] _timeStep 
        /// ---------------------------------------------------------
        void update(float _timeStep);
        /// ---------------------------------------------------------
        /// @build shape matching function
        /// @param[_in] _timeStep 
        /// ---------------------------------------------------------
        void shapematching(float _timeStep);
        /// ---------------------------------------------------------
        /// @build calculate center of mass of object
        /// @return the center of mass
        /// ---------------------------------------------------------
        glm::vec3 computeCOM();
        /// ---------------------------------------------------------
        /// @build calculate the orginal relative positions for each particle
        /// ---------------------------------------------------------
        void calculateQ(); 
        /// ---------------------------------------------------------
        /// @build calculate the current relative positions for each particle
        /// ---------------------------------------------------------
        void calculateP();
        /// ---------------------------------------------------------
        /// @build calculate the A_pq (rotation) matrix 
        /// ---------------------------------------------------------
        void calculateA_pq();
        /// ---------------------------------------------------------
        /// @build calculate the rotational matrix based on 
        /// linear decomposition 
        /// ---------------------------------------------------------
        void calculateR();
        /// ---------------------------------------------------------
        /// @build calculate goal positions for each particle (set) 
        /// ---------------------------------------------------------
        void calculateGoalPos(); 
    private:
        /// ---------------------------------------------------------
        /// @build container that holds the particles
        /// ---------------------------------------------------------
        std::vector<Particle> m_listOfParticles;
        /// ---------------------------------------------------------
        /// @build original center of mass
        /// ---------------------------------------------------------
        glm::vec3 m_originalCenterOfMass; 
        /// ---------------------------------------------------------
        /// @build current center of mass
        /// ---------------------------------------------------------
        glm::vec3 m_currentCenterOfMass; 
        // ---------------------------------------------------------
        /// @build A_pq (rotational matrix)
        /// ---------------------------------------------------------
        glm::mat3 m_Apq; 
        /// ---------------------------------------------------------
        /// @build Rotational matrix  
        /// ---------------------------------------------------------
        glm::mat3 m_R;
};

#endif // _DEFORMALEOBJECT_H_
