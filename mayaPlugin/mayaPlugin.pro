# This file is split into Three sections
# The first configures Qt and the source files for all platforms
# The second is the linux build
# The third the mac build
# (if your using windows you will need to add a fourth one!)
# first lets remove Qt core and gui not going to need it
QT       -= core gui
# set the variable for the Maya Location, this will be different depending
# upon the platform / version of maya used
TARGET = mayaPlugin
# for for mac we need a bundle so change the name
macx:TARGET=mayaPlugin.bundle
# here we add the source files (and headers if required)
SOURCES+=src/*.cpp
HEADERS+=include/*.h
OBJECTS_DIR = obj
# these are defines required by Maya to re-define some C++
# stuff, we will add some more later to tell what platform
# we are on as well
DEFINES+=REQUIRE_IOSTREAM \
         _BOOL
# These are the maya libs we need to link to, this will change depending
# upon which maya framework we use, just add them to the end of
# this list as required and they will be added to the build
MAYALIBS=-lOpenMaya \
        -lFoundation
INCLUDEPATH+=include 
# now tell linux we need to build a lib
linux-g++-64:TEMPLATE = lib
 
# this tells qmake where maya is
linux-g++-64:MAYALOCATION=/usr/autodesk/maya2011-x64/
# under linux we need to use the version of g++ used to build maya
# in this case g++412
linux-g++-64:QMAKE_CXX = g++412
# set the include path for linux
linux-g++-64:INCLUDEPATH += $$MAYALOCATION/include \
                        /usr/X11R6/include
# set which libs we need to include
linux-g++-64:LIBS += -L$$MAYALOCATION/lib \
                   $$MAYALIBS
# tell maya were building for linux
linux:DEFINES+=linux
 
# tell maya were building for Mac
macx:DEFINES+=OSMac_
macx:MAYALOCATION=/Applications/Autodesk/maya2017
macx:CONFIG -= app_bundle
macx:INCLUDEPATH+=$$MAYALOCATION/devkit/include
# under mac we need to build a bundle, to do this use
# the -bundle flag but we also need to not use -dynamic lib so
# remove this
macx:LIBS +=-bundle
mac:LIBS -=-dynamiclib
 
macx:LIBS += -L$$MAYALOCATION/Maya.app/Contents/MacOS \
             $$MAYALIBS
