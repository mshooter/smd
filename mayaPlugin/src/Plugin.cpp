#include "DeformerNode.h"
#include <maya/MFnPlugin.h>
MStatus initializePlugin(MObject obj)
{
    
    MFnPlugin plugin(obj, "Moira Shooter", "1.0", "Any");
    MStatus status = plugin.registerNode("DeformerNode",
            DeformerNode::id,
            &DeformerNode::creator, 
            &DeformerNode::initialize,
            MPxNode::kDeformerNode);
    if(!status)
    {
        status.perror("unable to register command");
        return status;
    }
    return status;
    
}
///-----------------------------------------
MStatus uninitializePlugin(MObject obj)
{
    MFnPlugin plugin(obj);
    MStatus status = plugin.deregisterNode(DeformerNode::id);
    return status;
}



