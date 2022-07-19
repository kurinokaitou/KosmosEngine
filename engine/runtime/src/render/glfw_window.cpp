#include "render/glfw_window.h"
#include "core/window.h"
#include <GLFW/glfw3.h>
#include <core/log.h>

using namespace Kosmos::Runtime;

GlfwWindow::GlfwWindow(const char* title, int width, int height, WindowMode mode) :
    Window(title, width, height, mode) {
    if (!glfwInit()) {
        glfwTerminate();
        KS_ENGINE_LOG_FATAL("failed to initialize glfw!");
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
    if (m_window == nullptr) {
        glfwTerminate();
        KS_ENGINE_LOG_FATAL("failed to initialize window!");
    }
    glfwSetWindowUserPointer(m_window, this);
    glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
    setupGlfwCallback();
    KS_ENGINE_LOG_TRACE("Window init success!");
}

GlfwWindow::~GlfwWindow() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void GlfwWindow::setTitle(const char* titleName) {
    Window::setTitle(titleName);
    glfwSetWindowTitle(m_window, titleName);
}
void GlfwWindow::setMode(WindowMode mode) {
    Window::setMode(mode);
    // TODO: implement fullscreen of glfw window
}
void GlfwWindow::setWindowSize(int width, int height) {
    Window::setWindowSize(width, height);
    glfwSetWindowSize(m_window, width, height);
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

inline bool GlfwWindow::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

inline void GlfwWindow::pollEvents() const {
    glfwPollEvents();
}

inline GLFWwindow* GlfwWindow::getWindow() const {
    return m_window;
}

void GlfwWindow::setupGlfwCallback() {
    glfwSetWindowSizeCallback(m_window, windowResizeCallback);
    glfwSetFramebufferSizeCallback(m_window, frameBufferResizeCallback);
    glfwSetWindowCloseCallback(m_window, windowCloseCallback);
}
