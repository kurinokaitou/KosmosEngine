#include <render/ResourceNode.h>
#include <render/RenderGraph.h>
using namespace Kosmos::Runtime::RDG;

ResourceNode::ResourceNode(RenderGraph& rdg, RenderGraphHandle parent) :
    Node(rdg.getDepGraph()), m_rdgRef(rdg), m_parentHandle(parent) {}

void ResourceNode::setInwardEdge(const std::shared_ptr<Edge> edge) {
    m_writerPassEdge = edge;
}

void ResourceNode::addOutwardEdge(const std::shared_ptr<Edge> edge) {
    m_readerPassEdges.push_back(edge);
}

std::optional<std::shared_ptr<ResourceNode>> ResourceNode::getParentNode() {
    if (m_parentHandle.isInitialized()) {
        return m_rdgRef.getResourceNode(m_parentHandle);
    } else {
        return std::nullopt;
    }
}

std::optional<std::shared_ptr<ResourceNode>> ResourceNode::getAncestorNode(std::shared_ptr<ResourceNode> node) {
    auto ancestor = node;
    while (true) {
        auto parent = ancestor->getParentNode();
        if (parent.has_value()) {
            ancestor = parent.value();
        } else {
            break;
        }
    }
    return ancestor;
}

void ResourceNode::setParentReadDependency(std::shared_ptr<ResourceNode> parent) {
    if (!m_parentReadEdge) {
        m_parentReadEdge = std::make_shared<Edge>(m_rdgRef.getDepGraph(), parent, shared_from_this());
    }
}

void ResourceNode::setParentWriteDependency(std::shared_ptr<ResourceNode> parent) {
    if (!m_parentWriteEdge) {
        m_parentWriteEdge = std::make_shared<Edge>(m_rdgRef.getDepGraph(), shared_from_this(), parent);
    }
}