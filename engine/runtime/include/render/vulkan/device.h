#ifndef DEVICE_H
#define DEVICE_H
#include <array>
#include <set>
#include <optional>
#include <render/vulkan/utils.h>
#include <vma/vk_mem_alloc.h>

namespace Kosmos::Runtime::Vulkan {
struct QueueFamiliyIndices {
    std::set<uint32_t> familiesIndexSet;
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    std::optional<uint32_t> transferFamily;
    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value() && transferFamily.has_value();
    }
    bool isGraphicPresentSameFamily() {
        if (graphicsFamily.has_value() && presentFamily.has_value()) {
            return graphicsFamily.value() == presentFamily.value();
        } else {
            return false;
        }
    }
    bool isGraphicTransferSameFamily() {
        if (graphicsFamily.has_value() && transferFamily.has_value()) {
            return graphicsFamily.value() == transferFamily.value();
        } else {
            return false;
        }
    }
    size_t familyCount() {
        return familiesIndexSet.size();
    }
};

class DebugMarker {
public:
    DebugMarker(VkPhysicalDevice physicalDevice, VkDevice device) {
        if (!Utils::checkDeviceExtentionsSupport(physicalDevice, debugMarkerExtentions)) {
            KS_ENGINE_LOG_FATAL("Failed to create debug marker!");
        }
        vkDebugMarkerSetObjectNameEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectNameEXT>(vkGetDeviceProcAddr(device, "vkDebugMarkerSetObjectNameEXT"));
        vkDebugMarkerSetObjectTagEXT = reinterpret_cast<PFN_vkDebugMarkerSetObjectTagEXT>(vkGetDeviceProcAddr(device, "vkDebugMarkerSetObjectTagEXT"));
        vkCmdDebugMarkerBeginEXT = reinterpret_cast<PFN_vkCmdDebugMarkerBeginEXT>(vkGetDeviceProcAddr(device, "vkCmdDebugMarkerBeginEXT"));
        vkCmdDebugMarkerEndEXT = reinterpret_cast<PFN_vkCmdDebugMarkerEndEXT>(vkGetDeviceProcAddr(device, "vkCmdDebugMarkerEndEXT"));
        vkCmdDebugMarkerInsertEXT = reinterpret_cast<PFN_vkCmdDebugMarkerInsertEXT>(vkGetDeviceProcAddr(device, "vkCmdDebugMarkerInsertEXT "));
        vkSetDebugUtilsObjectNameEXT = reinterpret_cast<PFN_vkSetDebugUtilsObjectNameEXT>(vkGetDeviceProcAddr(device, "vkSetDebugUtilsObjectNameEXT"));
        if (vkDebugMarkerSetObjectNameEXT == nullptr || vkDebugMarkerSetObjectTagEXT == nullptr || vkCmdDebugMarkerBeginEXT == nullptr
            || vkCmdDebugMarkerEndEXT == nullptr || vkCmdDebugMarkerInsertEXT == nullptr || vkSetDebugUtilsObjectNameEXT) {
            KS_ENGINE_LOG_FATAL("Failed to create debug extention proc functions!");
        }
    }

    // TODO: implement debug marker
    void setDebugObjectName(void* obj, VkDebugReportObjectTypeEXT type, const std::string&& name){};
    void setDebugObjectMemoryTag(void* obj, VkDebugReportObjectTypeEXT type, uint64_t name, size_t mem_size, const void* mem_block){};
    void beginDebugRegion(VkCommandBuffer commandBuffer, const std::string& name, std::array<float, 4> color){};
    void insertDebugMarker(VkCommandBuffer commandBuffer, const std::string& name, std::array<float, 4> color){};
    void endDebugRegion(VkCommandBuffer commandBuffer){};

private:
    PFN_vkDebugMarkerSetObjectNameEXT vkDebugMarkerSetObjectNameEXT{nullptr};
    PFN_vkDebugMarkerSetObjectTagEXT vkDebugMarkerSetObjectTagEXT{nullptr};
    PFN_vkCmdDebugMarkerBeginEXT vkCmdDebugMarkerBeginEXT{nullptr};
    PFN_vkCmdDebugMarkerEndEXT vkCmdDebugMarkerEndEXT{nullptr};
    PFN_vkCmdDebugMarkerInsertEXT vkCmdDebugMarkerInsertEXT{nullptr};
    PFN_vkSetDebugUtilsObjectNameEXT vkSetDebugUtilsObjectNameEXT{nullptr};
    std::vector<const char*> debugMarkerExtentions{VK_EXT_DEBUG_MARKER_EXTENSION_NAME};
};

