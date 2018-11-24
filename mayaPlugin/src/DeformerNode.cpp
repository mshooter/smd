#include "DeformerNode.h"
#include "DeformableObject.h"
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>

MTypeId DeformerNode::id(0x0100F );
MObject DeformerNode::m_stiffness;
bool DeformerNode::m_isFirstFrame;
MTime DeformerNode::m_previousTime;
MObject CurrentTime; 
DeformableObject defo;

void* DeformerNode::creator()
{
    return new DeformerNode;
}
///-----------------------------------------
MStatus DeformerNode::initialize()
{
    // set up attributes 
    m_isFirstFrame = true; 
    MFnTypedAttribute tAttr;
    MFnNumericAttribute nAttr;
    MFnUnitAttribute uAttr; 
    // numeric attribues
    CurrentTime = uAttr.create("CurrentTime", "ct", MFnUnitAttribute::kTime, 0.0);
    m_stiffness = nAttr.create("Stiffness", "st", MFnNumericData::kDouble, 0.0);
    // add attributes
    addAttribute(CurrentTime);
    addAttribute(m_stiffness);
    // affecting 
    attributeAffects(CurrentTime, outputGeom);
    attributeAffects(m_stiffness, outputGeom);
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
    MTime time_now = block.inputValue(CurrentTime).asTime();
    MStatus returnStatus;
    // set a vector of points
    for ( ; !iter.isDone(); iter.next())
    {
        MPoint pt = iter.position();
        // convert point to glm 
        glm::vec3 glmPt{pt.x, pt.y, pt.z};
        defo.setListOfParticles(glmPt);    
         
        // Perform some calculation on pt.
        //  e.g.
        // pt.x += 1.0 * i;
       
        //Set the final position.
    }
    defo.calculateCOM();
    defo.calculateQ();
    defo.calculateA_qq();
    defo.update(1.0f, 1.0f);

    auto parts = defo.getListOfParticles();
    int i =0;
    for(;!iter.isDone(); iter.next())
    {
        iter.setPosition(MPoint(parts[i].getCurrentPosition()[0], parts[i].getCurrentPosition()[1], parts[i].getCurrentPosition()[2]));
        i++;
    }

    return returnStatus;
}
///-----------------------------------------

