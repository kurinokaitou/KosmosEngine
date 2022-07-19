#include <memory>
#include <render/renderer.h>
using namespace Kosmos::Runtime;

Renderer::Renderer(std::shared_ptr<Window> window) :
    m_window(window) {}