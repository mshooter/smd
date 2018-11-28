

file(GLOB SOURCE_FILES "*.cpp")
if(MACOS)
    set(CMAKE_MODULE_PATH /Users/moirashooter/smd/mayaPlugin/cmake/Modules)
elseif(LINUX)
    set(CMAKE_MODULE_PATH /home/s4928793/smd/mayaPlugin/cmake/Modules)
endif()
# GLM
if(MACOS)
    find_package(GLM REQUIRED)
    include_directories(${GLM_INCLUDE_DIR})
elseif(LINUX)
    find_package(glm REQUIRED)
endif()    
# eigen
if(MACOS)
    set(EIGEN3_ROOT /usr/local/include/eigen3)
    find_package(Eigen3 REQUIRED)
    include_directories(${EIGEN3_INCLUDE_DIR})
elseif(LINUX)
    set(EIGEN3_ROOT /public/devel/2018/include/eigen3)
    find_package(Eigen3 REQUIRED) 
    include_directories(${EIGEN3_INCLUDE_DIR})
endif()

# maya
find_package(Maya REQUIRED)
include_directories(${MAYA_INCLUDE_DIR})
link_directories(${MAYA_LIBRARY_DIR})
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} )
MAYA_PLUGIN(${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME} ${MAYA_TARGET_TYPE} DESTINATION plug-ins)

# easier
include_directories(../include)

# third party - deformationLib
if(MACOS)
    include_directories(/Users/moirashooter/smd/deformationLib/include)
    target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES} /Users/moirashooter/smd/deformationLib/lib/libdeformationLib.a ) 
elseif(LINUX)
    set(DEFORMATION_LIB libdeformationLib.a)
    link_directories(/home/s4928793/smd/deformationLib/lib)
    include_directories(/home/s4928793/smd/deformationLib/include)
    target_link_libraries(${PROJECT_NAME} ${MAYA_LIBRARIES} glm ${DEFORMATION_LIB} ) 
endif()

