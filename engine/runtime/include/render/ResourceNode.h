#ifndef RESOURCE_NODE_H
#define RESOURCE_NODE_H
#include "DependencyGraph.h"
namespace Kosmos::Runtime::RenderGraph {
	// 用于记录resource本身与resource node之间对应关系的插槽，每一个插槽对应一种关系
struct ResourceSlot{
	uint32_t rid = 0; // resource id;
    uint32_t nid = 0;	// node id;
    uint32_t pid = -1;  // node id of parents
 };
class Edge;
class ResourceNode : public DependencyGraph::Node {
private:
    Edge* m_writerPassEdge;
    std::vector<Edge*> m_readerPassEdges;
 };
} // namespace Kosmos::Runtime::RenderGraph
#endif // RESOURCE_NODE_H