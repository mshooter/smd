#include <iostream>
#include "glm/glm.hpp"
#include "DeformableObject.h"
#include <iomanip>
#include <typeinfo>
int main()
{
    Mesh3D mesh("models/cube.obj");
    DeformableObject def(mesh);
    std::cout<<def.getA_qq()[0][0]<<std::endl;;

    return 0;
}
