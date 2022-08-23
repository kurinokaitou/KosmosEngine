#ifndef RESOURCE_H
#define RESOURCE_H
#include <string>
#include <memory>
#include <render/vulkan/FrameBuffer.h>
namespace Kosmos::Runtime::RDG {
class PassNode;
class VirtualResource {
protected:
    VirtualResource* m_parent;
    std::string m_name;

public:
    VirtualResource(const std::string& name);
    VirtualResource(const std::string& name, VirtualResource* parent);
    VirtualResource(VirtualResource&& resource) noexcept;
    virtual ~VirtualResource() = default;
    bool isSubResource() const { return m_parent != this; }
    VirtualResource* getResource() {
        VirtualResource* p = this;
        while (p->m_parent != p) {
            p = p->m_parent;
        }
        return p;
    };
    virtual bool hasDevirtualized() const { return false; }
    virtual bool isImported() const = 0;

    virtual void devirtulize() = 0;
    virtual void destory() = 0;

private:
    VirtualResource(const VirtualResource& resource) = delete;
};

template <typename ResourceType>
class Resource : public VirtualResource {
public:
    using Description = typename ResourceType::Description;
    using Usage = typename ResourceType::Usage;

protected:
    Usage m_usage; // 当编译时被解析
    Description m_description;
    std::shared_ptr<ResourceType> m_resource; // 当被实例化时才可用
    bool m_isDetached{false};                 // 脱离rander graph 的资源将不会被在周期结束时销毁

public:
    Resource(const std::string& name, const Description& description) :
        VirtualResource(name), m_description(description) {}
    Resource(const std::string& name, const Description& description, Resource* parent) :
        VirtualResource(name, parent), m_description(description) {}
    Resource(Resource&& resource) :
        VirtualResource(std::move(resource)) {
        m_usage = resource.m_usage;
        m_description = resource.m_description;
        m_resource = std::exchange(m_resource, nullptr);
        m_isDetached = resource.m_isDetached;
    }
    virtual ~Resource() = default;
    virtual bool hasDevirtualized() const override { return false; }
    virtual bool isImported() const override { return false; }

    virtual void devirtulize() override {
        if (!isSubResource()) {
            m_resource = std::make_shared<ResourceType>(m_name, m_description, m_usage);
        } else {
            m_resource = static_cast<const Resource*>(m_parent)->m_resource;
        }
    }
    virtual void destory() override {
        if (m_isDetached || isSubResource())
            return;
        else {
            m_resource->destroy();
        }
    }
    void setUsage(const Usage usage) { m_usage = usage; }
    void setDetached() { m_isDetached = true; }

private:
    Resource(const Resource& resource) = delete;
    Resource& operator=(const Resource& resource) = delete;
    Resource& operator=(Resource&& resource) = delete;
};

// 从外部导入的资源
template <typename ResourceType>
class ImportedResource : public Resource<ResourceType> {
public:
    using Description = typename ResourceType::Description;
    using Usage = typename ResourceType::Usage;
    ImportedResource(const std::string& name, const Description& description, const Usage& usage, std::shared_ptr<ResourceType> resource) :
        Resource<ResourceType>(name, description) {
        this->m_usage = usage;
        this->m_resource = resource;
    }
    ImportedResource(ImportedResource&& resource) :
        Resource<ResourceType>(resource) {}
    ~ImportedResource() = default;

private:
    ImportedResource(const ImportedResource& resource) = delete;
    ImportedResource& operator=(const ImportedResource& resource) = delete;
    ImportedResource& operator=(ImportedResource&& resource) = delete;
};

class RenderTarget : public Resource<Vulkan::FrameBuffer> {
public:
    using FrameBuffer = Vulkan::FrameBuffer;
    using Description = FrameBuffer::Description;

public:
    RenderTarget(const std::string& name, const Description& description) :
        Resource<FrameBuffer>(name, description) {
        m_isDetached = true;
    }
    RenderTarget(RenderTarget&& renderTarget) noexcept :
        Resource<FrameBuffer>(std::move(renderTarget)) {}
    ~RenderTarget() = default;

private:
    RenderTarget(const RenderTarget& resource) = delete;
    RenderTarget& operator=(const RenderTarget& resource) = delete;
    RenderTarget& operator=(RenderTarget&& resource) = delete;
};

} // namespace Kosmos::Runtime::RDG

#endif // RESOURCE_H