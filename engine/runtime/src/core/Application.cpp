#include <core/Application.h>
#include <render/GlfwWindow.h>
#include <render/vulkan/VulkanRenderer.h>
using namespace Kosmos::Runtime;

Application* Application::s_application = nullptr;
GlobalContext::GlobalContext(const std::string& configFileDir, const std::string& appName) {
    // TODO: config reader detect window type or api
    this->window = std::make_shared<GlfwWindow>(appName.c_str());
    this->renderer = std::make_unique<Vulkan::VulkanRenderer>(this->window);
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