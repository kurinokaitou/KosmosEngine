#include <render/vulkan/Image.h>
using namespace Kosmos::Runtime::Vulkan;
Image2D::Image2D(const Device& device, const VkFormat format, const VkImageUsageFlags usage,
                 const VkImageAspectFlags aspectMask, const VkSampleCountFlagBits sampleCount, const uint32_t mipLevels,
                 const uint32_t width, const uint32_t height, const std::string& name) :
    PhysicalMemory(VMA_MEMORY_USAGE_GPU_ONLY),
    m_deviceRef(device), m_format(format), m_usage(usage), m_name(name) {
    m_extent.width = width;
    m_extent.height = height;
    createImage(mipLevels, sampleCount, usage);
    m_deviceRef.createImageView(m_image, format, aspectMask, mipLevels, &m_imageView, m_name);
}
Image2D::Image2D(Image2D&& image) :
    PhysicalMemory(std::move(image)),
    m_deviceRef(image.m_deviceRef) {
    m_image = image.m_image;
    m_format = image.m_format;
    m_imageView = image.m_imageView;
    m_name = std::move(image.m_name);
}

Image2D::~Image2D() {
    vkDestroyImageView(m_deviceRef.getLogicalDevice(), m_imageView, nullptr);
    vmaDestroyImage(m_deviceRef.getAllocator(), m_image, m_allocation);
}

void Image2D::createImage(const uint32_t mipLevels, const VkSampleCountFlagBits sampleCount, const VkImageUsageFlags usage) {
    auto createInfo = makeInfo<VkImageCreateInfo>();
    createInfo.extent.width = m_extent.width;
    createInfo.extent.height = m_extent.height;
    createInfo.extent.depth = 1;
    createInfo.arrayLayers = 1;
    createInfo.mipLevels = mipLevels;
    createInfo.format = m_format;
    createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
    createInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    createInfo.samples = sampleCount;
    createInfo.usage = usage;
    createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (vmaCreateImage(m_deviceRef.getAllocator(), &createInfo, &m_allocCreateInfo, &m_image, &m_allocation, &m_allocInfo) == VK_SUCCESS) {
        KS_ENGINE_LOG_TRACE("Image create success.");
    } else {
        KS_ENGINE_LOG_WARN("Failed to create image {0}!", m_name);
    }
}