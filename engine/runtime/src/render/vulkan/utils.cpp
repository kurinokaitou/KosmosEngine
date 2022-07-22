#include <render/vulkan/Utils.h>
using namespace Kosmos::Runtime::Vulkan;
bool Utils::checkLayersProperties(std::vector<const char*>& layers) {
    uint32_t LayersCount = 0;
    vkEnumerateInstanceLayerProperties(&LayersCount, nullptr);
    assert(LayersCount != 0);
    std::vector<VkLayerProperties> availableLayers(LayersCount);
    vkEnumerateInstanceLayerProperties(&LayersCount, availableLayers.data());
    // 检查所有layers中要求的layer层是否都支持
    for (auto& layer : layers) {
        if (std::find_if(availableLayers.begin(), availableLayers.end(),
                         [layer](VkLayerProperties properties) {
                             return strcmp(properties.layerName, layer) == 0;
                         })
            == availableLayers.end()) {
            return false;
        }
    }
    return true;
}

std::vector<const char*> Utils::getGlfwRequiredExtentions() {
    uint32_t glfwExtentionCount = 0;
    const char** glfwExtentionName;
    glfwExtentionName = glfwGetRequiredInstanceExtensions(&glfwExtentionCount);
    std::vector<const char*> extentionList(
        glfwExtentionName, glfwExtentionName + glfwExtentionCount);
    return extentionList;
}

bool Utils::checkDeviceExtentionsSupport(VkPhysicalDevice physicalDevice, std::vector<const char*>& deviceExtentions) {
    uint32_t extentionCount = 0;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extentionCount,
                                         nullptr);
    assert(extentionCount != 0);
    std::vector<VkExtensionProperties> extentionsProperties(extentionCount);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extentionCount,
                                         extentionsProperties.data());
#ifdef PRINT_EXTENTION_INFO
    //打印可用的扩展信息
    std::cout << "\t" << extentionsProperties.size() << std::endl;
    for (auto& properties : extentionsProperties) {
        std::cout << "\t" << properties.extensionName << std::endl;
    }
#endif
    for (const char* name : deviceExtentions) {
        if (std::find_if(extentionsProperties.begin(), extentionsProperties.end(),
                         [name](VkExtensionProperties val) {
                             return strcmp(val.extensionName, name) == 0;
                         })
            == extentionsProperties.end()) {
            return false;
        }
    }
    return true;
}

bool Utils::checkInstanceExtentionsSupport(std::vector<const char*>& extentionsName) {
    uint32_t extentionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount, nullptr);
    assert(extentionCount != 0);
    std::vector<VkExtensionProperties> extentionsProperties(extentionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extentionCount,
                                           extentionsProperties.data());
#ifdef PRINT_EXTENTION_INFO
    //打印可用的扩展信息
    std::cout << "\t" << extentionsProperties.size() << std::endl;
    for (auto& properties : extentionsProperties) {
        std::cout << "\t" << properties.extensionName << std::endl;
    }
#endif
    for (const char* name : extentionsName) {
        if (std::find_if(extentionsProperties.begin(), extentionsProperties.end(),
                         [name](VkExtensionProperties val) {
                             return strcmp(val.extensionName, name) == 0;
                         })
            == extentionsProperties.end()) {
            return false;
        }
    }
    return true;
}

VKAPI_ATTR VkBool32 VKAPI_CALL Utils::debugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messagesSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messgaesType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) {
    KS_ENGINE_LOG_ERROR(pCallbackData->pMessage);
    return VK_FALSE;
}

VkResult Utils::createDebugUtilsMessengerEXT(
    VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pCallback) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
        instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pCallback);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void Utils::destroyDebugUtilsMessengerEXT(VkInstance instance,
                                          VkDebugUtilsMessengerEXT* pCallback,
                                          const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
        instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, *pCallback, pAllocator);
    }
}

VkSampleCountFlagBits Utils::getMaxUsableSampleCount(VkPhysicalDevice physicalDevice) {
    VkPhysicalDeviceProperties physicalDeviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);

    VkSampleCountFlags counts = physicalDeviceProperties.limits.framebufferColorSampleCounts & physicalDeviceProperties.limits.framebufferDepthSampleCounts;
    if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
    if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
    if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
    if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
    if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
    if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

    return VK_SAMPLE_COUNT_1_BIT;
}