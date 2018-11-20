#include <iostream>
#include "glm/glm.hpp"
#include "DeformableObject.h"
#include <iomanip>
#include <typeinfo>
int main()
{
    Mesh3D mesh("models/cube.obj");
    DeformableObject def(mesh);
    def.calculateQ();
    glm::mat3 A_qq(0.f);
    for(auto& part : def.getListOfParticles())
    {
       A_qq += glm::outerProduct(part.getQ(), part.getQ()) * part.getMass();
    }
    A_qq = glm::inverse(A_qq);
    std::cout<<A_qq[0][0]<<" "<<A_qq[0][1]<<" "<<A_qq[0][2]<<std::endl;
    std::cout<<A_qq[1][0]<<" "<<A_qq[1][1]<<" "<<A_qq[1][2]<<std::endl;
    std::cout<<A_qq[2][0]<<" "<<A_qq[2][1]<<" "<<A_qq[2][2]<<std::endl;

    return 0;
}
