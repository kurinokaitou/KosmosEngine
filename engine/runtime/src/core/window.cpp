#include <core/Window.h>
using namespace Kosmos::Runtime;
Window::Window(const char* title, int width, int height, WindowMode mode) :
    m_title(title), m_width(width), m_height(height), m_mode(mode) {
}
