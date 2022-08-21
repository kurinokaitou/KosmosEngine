#include <render/Resource.h>
using namespace Kosmos::Runtime;

VirtualResource::VirtualResource(const std::string& name) :
    m_name(name), m_parent(this) {}
VirtualResource::VirtualResource(const std::string& name, VirtualResource* parent) :
    m_name(name), m_parent(parent) {}
VirtualResource::VirtualResource(VirtualResource&& resource) noexcept{
    m_parent = resource.m_parent;
    m_name = std::move(m_name);
}
