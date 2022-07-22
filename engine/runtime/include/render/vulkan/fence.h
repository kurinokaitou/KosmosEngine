#ifndef FENCE_H
#define FENCE_H
#include <render/vulkan/Utils.h>

namespace Kosmos::Runtime::Vulkan {
class Device;
const static uint64_t FENCE_MAX_TIMEOUT = std::numeric_limits<uint64_t>::max();
class Fence {
private:
    VkFence m_fence{VK_NULL_HANDLE};
    const Device& m_deviceRef;
    std::string m_name;

public:
    Fence(const Device& device, const std::string& name, bool initSignaledState = true);
    ~Fence();
    Fence(Fence&& fence);
    VkFence getFence() const { return m_fence; }
    void waitFence(const uint64_t waitTime = FENCE_MAX_TIMEOUT);
    void resetFence();

private:
    Fence(const Fence& fence) = delete;
    Fence& operator=(const Fence& fence) = delete;
    Fence& operator=(Fence&& fence) = delete;
};
} // namespace Kosmos::Runtime::Vulkan

#endif // FENCE_H