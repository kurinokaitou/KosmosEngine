#ifndef SWAPCHAIN_H
#define SWAPCHAIN_H
#include "vulkan/vulkan_core.h"
#include <render/vulkan/utils.h>
#include <string>
namespace Kosmos::Runtime::Vulkan {
class Device;
class Swapchain {
private:
    Device& m_deviceRef;
    VkSwapchainKHR m_swapchain{VK_NULL_HANDLE};
    std::string m_name;
    bool m_enabledVSync{false};
    // 交换链中的图像句柄，我们操作其来渲染
    std::vector<VkImage> m_swapChainImages;
    // 对图像进行操作的views
    std::vector<VkImageView> m_swapChainImageViews;
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainImageExtent;

public:
    Swapchain(const Device& device, int windowWidth, int windowHeight, const std::string& name, bool enabledVSync = true);

    ~Swapchain();

private:
    void setupSwapchain(const Swapchain& oldSwapchain, int windowWidth, int windowHeight);
};
} // namespace Kosmos::Runtime::Vulkan
#endif // SWAPCHAIN_H