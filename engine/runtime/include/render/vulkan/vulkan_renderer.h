#ifndef VULKAN_RENDERER_H
#define VULKAN_RENDERER_H
#include "vulkan/vulkan_core.h"
#include <memory>
#include <render/vulkan/instance.h>
#include <render/renderer.h>
#include <stdint.h>
#include <vector>
namespace Kosmos::Runtime::Vulkan {
class VulkanRenderer : public Renderer {
private:
    std::unique_ptr<Instance> m_instance;

public:
    VulkanRenderer(std::shared_ptr<Window> window) :
        Renderer(window) {
        // TODO: Read from config
        std::string engineName = "KosmosEngine";
        std::string appName = "Kosmos";
        uint32_t engineVersion = VK_MAKE_VERSION(0, 0, 1);
        uint32_t appVersion = VK_MAKE_VERSION(0, 0, 1);
        std::vector<const char*> wishLayers{};
        std::vector<const char*> wishExtentions{};
        m_instance = std::make_unique<Instance>(engineName, appName, engineVersion, appVersion, true, false, wishLayers, wishExtentions);
    }
};
} // namespace Kosmos::Runtime::Vulkan
#endif // VULKAN_RENDERER_H