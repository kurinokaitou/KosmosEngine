#include "vulkan/vulkan_core.h"
#include "core/log.h"
#include "render/vulkan/make_info.h"
#include <render/renderer.h>
#include <render/vulkan/device.h>
#include <string>
#include <vulkan/vulkan_core.h>
using namespace Kosmos::Runtime::Vulkan;

Device::Device(VkInstance instance, VkSurfaceKHR surface, bool enabledDebugMarker, bool useDifferTransQueue, uint32_t preferPhysicalDeviceIndex) :
    m_enabledDebugMarker(enabledDebugMarker), m_useDiffTransQueue(useDifferTransQueue), m_surfaceRef(surface) {
    pickPhysicalDevice(instance, preferPhysicalDeviceIndex);
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    float queuePriority = 1.0f;
    for (auto index : m_queueFamilyIndices.familiesIndexSet) {
        auto queueInfo = makeInfo<VkDeviceQueueCreateInfo>();
        queueInfo.queueCount = 1;
        queueInfo.pQueuePriorities = &queuePriority;
        queueInfo.queueFamilyIndex = index;
        queueCreateInfos.push_back(queueInfo);
    }

    VkPhysicalDeviceFeatures features{};
    // TODO: implement samplerAnisotropy and sampleRateShading
    // features.samplerAnisotropy = VK_TRUE; // 启用各项异性
    // features.sampleRateShading = VK_TRUE; // 开启多重采样着色

    auto deviceCreateInfo = makeInfo<VkDeviceCreateInfo>();
    deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
    deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    deviceCreateInfo.pEnabledFeatures = &features;
    deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(m_wishDeviceExtentions.size());
    deviceCreateInfo.ppEnabledExtensionNames = m_wishDeviceExtentions.data();
    // 此处不再开启device校验层，因为已经deprecated
    deviceCreateInfo.enabledLayerCount = 0;
    deviceCreateInfo.ppEnabledLayerNames = nullptr;

    if (vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_device) == VK_SUCCESS) {
        KS_ENGINE_LOG_TRACE("Logical device create success.");
    } else {
        KS_ENGINE_LOG_FATAL("Failed to create logical device");
    }
    // 获取到三种队列
    vkGetDeviceQueue(m_device, static_cast<uint32_t>(m_queueFamilyIndices.graphicsFamily.value()), 0, &m_graphicQueue);
    vkGetDeviceQueue(m_device, static_cast<uint32_t>(m_queueFamilyIndices.presentFamily.value()), 0, &m_presentQueue);
    vkGetDeviceQueue(m_device, static_cast<uint32_t>(m_queueFamilyIndices.transferFamily.value()), 0, &m_transferQueue);
}
Device::Device(Device&& device) {
    m_device = std::exchange(device.m_device, nullptr);
    m_physicalDevice = std::exchange(device.m_physicalDevice, nullptr);
    m_surfaceRef = device.m_surfaceRef;
}
Device::~Device() {
    vmaDestroyAllocator(m_vmaAllocator);
    vkDestroyDevice(m_device, nullptr);
    KS_ENGINE_LOG_TRACE("Logical device has destroyed.");
}

void Device::createSwapchain(const VkSwapchainCreateInfoKHR& createInfo, VkSwapchainKHR* swapchain, const std::string& name) {
}
void Device::createImageView(const VkImageViewCreateInfo& createInfo, VkImageView* imageView, const std::string& name) {
}
void Device::createRenderPass(const VkRenderPassCreateInfo& createInfo, VkRenderPass* renderPass, const std::string& name) {
}
void Device::createGraphicsPipelineLayout(const VkPipelineLayoutCreateInfo& createInfo, VkPipelineLayout* layout, const std::string&) {
}
void Device::createGraphicsPipeline(const VkGraphicsPipelineCreateInfo& createInfo, VkPipeline* pipeline, const std::string& name) {
}
void Device::createCommandPool(const VkCommandPoolCreateInfo& createInfo, VkCommandPool* commandPool, const std::string& name) {
}
void Device::createCommandBuffer(const VkCommandBufferAllocateInfo& allocInfo, VkCommandBuffer* commandBuffer, const std::string& name) {
}
void Device::createFrameBuffer(const VkFramebufferCreateInfo& createInfo, VkFramebuffer* frameBuffer, const std::string& name) {
}
void Device::createDescriptorSetLayout(const VkDescriptorSetLayoutCreateInfo& createInfo, VkDescriptorSetLayout* descSetLayout, const std::string& name) {
}
void Device::createDescriptorPool(const VkDescriptorPoolCreateInfo& createInfo, VkDescriptorPool* descPool, const std::string& name) {
}
void Device::createSampler(const VkSamplerCreateInfo& createInfo, VkSampler* sampler, const std::string& name) {
}
void Device::createFence(const VkFenceCreateInfo& createInfo, VkFence* fence, const std::string& name) {
}
void Device::createSemahore(const VkSemaphoreCreateInfo& createInfo, VkSemaphore* semaphore, const std::string& name) {
}
void Device::createShaderModule(const VkShaderModuleCreateInfo& createInfo, VkShaderModule* shaderModule, const std::string& name) {
}

