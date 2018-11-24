# INSTRUCTIONS
Build on OSX: 
    mkdir build
    cd build 
    cmake -G "Unix Makefiles" _DMAYA_VERSION=2017 ../
Compile on OSX: 
    cd in build/ 
    sudo cmake --build . --config Release --target install
In maya:
    import maya.cmds as cmds 
    cmds.pluginName();
