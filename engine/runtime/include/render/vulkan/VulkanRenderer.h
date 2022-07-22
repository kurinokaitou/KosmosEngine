#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H
#include <render/vulkan/Swapchain.h>
#include <render/vulkan/Instance.h>
#include <render/vulkan/Device.h>
#include <render/vulkan/Surface.h>
#include <render/vulkan/CommandPool.h>
#include <render/Renderer.h>
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