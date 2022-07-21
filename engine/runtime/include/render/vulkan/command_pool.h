#ifndef COMMAND_POOL_H
#define COMMAND_POOL_H
#include <render/vulkan/utils.h>
namespace Kosmos::Runtime::Vulkan {
class Device;
class CommandPool {
private:
    const Device& m_deviceRef;
    VkCommandPool m_commandPool{VK_NULL_HANDLE};
    std::string m_name;

public:
    CommandPool(const Device& device, const uint32_t queueIndex, const std::string& name);
    ~CommandPool();
    CommandPool(CommandPool&& commandPool);
    VkCommandPool getCommandPool() const { return m_commandPool; }

private:
    CommandPool(const CommandPool& commandPool) = delete;
    CommandPool& operator=(const CommandPool& commandPool) = delete;
    CommandPool& operator=(CommandPool&& commandPool) = delete;
};
}; // namespace Kosmos::Runtime::Vulkan

#endif // COMMAND_POOL_H