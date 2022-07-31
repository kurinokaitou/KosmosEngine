#include <algorithm>
#include <stack>
#include <render/DependencyGraph.h>
using namespace Kosmos::Runtime::RenderGraph;
DependencyGraph::DependencyGraph() {
    m_nodes.reserve(8);
    m_edges.reserve(16);
}

void DependencyGraph::typologyCull() {
    std::stack<Node*> culledStack;
    for (auto node : m_nodes) {
        if (node->getRefCount() == 0) {
            culledStack.push(node);
        }
    }
    while (!culledStack.empty()) {
        auto node = culledStack.top();
        culledStack.pop();
        auto inwardEdges = getNodeInwardEdges(node);
        for (auto edge : inwardEdges) {
            auto fromNode = m_nodes[edge->m_fromNode];
            if (--fromNode->m_refCount == 0) {
                culledStack.push(fromNode);
            }
        }
    }
}
void DependencyGraph::clear() {
    m_edges.clear();
    m_nodes.clear();
}
void DependencyGraph::exportGraphviz() {
    // TODO: implement graphviz
}
bool DependencyGraph::isEdgeValid(const Edge* edge) {
    auto fromNode = m_nodes[edge->m_fromNode];
    auto toNode = m_nodes[edge->m_toNode];
    return !fromNode->isCulled() && !toNode->isCulled();
}
std::vector<DependencyGraph::Edge*> DependencyGraph::getNodeInwardEdges(const Node* node) {
    std::vector<Edge*> inward;
    NodeHandle handle = node->getNodeHandle();
    std::copy_if(m_edges.begin(), m_edges.end(), inward.begin(), [handle](Edge* edge) {
        return edge->m_toNode == handle;
    });
    return inward;
}
std::vector<DependencyGraph::Edge*> DependencyGraph::getNodeOutwardEdges(const Node* node) {
    std::vector<Edge*> outward;
    NodeHandle handle = node->getNodeHandle();
    std::copy_if(m_edges.begin(), m_edges.end(), outward.begin(), [handle](Edge* edge) {
        return edge->m_fromNode == handle;
    });
    return outward;
}

void DependencyGraph::registerNode(Node* node) {
    m_nodes.push_back(node);
}
void DependencyGraph::registerEgde(Edge* edge) {
    m_nodes[edge->m_fromNode]->m_refCount++;
    m_edges.push_back(edge);
}