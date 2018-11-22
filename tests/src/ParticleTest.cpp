#include "Particle.h"
#include "gtest/gtest.h"

TEST(Particle, setMasss)
{
    Particle particle; 
    particle.setMass(1.0f);
    EXPECT_EQ(1.0f, particle.getMass());
}

TEST(Particle, setInitPosition)
{
    Particle particle; 
    particle.setInitPosition(glm::vec3(1.0f, 2.0f, 4.0f));
    EXPECT_EQ(glm::vec3(1.0f,2.0f,4.0f), particle.getInitPosition());
}

TEST(Particle, setCurrentPosition)
{
    Particle particle; 
    particle.setCurrentPosition(glm::vec3(1.0f, 1.0f, 1.0f));
    EXPECT_EQ(glm::vec3(1.0f, 1.0f, 1.0f), particle.getCurrentPosition());
}
