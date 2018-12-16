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
enum DeformationMode {Basic=0, Linear=1, Quadratic=2};

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
        DeformableObject(std::vector<glm::vec3> _originalPositions, int _mode, float _linearParam);
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
        /// @build update function
        /// @param[_in] _timeStep 
        /// ---------------------------------------------------------
        void update(float _timeStep);
        /// ---------------------------------------------------------
        /// @build shape matching function
        /// @param[_in] _timeStep 
        /// ---------------------------------------------------------
        void shapematching(float _timeStep, float _stiffness);
        /// ---------------------------------------------------------
        /// @build calculate center of mass of object
        /// @return the center of mass
        /// ---------------------------------------------------------
        glm::vec3 computeCOM();
        /// ---------------------------------------------------------
        /// @build calculate the rotational matrix based on 
        /// linear decomposition 
        /// ---------------------------------------------------------
        glm::mat3 calculateR();
    private:
        /// ---------------------------------------------------------
        /// @build container that holds the particles
        /// ---------------------------------------------------------
        std::vector<Particle> m_listOfParticles;
        /// ---------------------------------------------------------
        /// @build original center of mass
        /// ---------------------------------------------------------
        glm::vec3 m_originalCenterOfMass; 
        // ---------------------------------------------------------
        /// @build A_pq (rotational matrix)
        /// ---------------------------------------------------------
        glm::mat3 m_Apq; 
        /// ---------------------------------------------------------
        /// @build Rotational matrix  
        /// ---------------------------------------------------------
        glm::mat3 m_R;
        // symmetric mattric 
        glm::mat3 m_Aqq; 
        // transformation matrix
        glm::mat3 m_A;
        // mode of the deformation (basic. linear, quadratic)
        int m_mode; 
        // beta in the paper
        float m_linearParam;
};

#endif // _DEFORMALEOBJECT_H_
