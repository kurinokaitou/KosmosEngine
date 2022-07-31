#ifndef APPLICATION_H
#define APPLICATION_H

#include "Window.h"
#include <render/Renderer.h>
int main(int argc, char** argv);
namespace Kosmos::Runtime {
struct ApplicationCreateInfo {
    std::string appName{"Kosmos Application"};
    std::string currentWorkDir{"./"};
    std::string configFileDir{"./"};
    bool isEngine{false};
    int argc;
    char** argv; // pass from main
};

struct GlobalContext {
    GlobalContext(const std::string& configFileDir, const std::string& appName);
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<Window> window;
};

class Application {
    friend int ::main(int argc, char** argv);

private:
    std::string m_appName{nullptr};
    std::string m_currentWorkDir{nullptr};
    std::unique_ptr<GlobalContext> m_globalContext;

public:
    Application(ApplicationCreateInfo& createInfo);
    virtual ~Application();
    void run();

private:
    Application(const Application& app) = delete;
    Application(Application&& app) = delete;
    Application& operator=(const Application& app) = delete;
    Application& operator=(Application&& app) = delete;

    static Application* s_application;
};

Application* createApplication(int argc, char** argv);
} // namespace Kosmos::Runtime

#endif // APPLICATION_H