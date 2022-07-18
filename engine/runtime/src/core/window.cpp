#include <core/window.h>
using namespace Kosmos::Runtime;

Window::Window(const char* title, int width, int height, WindowMode mode) :
    m_title(title), m_width(width), m_height(height), m_mode(mode) {
}
inline void Window::setTitle(const char* titleName) {
    m_title = titleName;
}
inline void Window::setMode(WindowMode mode) {
    m_mode = mode;
}
inline void Window::setWindowSize(int width, int height) {
    m_width = width;
    m_height = height;
}
inline std::tuple<int, int> Window::getWindowSize() const {
    return std::make_tuple(m_width, m_height);
}
// register window events
inline void Window::registerWindowResize(onResizeFunc func) {
    m_windowResizeFuncs.push_back(func);
}

inline void Window::registerFrameBufferResize(onResizeFunc func) {
    m_frameBufferResizeFuncs.push_back(func);
}

inline void Window::registerWindowClose(onCloseFunc func) {
    m_closeFuncs.push_back(func);
}
