TEMPLATE = app
TARGET = tests

QT-= core gui 

OBJECTS_DIR = obj 

CONFIG += console c++14
CONFIG -= app_bundle

SOURCES += $$files(src/*.cpp,true)

DEPENDPATH += . ../deformationLib 
INCLUDEPATH += ../deformationLib/include 
INCLUDEPATH += \
   /usr/local/include/glm \ 
   /usr/local/include/gtest \ 
   /usr/local/include 
  
OTHER_FILES += \ 
    $$files(models/*, true)
QMAKE_CXXFLAGS += -std=c++14 -fPIC -g -O3 

LIBS += -L../deformationLib/lib -ldeformationLib -L/usr/local/lib -lgtest -pthread

macx:{
    INCLUDEPATH += ../deformationLib/include 
    LIBS += -L$$PWD/../deformationLib/lib -ldeformationLib -lgtest -pthread
 }

