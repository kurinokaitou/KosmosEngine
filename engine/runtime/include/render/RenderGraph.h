#ifndef RENDER_GRAPH_H
#define RENDER_GRAPH_H
#include <render/vulkan/Utils.h>
#include <render/DependencyGraph.h>
#include <render/ResourceNode.h>
#include <render/Resource.h>
#include <render/RenderGraphHandle.h>
namespace Kosmos::Runtime::RDG {

class RenderGraph {
    friend class DependencyGraph;
    friend class ResourceNode;

private:
    DependencyGraph m_graph;

    std::vector<ResourceSlot> m_resourceSlots;
    std::vector<std::shared_ptr<ResourceNode>> m_resourceNodes;
    std::vector<std::shared_ptr<VirtualResource>> m_resources;

public:
    RenderGraph() = default;
    DependencyGraph& getDepGraph() { return m_graph; }
    void compile();
    void execute();

private:
    RenderGraph(const RenderGraph& graph) = delete;
    RenderGraph& operator=(const RenderGraph& graph) = delete;
    const ResourceSlot& getResourceSlot(RenderGraphHandle handle);
    std::shared_ptr<ResourceNode> getResourceNode(RenderGraphHandle handle); // 获取的是cull之后的
    std::shared_ptr<VirtualResource> getResource(RenderGraphHandle handle);
};
} // namespace Kosmos::Runtime::RDG
#endif // RENDER_GRAPH_H