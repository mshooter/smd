#ifndef _DEFORMERNODE_H_
#define _DEFORMERNODE_H_

#include <maya/MPxDeformerNode.h>

class DeformerNode : public MPxDeformerNode
{
    public:
        DeformerNode() = default;
        static void* creator();
        static MStatus initialize();

        static MTypeId id; 
    protected:
    private:
};

#endif // _DEFORMERNODE_H_
