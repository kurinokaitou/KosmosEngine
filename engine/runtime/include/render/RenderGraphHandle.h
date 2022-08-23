#ifndef RENDER_GRAPH_HANDLE
#define RENDER_GRAPH_HANDLE
#include <limits>
namespace Kosmos::Runtime::RDG {
struct ResourceSlot {
    uint32_t rid = 0;  // resource id;
    uint32_t nid = 0;  // node id;
    uint32_t pid = -1; // node id of parents
};

// 用于指向resourceSlot的句柄
class RenderGraphHandle {
    friend class RenderGraph;
    friend class DependencyGraph;
    friend class ResourceNode;
    friend class PassNode;
    using Index = size_t;

private:
    static const Index UNINITIALIZED = std::numeric_limits<Index>::max();
    Index index{UNINITIALIZED};

public:
    RenderGraphHandle() = default;
    explicit RenderGraphHandle(Index idx) :
        index(idx) {}
    RenderGraphHandle(const RenderGraphHandle& handle) = default;
    RenderGraphHandle& operator=(const RenderGraphHandle& handle) = default;
    bool isInitialized() const { return index != UNINITIALIZED; }
    void clear() { index = UNINITIALIZED; }
    operator bool() const { return isInitialized(); }
    bool operator<(const RenderGraphHandle& rhs) {
        return (index < rhs.index);
    }
    bool operator>(const RenderGraphHandle& rhs) {
        return (index > rhs.index);
    }
    bool operator==(const RenderGraphHandle& rhs) {
        return (index == rhs.index);
    }
    bool operator!=(const RenderGraphHandle& rhs) {
        return (index != rhs.index);
    }
};
} // namespace Kosmos::Runtime::RDG
#endif // RENDER_GRAPH_HANDLE