class Device {
private:
    VkDevice m_device{VK_NULL_HANDLE};
    VkPhysicalDevice m_physicalDevice{VK_NULL_HANDLE};
    VmaAllocator m_vmaAllocator{VK_NULL_HANDLE};
    std::string m_physicalDeviceName;
    std::vector<const char*> m_wishDeviceExtentions{VK_KHR_SWAPCHAIN_EXTENSION_NAME};
    VkSurfaceKHR m_surfaceRef{VK_NULL_HANDLE};
    VkQueue m_graphicQueue{VK_NULL_HANDLE};
    VkQueue m_presentQueue{VK_NULL_HANDLE};
    VkQueue m_transferQueue{VK_NULL_HANDLE};
    QueueFamiliyIndices m_queueFamilyIndices;
    bool m_enabledDebugMarker = false;
    std::shared_ptr<DebugMarker> m_debugMarkder;
    bool m_useDiffTransQueue;

public:
    Device(VkInstance instance, VkSurfaceKHR surface, bool enabledDebugMarker, bool useDiffTransQueue, uint32_t preferPhysicalDeviceIndex = -1);
    Device(Device&& device);
    ~Device();

    VkDevice getLogicalDevice() const { return m_device; }
    VkPhysicalDevice getPhysicalDevice() const { return m_physicalDevice; }
    std::shared_ptr<DebugMarker> getDebugMarker() const { return m_debugMarkder; }

    void createSwapchain(const VkSwapchainCreateInfoKHR& createInfo, VkSwapchainKHR* swapchain, const std::string& name = "swapchain");
    void createImageView(const VkImageViewCreateInfo& createInfo, VkImageView* imageView, const std::string& name = "imageView");
    void createRenderPass(const VkRenderPassCreateInfo& createInfo, VkRenderPass* renderPass, const std::string& name = "renderPass");
    void createGraphicsPipelineLayout(const VkPipelineLayoutCreateInfo& createInfo, VkPipelineLayout* layout, const std::string& = "pipelineLayout");
    void createGraphicsPipeline(const VkGraphicsPipelineCreateInfo& createInfo, VkPipeline* pipeline, const std::string& name = "pipeline");
    void createCommandPool(const VkCommandPoolCreateInfo& createInfo, VkCommandPool* commandPool, const std::string& name = "commandPool");
    void createCommandBuffer(const VkCommandBufferAllocateInfo& allocInfo, VkCommandBuffer* commandBuffer, const std::string& name = "commandBuffer");
    void createFrameBuffer(const VkFramebufferCreateInfo& createInfo, VkFramebuffer* frameBuffer, const std::string& name = "frameBuffer");
    void createDescriptorSetLayout(const VkDescriptorSetLayoutCreateInfo& createInfo, VkDescriptorSetLayout* descSetLayout, const std::string& name = "descSetLayout");
    void createDescriptorPool(const VkDescriptorPoolCreateInfo& createInfo, VkDescriptorPool* descPool, const std::string& name = "descPool");
    void createSampler(const VkSamplerCreateInfo& createInfo, VkSampler* sampler, const std::string& name = "sampler");
    void createFence(const VkFenceCreateInfo& createInfo, VkFence* fence, const std::string& name = "fence");
    void createSemahore(const VkSemaphoreCreateInfo& createInfo, VkSemaphore* semaphore, const std::string& name = "semaphore");
    void createShaderModule(const VkShaderModuleCreateInfo& createInfo, VkShaderModule* shaderModule, const std::string& name = "shaderModule");

private:
    void pickPhysicalDevice(VkInstance instance, uint32_t preferPhysicalDeviceIndex);
    bool isDeviceSuitable(VkPhysicalDevice physicalDevice);
    QueueFamiliyIndices findDeviceQueueFamilies(VkPhysicalDevice physicalDevice);
    std::tuple<VkSurfaceCapabilitiesKHR, std::vector<VkSurfaceFormatKHR>, std::vector<VkPresentModeKHR>>
    queryDeviceSwapChainSupport(VkPhysicalDevice physicalDevice);

private:
    Device(Device& device) = delete;
    Device& operator=(const Device& device) = delete;
    Device& operator=(Device&& device) = delete;
};
} // namespace Kosmos::Runtime::Vulkan
#endif // DEVICE_H