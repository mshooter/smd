#include <iostream>
#include "glm/glm.hpp"
#include "DeformableObject.h"
#include <typeinfo>

int main()
{
    Eigen::MatrixXf m = Eigen::MatrixXf(3,9);
    Eigen::MatrixXf t = Eigen::MatrixXf(9,9);

    Eigen::MatrixXf r = Eigen::MatrixXf(3,9);
    Eigen::Matrix3f A;
    Eigen::Matrix3f Q;
    Eigen::Matrix3f M;
    
    r = m*t+Eigen::MatrixXf::Identity(3,9); 
    std::cout<<r<<std::endl;
    return 0;
}
