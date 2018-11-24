#ifndef _DEFORMERNODE_H_
#define _DEFORMERNODE_H_

#include <maya/MPxGeometryFilter.h>
#include <maya/MTypeId.h>
#include <maya/MItGeometry.h>
#include <maya/MMatrix.h>
#include <maya/MDataBlock.h>
#include <maya/MPoint.h>


class DeformerNode : public MPxGeometryFilter 
{
    public:
        static void* creator();
        static MStatus initialize();
        virtual MStatus deform(MDataBlock& lock, 
                              MItGeometry& iterator, 
                              const MMatrix& matrix, 
                              unsigned int multiIndex);
        static MTypeId id; 
};

#endif // _DEFORMERNODE_H_
