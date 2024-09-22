#include "Logger.h"

bool Logger::_allowLogging = true;

std::string Logger::GetLogTypeColor(const LogType logType)
{
	switch (logType)
	{
	case LogType::Log:
		return "\033[37m";
	case LogType::Warning:
		return "\033[33m";
	case LogType::Error:
		return "\033[31m";
	case LogType::Success:
		return "\033[32m";
	case LogType::EngineRelated:
		return "\033[35m";
	case LogType::ComponentRelated:
		return "\033[36m";
	case LogType::EntityRelated:
		return "\033[34m";
	case LogType::SceneRelated:
		return "\033[1;35m";
	default:
		return "\033[37m";
	}
}

const std::tuple<unsigned int, unsigned int, unsigned int> Logger::GetLogTimestamp()
{
	// Get the current time in the local time zone.
	const auto now = std::chrono::system_clock::now();
	const auto timeZone = std::chrono::current_zone();
	const auto localNowTime = timeZone->to_local(now);

	// Extract the hours, minutes, and seconds from the local time.
	const auto hours = std::chrono::floor<std::chrono::hours>(localNowTime.time_since_epoch()) % 24;
	const auto minutes = std::chrono::floor<std::chrono::minutes>(localNowTime.time_since_epoch()) % 60;
	const auto seconds = std::chrono::floor<std::chrono::seconds>(localNowTime.time_since_epoch()) % 60;

	return { static_cast<unsigned int>(hours.count()), static_cast<unsigned int>(minutes.count()), static_cast<unsigned int>(seconds.count()) };
}

std::string Logger::GetLogTypePrefix(const LogType logType)
{
	switch (logType)
	{
	case LogType::Log:
		return "[Log]";
	case LogType::Warning:
		return "[Warning]";
	case LogType::Error:
		return "[Error]";
	case LogType::Success:
		return "[Success]";
	case LogType::EngineRelated:
		return "[Engine]";
	case LogType::ComponentRelated:
		return "[Component]";
	case LogType::EntityRelated:
		return "[Entity]";
	case LogType::SceneRelated:
		return "[Scene]";
	default:
		return "[Log]";
	}
}
