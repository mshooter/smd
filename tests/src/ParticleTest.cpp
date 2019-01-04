#include "Particle.h"
#include "gtest/gtest.h"

TEST(Particle, constructor)
{
    // variables to test 
    glm::vec3 originalPositions{0.0f, 1.0f, 0.0f};
    glm::vec3 originalVelocity{2.0f, 0.0f, 0.0f};

    // constructor
    Particle particle(originalPositions, originalVelocity);
    
    EXPECT_EQ(particle.getInitPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    EXPECT_EQ(particle.getCurrentPosition(),glm::vec3(0.0f, 1.0f, 0.0f));
    EXPECT_EQ(particle.getGoalPosition(),glm::vec3(0.0f, 1.0f, 0.0f));
    EXPECT_EQ(particle.getVelocity(),glm::vec3(2.0f, 0.0f, 0.0f));
    EXPECT_EQ(particle.getForce(),glm::vec3(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(particle.getMass(),1.0f);
}
//----------------------------------------------------
TEST(Particle, setMasss)
{
    Particle particle; 
    particle.setMass(1.0f);
    EXPECT_EQ(1.0f, particle.getMass());
}
//----------------------------------------------------
TEST(Particle, setQ)
{
    // variables to test 
    glm::vec3 originalPositions{0.0f, 1.0f, 0.0f};
    glm::vec3 originalVelocity{2.0f, 0.0f, 0.0f};
    // constructor
    Particle particle(originalPositions, originalVelocity);
    ASSERT_EQ(particle.getInitPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    ASSERT_EQ(particle.getCurrentPosition(),glm::vec3(0.0f, 1.0f, 0.0f));
    ASSERT_EQ(particle.getGoalPosition(),glm::vec3(0.0f, 1.0f, 0.0f));
    ASSERT_EQ(particle.getVelocity(),glm::vec3(2.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getForce(),glm::vec3(0.0f, 0.0f, 0.0f));
    // center of mass
    glm::vec3 com{0.0f, 0.0f, 0.0f};
    // relative position original
    glm::vec3 q = particle.getInitPosition() - com;
    // set Q function
    particle.setQ(q);
    // test
    EXPECT_EQ(particle.getQ(), glm::vec3(0.0f, 1.0f, 0.0f));
}
//----------------------------------------------------
TEST(Particle, setP)
{
    // variables to test 
    glm::vec3 originalPositions{0.0f, 1.0f, 0.0f};
    glm::vec3 originalVelocity{2.0f, 0.0f, 0.0f};
    // constructor 
    Particle particle(originalPositions, originalVelocity);
    // assert
    ASSERT_EQ(particle.getInitPosition(), glm::vec3(0.0f, 1.0f, 0.0f));
    ASSERT_EQ(particle.getCurrentPosition(),glm::vec3(0.0f, 1.0f, 0.0f));
    ASSERT_EQ(particle.getGoalPosition(),glm::vec3(0.0f, 1.0f, 0.0f));
    ASSERT_EQ(particle.getVelocity(),glm::vec3(2.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getForce(),glm::vec3(0.0f, 0.0f, 0.0f));
    // center of mass
    glm::vec3 com{0.0f, 0.0f, 0.0f};
    // relative position original
    glm::vec3 p = particle.getCurrentPosition()- com;
    // set P function
    particle.setP(p);
    // test
    EXPECT_EQ(particle.getP(), glm::vec3(0.0f, 1.0f, 0.0f));
}
//----------------------------------------------------
TEST(Particle, updateForces)
{
    // variables to test 
    glm::vec3 originalPositions{0.0f, 0.0f, 0.0f};
    glm::vec3 originalVelocity{2.0f, 0.0f, 0.0f};
    // constructor 
    Particle particle(originalPositions, originalVelocity);
    // assert
    ASSERT_EQ(particle.getInitPosition(), glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getCurrentPosition(),glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getGoalPosition(),glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getVelocity(),glm::vec3(2.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getForce(),glm::vec3(0.0f, 0.0f, 0.0f));
    // fucntion 
    particle.setMass(10.0f);
    // with time step 1.0f
    particle.updateForces(1.0f);
    // test the function   
    EXPECT_EQ(particle.getForce(), glm::vec3(-4.0f,-98.0f,0.0f));
    EXPECT_EQ(particle.getMass(), 10.0f);
    EXPECT_EQ(particle.getCurrentPosition().y, 0.01f);
}
//----------------------------------------------------
TEST(Particle, updateVelocity)
{
    // variables to test 
    glm::vec3 originalPositions{0.0f, 0.0f, 0.0f};
    glm::vec3 originalVelocity{2.0f, 0.0f, 0.0f};
    // constructor 
    Particle particle(originalPositions, originalVelocity);
    // assert
    ASSERT_EQ(particle.getInitPosition(), glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getCurrentPosition(),glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getGoalPosition(),glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getVelocity(),glm::vec3(2.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getForce(),glm::vec3(0.0f, 0.0f, 0.0f));
    // with time step 1.0f
    particle.updateForces(1.0f);
    // test the function   
    ASSERT_EQ(particle.getForce(), glm::vec3(-0.4f,-9.8f,0.0f));
    ASSERT_EQ(particle.getMass(), 1.0f);
    ASSERT_EQ(particle.getCurrentPosition().y, 0.01f);
    // update velocity
    particle.updateVelocity(1.0f);
    EXPECT_EQ(particle.getVelocity(), glm::vec3(1.6f, -9.8f, 0.0f));
    EXPECT_EQ(particle.getForce(), glm::vec3(0.0f, 0.0f, 0.0f));
}
//----------------------------------------------------
TEST(Particle, updatePosition)
{
    // variables to test 
    glm::vec3 originalPositions{0.0f, 0.0f, 0.0f};
    glm::vec3 originalVelocity{2.0f, 0.0f, 0.0f};
    // constructor 
    Particle particle(originalPositions, originalVelocity);
    // assert
    ASSERT_EQ(particle.getInitPosition(), glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getCurrentPosition(),glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getGoalPosition(),glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getVelocity(),glm::vec3(2.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getForce(),glm::vec3(0.0f, 0.0f, 0.0f));
    // with time step 1.0f
    particle.updateForces(1.0f);
    // test the function   
    ASSERT_EQ(particle.getForce(), glm::vec3(-0.4f,-9.8f,0.0f));
    ASSERT_EQ(particle.getMass(), 1.0f);
    ASSERT_EQ(particle.getCurrentPosition().y, 0.01f);
    // update velocity
    particle.updateVelocity(1.0f);
    ASSERT_EQ(particle.getVelocity(), glm::vec3(1.6f, -9.8f, 0.0f));
    ASSERT_EQ(particle.getForce(), glm::vec3(0.0f, 0.0f, 0.0f));
    // update position
    particle.updatePosition(1.0f);
    EXPECT_EQ(particle.getCurrentPosition(), glm::vec3(1.6f, 0.01f, 0.0f));
}
//----------------------------------------------------
TEST(Particle, shapeMatchUpdate)
{
    // variables to test 
    glm::vec3 originalPositions{0.0f, 0.0f, 0.0f};
    glm::vec3 originalVelocity{2.0f, 0.0f, 0.0f};
    // constructor 
    Particle particle(originalPositions, originalVelocity);
    // assert
    ASSERT_EQ(particle.getInitPosition(), glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getCurrentPosition(),glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getGoalPosition(),glm::vec3(0.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getVelocity(),glm::vec3(2.0f, 0.0f, 0.0f));
    ASSERT_EQ(particle.getForce(),glm::vec3(0.0f, 0.0f, 0.0f));
    // with time step 1.0f
    particle.updateForces(1.0f);
    // test the function   
    ASSERT_EQ(particle.getForce(), glm::vec3(-0.4f,-9.8f,0.0f));
    ASSERT_EQ(particle.getMass(), 1.0f);
    ASSERT_EQ(particle.getCurrentPosition().y, 0.01f);
    // update velocity
    particle.updateVelocity(1.0f);
    ASSERT_EQ(particle.getVelocity(), glm::vec3(1.6f, -9.8f, 0.0f));
    ASSERT_EQ(particle.getForce(), glm::vec3(0.0f, 0.0f, 0.0f));
    // update position
    particle.updatePosition(1.0f);
    ASSERT_EQ(particle.getCurrentPosition(), glm::vec3(1.6f, 0.01f, 0.0f));
    // shape match
    particle.shapeMatchUpdate(1.0f, 0.5f);
    EXPECT_EQ(particle.getVelocity().x, 1.44f);
    EXPECT_FLOAT_EQ(particle.getVelocity().y, -9.801f);
    EXPECT_EQ(particle.getVelocity().z, 0.0f);
    EXPECT_EQ(particle.getCurrentPosition(), glm::vec3(0.8f, 0.005f, 0.0f));
}
