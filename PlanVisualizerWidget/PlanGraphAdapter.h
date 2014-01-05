#ifndef PLANGRAPHADAPTER_H
#define PLANGRAPHADAPTER_H

#include "IDigraph.h"
#include "PlanStepEx.h"

namespace IStrategizer
{
    class PlanGraph;

    class PlanGraphAdapter : public IDigraph<PlanStepEx*>
    {
    public:
        PlanGraphAdapter(PlanGraph* pAdaptee)
            : m_pAdaptee(pAdaptee)
        { }

        ~PlanGraphAdapter() {}

        NodeID AddNode(NodeValue val);

        void RemoveNode(NodeID id);

        void AddEdge(NodeID sourceNodeId, NodeID destNodeId);

        void RemoveEdge(NodeID sourceNodeId, NodeID destNodeId);

        NodeValue GetNode(NodeID id);

        NodeSet GetNodes() const;

        bool IsAdjacent(NodeID sourceNodeId, NodeID destNodeId) const;

        NodeSet GetAdjacentNodes(NodeID sourceNodeId) const;

        NodeSet GetOrphanNodes() const;

    private:
        PlanGraph* m_pAdaptee;
    };
}
#endif // PLANGRAPHADAPTER_H