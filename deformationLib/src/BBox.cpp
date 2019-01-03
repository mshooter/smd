#include "BBox.h"

BBox::BBox(std::vector<glm::vec3> _Positions)
{
    for(auto& vert : _Positions)
    {
        if(vert.x < m_min.x ) m_min.x = vert.x;
        if(vert.x > m_max.x ) m_max.x = vert.x;
        if(vert.y < m_min.y ) m_min.y = vert.y;
        if(vert.y > m_max.y ) m_max.y = vert.y;
        if(vert.z < m_min.z ) m_min.z = vert.z;
        if(vert.z > m_max.z ) m_max.z = vert.z;
    }

    m_size = m_max-m_min;
    m_center = (m_min+m_max) / 2.0f;
}
//-----------------------------------------------------
glm::vec3 BBox::getMin()
{
    return m_min;
}
//-----------------------------------------------------
glm::vec3 BBox::getMax()
{
    return m_max;
}
//-----------------------------------------------------
glm::vec3 BBox::getCenter()
{
    return m_center;
}
//-----------------------------------------------------
glm::vec3 BBox::getSize()
{
    return m_size;
}
