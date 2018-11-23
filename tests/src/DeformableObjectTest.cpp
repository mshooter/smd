#include "DeformableObject.h"
#include "gtest/gtest.h"
#include "math.h"
#include <chrono>

typedef std::chrono::high_resolution_clock Clock; 
const char* path = "models/cube.obj";

TEST(DeformableObject, getAmountOfParticles)
{
    Mesh3D mesh(path);
    DeformableObject def;
    def.setListOfParticles(mesh);
    const unsigned int sizeOfParts = def.getListOfParticles().size();
    EXPECT_EQ((const unsigned int)8, sizeOfParts);
}
/// ----------------------------------------------------------------------------
TEST(DeformableObject, getOriginalCenterOfMass)
{
    Mesh3D mesh(path);
    DeformableObject def(mesh);
    // orignal center of mass is 0 
    glm::vec3 centerOfMass = def.getOriginalCOM();
    EXPECT_FLOAT_EQ(0.0f, centerOfMass[0]);
    EXPECT_FLOAT_EQ(0.0f, centerOfMass[1]);
    EXPECT_FLOAT_EQ(0.0f, centerOfMass[2]);
}
/// ----------------------------------------------------------------------------
TEST(DeformableObject, getQ)
{
    Mesh3D mesh(path);
    DeformableObject def;
    def.setListOfParticles(mesh);
    def.calculateQ();
    // assert equals - > amount of particles
    // copy

    std::vector<Particle> listOfParticles = def.getListOfParticles();
    ASSERT_EQ(listOfParticles.size(), (const unsigned int)8);
    EXPECT_EQ(glm::vec3(-0.5f, -0.5f, 0.5f), listOfParticles[0].getQ()); 
    EXPECT_EQ(glm::vec3(0.5f, -0.5f, 0.5f), listOfParticles[1].getQ()); 
    EXPECT_EQ(glm::vec3(-0.5f, 0.5f, 0.5f), listOfParticles[2].getQ()); 
    EXPECT_EQ(glm::vec3(0.5f, 0.5f, 0.5f), listOfParticles[3].getQ()); 
    
    EXPECT_EQ(glm::vec3(-0.5f, 0.5f, -0.5f), listOfParticles[4].getQ()); 
    EXPECT_EQ(glm::vec3(0.5f, 0.5f,-0.5f), listOfParticles[5].getQ()); 
    EXPECT_EQ(glm::vec3(-0.5f, -0.5f,-0.5f), listOfParticles[6].getQ()); 
    EXPECT_EQ(glm::vec3(0.5f, -0.5f,-0.5f), listOfParticles[7].getQ()); 
    
}
/// ----------------------------------------------------------------------------
TEST(DeformableObject, getA_qq)
{
    Mesh3D mesh(path);
    DeformableObject def; 
    def.setListOfParticles(mesh);
    def.calculateQ();
    def.calculateA_qq();

    glm::mat3 A_qqTest(0.5, 0, 0,
                        0, 0.5, 0,
                        0, 0, 0.5);

    glm::mat3 A_qq = def.getA_qq();
    for(int i=0; i<3; ++i)
    {
        for(int j=0; j<3; ++j)
        {
            EXPECT_EQ(A_qqTest[i][j], A_qq[i][j]);
        }
    }
}
/// ----------------------------------------------------------------------------
TEST(DeformableObject, calculateCurrentPos)
{
    Mesh3D mesh(path);
    DeformableObject def(mesh); 

    ASSERT_EQ(def.getListOfParticles().size(), (const unsigned int)8);

}
