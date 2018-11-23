#include "DeformerNode.h"

MTypeId DeformerNode::id(0x03005001);

void* DeformerNode::creator()
{
    return new DeformerNode;
}

