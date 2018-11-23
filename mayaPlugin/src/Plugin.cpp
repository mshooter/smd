#include <maya/MFnPlugin.h>
#include "DeformerNode.h"
MStatus initializePlugin(MObject obj)
{
    
    MFnPlugin plugin(obj, "Moira Shooter", "1.0", "Amy");
    MStatus status = plugin.registerCommand("smd",DeformerNode::creator);
    if(!status)
    {
        status.perror("unable to register command");
        return status;
    }
    return status;
    
}

MStatus uninitializePlugin(MObject obj)
{
    MFnPlugin plugin(obj);
    MStatus status = plugin.deregisterCommand("deformerNode");
    return status;
}

