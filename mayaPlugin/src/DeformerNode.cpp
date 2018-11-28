#include "DeformerNode.h"
#include "/home/s4928793/smd/deformationLib/include/DeformableObject.h"
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MAnimControl.h>
#define SIGN(a) (a < 0 ? -1 : 1)
MTypeId DeformerNode::id(0x0100F );
MObject DeformerNode::m_stiffness;
bool DeformerNode::m_isFirstFrame;
MTime DeformerNode::m_previousTime;
MObject DeformerNode::CurrentTime; 
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
    uAttr.setDefault(MAnimControl::currentTime().as(MTime::kFilm));
    uAttr.setChannelBox(true);

    m_stiffness = nAttr.create("Stiffness", "st", MFnNumericData::kDouble, 1.0);
    nAttr.setChannelBox(true);
    nAttr.setMin(0.0f);
    nAttr.setMax(1.0f);
    // add attributes
    addAttribute(CurrentTime);
    addAttribute(m_stiffness);
    // affecting 
    attributeAffects(CurrentTime, outputGeom);
    attributeAffects(m_stiffness, outputGeom);
    return MStatus::kSuccess;
}
///-----------------------------------------
MStatus DeformerNode::deform(MDataBlock& block, MItGeometry& iter, const MMatrix& localToWorldMatrix, unsigned int multiIndex)
{
    /// @arugments
    /// block : data block of the node 
    /// iter : iterator for the geometry to be deformed 
    /// m : matrix to transform the point into world space
    /// multiIndex : the index of geometry that we are deforming 
    // get the values from the user
    MTime time_now = block.inputValue(CurrentTime).asTime();
    MTime delta_time = time_now - m_previousTime;
    m_previousTime = time_now; 
    MStatus returnStatus;
    // not using envelope would be weird - own pp 
    // update 
    int delta_timeV = delta_time.value();
    int delta_timeTs = 2; 
    for(int i = 0 ; i < abs(delta_timeV) * delta_timeTs; ++i)
    {
        defo.update(1 / 24.0f / delta_timeTs * SIGN(delta_timeV), block.inputValue(m_stiffness).asFloat());
    }
    // update output pos 
    MMatrix localToWorldInv = localToWorldMatrix.inverse();
    for(; iter.isDone(); iter.next())
    {
        int idx = iter.index();
        glm::vec3 p = defo.getListOfParticles()[idx].getCurrentPosition();
        MPoint newPos(p[0], p[1], p[3]);
        iter.setPosition(newPos * localToWorldInv);
    }
    return returnStatus;
}
///-----------------------------------------

