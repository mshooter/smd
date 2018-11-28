TEMPLATE = app 
TARGET = demo 
QT-=gui core
OBJECTS_DIR = obj 
CONFIG += console c++14
CONFIG -= app_bundle 

DEPENDPATH += . ../deformationLib/lib
INCLUDEPATH += ../deformationLib/include \
               /public/devel/2018/include/eigen3 \
               /public/devel/2018/include

SOURCES += \ 
    src/main.cpp 

QMAKE_CXXFLAGS += -O3 -std=c++14 

LIBS += -L../deformationLib/lib -ldeformationLib

macx:{
    INCLUDEPATH += /usr/local/include 
    INCLUDEPATH += /usr/local/Cellar
    INCLUDEPATH += /usr/local/lib \ 
                   /usr/local/include/eigen3 \
                   /public/devel/2018/include/eigen3 \
                   /public/devel/2018/include
}

OTHER_FILES += \ 
    $$files(models/*,true)
