#include "stdafx.h"
#include "PlanGraphAdapter.h"
#include "IStrategizerException.h"
#include "PlanGraph.h"

using namespace IStrategizer;
using namespace std;

PlanGraphAdapter::PlanGraphAdapter(PlanGraph* pAdaptee)
: m_pAdaptee(pAdaptee)
{
    m_lastNodeID = 0;

    // A non empty graph, we need to construct our nodeId to nodeIdx mapping
    if (m_pAdaptee->Size() > 0)
    {
        for (size_t nodeIdx = 0; nodeIdx < m_pAdaptee->Size(); ++nodeIdx)
        {
            m_nodeIdToAdjMatrixIdx[++m_lastNodeID] = nodeIdx;
        }
    }
}

PlanGraphAdapter::NodeID PlanGraphAdapter::AddNode(NodeValue val)
{
    NodeID nodeId = ++m_lastNodeID;

    m_nodeIdToAdjMatrixIdx[nodeId] = m_pAdaptee->AddNode(val, m_pAdaptee->Size());

    return nodeId;
}

void PlanGraphAdapter::RemoveNode(NodeID id)
{
    if (m_nodeIdToAdjMatrixIdx.count(id) == 0)
        throw ItemNotFoundException(XcptHere);

    size_t nodeIdx = m_nodeIdToAdjMatrixIdx[id];
    m_pAdaptee->RemoveNode(nodeIdx);
    m_nodeIdToAdjMatrixIdx.erase(id);

    // Update indices of nodes after the removed node
    for (map<NodeID, size_t>::iterator itr = m_nodeIdToAdjMatrixIdx.begin();
        itr != m_nodeIdToAdjMatrixIdx.end(); ++itr)
    {
        if (itr->second > nodeIdx)
            --itr->second;
    }
}

void PlanGraphAdapter::AddEdge(NodeID sourceNodeId, NodeID destNodeId)
{
    if (m_nodeIdToAdjMatrixIdx.count(sourceNodeId) == 0 ||
        m_nodeIdToAdjMatrixIdx.count(destNodeId) == 0)
        throw ItemNotFoundException(XcptHere);

    m_pAdaptee->Connect(m_nodeIdToAdjMatrixIdx[sourceNodeId], m_nodeIdToAdjMatrixIdx[destNodeId], EdgeAnnotation());
}

void PlanGraphAdapter::RemoveEdge(NodeID sourceNodeId, NodeID destNodeId)
{
    if (m_nodeIdToAdjMatrixIdx.count(sourceNodeId) == 0 ||
        m_nodeIdToAdjMatrixIdx.count(destNodeId) == 0)
        throw ItemNotFoundException(XcptHere);

    m_pAdaptee->Disconnect(m_nodeIdToAdjMatrixIdx[sourceNodeId], m_nodeIdToAdjMatrixIdx[destNodeId]);
}

PlanGraphAdapter::NodeValue PlanGraphAdapter::GetNode(NodeID id)
{
    if (m_nodeIdToAdjMatrixIdx.count(id) == 0)
        return nullptr;

    return m_pAdaptee->At(m_nodeIdToAdjMatrixIdx[id])->Value();
}

PlanGraphAdapter::NodeSet PlanGraphAdapter::GetNodes() const
{
    NodeSet nodes;

    for each (auto nodeEntry in m_nodeIdToAdjMatrixIdx)
    {
        nodes.insert(nodeEntry.first);
    }

    return nodes;
}

bool PlanGraphAdapter::IsAdjacent(NodeID sourceNodeId, NodeID destNodeId) const
{
    if (m_nodeIdToAdjMatrixIdx.count(sourceNodeId) == 0 ||
        m_nodeIdToAdjMatrixIdx.count(destNodeId) == 0)
        throw ItemNotFoundException(XcptHere);

    return m_pAdaptee->IsConnected(m_nodeIdToAdjMatrixIdx.at(sourceNodeId), m_nodeIdToAdjMatrixIdx.at(destNodeId)) == CONNECTED;
}

PlanGraphAdapter::NodeSet PlanGraphAdapter::GetAdjacentNodes(NodeID sourceNodeId) const
{
    if (m_nodeIdToAdjMatrixIdx.count(sourceNodeId) == 0)
        throw ItemNotFoundException(XcptHere);

    NodeSet nodes;
    vector<int> children = m_pAdaptee->GetChildren(m_nodeIdToAdjMatrixIdx.at(sourceNodeId));

    for each (auto nodeIdx in children)
        nodes.insert(GetNodeIdFromIdx(nodeIdx));

    return nodes;
}

PlanGraphAdapter::NodeSet PlanGraphAdapter::GetOrphanNodes() const
{
    NodeSet nodes;

    vector<int> roots = m_pAdaptee->GetRoots();

    for each (auto nodeIdx in roots)
    {
        nodes.insert(GetNodeIdFromIdx(nodeIdx));
    }

    return nodes;
}

PlanGraphAdapter::NodeID PlanGraphAdapter::GetNodeIdFromIdx(size_t nodeIdx) const
{
    for each (auto nodeEntry in m_nodeIdToAdjMatrixIdx)
    {
        if (nodeEntry.second == nodeIdx)
            return nodeEntry.first;
    }

    throw ItemNotFoundException(XcptHere);
}