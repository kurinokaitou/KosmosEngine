#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include <render/vulkan/Utils.h>
namespace Kosmos::Runtime::Vulkan {
class Device;
class Semaphore {
private:
    const Device& m_deviceRef;
    VkSemaphore m_semaphore;
    std::string m_name;

public:
    Semaphore(const Device& device, std::string& name);
    Semaphore(Semaphore&& semahore);
    ~Semaphore();
    VkSemaphore getSemaphore() const { return m_semaphore; }

private:
    Semaphore(const Semaphore& semaphore) = delete;
    Semaphore& operator=(const Semaphore& semaphore) = delete;
    Semaphore& operator=(Semaphore&& semaphore) = delete;
};
} // namespace Kosmos::Runtime::Vulkan
#endif // SEMAPHORE_H