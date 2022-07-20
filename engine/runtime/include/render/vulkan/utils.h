#ifndef UTILS_H
#define UTILS_H
#include <GLFW/glfw3.h>
#include <string.h>
#include <stdint.h>
#include <string>
#include <assert.h>
#include <vector>
#include <memory.h>
#include <algorithm>
#include <core/log.h>
#include "make_info.h"

namespace Kosmos::Runtime::Vulkan {
class Utils {
public:
    static bool checkLayersProperties(std::vector<const char*>& layers);
    static std::vector<const char*> getGlfwRequiredExtentions();
    static bool checkInstanceExtentionsSupport(std::vector<const char*>& extentionName);
    static bool checkDeviceExtentionsSupport(VkPhysicalDevice physicalDevice, std::vector<const char*>& deviceExtentions);
    // 被Vulkan调用的静态用户定义行为函数，在一般情况只返回VK_FALSE
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messagesSeverity,
                                                        VkDebugUtilsMessageTypeFlagsEXT messgaesType,
                                                        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
    static VkResult createDebugUtilsMessengerEXT(
        VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pCallback);
    static void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT* pCallback, const VkAllocationCallbacks* pAllocator);
    static VkSampleCountFlagBits getMaxUsableSampleCount(VkPhysicalDevice physicalDevice);
};
} // namespace Kosmos::Runtime::Vulkan

#endif // UTILS_H