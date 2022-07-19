#ifndef RENDERER_H
#define RENDERER_H
#include <core/window.h>
#include "render_graph.h"
#include <memory>
namespace Kosmos::Runtime {

class Renderer {
private:
    std::shared_ptr<Window> m_window;
    std::unique_ptr<RenderGraph> m_renderGraph;

public:
    Renderer(std::shared_ptr<Window> window);
    virtual ~Renderer() {}
};
} // namespace Kosmos::Runtime
#endif // RENDERER_H