#ifndef SURFACE_H
#define SURFACE_H
#include <render/vulkan/Utils.h>
namespace Kosmos::Runtime::Vulkan {
class Surface {
private:
    VkSurfaceKHR m_surface{VK_NULL_HANDLE};
    VkInstance m_instanceRef{VK_NULL_HANDLE};

public:
    Surface(VkInstance instance, GLFWwindow* window);
    Surface(Surface&& surface);
    Surface& operator=(Surface&& surface);
    ~Surface();
    VkSurfaceKHR getSurface() { return m_surface; }

private:
    Surface(const Surface& surface) = delete;
    Surface& operator=(const Surface& surface) = delete;
};
} // namespace Kosmos::Runtime::Vulkan

#endif // SURFACE_H