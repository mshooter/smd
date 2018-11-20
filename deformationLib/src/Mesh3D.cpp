#include "Mesh3D.h"

Mesh3D::Mesh3D(const char* _filename)
{
    loadObject(_filename);
}
/// ---------------------------------------------------------
void Mesh3D::loadObject(const char* _filename)
{
    // check if file exists and can open
    std::ifstream in(_filename, std::ios::in);
    if(!in)
    {
        std::cerr<<"cannot open" << _filename << std::endl; std::exit(1);
    }
    
    // set the vertex positions
    std::string line;
    while(std::getline(in, line))
    {
        if(line.substr(0,2) == "v ")
        {
            std::istringstream s(line.substr(2));
            glm::vec3 v; 
            s >> v.x;
            s >> v.y;
            s >> v.z; 
            m_vertexPositions.push_back(v);
        }
    }
    // set the numbe of vertices 
    m_numberOfVertices = m_vertexPositions.size();

}
/// ---------------------------------------------------------
std::vector<glm::vec3> Mesh3D::getVertexPositions()
{
    return m_vertexPositions; 
}
/// ---------------------------------------------------------
void Mesh3D::setNumberOfVertex()
{
    m_numberOfVertices = m_vertexPositions.size();
}
/// ---------------------------------------------------------
int Mesh3D::getNumberOfVertex()
{
    return m_numberOfVertices;
}
