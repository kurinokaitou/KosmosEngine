#ifndef WINDOW
#define WINDOW

#include <functional>
#include <stdint.h>
#include <tuple>
#include <vector>

namespace Kosmos::Runtime {

class Window {
public:
    enum class WindowMode { WINDOWED,
                            FULLSCREEN };
    typedef std::function<void(int, int)> onResizeFunc;
    typedef std::function<void()> onCloseFunc;
    // TODO: more events
protected:
    int m_width{1280};
    int m_height{800};
    WindowMode m_mode{WindowMode::WINDOWED};
    const char* m_title{"Kosmos Engine"};
    std::vector<onResizeFunc> m_windowResizeFuncs;
    std::vector<onResizeFunc> m_frameBufferResizeFuncs;
    std::vector<onCloseFunc> m_closeFuncs;

public:
    Window(const char* title, int width = 1280, int height = 800, WindowMode mode = WindowMode::WINDOWED);
    virtual ~Window(){};
    virtual void setTitle(const char* titleName);
    virtual void setMode(WindowMode mode);
    virtual void setWindowSize(int width, int height);
    std::tuple<int, int> getWindowSize() const;
    // register window events
    void registerWindowResize(onResizeFunc func);
    void registerFrameBufferResize(onResizeFunc func);
    void registerWindowClose(onCloseFunc func);

    // execute registed events
    virtual void onWindowResize(int width, int height) = 0;
    virtual void onWindowClose() = 0;
    virtual void onFrameBufferResize(int width, int height) = 0;

    virtual bool shouldClose() const = 0;
    virtual void pollEvents() const = 0;

private:
    Window(const Window& window) = delete;
    Window& operator=(const Window& window) = delete;
    Window(Window&& window) = delete;
    Window&& operator=(Window&& window) = delete;
};

} // namespace Kosmos::Runtime

#endif // WINDOW