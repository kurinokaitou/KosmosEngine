#ifndef VULKAN_WINDOW_H
#define VULKAN_WINDOW_H
#include <GLFW/glfw3.h>
#include <core/window.h>
namespace Kosmos::Runtime {
class GlfwWindow : public Window {
private:
    GLFWwindow* m_window{nullptr};

public:
    GlfwWindow(const char* title, int width = 1280, int height = 800, WindowMode mode = WindowMode::WINDOWED);
    ~GlfwWindow();
    virtual void setTitle(const char* titleName) override;
    virtual void setMode(WindowMode mode) override;
    virtual void setWindowSize(int width, int height) override;
    virtual void onWindowResize(int width, int height) override;
    virtual void onWindowClose() override;
    virtual void onFrameBufferResize(int width, int height) override;
    virtual bool shouldClose() const override;
    virtual void pollEvents() const override;
    GLFWwindow* getWindow() const { return m_window; };

private:
    void setupGlfwCallback();
    static void windowResizeCallback(GLFWwindow* window, int width, int height) {
        GlfwWindow* appWindow = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
        if (appWindow) {
            appWindow->setWindowSize(width, height);
            appWindow->onWindowResize(width, height);
        }
    }

    static void windowCloseCallback(GLFWwindow* window) {
        GlfwWindow* appWindow = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
        if (appWindow) {
            appWindow->onWindowClose();
            glfwSetWindowShouldClose(window, true);
        }
    }

    static void frameBufferResizeCallback(GLFWwindow* window, int width, int height) {
        GlfwWindow* appWindow = static_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
        if (appWindow) {
            appWindow->onFrameBufferResize(width, height);
        }
    }
};
} // namespace Kosmos::Runtime

#endif // VULKAN_WINDOW_H