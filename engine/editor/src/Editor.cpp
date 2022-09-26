#include <Editor.h>
#include <filesystem>
Kosmos::Runtime::Application* createApplication(int argc, char** argv) {
    Kosmos::Runtime::ApplicationCreateInfo createInfo{};
    createInfo.appName = "KosmoEditor";
    createInfo.currentWorkDir = std::filesystem::current_path().generic_string();
    // TODO: config loader toml implemented
    createInfo.configFileDir = "./";
    createInfo.isEngine = true;
    return new Kosmos::Editor::KosmosEditor(createInfo);
}