#ifndef INSTANCE_H
#define INSTANCE_H
#include "core/log.h"
#include "render/vulkan/make_info.h"
#include "vulkan/vulkan_core.h"
#include <render/vulkan/utils.h>
#include <vector>
namespace Kosmos::Runtime::Vulkan {
class Instance {
private:
    VkInstance m_instance{VK_NULL_HANDLE};
    static constexpr uint32_t REQUIRED_VULKAN_API_VERSION{VK_API_VERSION_1_3};
    std::vector<const char*> m_instanceLayers;
    std::vector<const char*> m_instanceExtentions;
    bool m_enabledValidationLayer = true;
    bool m_enabledRenderDocLayer = false;
    VkDebugUtilsMessengerEXT m_callBack;

public:
    Instance(const std::string& engineName, const std::string& appName,
             uint32_t engineVersion, uint32_t appVersion, bool enableValidationLayer, bool enableRenderDoc,
             std::vector<const char*>& wishLayers, std::vector<const char*>& wishExtentions);
    Instance(Instance&& instance);
    Instance& operator=(Instance&& instance);
    ~Instance();
    VkInstance getVkInstance() const { return m_instance; }

private:
    // 设置debug的回调函数
    void setupDebugCallback();

    Instance(const Instance& instance) = delete;
    Instance& operator=(const Instance& instance) = delete;
};
} // namespace Kosmos::Runtime::Vulkan
#endif // INSTANCE_H