#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H
#include <render/vulkan/swapchain.h>
#include <render/vulkan/instance.h>
#include <render/vulkan/device.h>
#include <render/vulkan/surface.h>
#include <render/vulkan/command_pool.h>
#include <render/renderer.h>
namespace Kosmos::Runtime::Vulkan {
class VulkanRenderer : public Renderer {
private:
    std::unique_ptr<Instance> m_instance;
    std::unique_ptr<Surface> m_surface;
    std::unique_ptr<Device> m_device;
    std::unique_ptr<Swapchain> m_swapchain;
    std::unique_ptr<CommandPool> m_commandPool;

public:
    VulkanRenderer(std::shared_ptr<Window> window);
    ~VulkanRenderer();
};
} // namespace Kosmos::Runtime::Vulkan
#endif // VULKAN_RENDERER_H