
#include <core/Entry.h>
#include <core/Log.h>
int main(int argc, char** argv) {
    Kosmos::Runtime::Application* app;
    Kosmos::Runtime::Logger::init();
    try {
        app = createApplication(argc, argv);
        app->run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    Kosmos::Runtime::Logger::destroy();
    delete app;
}