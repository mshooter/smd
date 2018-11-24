include_directories(/Users/moirashooter/smd/deformationLib/include)
file(GLOB SOURCE_FILES "*.cpp")
file(GLOB LIBRARIES "/Users/moirashooter/smd/deformationLib/lib/*.dylib")
set(CMAKE_MODULE_PATH /Users/moirashooter/smd/mayaPlugin/cmake/Modules)
# GLM
find_package(GLM REQUIRED)
include_directories(${GLM_INCLUDE_DIR})
# eigen
set(EIGEN3_ROOT /usr/local/include/eigen3)
find_package(Eigen REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
# maya
find_package(Maya REQUIRED)
include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
MAYA_PLUGIN(${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} ${MAYA_TARGET_TYPE} DESTINATION plug-ins)

# easier 
include_directories(../include)

# third party - deformationLib
target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES} ${LIBRARIES})
