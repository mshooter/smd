/// @file Mesh3D.h 
#ifndef _MESH3D_H_
#define _MESH3D_H_

#include "glm/glm.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

/// \author Moira Shooter
/// \version 1.0
/// \date 17 November 2018

/// \Revision history: \n

/// \class Mesh3D
/// \brief class that represent a mesh 
/// \todo 

class Mesh3D
{
    public:
        /// ---------------------------------------------------------
        /// @build default constructor 
        /// ---------------------------------------------------------
        Mesh3D() = default;
        /// ---------------------------------------------------------
        /// @build constructor that loads the model already 
        /// @param[_in] _filename : the path to the file 
        /// ---------------------------------------------------------
        Mesh3D(const char* _filename);
        /// ---------------------------------------------------------
        /// @build copy constructor 
        /// ---------------------------------------------------------
        Mesh3D(const Mesh3D&) = default;
        /// ---------------------------------------------------------
        /// @build default copy assignment operator
        /// ---------------------------------------------------------
        Mesh3D& operator=(const Mesh3D&) = default;
        /// ---------------------------------------------------------
        /// @build default move constructor
        /// ---------------------------------------------------------
        Mesh3D(Mesh3D&&) = default; 
        /// ---------------------------------------------------------
        /// @build default move assignment operator
        /// ---------------------------------------------------------
        Mesh3D& operator=(Mesh3D&&) = default; 
        /// ---------------------------------------------------------
        /// @ build default deconstructor 
        /// ---------------------------------------------------------
        ~Mesh3D() = default;
        /// ---------------------------------------------------------
        /// @build load an object method 
        /// @param[_in] : const char* filename / file path 
        /// ---------------------------------------------------------
        void loadObject(const char* _filename);
        /// ---------------------------------------------------------
        /// @build get list of vertices with their positions 
        /// ---------------------------------------------------------
        std::vector<glm::vec3> getVertexPositions();
        /// ---------------------------------------------------------
        /// @build set number of vertices 
        /// ---------------------------------------------------------
        void setNumberOfVertex(); 
        /// ---------------------------------------------------------
        /// @build get number of vertices 
        /// ---------------------------------------------------------
        int getNumberOfVertex();
    
    private:
        /// ---------------------------------------------------------
        /// @build list of amount of vertices
        /// ---------------------------------------------------------
        int m_numberOfVertices;
        /// ---------------------------------------------------------
        /// @build list of positions of vertices 
        /// ---------------------------------------------------------
        std::vector<glm::vec3> m_vertexPositions; 
        
}; // end class

#endif // _MESH3D_H_
