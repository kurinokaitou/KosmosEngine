#include <render/Renderer.h>
using namespace Kosmos::Runtime;

VkSampleCountFlagBits Renderer::s_msaaSampleCount = VK_SAMPLE_COUNT_1_BIT;
Renderer::Renderer(std::shared_ptr<Window> window) :
    m_window(window) {
}