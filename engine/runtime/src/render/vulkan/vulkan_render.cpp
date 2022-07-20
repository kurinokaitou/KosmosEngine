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
    auto glfwWindow = std::dynamic_pointer_cast<GlfwWindow>(window);

    m_instance = std::make_unique<Instance>(engineName, appName, engineVersion, appVersion, true, false, wishLayers, wishExtentions);
    m_surface = std::make_unique<Surface>(m_instance->getVkInstance(), glfwWindow->getWindow());
}