#include <render/vulkan/surface.h>
using namespace Kosmos::Runtime::Vulkan;
Surface::Surface(VkInstance instance, GLFWwindow* window) {
    if (glfwCreateWindowSurface(instance, window, nullptr, &m_surface) == VK_SUCCESS) {
        KS_ENGINE_LOG_TRACE("Surface create success.");
    } else {
        KS_ENGINE_LOG_FATAL("Failed to create surface!");
    }
}
Surface::Surface(Surface&& surface) {
    m_instanceRef = surface.m_instanceRef;
    m_surface = std::exchange(surface.m_surface, nullptr);
}

Surface& Surface::operator=(Surface&& surface) {
    if (&surface != this) {
        m_instanceRef = surface.m_instanceRef;
        m_surface = std::exchange(surface.m_surface, nullptr);
    }
    return *this;
}

Surface::~Surface() {
    vkDestroySurfaceKHR(m_instanceRef, m_surface, nullptr);
}