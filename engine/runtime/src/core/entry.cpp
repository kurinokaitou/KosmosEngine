
#include <core/entry.h>
#include <core/log.h>
#include <exception>
#include <iostream>
int main(int argc, char** argv) {
    Kosmos::Runtime::Application* app;
    Kosmos::Runtime::Logger::init();
    try {
        app = createApplication(argc, argv);
        app->run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        delete app;
    }
    Kosmos::Runtime::Logger::destroy();
    delete app;
}