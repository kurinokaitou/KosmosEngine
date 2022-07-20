#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H
#include <render/vulkan/surface.h>
#include <render/vulkan/instance.h>
#include <render/renderer.h>
namespace Kosmos::Runtime::Vulkan {
class Instance;
class Surface;
class VulkanRenderer : public Renderer {
private:
    std::unique_ptr<Instance> m_instance;
    std::unique_ptr<Surface> m_surface;

public:
    VulkanRenderer(std::shared_ptr<Window> window);
};
} // namespace Kosmos::Runtime::Vulkan
#endif // VULKAN_RENDERER_H