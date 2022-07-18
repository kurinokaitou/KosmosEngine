#ifndef INSTANCE_H
#define INSTANCE_H
#include <vulkan/vulkan_core.h>
namespace Kosmos::Runtime::Vulkan {
class Instance {
    VkInstance m_instance;
};
} // namespace Kosmos::Runtime::Vulkan
#endif // INSTANCE_H