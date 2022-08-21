#ifndef RESOURCE_NODE_H
#define RESOURCE_NODE_H
#include "DependencyGraph.h"
namespace Kosmos::Runtime::RenderGraph {
	// ���ڼ�¼resource������resource node֮���Ӧ��ϵ�Ĳ�ۣ�ÿһ����۶�Ӧһ�ֹ�ϵ
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