#ifndef MEMORY_H
#define MEMORY_H
#include <render/vulkan/Device.h>
#include <cstdlib>
namespace Kosmos::Runtime::Vulkan {
class PhysicalMemory {
protected:
    VmaAllocation m_allocation;
    VmaAllocationInfo m_allocInfo;
    VmaAllocationCreateInfo m_allocCreateInfo;

public:
    PhysicalMemory(VmaMemoryUsage usage) {
        m_allocCreateInfo.usage = usage;
        m_allocCreateInfo.flags = VMA_ALLOCATION_CREATE_MAPPED_BIT;
    }
    PhysicalMemory(void* data, size_t size, VmaMemoryUsage usage) :
        PhysicalMemory(usage) {
        memcpy(m_allocInfo.pMappedData, data, size);
    }
    PhysicalMemory(PhysicalMemory&& memory) {
        m_allocation = std::exchange(memory.m_allocation, nullptr);
        m_allocInfo = memory.m_allocInfo;
        m_allocCreateInfo = memory.m_allocCreateInfo;
    }
    ~PhysicalMemory() = default;
};
} // namespace Kosmos::Runtime::Vulkan
#endif // MEMORY_H