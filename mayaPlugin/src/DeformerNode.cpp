#include "DeformerNode.h"
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MAnimControl.h>
#include <maya/MGlobal.h>
#define SIGN(a) (a < 0 ? -1 : 1)

MTypeId DeformerNode::id(0x0100F);
MObject DeformerNode::Stiffness;
MObject DeformerNode::GravityX;
MObject DeformerNode::GravityY;
MObject DeformerNode::GravityZ;
MObject DeformerNode::Mass; 
MObject DeformerNode::Beta;
MObject DeformerNode::CurrentTime; 
bool DeformerNode::isFirstFrame;
MObject DeformerNode::Mode;
MTime DeformerNode::PreviousTime;

DeformableObject* DeformerNode::ps; 


///-----------------------------------------
void* DeformerNode::creator()
{
    return new DeformerNode;
}
///-----------------------------------------
MStatus DeformerNode::initialize()
{
    // set up attributes 
    isFirstFrame = true; 
    MFnTypedAttribute tAttr;
    MFnNumericAttribute nAttr;
    MFnUnitAttribute uAttr; 
    MFnEnumAttribute eAttr;
    // numeric attribues
    CurrentTime = uAttr.create("CurrentTime", "ct", MFnUnitAttribute::kTime, 0.0);
    uAttr.setDefault(MAnimControl::currentTime().as(MTime::kFilm));
    uAttr.setChannelBox(true);

    Stiffness = nAttr.create("Stiffness", "st", MFnNumericData::kFloat, 1.0);
    nAttr.setChannelBox(true);
    nAttr.setMin(0.0f);
    nAttr.setMax(1.0f);
    
    Mass = nAttr.create("Mass", "mas", MFnNumericData::kFloat, 1.0);
    nAttr.setChannelBox(true);
    nAttr.setMin(0.0);
    nAttr.setMax(10.0);

    Mode = eAttr.create("Mode", "mod", 0);
    eAttr.setStorable(true);
    eAttr.setKeyable(true);
    eAttr.addField("Rigid", 0);
    eAttr.addField("Linear", 1);
    eAttr.addField("Quadratic", 2);

    GravityX = nAttr.create("GravityX", "gx", MFnNumericData::kFloat, 0.0f);
    nAttr.setMin(-10.0f);
    nAttr.setMax(10.0f);

    GravityY = nAttr.create("GravityY", "gy", MFnNumericData::kFloat, -9.8f);
    nAttr.setMin(-10.0f);
    nAttr.setMax(10.0f);
    
    GravityZ = nAttr.create("GravityZ", "gz", MFnNumericData::kFloat, 0.0f);
    nAttr.setMin(-10.0f);
    nAttr.setMax(10.0f);

    Beta = nAttr.create("Beta", "ba", MFnNumericData::kFloat, 0.2f);
    nAttr.setMin(0.0f);
    nAttr.setMax(1.0f);
    // add attributes
    addAttribute(CurrentTime);
    addAttribute(Stiffness);
    addAttribute(Mass);
    addAttribute(Mode);
    addAttribute(GravityX);
    addAttribute(GravityY);
    addAttribute(GravityZ);
    addAttribute(Beta);
    // affecting - dependencies 
    // input - output 
    attributeAffects(CurrentTime, outputGeom);
    attributeAffects(Stiffness, outputGeom);
    attributeAffects(Mass, outputGeom);
    attributeAffects(Mode, outputGeom);
    attributeAffects(GravityX, outputGeom);
    attributeAffects(GravityY, outputGeom);
    attributeAffects(GravityZ, outputGeom);
    attributeAffects(Beta, outputGeom);
    return MStatus::kSuccess;
}
///-----------------------------------------
MStatus DeformerNode::deform(MDataBlock& block, MItGeometry& iter, const MMatrix& localToWorldMatrix, unsigned int multiIndex)
{
    // if first frame set up the values 
    MTime time_now = block.inputValue(CurrentTime).asTime();
    if(isFirstFrame || time_now.value() == 1)
    {
       if(ps)
           delete ps;
        std::vector<glm::vec3> initial_positions_list; 
        // initial velocity ? init 
        // iterate through ever point of the mesh and set it to the initial position 
        PreviousTime = block.inputValue(CurrentTime).asTime();
        for(; !iter.isDone(); iter.next())
        {
            // posintions in world coordinates 
            MPoint vertexPosition = iter.position() * localToWorldMatrix; 
            glm::vec3 pposition(vertexPosition.x, vertexPosition.y, vertexPosition.z);
            initial_positions_list.emplace_back(pposition);
        }
        // create particle system - deformable object
        ps = new DeformableObject(initial_positions_list);
        // set firstFrame to false 
        isFirstFrame = false; 
        return MS::kSuccess;
    }
    else
    {

        // fetch attriute values 
        time_now = block.inputValue(CurrentTime).asTime(); 
        MTime delta_time = time_now - PreviousTime; 
        PreviousTime = time_now;
        // for particle in deformable object
        // set attributes
        ps->setMode(block.inputValue(Mode).asInt());
        ps->setParameters(block.inputValue(Mass).asFloat(), glm::vec3(block.inputValue(GravityX).asFloat(), block.inputValue(GravityY).asFloat(), block.inputValue(GravityZ).asFloat()));
        float stiffness =block.inputValue(Stiffness).asFloat(); 
        ps->setBeta(block.inputValue(Beta).asFloat());
        if(ps)
        {
            float deltaTimeValue = delta_time.value();
            int updatesPerTimeStep = 2; 
            for(int i =0; i < abs(deltaTimeValue) * updatesPerTimeStep; ++i)
            {
                // update and shape match  
                ps->update(1/24.0/updatesPerTimeStep * SIGN(deltaTimeValue));
                ps->shapematching(1/24.0/updatesPerTimeStep * SIGN(deltaTimeValue), stiffness);
            }
        }
        else
        {
            MGlobal::displayInfo("ps==NULL");
        }

        // update output positions 
        MMatrix localToWoldMatrixInv = localToWorldMatrix.inverse();
        for(; !iter.isDone(); iter.next())
        {
            int idx = iter.index();
            glm::vec3 particlePos = ps->getListOfParticles()[idx].getCurrentPosition();
            MPoint newPos(particlePos.x, particlePos.y, particlePos.z); 
            iter.setPosition(newPos * localToWoldMatrixInv);
        }
    }
    return MS::kSuccess;
}
