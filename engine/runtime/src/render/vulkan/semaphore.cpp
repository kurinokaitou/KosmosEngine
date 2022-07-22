#include <render/vulkan/Semaphore.h>
#include <render/vulkan/Device.h>
using namespace Kosmos::Runtime::Vulkan;

Semaphore::Semaphore(const Device& device, std::string& name) :
    m_deviceRef(device), m_name(name) {
    auto createInfo = makeInfo<VkSemaphoreCreateInfo>();
    m_deviceRef.createSemahore(createInfo, &m_semaphore);
}
Semaphore::Semaphore(Semaphore&& semahore) :
    m_deviceRef(semahore.m_deviceRef) {
    m_semaphore = std::exchange(m_semaphore, nullptr);
    m_name = std::move(semahore.m_name);
}

Semaphore::~Semaphore() {
    vkDestroySemaphore(m_deviceRef.getLogicalDevice(), m_semaphore, nullptr);
    KS_ENGINE_LOG_TRACE("Semaphore has destoryed.");
}