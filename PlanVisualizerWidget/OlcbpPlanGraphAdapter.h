#ifndef OLCBPPLANGRAPHADAPTER_H
#define OLCBPPLANGRAPHADAPTER_H

#include "IDigraph.h"
#include "PlanStepEx.h"
#include "OnlinePlanExpansionExecutionEx.h"

namespace IStrategizer
{
    class PlanGraphNode;

    typedef IDigraph<PlanStepEx*> IPlanDigraph;

    class OlcbpPlanGraphAdapter : public IPlanDigraph
    {
    public:
        OlcbpPlanGraphAdapter(OnlinePlanExpansionExecutionEx& adaptee)
            : m_adaptee(adaptee)
        { }

        ~OlcbpPlanGraphAdapter() {}

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
        OlcbpPlanGraphAdapter(const OlcbpPlanGraphAdapter&);
        OlcbpPlanGraphAdapter& operator = (const OlcbpPlanGraphAdapter&);

        OnlinePlanExpansionExecutionEx& m_adaptee;
    };
}

#endif // OLCBPPLANGRAPHADAPTER_H