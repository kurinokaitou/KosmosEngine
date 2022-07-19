#ifndef KOSMOS_EDITOR_H
#define KOSMOS_EDITOR_H
#include <core/application.h>
namespace Kosmos::Editor {
class KosmosEditor : public Runtime::Application {
public:
    KosmosEditor(Runtime::ApplicationCreateInfo& createInfo) :
        Runtime::Application(createInfo) {
    }
    ~KosmosEditor() {
    }
};
} // namespace Kosmos::Editor
#endif // KOSMOS_EDITOR_H