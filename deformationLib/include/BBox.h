/// @file BBox.h
#ifndef _BBOX_H_
#define _BBOX_H_

#include "glm/glm.hpp"

class BBox
{
    public:
        /// ---------------------------------------------------------
        /// @uild default constructor 
        /// ---------------------------------------------------------
        BBox() = default;
        /// ---------------------------------------------------------
        /// @build constructor
        /// @param[_in] _Positions : positions of my mesh
        /// ---------------------------------------------------------
        BBox(glm::vec3 _Positions);
        /// ---------------------------------------------------------
        /// @default copy constructor 
        /// ---------------------------------------------------------
        BBox(const BBox&) = default;
        /// ---------------------------------------------------------
        /// @build default copy assignment operator
        /// ---------------------------------------------------------
        BBox& operator=(const BBox&) = default;
        /// ---------------------------------------------------------
        /// @build  default move constructor
        /// ---------------------------------------------------------
        BBox(BBox&&) = default; 
        /// ---------------------------------------------------------
        /// @build default move assignment opeartor 
        /// ---------------------------------------------------------
        BBox& operator=(BBox&&) = default;
        /// ---------------------------------------------------------
        /// @default  deconstrutor 
        /// ---------------------------------------------------------
        ~BBox() = default;

        glm::vec3 getMin();
        glm::vec3 getMax();
        glm::vec3 getCenter();
        glm::vec3 getSize();
    private:
        glm::vec3 m_min{0.0f,0.0f,0.0f}; 
        glm::vec3 m_max{0.0f,0.0f,0.0f};
        glm::vec3 m_center{0.0f, 0.0f, 0.0f};
        glm::vec3 m_size{0.0f, 0.0f, 0.0f};
};

#endif // _BBOX_H_
