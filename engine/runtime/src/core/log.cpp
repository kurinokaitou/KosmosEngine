#include <core/log.h>
#include <vendor/spdlog/async.h>
#include <vendor/spdlog/sinks/basic_file_sink.h>
#include <vendor/spdlog/sinks/stdout_color_sinks.h>
using namespace Kosmos::Runtime;

std::shared_ptr<spdlog::logger> Logger::s_appLogger;
std::shared_ptr<spdlog::logger> Logger::s_engineLogger;
void Logger::init() {
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_level(spdlog::level::trace);
    consoleSink->set_pattern("[%^%l%$] %v");
    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Kosmos", true);
    fileSink->set_level(spdlog::level::trace);
    fileSink->set_pattern("[%^%l%$] %v");
    const spdlog::sinks_init_list sinkList{consoleSink, fileSink};
    spdlog::init_thread_pool(8192, 2);

    s_appLogger = std::make_shared<spdlog::async_logger>("App", sinkList.begin(), sinkList.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    s_appLogger->set_level(spdlog::level::trace);
    s_appLogger->flush_on(spdlog::level::trace);
    spdlog::register_logger(s_appLogger);
    s_engineLogger = std::make_shared<spdlog::async_logger>("Engine", sinkList.begin(), sinkList.end(), spdlog::thread_pool(), spdlog::async_overflow_policy::block);
    s_engineLogger->set_level(spdlog::level::trace);
    s_engineLogger->flush_on(spdlog::level::trace);
    spdlog::register_logger(s_engineLogger);
}

void Logger::destroy() {
    s_appLogger->flush();
    s_engineLogger->flush();
    spdlog::drop_all();
}
std::shared_ptr<spdlog::logger>& Logger::getAppLogger() {
    return s_appLogger;
}

std::shared_ptr<spdlog::logger>& Logger::getEngineLogger() {
    return s_engineLogger;
}