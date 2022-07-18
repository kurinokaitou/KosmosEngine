#include <core/application.h>
#include <render/glfw_window.h>
#include <memory>
using namespace Kosmos::Runtime;

Application* Application::s_application = nullptr;
GlobalContext::GlobalContext(const std::string& congigFileDir, const std::string& appName) {
    this->window = std::make_shared<GlfwWindow>(appName.c_str());
}

Application::Application(ApplicationCreateInfo& createInfo) :
    m_appName(createInfo.appName),
    m_currentWorkDir(createInfo.currentWorkDir) {
    m_globalContext = std::make_unique<GlobalContext>(createInfo.configFileDir, createInfo.appName);
    s_application = this;
}

Application::~Application() {
}

void Application::run() {
    auto& window = m_globalContext->window;
    while (!window->shouldClose()) {
        window->pollEvents();
    }
}