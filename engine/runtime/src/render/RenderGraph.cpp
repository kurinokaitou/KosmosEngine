#include <render/RenderGraph.h>

using namespace Kosmos::Runtime::RDG;

void RenderGraph::compile() {
}

void RenderGraph::execute() {
}

const ResourceSlot& RenderGraph::getResourceSlot(RenderGraphHandle handle) {
    return m_resourceSlots[handle.index];
}

std::shared_ptr<ResourceNode> RenderGraph::getResourceNode(RenderGraphHandle handle) {
    auto& slot = getResourceSlot(handle);
    return m_resourceNodes[slot.nid];
}

std::shared_ptr<VirtualResource> RenderGraph::getResource(RenderGraphHandle handle) {
    auto& slot = getResourceSlot(handle);
    return m_resources[slot.rid];
}