#include "stdafx.h"
#include "PlanGraphAdapter.h"
#include "IStrategizerException.h"
#include "PlanGraph.h"

using namespace IStrategizer;


PlanGraphAdapter::NodeID PlanGraphAdapter::AddNode(NodeValue id)
{
    throw NotImplementedException(XcptHere);
}

void PlanGraphAdapter::RemoveNode(NodeID id)
{
    throw NotImplementedException(XcptHere);
}

void PlanGraphAdapter::AddEdge(NodeID sourceNodeId, NodeID destNodeId)
{
    throw NotImplementedException(XcptHere);
}

void PlanGraphAdapter::RemoveEdge(NodeID sourceNodeId, NodeID destNodeId)
{
    throw NotImplementedException(XcptHere);
}

NodeValue PlanGraphAdapter::GetNode(NodeID id)
{
    return m_pAdaptee->At((int)id)->Value();
}

PlanGraphAdapter::NodeSet PlanGraphAdapter::GetNodes() const
{
    NodeSet nodes;

    for (size_t i = 0; i < m_pAdaptee->Size(); ++i)
    {
        nodes.insert((NodeID)i);
    }

    return nodes;
}

bool PlanGraphAdapter::IsAdjacent(NodeID sourceNodeId, NodeID destNodeId) const
{
    return m_pAdaptee->IsConnected((int)sourceNodeId, (int)destNodeId);
}

PlanGraphAdapter::NodeSet PlanGraphAdapter::GetAdjacentNodes(NodeID sourceNodeId) const
{
    NodeSet nodes;

    for each (int nodeIdx in m_pAdaptee->GetChildren(sourceNodeId))
        nodes.insert((NodeID)nodeIdx);

    return nodes;
}

PlanGraphAdapter::NodeSet PlanGraphAdapter::GetOrphanNodes() const
{
    NodeSet nodes;

    for each (int nodeIdx in m_pAdaptee->GetRoots())
        nodes.insert((NodeID)nodeIdx);

    return nodes;
}
