#include <iostream>
#include "glm/glm.hpp"
#include "DeformableObject.h"
#include <iomanip>
#include <typeinfo>
int main()
{
    Mesh3D mesh("models/cube.obj");
    DeformableObject def(mesh);
    glm::mat3 mat(0.0f);
    for(auto& part: def.getListOfParticles())
    {
        mat += part.getMass() * glm::outerProduct(part.getQ(), part.getQ());
        std::cout<<mat[0][0]<<" " <<mat[0][1]<<" "<<mat[0][2]<<std::endl; 
        std::cout<<mat[1][0]<<" " <<mat[1][1]<<" "<<mat[1][2]<<std::endl; 
        std::cout<<mat[2][0]<<" " <<mat[2][1]<<" "<<mat[2][2]<<std::endl; 
        
    }
        //std::cout<<mat[0][0]<<" " <<mat[0][1]<<" "<<mat[0][2]<<std::endl; 
        //std::cout<<mat[1][0]<<" " <<mat[1][1]<<" "<<mat[1][2]<<std::endl; 
        //std::cout<<mat[2][0]<<" " <<mat[2][1]<<" "<<mat[2][2]<<std::endl; 
    return 0;
}
