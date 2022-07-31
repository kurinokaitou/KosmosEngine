#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
#include <render/vulkan/Utils.h>
namespace Kosmos::Runtime::Vulkan {
class FrameBuffer {
public:
    struct Description {
    } m_description;

    struct Usage {
    } m_usage;

public:
    FrameBuffer(const std::string& name, const Description& desc, const Usage& usage);
    FrameBuffer(FrameBuffer&& frameBuffer) {
    }
    ~FrameBuffer();
    void destroy();

private:
    FrameBuffer(const FrameBuffer& frameBuffer) = delete;
    FrameBuffer& operator=(const FrameBuffer& frameBuffer) = delete;
    FrameBuffer& operator=(FrameBuffer&& frameBuffer) = delete;
};
} // namespace Kosmos::Runtime::Vulkan

#endif // FRAME_BUFFER_H