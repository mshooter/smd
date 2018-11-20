#include "DeformableObject.h"
#include "gtest/gtest.h"
#include "math.h"

const char* path = "models/cube.obj";

TEST(DeformableObject, getAmountOfParticles)
{
    Mesh3D mesh(path);
    DeformableObject def(mesh);

    EXPECT_EQ((int unsigned long)8, def.getListOfParticles().size());
}

TEST(DeformableObject, getOriginalCenterOfMass)
{
    Mesh3D mesh(path);
    DeformableObject def(mesh);

    EXPECT_FLOAT_EQ(0.0f, def.getOriginalCOM()[0]);
    EXPECT_FLOAT_EQ(-0.133149f, def.getOriginalCOM()[1]);
    EXPECT_FLOAT_EQ(0.0f, def.getOriginalCOM()[2]);
}

TEST(DeformableObject, getQ)
{
    Mesh3D mesh(path);
    DeformableObject def(mesh);
   
     
}
