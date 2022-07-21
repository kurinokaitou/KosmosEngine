#include <render/vulkan/swapchain.h>
#include <render/vulkan/device.h>
using namespace Kosmos::Runtime::Vulkan;

Swapchain::Swapchain(Device& device, VkSurfaceKHR surface, int windowWidth, int windowHeight, const std::string& name, bool enabledVSync) :
    m_deviceRef(device), m_surfaceRef(surface), m_name(name), m_enabledVSync(enabledVSync) {
    setupSwapchain(VK_NULL_HANDLE, windowWidth, windowHeight);
}

Swapchain::~Swapchain() {
    vkDestroySwapchainKHR(m_deviceRef.getLogicalDevice(), m_swapchain, nullptr);
    KS_ENGINE_LOG_TRACE("Swapchain has destroyed.");
    for (auto& imageView : m_swapchainImageViews) {
        vkDestroyImageView(m_deviceRef.getLogicalDevice(), imageView, nullptr);
    }
    KS_ENGINE_LOG_TRACE("Swapchain ImageViews has destroyed.");
}
uint32_t Swapchain::acquireNextImage() {
    uint32_t imageIndex{0};
    // TODO: vkAcquireNextImage and semaphore
    return imageIndex;
}

void Swapchain::recreateSwapchain(int windowWidth, int windowHeight) {
    for (auto& imageView : m_swapchainImageViews) {
        vkDestroyImageView(m_deviceRef.getLogicalDevice(), imageView, nullptr);
    }
    m_swapchainImageViews.clear();
    m_swapchainImages.clear();
    setupSwapchain(m_swapchain, windowWidth, windowHeight);
}

void Swapchain::setupSwapchain(VkSwapchainKHR oldSwapchain, int windowWidth, int windowHeight) {
    auto surfaceCapabilities = m_deviceRef.getSurfaceCapabilities();
    auto surfaceFormat = chooseBestfitSurfaceFormat(m_deviceRef.getAvailableSurfaceFormats());
    auto presentMode = chooseBestfitPresentMode(m_deviceRef.getAvailablePresentMode());
    auto extent = chooseSwapExtent(surfaceCapabilities, windowWidth, windowHeight);
    // 决定交换链图片的数量
    uint32_t imageCount = surfaceCapabilities.minImageCount + 1;
    uint32_t maxImageCount = surfaceCapabilities.maxImageCount;
    if (maxImageCount > 0 && imageCount > maxImageCount) {
        imageCount = maxImageCount;
    }
    auto createInfo = makeInfo<VkSwapchainCreateInfoKHR>();
    createInfo.surface = m_surfaceRef;
    createInfo.minImageCount = imageCount;
    createInfo.imageArrayLayers = 1;
    // 只是绘制选择颜色附着，如果需要后处理则需要选择TRANSFER_DST
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.imageExtent = extent;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.oldSwapchain = oldSwapchain; // 允许重建交换链在渲染时进行

    auto queueFamilyIndice = m_deviceRef.getQueueFamiliyIndices();
    auto& indicesSet = queueFamilyIndice.familiesIndexSet;
    std::vector<uint32_t> indices(indicesSet.begin(), indicesSet.end());
    for (auto& index : indicesSet) {
        KS_LOG_TRACE("{0}", index);
    }
    if (indicesSet.size() != 1) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = static_cast<uint32_t>(indicesSet.size());
        createInfo.pQueueFamilyIndices = indices.data();
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // 如果只有一个就不存在并发问题，这里随意填写即可
        createInfo.pQueueFamilyIndices = nullptr;
    }
    createInfo.preTransform = surfaceCapabilities.currentTransform; // 预设的缩放旋转等
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;  // 窗口透明混合策略
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE; // 允许被遮挡像素剔除

    m_deviceRef.createSwapchain(createInfo, &m_swapchain, m_name);
    uint32_t imgCount = 0;
    // 获取交换链图像的句柄
    vkGetSwapchainImagesKHR(m_deviceRef.getLogicalDevice(), m_swapchain, &imgCount, nullptr);
    m_swapchainImages.resize(imgCount);
    vkGetSwapchainImagesKHR(m_deviceRef.getLogicalDevice(), m_swapchain, &imgCount,
                            m_swapchainImages.data());
    m_swapchainImageFormat = surfaceFormat.format;
    m_swapchainImageExtent = extent;
    // 创建交换链图像的视图
    m_swapchainImageViews.resize(m_swapchainImages.size());
    for (int i = 0; i < m_swapchainImages.size(); i++) {
        m_deviceRef.createImageView(m_swapchainImages[i], m_swapchainImageFormat,
                                    VK_IMAGE_ASPECT_COLOR_BIT, 1, &m_swapchainImageViews[i], m_name + "_imageView");
    }
}

VkSurfaceFormatKHR Swapchain::chooseBestfitSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& formats) {
    if (formats.size() == 1 && formats[0].format == VK_FORMAT_UNDEFINED) {
        return {VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    } else {
        for (auto& format : formats) {
            if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                return format;
            }
        }
    }
    return formats[0];
}

VkPresentModeKHR Swapchain::chooseBestfitPresentMode(const std::vector<VkPresentModeKHR>& presentModes) {
    VkPresentModeKHR bestMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
    if (!m_enabledVSync) return bestMode;
    for (auto& presentMode : presentModes) {
        if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            KS_ENGINE_LOG_INFO("VSync on: MODE_MAILBOX enabled.");
            return presentMode;
        } else if (presentMode == VK_PRESENT_MODE_FIFO_KHR) {
            bestMode = VK_PRESENT_MODE_FIFO_KHR;
        }
    }
    if (bestMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
        KS_ENGINE_LOG_WARN("VSync failed: dropback to MODE_IMMEDIATE");
    } else {
        KS_ENGINE_LOG_INFO("VSync on: MODE_FIFO enabled.");
    }
    return bestMode;
}

VkExtent2D Swapchain::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, int windowWidth, int windowHeight) {
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        VkExtent2D actualExtent = {static_cast<uint32_t>(windowWidth), static_cast<uint32_t>(windowHeight)};
        actualExtent.width = std::max(
            capabilities.minImageExtent.width,
            std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(
            capabilities.minImageExtent.height,
            std::min(capabilities.maxImageExtent.height, actualExtent.height));
        return actualExtent;
    }
}