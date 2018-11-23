#include <iostream>
#include "glm/glm.hpp"
#include "DeformableObject.h"
#include <chrono>
#include <typeinfo>
typedef std::chrono::high_resolution_clock timeStep; 

int main()
{
    Mesh3D mesh("models/cube.obj");
    DeformableObject def(mesh);
   
   float f = 10.0f;  
   while(f!=0)
   {
   def.update(f, 1.0f);
   for(int i=0; i<8; i++)
   {
   Particle part = def.getListOfParticles()[i];

   std::cout<<"position:   "<<part.getCurrentPosition()[0]<<" "<<part.getCurrentPosition()[1]<<" "<<part.getCurrentPosition()[2]<<std::endl;
  // std::cout<<"velocity:   "<<part.getVelocity()[0]<<" "<<part.getVelocity()[1]<<" "<<part.getVelocity()[2]<<std::endl;
   }
   f--;
}
    return 0;
}
