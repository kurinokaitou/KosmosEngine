#include <render/vulkan/Instance.h>
using namespace Kosmos::Runtime::Vulkan;

Instance::Instance(const std::string& engineName, const std::string& appName,
                   uint32_t engineVersion, uint32_t appVersion, bool enableValidationLayer, bool enableRenderDoc,
                   std::vector<const char*> wishLayers, std::vector<const char*> wishExtentions) :
    m_enabledValidationLayer(enableValidationLayer),
    m_instanceLayers(wishLayers.begin(), wishLayers.end()),
    m_instanceExtentions(wishExtentions.begin(), wishExtentions.end()) {
    if (m_enabledValidationLayer) {
        m_instanceLayers.push_back("VK_LAYER_KHRONOS_validation");
        m_instanceExtentions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    if (m_enabledRenderDocLayer) {
        m_instanceLayers.push_back("VK_LAYER_RENDERDOC_Capture");
    }
    auto glfwExtentions = Utils::getGlfwRequiredExtentions();
    for (auto& extention : glfwExtentions) {
        m_instanceExtentions.push_back(extention);
    }
    if (!Utils::checkLayersProperties(m_instanceLayers)) {
        KS_ENGINE_LOG_FATAL("Failed to create layers!");
    }
    if (!Utils::checkInstanceExtentionsSupport(m_instanceExtentions)) {
        KS_ENGINE_LOG_FATAL("Failed to support extensions!");
    }
    auto appInfo = makeInfo<VkApplicationInfo>();
    appInfo.applicationVersion = appVersion;
    appInfo.apiVersion = REQUIRED_VULKAN_API_VERSION;
    appInfo.engineVersion = engineVersion;
    appInfo.pEngineName = engineName.c_str();
    appInfo.pApplicationName = appName.c_str();

    auto createInfo = makeInfo<VkInstanceCreateInfo>();
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(m_instanceExtentions.size());
    createInfo.enabledLayerCount = static_cast<uint32_t>(m_instanceLayers.size());
    createInfo.ppEnabledExtensionNames = m_instanceExtentions.data();
    createInfo.ppEnabledLayerNames = m_instanceLayers.data();

    if (vkCreateInstance(&createInfo, nullptr, &m_instance) == VK_SUCCESS) {
        KS_ENGINE_LOG_TRACE("Instance create success.");
    } else {
        KS_ENGINE_LOG_FATAL("Failed to create instance!");
    }
    setupDebugCallback();
}
Instance::Instance(const std::string& engineName, const std::string& appName,
                   uint32_t engineVersion, uint32_t appVersion) :
    Instance(engineName, appName, engineVersion, appVersion, true, true, {}, {}) {}

Instance::Instance(Instance&& instance) {
    m_instance = std::exchange(instance.m_instance, VK_NULL_HANDLE);
}

Instance& Instance::operator=(Instance&& instance) {
    if (&instance != this) {
        m_instance = std::exchange(instance.m_instance, VK_NULL_HANDLE);
    }
    return *this;
}

Instance::~Instance() {
    if (m_enabledValidationLayer) {
        Utils::destroyDebugUtilsMessengerEXT(m_instance, &m_callBack, nullptr);
    }
    vkDestroyInstance(m_instance, nullptr);
    KS_ENGINE_LOG_TRACE("Instance has destroyed.");
}

void Instance::setupDebugCallback() {
    if (!m_enabledValidationLayer) return;
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = Utils::debugCallback;
    createInfo.pUserData = nullptr;
    VkResult res = Utils::createDebugUtilsMessengerEXT(m_instance, &createInfo,
                                                       nullptr, &m_callBack);
    if (res == VK_SUCCESS) {
        KS_ENGINE_LOG_TRACE("Setup debug callback success.");
    } else {
        KS_ENGINE_LOG_FATAL("Failed to setup debug callback!");
    }
}