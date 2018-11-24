#ifndef _DEFORMERNODE_H_
#define _DEFORMERNODE_H_

#include <maya/MPxDeformerNode.h>
#include <maya/MTypeId.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MDataBlock.h>
#include <maya/MPoint.h>
#include <maya/MTime.h>

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
        static MObject m_stiffness; 
        static bool m_isFirstFrame; 
        static MObject CurrentTime;
        static MTime m_previousTime;
};

#endif // _DEFORMERNODE_H_
