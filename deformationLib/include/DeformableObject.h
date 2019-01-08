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
        DeformableObject(std::vector<glm::vec3> _originalPositions, glm::vec3 _vel);
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
        void update(float _timeStep, std::vector<float> _impuls);
        /// ---------------------------------------------------------
        /// @build shape matching function
        /// @param[_in] _timeStep 
        /// ---------------------------------------------------------
        void shapematching(float _timeStep, float _stiffness, float _bounciness);
        /// ---------------------------------------------------------
        /// @build get Mode
        /// ---------------------------------------------------------
        int getMode();
        /// ---------------------------------------------------------
        /// @build set Mode
        /// ---------------------------------------------------------
        void setMode(int _mode);
        /// ---------------------------------------------------------
        /// @build set beta 
        /// ---------------------------------------------------------
        void setBeta(float _beta);
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
        void setParameters(float _mass);
        glm::mat3 getAqq();
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
        // symmetric matrix 
        glm::mat3 m_Aqq = glm::mat3(0.0f); 
        // transformation matrix
        glm::mat3 m_A = glm::mat3(0.0f);
        // quadratic matrix
        Eigen::MatrixXf m_AR = Eigen::MatrixXf::Zero(3,9);
        Eigen::Matrix3f m_ARA;
        Eigen::Matrix3f m_ARQ;
        Eigen::Matrix3f m_ARM;
        glm::mat3 m_ARAgl;
        glm::mat3 m_ARQgl;
        glm::mat3 m_ARMgl;
        Eigen::MatrixXf m_AqqTilde = Eigen::MatrixXf::Zero(9,9);
        Eigen::MatrixXf m_ApqTilde = Eigen::MatrixXf::Zero(3,9);
        Eigen::MatrixXf m_ATilde = Eigen::MatrixXf(3,9);
        Eigen::MatrixXf m_RTilde = Eigen::MatrixXf::Zero(3,9);

        // mode of the deformation (basic. linear, quadratic)
        int m_mode; 
        // mode of the deformation (basic. linear, quadratic)
        float m_beta; 
};

#endif // _DEFORMALEOBJECT_H_
