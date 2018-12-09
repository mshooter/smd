#include <iostream>
#include "glm/glm.hpp"
#include "DeformableObject.h"
#include "Mesh3D.h"
#include <chrono>
#include <typeinfo>
typedef std::chrono::high_resolution_clock timeStep; 

int main()
{
    Mesh3D mesh("models/cube.obj");
    DeformableObject def(mesh.getVertexPositions());
    for(auto& part : def.getListOfParticles())
    {
        std::cout<<"Before pos: " <<part.getCurrentPosition()[0]<<" " <<part.getCurrentPosition()[1] << " "<<part.getCurrentPosition()[2]<< std::endl;
        std::cout<<"Before vel: " <<part.getVelocity()[0] <<" "<<part.getVelocity()[1] << " "<<part.getVelocity()[2]<< std::endl;
    }
    def.update(2.0/24.0);
    for(auto& part : def.getListOfParticles())
    {
        std::cout<<"after pos: " <<part.getCurrentPosition()[0]<<" " <<part.getCurrentPosition()[1] << " "<<part.getCurrentPosition()[2]<< std::endl;
        std::cout<<"after vel: " <<part.getVelocity()[0] <<" "<<part.getVelocity()[1] << " "<<part.getVelocity()[2]<< std::endl;
    }
    return 0;
}
