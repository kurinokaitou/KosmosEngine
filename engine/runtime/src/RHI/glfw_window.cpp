#include "RHI/glfw_window.h"

using namespace Kosmos::Runtime;

GlfwWindow::GlfwWindow(const char* title, uint32_t width, uint32_t height, WindowMode mode) :
    Window(title, width, height, mode) {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
    if (m_window == nullptr) {
        // TODO: implement log system and log error
        glfwTerminate();
    }
    setupGlfwCallback();
}

void GlfwWindow::onWindowResize(int width, int height) {
    for (auto& func : m_windowResizeFuncs) {
        func(width, height);
    }
}

void GlfwWindow::onWindowClose() {
    for (auto& func : m_closeFuncs) {
        func();
    }
}

void GlfwWindow::onFrameBufferResize(int width, int height) {
    for (auto& func : m_frameBufferResizeFuncs) {
        func(width, height);
    }
}

void GlfwWindow::setupGlfwCallback() {
    glfwSetWindowSizeCallback(m_window, windowResizeCallback);
    glfwSetFramebufferSizeCallback(m_window, frameBufferResizeCallback);
    glfwSetWindowCloseCallback(m_window, windowCloseCallback);
}
