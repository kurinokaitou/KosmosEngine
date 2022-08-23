#ifndef RENDER_GRAPH_H
#define RENDER_GRAPH_H
#include <render/vulkan/Utils.h>
#include <render/DependencyGraph.h>
#include <render/ResourceNode.h>
#include <render/Resource.h>
#include <render/RenderGraphHandle.h>
namespace Kosmos::Runtime::RenderGraph {

class RenderGraph {
    friend class DependencyGraph;
    friend class ResourceNode;

private:
    DependencyGraph m_graph;

    std::vector<ResourceSlot> m_resourceSlots;
    std::vector<std::shared_ptr<ResourceNode>> m_resourceNodes;
    std::vector<std::shared_ptr<VirtualResource>> m_resources;

public:
    DependencyGraph& getDepGraph() { return m_graph; }
    void compile();
    void execute();

private:
    const ResourceSlot& getResourceSlot(RenderGraphHandle handle);
    std::shared_ptr<ResourceNode> getInSlotResourceNode(RenderGraphHandle handle);
};
} // namespace Kosmos::Runtime::RenderGraph
#endif // RENDER_GRAPH_H