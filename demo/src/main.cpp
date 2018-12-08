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
    def.update(1.0f);
    glm::vec3 com = def.computeCOM();
    std::cout<<"After center of mass "<<com[0]<<" "<<com[1]<<" "<<com[2]<<std::endl;
    for(auto& part : def.getListOfParticles())
    {
        part.setQ(part.getCurrentPosition()-com);
        part.setP(part.getInitPosition() - def.getOriginalCOM());
        std::cout<<"after Q's "<< part.getQ()[0] <<" "<<part.getQ()[1]<<" "<<part.getQ()[2]<<std::endl;
        std::cout<<"after P's "<< part.getP()[0] <<" "<<part.getP()[1]<<" "<<part.getP()[2]<<std::endl;
    }
    return 0;
}
