#include "stdafx.h"
#include "OlcbpPlanGraphAdapter.h"
#include "IStrategizerException.h"
#include "PlanGraphNode.h"

using namespace IStrategizer;

OlcbpPlanGraphAdapter::NodeID OlcbpPlanGraphAdapter::AddNode(NodeValue id)
{
    throw NotImplementedException(XcptHere);
}

void OlcbpPlanGraphAdapter::RemoveNode(NodeID id)
{
    throw NotImplementedException(XcptHere);
}

void OlcbpPlanGraphAdapter::AddEdge(NodeID sourceNodeId, NodeID destNodeId)
{
    throw NotImplementedException(XcptHere);
}

void OlcbpPlanGraphAdapter::RemoveEdge(NodeID sourceNodeId, NodeID destNodeId)
{
    throw NotImplementedException(XcptHere);
}

OlcbpPlanGraphAdapter::NodeValue OlcbpPlanGraphAdapter::GetNode(NodeID id)
{
    return m_adaptee.Plan()[id]->PlanStep();
}

OlcbpPlanGraphAdapter::NodeSet OlcbpPlanGraphAdapter::GetNodes() const
{
    NodeSet nodes;

    for each (pair<NodeID, PlanGraphNode*> node in m_adaptee.Plan())
    {
        nodes.insert(node.first);
    }

    return nodes;
}

bool OlcbpPlanGraphAdapter::IsAdjacent(NodeID sourceNodeId, NodeID destNodeId) const
{
    const PlanGraphNode::List& sourceNodeChildren = m_adaptee.Plan()[sourceNodeId]->Children();

    return count_if(sourceNodeChildren.begin(), sourceNodeChildren.end(), 
        [destNodeId](const PlanGraphNode* other) { return other->Id() == destNodeId; }) > 0;
}

OlcbpPlanGraphAdapter::NodeSet OlcbpPlanGraphAdapter::GetAdjacentNodes(NodeID sourceNodeId) const
{
    NodeSet nodes;
    const PlanGraphNode::List& sourceNodeChildren = m_adaptee.Plan()[sourceNodeId]->Children();

    for each (PlanGraphNode* node in sourceNodeChildren)
        nodes.insert(node->Id());

    return nodes;
}

OlcbpPlanGraphAdapter::NodeSet OlcbpPlanGraphAdapter::GetOrphanNodes() const
{
    NodeSet nodes;

    nodes.insert(m_adaptee.PlanRoot()->Id());

    return nodes;
}
