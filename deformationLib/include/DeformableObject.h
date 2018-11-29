/// @file DeformableObject.h 
#ifndef _DEFORMALEOBJECT_H_
#define _DEFORMALEOBJECT_H_

#include <vector>
#include <Eigen/Dense>
#include "Mesh3D.h"
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
        DeformableObject(Mesh3D _mesh);  
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
        /// @build initialize 
        /// ---------------------------------------------------------
        void initialize(Mesh3D _mesh);
        /// ---------------------------------------------------------
        /// @build set the particle list 
        /// ---------------------------------------------------------
        void setListOfParticles(glm::vec3 _vert);
        /// ---------------------------------------------------------
        /// @build set the particle list 
        /// ---------------------------------------------------------
        void setListOfParticles(Mesh3D _mesh);
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
        /// @build get A_qq
        /// ---------------------------------------------------------
        glm::mat3 getA_qq();
        /// ---------------------------------------------------------
        /// @build get A_pq
        /// ---------------------------------------------------------
        glm::mat3 getA_pq();
        /// ---------------------------------------------------------
        /// @build update function
        /// @param[_in] _timeStep 
        /// ---------------------------------------------------------
        void update(float _timeStep);
        void shapematching(float _timeStep);
        /// ---------------------------------------------------------
        /// @build calculate center of mass of object
        /// @param[_in] _isCurrent : determines if you calculate the current or not  
        /// ---------------------------------------------------------
        void calculateCOM(bool _isCurrent=true);
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
        /// ---------------------------------------------------------
        /// @build calculate goal positions for each particle (set) 
        /// ---------------------------------------------------------
        void calculateGoalPos(); 
        /// ---------------------------------------------------------
        /// @build set current positions for each particle
        /// ---------------------------------------------------------
        void setCurrentPos(float _timeStep);
        void setStiffness(float _stiffness);
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
        glm::mat3 m_Aqq{0.0f}; 
        // ---------------------------------------------------------
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
        float m_stiffness; 
};

#endif // _DEFORMALEOBJECT_H_
