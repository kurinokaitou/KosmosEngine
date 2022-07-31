#ifndef IMAGE_H
#define IMAGE_H
#include <render/vulkan/Utils.h>
#include <render/vulkan/Memory.h>
namespace Kosmos::Runtime::Vulkan {
class Device;
class Image2D : PhysicalMemory {
private:
    const Device& m_deviceRef;
    VkImage m_image;
    VkImageView m_imageView;
    VkExtent2D m_extent;
    VkImageUsageFlags m_usage;
    VkFormat m_format;
    std::string m_name;

public:
    Image2D(const Device& device, const VkFormat format, const VkImageUsageFlags usage,
            const VkImageAspectFlags aspectMask, const VkSampleCountFlagBits sampleCount, const uint32_t mipLevels,
            const uint32_t width, const uint32_t height, const std::string& name);
    Image2D(Image2D&& image);
    ~Image2D();
    VkExtent2D getExtent() const { return m_extent; }
    VkFormat getFormat() const { return m_format; }
    VkImageUsageFlags getUsage() const { return m_usage; }

private:
    void createImage(const uint32_t mipLevels, const VkSampleCountFlagBits sampleCount, const VkImageUsageFlags usage);

private:
    Image2D(const Image2D& image) = delete;
    Image2D& operator=(const Image2D& image) = delete;
    Image2D& operator=(Image2D&& image) = delete;
};
} // namespace Kosmos::Runtime::Vulkan
#endif