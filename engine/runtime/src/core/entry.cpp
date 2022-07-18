
#include <core/entry.h>
#include <exception>
#include <iostream>
int main(int argc, char** argv) {
    Kosmos::Runtime::Application* app;
    try {
        app = createApplication(argc, argv);
        app->run();
    } catch (std::exception& e) {
        delete app;
        std::cerr << e.what() << std::endl;
    }
    delete app;
}