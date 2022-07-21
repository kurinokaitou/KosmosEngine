#ifndef SWAPCHAIN_H
#define SWAPCHAIN_H
#include "vulkan/vulkan_core.h"
#include <render/vulkan/utils.h>
#include <stdint.h>
namespace Kosmos::Runtime::Vulkan {
class Device;
class Swapchain {
private:
    Device& m_deviceRef;
    VkSwapchainKHR m_swapchain{VK_NULL_HANDLE};
    VkSurfaceKHR m_surfaceRef{VK_NULL_HANDLE};
    std::string m_name;
    bool m_enabledVSync{false};
    // 交换链中的图像句柄，我们操作其来渲染
    std::vector<VkImage> m_swapchainImages;
    // 对图像进行操作的views
    std::vector<VkImageView> m_swapchainImageViews;
    VkFormat m_swapchainImageFormat;
    VkExtent2D m_swapchainImageExtent;
    uint32_t m_swapchainImageCount{0};

public:
    Swapchain(Device& device, VkSurfaceKHR surface, int windowWidth, int windowHeight, const std::string& name, bool enabledVSync = true);
    ~Swapchain();
    void recreateSwapchain(int windowWidth, int windowHeight);
    VkSwapchainKHR getSwapchain() const { return m_swapchain; }
    VkImageView getImageViewByIndex(uint32_t index) const { return m_swapchainImageViews[index]; }
    VkFormat getImageFormat() const { return m_swapchainImageFormat; }
    VkExtent2D getExtent() const { return m_swapchainImageExtent; }
    uint32_t getImageCount() const { return m_swapchainImageCount; }
    uint32_t acquireNextImage(); // 返回下一张图片的index

private:
    void setupSwapchain(VkSwapchainKHR oldSwapchain, int windowWidth, int windowHeight);
    VkSurfaceFormatKHR chooseBestfitSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats);
    VkPresentModeKHR chooseBestfitPresentMode(const std::vector<VkPresentModeKHR>& presentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, int windowWidth, int windowHeight);
};
} // namespace Kosmos::Runtime::Vulkan
#endif // SWAPCHAIN_H