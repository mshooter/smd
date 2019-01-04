#include "DeformableObject.h"
#include "Mesh3D.h"
#include "gtest/gtest.h"
#include "math.h"

const char* path = "models/cube.obj";
TEST(DeformableObject, constructor)
{
    // load mesh and get list of vertices
    Mesh3D mesh(path);
    // deformable object constructor
    DeformableObject def(mesh.getVertexPositions(), glm::vec3(.0f, .0f, .0f));
    auto particles = def.getListOfParticles();
    // test
    // get mode
    EXPECT_EQ(def.getMode(), 0);
    // list of particles
    EXPECT_EQ(int(def.getListOfParticles().size()), 8); 
    // center of mass
    EXPECT_EQ(def.getOriginalCOM(), glm::vec3(0.0f, 0.0f, 0.0f)); 
    // relative original q position 
    glm::vec3 originCom = def.getOriginalCOM();
    glm::vec3 q_0 = particles[0].getInitPosition() - originCom;
    glm::vec3 q_1 = particles[1].getInitPosition() - originCom;
    glm::vec3 q_2 = particles[2].getInitPosition() - originCom;
    glm::vec3 q_3 = particles[3].getInitPosition() - originCom;

    glm::vec3 q_4 = particles[4].getInitPosition() - originCom;
    glm::vec3 q_5 = particles[5].getInitPosition() - originCom;
    glm::vec3 q_6 = particles[6].getInitPosition() - originCom;
    glm::vec3 q_7 = particles[7].getInitPosition() - originCom;

    EXPECT_EQ(q_0, glm::vec3(-0.5f, -0.5, 0.5f));
    EXPECT_EQ(q_1, glm::vec3(0.5f, -0.5, 0.5f));
    EXPECT_EQ(q_2, glm::vec3(-0.5f, 0.5, 0.5f));
    EXPECT_EQ(q_3, glm::vec3(0.5f, 0.5, 0.5f));

    EXPECT_EQ(q_4, glm::vec3(-0.5f, 0.5, -0.5f));
    EXPECT_EQ(q_5, glm::vec3(0.5f, 0.5, -0.5f));
    EXPECT_EQ(q_6, glm::vec3(-0.5f, -0.5, -0.5f));
    EXPECT_EQ(q_7, glm::vec3(0.5f, -0.5, -0.5f));
    glm::mat3 scalarMatrix(2.0f);
    // scalar matrix
    EXPECT_EQ(def.getAqq(), glm::mat3(2.0f)); 
}
/// ----------------------------------------------------------------------------
TEST(DeformableObject, calculateR )
{
    // rotational matrix
    glm::mat3 Apq(0.0f);
    Apq[0][0] = 1.0f;
    Apq[0][1] = 2.0f;
    Apq[0][2] = 3.0f;

    Apq[1][0] = 4.0f;
    Apq[1][1] = 5.0f;
    Apq[1][2] = 6.0f;
    
    Apq[2][0] = 7.0f;
    Apq[2][1] = 8.0f;
    Apq[2][2] = 9.0f;
    // transpose
    glm::mat3 tA = glm::transpose(Apq);
    EXPECT_EQ(tA[0][0], 1.0f);
    EXPECT_EQ(tA[1][0], 2.0f);
    EXPECT_EQ(tA[2][0], 3.0f);
    
    EXPECT_EQ(tA[0][1], 4.0f);
    EXPECT_EQ(tA[1][1], 5.0f);
    EXPECT_EQ(tA[2][1], 6.0f);

    EXPECT_EQ(tA[0][2], 7.0f);
    EXPECT_EQ(tA[1][2], 8.0f);
    EXPECT_EQ(tA[2][2], 9.0f);
    
    glm::mat3 S = tA * Apq;
    EXPECT_EQ(S[0][0], 14.0f);
    EXPECT_EQ(S[0][1], 32.0f);
    EXPECT_EQ(S[0][2], 50.0f);
    
    EXPECT_EQ(S[1][0], 32.0f);
    EXPECT_EQ(S[1][1], 77.0f);
    EXPECT_EQ(S[1][2], 122.0f);
    
    EXPECT_EQ(S[2][0], 50.0f);
    EXPECT_EQ(S[2][1], 122.0f);
    EXPECT_EQ(S[2][2], 194.0f);
    
    
}

