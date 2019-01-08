#include "DeformerNode.h"
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MAnimControl.h>
#include <maya/MGlobal.h>

#define SIGN(a) (a < 0 ? -1 : 1)

MTypeId DeformerNode::id(0x0100F);
bool DeformerNode::isFirstFrame;
MObject DeformerNode::CurrentTime; 
MObject DeformerNode::Mode;
MObject DeformerNode::Mass; 
MObject DeformerNode::Stiffness;
MObject DeformerNode::Beta;
MObject DeformerNode::Velocity;
MObject DeformerNode::Friction;
MObject DeformerNode::Elasticity;
MObject DeformerNode::Bounciness;
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
    uAttr.setHidden(true);

    Mode = eAttr.create("Mode", "mod", 0);
    eAttr.setStorable(true);
    eAttr.setKeyable(true);
    eAttr.addField("Rigid", 0);
    eAttr.addField("Linear", 1);
    eAttr.addField("Quadratic", 2);

    Mass = nAttr.create("Mass", "mas", MFnNumericData::kFloat, 1.0);
    nAttr.setMin(0.0);
    nAttr.setMax(10.0);

    Stiffness = nAttr.create("Stiffness", "st", MFnNumericData::kFloat, 1.0);
    nAttr.setMin(0.0f);
    nAttr.setMax(1.0f);
    
    Beta = nAttr.create("Beta", "ba", MFnNumericData::kFloat, 0.0f);
    nAttr.setMin(0.0f);
    nAttr.setMax(1.0f);

    Friction = nAttr.create("Friction", "fr", MFnNumericData::kFloat, 0.5f);
    nAttr.setMin(0.0f);
    nAttr.setMax(1.0f);
    
    Elasticity = nAttr.create("Elasticity", "el", MFnNumericData::kFloat, 0.5f);
    nAttr.setMin(0.0f);
    nAttr.setMax(1.0f);
    
    Bounciness = nAttr.create("Bounciness", "bs", MFnNumericData::kFloat, 0.5f);
    nAttr.setMin(0.0f);
    nAttr.setMax(1.0f);

    MObject velx = nAttr.create( "velx", "vx", MFnNumericData::kFloat, 0.0f );
    MObject vely = nAttr.create( "vely", "vy", MFnNumericData::kFloat, 0.0f );
    MObject velz = nAttr.create( "velz", "vz", MFnNumericData::kFloat, 0.0f );
    Velocity = nAttr.create("Velocity", "v", velx, vely, velz);
    nAttr.setMin(-10.0f);
    nAttr.setMax(10.0f);

    // add attributes
    addAttribute(CurrentTime);
    addAttribute(Mode);
    addAttribute(Mass);
    addAttribute(Stiffness);
    addAttribute(Beta);
    addAttribute(Friction);
    addAttribute(Elasticity);
    addAttribute(Bounciness);
    addAttribute(Velocity);

    // affecting - dependencies 
    // input - output 
    attributeAffects(CurrentTime, outputGeom);
    attributeAffects(Mode, outputGeom);
    attributeAffects(Mass, outputGeom);
    attributeAffects(Stiffness, outputGeom);
    attributeAffects(Beta, outputGeom);
    attributeAffects(Friction, outputGeom);
    attributeAffects(Elasticity, outputGeom);
    attributeAffects(Bounciness, outputGeom);
    attributeAffects(Velocity, outputGeom);

    return MStatus::kSuccess;
}
///-----------------------------------------
MStatus DeformerNode::deform(MDataBlock& block, MItGeometry& iter, const MMatrix& localToWorldMatrix, unsigned int multiIndex)
{
    // if first frame set up the values 
    MTime time_now = block.inputValue(CurrentTime).asTime();
    const float3 & velocity = block.inputValue(Velocity).asFloat3();
    if(isFirstFrame || time_now.value() == 1)
    {
       if(ps)
           delete ps;
        std::vector<glm::vec3> initial_positions_list; 
        PreviousTime = block.inputValue(CurrentTime).asTime();
        for(; !iter.isDone(); iter.next())
        {
            MPoint vertexPosition = iter.position() * localToWorldMatrix; 
            glm::vec3 pposition(vertexPosition.x, vertexPosition.y, vertexPosition.z);
            initial_positions_list.emplace_back(pposition);
        }
        // create particle system - deformable object
        ps = new DeformableObject(initial_positions_list, glm::vec3(velocity[0], velocity[1], velocity[2]));
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
        ps->setParameters(block.inputValue(Mass).asFloat());
        float stiffness =block.inputValue(Stiffness).asFloat(); 
        ps->setBeta(block.inputValue(Beta).asFloat());
        std::vector<float> impulse(2); 
        // coll = elasticity first
        impulse[0] = block.inputValue(Elasticity).asFloat();
        impulse[1] = block.inputValue(Friction).asFloat();
        float bounce = block.inputValue(Bounciness).asFloat();
        if(ps)
        {
            float deltaTimeValue = delta_time.value();
            int updatesPerTimeStep = 2; 
            for(int i =0; i < abs(deltaTimeValue) * updatesPerTimeStep; ++i)
            {
                // update and shape match  
                ps->update(1/24.0/updatesPerTimeStep * SIGN(deltaTimeValue), impulse);
                ps->shapematching(1/24.0/updatesPerTimeStep * SIGN(deltaTimeValue), stiffness, bounce);
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
