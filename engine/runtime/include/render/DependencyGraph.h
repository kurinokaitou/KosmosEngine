#ifndef DEPENDENCY_GRAPH_H
#define DEPENDENCY_GRAPH_H
#include <limits>
#include <vector>
#include <string>
#include <cstdint>
#include <memory>
namespace Kosmos::Runtime::RenderGraph {
const static uint32_t INF_REF_COUNT = std::numeric_limits<uint32_t>::max();
class DependencyGraph {
    friend class RenderGraph;
    using NodeHandle = uint32_t;

public:
    class Node {
        friend class DependencyGraph;

    private:
        uint32_t m_refCount{0};
        NodeHandle m_index;
        std::string m_name;

    public:
        Node(DependencyGraph& graph, std::string& name) :
            m_name(name), m_index(graph.newNodeHandle()) {
            graph.registerNode(std::shared_ptr<Node>(this));
        }
        virtual ~Node() = default;
        bool isCulled() const { return m_refCount == 0; }
        void markNeverCull() { m_refCount = INF_REF_COUNT; }
        uint32_t getRefCount() const { return m_refCount; }
        NodeHandle getNodeHandle() const { return m_index; }

    private:
        Node(const Node& node) = delete;
        Node& operator=(const Node& node) = delete;
        Node& operator=(Node&& node) = delete;
    };

    class Edge {
        friend class DependencyGraph;

    private:
        const NodeHandle m_fromNode;
        const NodeHandle m_toNode;

    public:
        Edge(DependencyGraph& graph, Node* from, Node* to) :
            m_fromNode(from->getNodeHandle()), m_toNode(to->getNodeHandle()) {
            graph.registerEgde(std::shared_ptr<Edge>(this));
        }
    };

private:
    std::vector<std::shared_ptr<Node>> m_nodes;
    std::vector<std::shared_ptr<Edge>> m_edges;

public:
    DependencyGraph();
    ~DependencyGraph() = default;
    void typologyCull();
    void clear();
    void exportGraphviz();
    bool isEdgeValid(const Edge* edge);
    std::vector<std::shared_ptr<Edge>> getNodeInwardEdges(const std::shared_ptr<Node> node);
    std::vector<std::shared_ptr<Edge>> getNodeOutwardEdges(const std::shared_ptr<Node> node);
    std::shared_ptr<Node> getNode(NodeHandle handle) { return m_nodes[handle]; };
private:
    void registerNode(const std::shared_ptr<Node> node);
    void registerEgde(const std::shared_ptr<Edge> node);
    NodeHandle newNodeHandle() const { return m_nodes.size(); }

private:
    DependencyGraph(const DependencyGraph& dependency) = delete;
    DependencyGraph(DependencyGraph&& dependency) = delete;
    DependencyGraph& operator=(const DependencyGraph& dependency) = delete;
    DependencyGraph& operator=(DependencyGraph&& dependency) = delete;
};
} // namespace Kosmos::Runtime::RenderGraph
#endif // DEPENDENCY_GRAPH_H