#include <render/glfw_window.h>
#include <render/vulkan/vulkan_renderer.h>
using namespace Kosmos::Runtime::Vulkan;
VulkanRenderer::VulkanRenderer(std::shared_ptr<Window> window) :
    Renderer(window) {
    // TODO: Read from config
    std::string engineName = "KosmosEngine";
    std::string appName = "Kosmos";
    uint32_t engineVersion = VK_MAKE_VERSION(0, 0, 1);
    uint32_t appVersion = VK_MAKE_VERSION(0, 0, 1);
    std::vector<const char*> wishLayers{};
    std::vector<const char*> wishExtentions{};

    m_instance = std::make_unique<Instance>(engineName, appName, engineVersion, appVersion, true, false, wishLayers, wishExtentions);
    m_surface = std::make_unique<Surface>(m_instance->getVkInstance(), reinterpret_cast<GLFWwindow*>(m_window->getWindowPtr()));
    m_device = std::make_unique<Device>(m_instance->getVkInstance(), m_surface->getSurface(), false, true);
    auto [width, height] = m_window->getWindowSize();
    m_swapchain = std::make_unique<Swapchain>(*m_device, m_surface->getSurface(), width, height, "defaultSwapchain");
    m_commandPool = std::make_unique<CommandPool>(*m_device, m_device->getQueueFamiliyIndices().graphicsFamily.value(), "defaultCommandPool");
}

VulkanRenderer::~VulkanRenderer() {
    if (m_device == nullptr) {
        return;
    }
    vkDeviceWaitIdle(m_device->getLogicalDevice());
    KS_ENGINE_LOG_TRACE("Renderer has destroyed.");
}