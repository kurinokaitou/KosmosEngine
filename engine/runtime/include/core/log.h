#ifndef LOG_H
#define LOG_H

#include <memory>
#include <stdexcept>
#include <vendor/spdlog/spdlog.h>
namespace Kosmos::Runtime {
class Logger {
public:
    static void init();
    static void destroy();
    static std::shared_ptr<spdlog::logger>& getAppLogger();
    static std::shared_ptr<spdlog::logger>& getEngineLogger();

private:
    static std::shared_ptr<spdlog::logger> s_appLogger;
    static std::shared_ptr<spdlog::logger> s_engineLogger;
};
} // namespace Kosmos::Runtime

#define KS_LOG_TRACE(...) ::Kosmos::Runtime::Logger::getAppLogger()->trace("[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__)
#define KS_LOG_INFO(...) ::Kosmos::Runtime::Logger::getAppLogger()->info("[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__)
#define KS_LOG_WARN(...) ::Kosmos::Runtime::Logger::getAppLogger()->warn("[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__)
#define KS_LOG_ERROR(...) ::Kosmos::Runtime::Logger::getAppLogger()->error("[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__)
#define KS_LOG_FATAL(...)                                                                                          \
    do {                                                                                                           \
        ::Kosmos::Runtime::Logger::getAppLogger()->critical("[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__); \
        throw std::runtime_error(__VA_ARGS__);                                                                     \
    } while (false)

#define KS_ENGINE_LOG_TRACE(...) ::Kosmos::Runtime::Logger::getEngineLogger()->trace("[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__)
#define KS_ENGINE_LOG_INFO(...) ::Kosmos::Runtime::Logger::getEngineLogger()->info("[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__)
#define KS_ENGINE_LOG_WARN(...) ::Kosmos::Runtime::Logger::getEngineLogger()->warn("[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__)
#define KS_ENGINE_LOG_ERROR(...) ::Kosmos::Runtime::Logger::getEngineLogger()->error("[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__)
#define KS_ENGINE_LOG_FATAL(...)                                                                                      \
    do {                                                                                                              \
        ::Kosmos::Runtime::Logger::getEngineLogger()->critical("[" + std::string(__FUNCTION__) + "] " + __VA_ARGS__); \
        throw std::runtime_error(__VA_ARGS__);                                                                        \
    } while (false)
#endif // LOG_H