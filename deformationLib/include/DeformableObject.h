/// @file DeformableObject.h 
#ifndef _DEFORMALEOBJECT_H_
#define _DEFORMALEOBJECT_H_

#include <vector>
#include "Mesh3D.h"
#include "Particle.h"
/// \author Moira Shooter
/// \version 1.0
/// \date 17 November 2018

/// \Revision history: \n

/// \class DeformableObject
/// \brief class that represent a mesh 
/// \todo the particle system with the update function 
/// \todo 1) center of mass 

class DeformableObject
{
    public:
        /// ---------------------------------------------------------
        /// @build constructor that sets the particle system initial
        /// state
        /// ---------------------------------------------------------
        DeformableObject(Mesh3D _mesh);  
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
        /// @build update function
        /// @param[_in] _timeStep 
        /// ---------------------------------------------------------
        void update(float _timeStep);
        /// ---------------------------------------------------------
        /// @build calculate center of mass of object
        /// @param[_in] _isCurrent : determines if you calculate the current or not  
        /// ---------------------------------------------------------
        void calculateCOM(bool _isCurrent=true);
        /// ---------------------------------------------------------
        /// @build calculate the orginal relative positions 
        /// ---------------------------------------------------------
        void calculateQ(); 
        /// ---------------------------------------------------------
        /// @build calculate the current relative positions 
        /// ---------------------------------------------------------
        void calculateP();
        /// ---------------------------------------------------------
        /// @build calculate the symmetric matrix (scaling, no rotation) 
        /// ---------------------------------------------------------
        void calculateA_qq();
        /// ---------------------------------------------------------
        /// @build calculate the A_pq (rotation) matrix 
        /// ---------------------------------------------------------
        void calculateA_pq();
        /// ---------------------------------------------------------
        /// @build calculate the rotational matrix based on 
        /// linear decomposition 
        /// ---------------------------------------------------------
        void calculateR();
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
        /// ---------------------------------------------------------
        /// @build symmetric matrix
        /// ---------------------------------------------------------
        glm::mat3 m_Aqq; 
        /// ---------------------------------------------------------
        /// @build A_pq (rotational matrix)
        /// ---------------------------------------------------------
        glm::mat3 m_Apq; 
        /// ---------------------------------------------------------
        /// @build A linear transformation matrix
        /// the matrix is used for Linear deformation 
        /// ---------------------------------------------------------
        glm::mat3 m_A;  
        /// ---------------------------------------------------------
        /// @build Rotational matrix  
        /// ---------------------------------------------------------
        glm::mat3 m_R;
        /// ----
        // remove file
};

#endif // _DEFORMALEOBJECT_H_