void Device::pickPhysicalDevice(VkInstance instance, uint32_t preferPhysicalDeviceIndex) {
    uint32_t deviceCount = 0;
    bool preferredPicked = false;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        KS_ENGINE_LOG_FATAL("Failed to pick a GPU with Vulkan support!");
    }
    std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, physicalDevices.data());
    if (preferPhysicalDeviceIndex != -1) {
        if (preferPhysicalDeviceIndex >= deviceCount) {
            KS_ENGINE_LOG_ERROR("Preferred device index out of range!");
        } else {
            auto& preferredDevice = physicalDevices[preferPhysicalDeviceIndex];
            if (isDeviceSuitable(preferredDevice)) {
                m_physicalDevice = preferredDevice;
                Renderer::s_msaaSampleCount = Utils::getMaxUsableSampleCount(preferredDevice);
                preferredPicked = true;
            }
        }
    }
    if (m_physicalDevice == VK_NULL_HANDLE) {
        for (auto& device : physicalDevices) {
            if (isDeviceSuitable(device)) {
                m_physicalDevice = device;
                Renderer::s_msaaSampleCount = Utils::getMaxUsableSampleCount(device);
                break;
            }
        }
    }
    if (m_physicalDevice == VK_NULL_HANDLE) {
        KS_ENGINE_LOG_FATAL("Failed to pick a suitable GPU!");
    } else {
        VkPhysicalDeviceProperties properties;
        vkGetPhysicalDeviceProperties(m_physicalDevice, &properties);
        std::string gpuType = "unknown type";
        std::string gpuName(properties.deviceName);
        if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            gpuType = "discrete";
        } else if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU) {
            gpuType = "intergrated";
        }
        if (preferredPicked) {
            KS_ENGINE_LOG_TRACE("Preferrd {0} GPU {1} picked.", gpuType, gpuName);
        } else {
            KS_ENGINE_LOG_TRACE("A suitable {0} GPU {1} picked.", gpuType, gpuName);
        }
    }
}

bool Device::isDeviceSuitable(VkPhysicalDevice physicalDevice) {
    VkPhysicalDeviceProperties properties = {};
    VkPhysicalDeviceFeatures features = {};
    vkGetPhysicalDeviceProperties(physicalDevice, &properties);
    vkGetPhysicalDeviceFeatures(physicalDevice, &features);

    m_queueFamilyIndices = findDeviceQueueFamilies(physicalDevice);
    // 查询设备是否支持要求的扩展
    bool extentionsSupport = Utils::checkDeviceExtentionsSupport(physicalDevice, m_wishDeviceExtentions);
    bool swapChainAdequate = false;
    if (extentionsSupport) {
        auto [surfaceCapabilities, formats, presentModes] = queryDeviceSwapChainSupport(physicalDevice);
        swapChainAdequate = !formats.empty() && !presentModes.empty();
    }
    return m_queueFamilyIndices.isComplete() && extentionsSupport && swapChainAdequate && features.samplerAnisotropy;
}

QueueFamiliyIndices Device::findDeviceQueueFamilies(VkPhysicalDevice physicalDevice) {
    QueueFamiliyIndices indices;
    uint32_t deviceQueueFamilyCount = 0;
    VkBool32 presentSupport = false;

    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice,
                                             &deviceQueueFamilyCount, nullptr);
    assert(deviceQueueFamilyCount != 0);
    std::vector<VkQueueFamilyProperties> properties(deviceQueueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(
        physicalDevice, &deviceQueueFamilyCount, properties.data());

    for (uint32_t i = 0; i < deviceQueueFamilyCount; i++) {
        VkQueueFamilyProperties queueFamily = properties[i];
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, m_surfaceRef,
                                             &presentSupport);
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            indices.graphicsFamily = i;
        }
        if (presentSupport) {
            indices.presentFamily = i;
        }
        if (indices.isGraphicPresentSameFamily()) {
            break;
        }
    }
    indices.familiesIndexSet.insert(indices.graphicsFamily.value());
    indices.familiesIndexSet.insert(indices.presentFamily.value());
    // 如果不指定单独的传输队列族，则使用图形队列族
    indices.transferFamily = indices.graphicsFamily;
    if (m_useDiffTransQueue) {
        for (uint32_t i = 0; i < deviceQueueFamilyCount; i++) {
            VkQueueFamilyProperties queueFamily = properties[i];
            if (queueFamily.queueCount > 0) {
                if (!(queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
                    if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT) {
                        indices.transferFamily = i;
                        indices.familiesIndexSet.insert(indices.transferFamily.value());
                        KS_ENGINE_LOG_INFO("Use different transfer queue success.");
                    }
                }
            }
        }
        if (indices.isGraphicTransferSameFamily()) {
            KS_ENGINE_LOG_WARN("Failed to use different transfer queue.");
        }
    }
    return indices;
}

std::tuple<VkSurfaceCapabilitiesKHR, std::vector<VkSurfaceFormatKHR>, std::vector<VkPresentModeKHR>>
Device::queryDeviceSwapChainSupport(VkPhysicalDevice physicalDevice) {
    VkSurfaceCapabilitiesKHR surfaceCapabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, m_surfaceRef,
                                              &surfaceCapabilities);
    // 获取物理设备表面支持的格式
    uint32_t formatCount = 0;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, m_surfaceRef, &formatCount,
                                         nullptr);
    if (formatCount != 0) {
        formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, m_surfaceRef,
                                             &formatCount, formats.data());
    }
    uint32_t presentModeCount = 0;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, m_surfaceRef,
                                              &presentModeCount, nullptr);
    if (presentModeCount != 0) {
        presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, m_surfaceRef,
                                                  &presentModeCount,
                                                  presentModes.data());
    }
    return {surfaceCapabilities, formats, presentModes};
}