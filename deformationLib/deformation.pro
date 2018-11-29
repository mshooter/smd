# set to buidl dynamic library 
TEMPLATE = lib 

TARGET = deformationLib 
QT-=core gui 
# use this directory to store all the intermediate obbject
OBJECTS_DIR = obj 

# not an app 
CONFIG += console c++14
CONFIG -= app_bundle 
#CONFIG += staticlib
DESTDIR = $$PWD/lib

# set up C++ flags for this compliation when using the host compiler 
QMAKE_CXXFLAGS += -std=c++14 -fPIC -g -O3 

INCLUDEPATH += \
    /usr/local/include/glm \ 
    /usr/local/include \ 
    $$PWD/include \
    /public/devel/2018/include \
    /public/devel/2018/include/eigen3 \
    /usr/local/include/eigen3

macx:{
    QMAKE_CXXFLAGS += -arch x86_64
}

# Input
HEADERS += $$files(include/*.h, true) 
SOURCES += $$files(src/*.cpp,true) 
