#include <render/vulkan/CommandPool.h>
#include <render/vulkan/Device.h>

using namespace Kosmos::Runtime::Vulkan;
CommandPool::CommandPool(const Device& device, const uint32_t queueIndex, const std::string& name) :
    m_deviceRef(device), m_name(name) {
    auto createInfo = makeInfo<VkCommandPoolCreateInfo>();
    createInfo.queueFamilyIndex = queueIndex;
    createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    m_deviceRef.createCommandPool(createInfo, &m_commandPool, m_name);
}

CommandPool::CommandPool(CommandPool&& commandPool) :
    m_deviceRef(commandPool.m_deviceRef) {
    m_commandPool = std::exchange(commandPool.m_commandPool, nullptr);
    m_name = std::move(commandPool.m_name);
}

CommandPool::~CommandPool() {
    vkDestroyCommandPool(m_deviceRef.getLogicalDevice(), m_commandPool, nullptr);
    KS_ENGINE_LOG_TRACE("CommandPool has destroyed.");
}