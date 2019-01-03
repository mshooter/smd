#ifndef _DEFORMERNODE_H_
#define _DEFORMERNODE_H_

#include <maya/MPxDeformerNode.h>
#include <maya/MTypeId.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MDataBlock.h>
#include <maya/MPoint.h>
#include <maya/MTime.h>
#include <iostream>
#include "DeformableObject.h"

class DeformerNode : public MPxDeformerNode
{
    public:
        static void* creator();
        static MStatus initialize();
        virtual MStatus deform(MDataBlock& lock, 
                              MItGeometry& iterator, 
                              const MMatrix& matrix, 
                              unsigned int multiIndex);
        static MTypeId id;

        // Attributes
        static MObject Stiffness; 
        static MObject GravityX; 
        static MObject GravityY; 
        static MObject GravityZ; 
        static MObject Mass; 
        static MObject CurrentTime;
        static bool isFirstFrame; 
        static MObject Mode; 
        static MObject Beta;
        static MTime PreviousTime;
        
        static DeformableObject* ps; 
};


#endif // _DEFORMERNODE_H_
