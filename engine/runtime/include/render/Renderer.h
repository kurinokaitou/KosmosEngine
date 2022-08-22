#ifndef RENDERER_H
#define RENDERER_H
#include <core/Window.h>
#include "RenderGraph.h"
#include <memory>
namespace Kosmos::Runtime {

class Renderer {
protected:
    std::shared_ptr<Window> m_window;
    std::unique_ptr<RenderGraph::RenderGraph> m_renderGraph;

public:
    Renderer(std::shared_ptr<Window> window);
    virtual ~Renderer() {}

    static VkSampleCountFlagBits s_msaaSampleCount;
};
} // namespace Kosmos::Runtime
#endif // RENDERER_H