#include <render/vulkan/Fence.h>
#include <render/vulkan/Device.h>
using namespace Kosmos::Runtime::Vulkan;

Fence::Fence(const Device& device, const std::string& name, bool initSignaledState) :
    m_deviceRef(device), m_name(name) {
    auto createInfo = makeInfo<VkFenceCreateInfo>();
    createInfo.flags = initSignaledState ? VK_FENCE_CREATE_SIGNALED_BIT : 0;
    m_deviceRef.createFence(createInfo, &m_fence);
}

Fence::~Fence() {
    vkDestroyFence(m_deviceRef.getLogicalDevice(), m_fence, nullptr);
    KS_ENGINE_LOG_TRACE("Fence has destroyed.");
}

Fence::Fence(Fence&& fence) :
    m_deviceRef(fence.m_deviceRef) {
    m_fence = std::exchange(fence.m_fence, nullptr);
    m_name = std::move(fence.m_name);
}

void Fence::waitFence(const uint64_t waitTime) {
    // 等待某个预渲染的帧被GPU处理完毕，通过栅栏，实现不会提交过多的帧
    vkWaitForFences(m_deviceRef.getLogicalDevice(), 1, &m_fence, VK_TRUE, waitTime);
}

void Fence::resetFence() {
    vkResetFences(m_deviceRef.getLogicalDevice(), 1, &m_fence);
}