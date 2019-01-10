# Build
Build on OSX:   
* mkdir build  
* cd build 
* cmake -G "Unix Makefiles" _DMAYA_VERSION=2017 ../ (or whatever version) 
* you may have to specify MAYA_LIBRARY_DIR or/and MAYA_INCLUDE_DIR in cmake
Compile on OSX:   
* cd in build/   
* sudo cmake --build . --config Release --target install 

# Example instructions 
How to use the deformer on the mesh. <br/>
1. Load plugin:
    * Window -> Settings/Preferences -> Plug-in Manager
    * browse for DeformerPlugin.bundle and open (the path is given by the terminal when compiled)
2. Create or select a mesh (make sure the mesh is above 0 in the y axis) 
3. Go into the script editor(MEL)
4. command line: deformer -type DeformerNode;
5. connectAttr -f time1.outTime DeformerNode1.CurrentTime; 
