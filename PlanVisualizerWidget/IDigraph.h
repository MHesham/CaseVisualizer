#ifndef IPLANGRAPH_H
#define IPLANGRAPH_H

#include <set>

namespace IStrategizer
{
    template<class TNodeValue>
    class IDigraph
    {
    public:
        typedef unsigned NodeID;
        typedef TNodeValue NodeValue;
        typedef std::set<NodeID> NodeSet;

        virtual ~IDigraph() {};

        virtual NodeID AddNode(NodeValue val) = 0;
        virtual void RemoveNode(NodeID id) = 0;
        virtual void AddEdge(NodeID sourceNodeId, NodeID destNodeId) = 0;
        virtual void RemoveEdge(NodeID sourceNodeId, NodeID destNodeId) = 0;
        virtual NodeValue GetNode(NodeID id) = 0;
        virtual NodeSet GetNodes() const = 0;
        virtual bool IsAdjacent(NodeID sourceNodeId, NodeID destNodeId) const = 0;
        virtual NodeSet GetAdjacentNodes(NodeID sourceNodeId) const = 0;
        virtual NodeSet GetOrphanNodes() const = 0;
    };
}

#endif // IPLANGRAPH_H