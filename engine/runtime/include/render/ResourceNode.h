#ifndef RESOURCE_NODE_H
#define RESOURCE_NODE_H
#include "DependencyGraph.h"
#include "RenderGraphHandle.h"
#include <optional>
namespace Kosmos::Runtime::RDG {

class RenderGraph;
class ResourceNode : public DependencyGraph::Node, public std::enable_shared_from_this<ResourceNode> {
    friend class RenderGraph;
    using Edge = DependencyGraph::Edge;

private:
    RenderGraph& m_rdgRef;
    const RenderGraphHandle m_parentHandle;
    const RenderGraphHandle m_handle;
    std::shared_ptr<Edge> m_parentWriteEdge;
    std::shared_ptr<Edge> m_parentReadEdge;
    std::shared_ptr<Edge> m_writerPassEdge;
    std::vector<std::shared_ptr<Edge>> m_readerPassEdges;

public:
    ResourceNode(RenderGraph& rdg, RenderGraphHandle parent = RenderGraphHandle{});
    ~ResourceNode() = default;
    void setInwardEdge(const std::shared_ptr<Edge> edge);
    void addOutwardEdge(const std::shared_ptr<Edge> edge);
    std::optional<std::shared_ptr<ResourceNode>> getParentNode();
    void setParentReadDependency(std::shared_ptr<ResourceNode> parent);
    void setParentWriteDependency(std::shared_ptr<ResourceNode> parent);

    static std::optional<std::shared_ptr<ResourceNode>> getAncestorNode(std::shared_ptr<ResourceNode> node);

private:
    ResourceNode(const ResourceNode& node) = delete;
    ResourceNode& operator=(const ResourceNode& node) = delete;
};
} // namespace Kosmos::Runtime::RDG
#endif // RESOURCE_NODE_H