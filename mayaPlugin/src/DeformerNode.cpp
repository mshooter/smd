#include "../include/DeformerNode.h"
#include <maya/MFnPlugin.h>

MTypeId DeformerNode::id(0x0100F );

void* DeformerNode::creator()
{
    return new DeformerNode;
}
///-----------------------------------------
MStatus DeformerNode::initialize()
{
    return MStatus::kSuccess;
}
///-----------------------------------------
MStatus DeformerNode::deform(MDataBlock& block, MItGeometry& iter, const MMatrix&, unsigned int multiIndex)
{
    /// @arugments
    /// block : data block of the node 
    /// iter : iterator for the geometry to be deformed 
    /// m : matrix to transform the point into world space
    /// multiIndex : the index of geometry that we are deforming 
    float env = block.inputValue( envelope ).asFloat();
    MStatus returnStatus;
        for ( ; !iter.isDone(); iter.next()) {
        MPoint pt = iter.position();
        
       // Perform some calculation on pt.
       // e.g.
        pt.x += 1.0 * env;
       
        //Set the final position.
        iter.setPosition(pt);
    }
    /*for iter.isDone; iter.next()
     * {
     *      get the points 
     *      do some calculation on the points            set final position
     * }*/
    return returnStatus;
}
///-----------------------------------------
MStatus initializePlugin(MObject obj)
{
    
    MFnPlugin plugin(obj, "Moira Shooter", "1.0", "Any");
    MStatus status = plugin.registerNode("smd",
            DeformerNode::id,
            &DeformerNode::creator, 
            &DeformerNode::initialize,
            MPxNode::kGeometryFilter);
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


