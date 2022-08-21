#ifndef RENDER_GRAPH_H
#define RENDER_GRAPH_H
#include <render/vulkan/Utils.h>
#include <render/DependencyGraph.h>
#include <render/ResourceNode.h>
#include <render/Resource.h>
namespace Kosmos::Runtime::RenderGraph {
class RenderGraph {

private:
    std::unique_ptr<DependencyGraph> m_graph;
    std::vector<ResourceSlot> m_resourceSlots;
    std::vector<ResourceNode*> m_resourceNodes;
    std::vector<VirtualResource*> m_resources;

public:
    void compile();
    void execute();
};
} // namespace Kosmos::Runtime
#endif // RENDER_GRAPH_H