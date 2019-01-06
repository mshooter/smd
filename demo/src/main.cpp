#include <iostream>
#include "glm/glm.hpp"
#include "DeformableObject.h"
#include <typeinfo>

int main()
{
    Eigen::MatrixXf mat = Eigen::MatrixXf::Identity(3,9);
    Eigen::VectorXf vec = Eigen::VectorXf::Zero(9);
    glm::vec3 p = glm::vec3(vec(0), vec(1), vec(2));
    std::cout<<p.x<<p.y<<p.z<<std::endl;
    return 0;
}
