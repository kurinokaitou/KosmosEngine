#include <render/vulkan/make_info.h>
namespace Kosmos::Runtime::Vulkan {

template <>
VkApplicationInfo makeInfo() {
    VkApplicationInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    return ret;
}

template <>
VkBufferCreateInfo makeInfo() {
    VkBufferCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    return ret;
}

template <>
VkCommandBufferAllocateInfo makeInfo() {
    VkCommandBufferAllocateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    return ret;
}

template <>
VkCommandBufferBeginInfo makeInfo() {
    VkCommandBufferBeginInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    return ret;
}

template <>
VkCommandPoolCreateInfo makeInfo() {
    VkCommandPoolCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    return ret;
}

template <>
VkDebugMarkerMarkerInfoEXT makeInfo() {
    VkDebugMarkerMarkerInfoEXT ret{};
    ret.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_MARKER_INFO_EXT;
    return ret;
}

template <>
VkDebugMarkerObjectNameInfoEXT makeInfo() {
    VkDebugMarkerObjectNameInfoEXT ret{};
    ret.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_NAME_INFO_EXT;
    return ret;
}

template <>
VkDebugMarkerObjectTagInfoEXT makeInfo() {
    VkDebugMarkerObjectTagInfoEXT ret{};
    ret.sType = VK_STRUCTURE_TYPE_DEBUG_MARKER_OBJECT_TAG_INFO_EXT;
    return ret;
}

template <>
VkDebugReportCallbackCreateInfoEXT makeInfo() {
    VkDebugReportCallbackCreateInfoEXT ret{};
    ret.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
    return ret;
}

template <>
VkDescriptorPoolCreateInfo makeInfo() {
    VkDescriptorPoolCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    return ret;
}

template <>
VkDescriptorSetAllocateInfo makeInfo() {
    VkDescriptorSetAllocateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    return ret;
}

template <>
VkDescriptorSetLayoutCreateInfo makeInfo() {
    VkDescriptorSetLayoutCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    return ret;
}

template <>
VkDeviceCreateInfo makeInfo() {
    VkDeviceCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    return ret;
}

template <>
VkDeviceQueueCreateInfo makeInfo() {
    VkDeviceQueueCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    return ret;
}

template <>
VkFenceCreateInfo makeInfo() {
    VkFenceCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    return ret;
}

template <>
VkFramebufferCreateInfo makeInfo() {
    VkFramebufferCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    return ret;
}

template <>
VkGraphicsPipelineCreateInfo makeInfo() {
    VkGraphicsPipelineCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    return ret;
}

template <>
VkImageCreateInfo makeInfo() {
    VkImageCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    return ret;
}

template <>
VkImageMemoryBarrier makeInfo() {
    VkImageMemoryBarrier ret{};
    ret.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
    return ret;
}

template <>
VkImageViewCreateInfo makeInfo() {
    VkImageViewCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    return ret;
}

template <>
VkInstanceCreateInfo makeInfo() {
    VkInstanceCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    return ret;
}

template <>
VkPipelineColorBlendStateCreateInfo makeInfo() {
    VkPipelineColorBlendStateCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    return ret;
}

template <>
VkPipelineDepthStencilStateCreateInfo makeInfo() {
    VkPipelineDepthStencilStateCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    return ret;
}

template <>
VkPipelineInputAssemblyStateCreateInfo makeInfo() {
    VkPipelineInputAssemblyStateCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    return ret;
}

template <>
VkPipelineLayoutCreateInfo makeInfo() {
    VkPipelineLayoutCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    return ret;
}

template <>
VkPipelineMultisampleStateCreateInfo makeInfo() {
    VkPipelineMultisampleStateCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    return ret;
}

template <>
VkPipelineRasterizationStateCreateInfo makeInfo() {
    VkPipelineRasterizationStateCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    return ret;
}

template <>
VkPipelineShaderStageCreateInfo makeInfo() {
    VkPipelineShaderStageCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    return ret;
}

template <>
VkPipelineVertexInputStateCreateInfo makeInfo() {
    VkPipelineVertexInputStateCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    return ret;
}

template <>
VkPipelineViewportStateCreateInfo makeInfo() {
    VkPipelineViewportStateCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    return ret;
}

template <>
VkPresentInfoKHR makeInfo() {
    VkPresentInfoKHR ret{};
    ret.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    return ret;
}

template <>
VkRenderPassBeginInfo makeInfo() {
    VkRenderPassBeginInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    return ret;
}

template <>
VkRenderPassCreateInfo makeInfo() {
    VkRenderPassCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    return ret;
}

template <>
VkSamplerCreateInfo makeInfo() {
    VkSamplerCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    return ret;
}

template <>
VkSemaphoreCreateInfo makeInfo() {
    VkSemaphoreCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
    return ret;
}

template <>
VkShaderModuleCreateInfo makeInfo() {
    VkShaderModuleCreateInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    return ret;
}

template <>
VkSubmitInfo makeInfo() {
    VkSubmitInfo ret{};
    ret.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    return ret;
}

template <>
VkSwapchainCreateInfoKHR makeInfo() {
    VkSwapchainCreateInfoKHR ret{};
    ret.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    return ret;
}
} // namespace Kosmos::Runtime::Vulkan