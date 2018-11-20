#include "Mesh3D.h"
#include "gtest/gtest.h"

TEST(Mesh3D, getVertices)
{
    Mesh3D mesh;
    mesh.loadObject("models/cube.obj");
    std::vector<glm::vec3> test_vert;
    test_vert.push_back(glm::vec3(-0.5f, -0.633149f, 0.5f));
    test_vert.push_back(glm::vec3( 0.5f, -0.633149f, 0.5f));
    test_vert.push_back(glm::vec3( 0.5f, 0.366851f, 0.5f));
    test_vert.push_back(glm::vec3( -0.5f, 0.366851f, 0.5f));
    test_vert.push_back(glm::vec3( 0.5f, 0.366851f, -0.5f));
    test_vert.push_back(glm::vec3( -0.5f, 0.366851f, -0.5f));
    test_vert.push_back(glm::vec3( 0.5f, -0.633149f, -0.5f));
    test_vert.push_back(glm::vec3( -0.5f, -0.633149f, -0.5f));

    EXPECT_EQ(test_vert, mesh.getVertexPositions());

}

TEST(Mesh3D, getNumberOfVertices)
{
    Mesh3D mesh;
    // in the load object method you set the vertices already
    mesh.loadObject("models/cube.obj");
    
    EXPECT_EQ(8, mesh.getNumberOfVertex());

}


