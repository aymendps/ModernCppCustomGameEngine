#pragma once
#include <iostream>
#include <chrono>

enum class LogType
{
	Log,
	Warning,
	Error,
	Success,
	EngineRelated,
	ComponentRelated,
	EntityRelated,
	SceneRelated,
};

class Logger
{
public:
	/// <summary>
	/// Logs a message to the console. Does not add a new line at the end. 
	/// Pass the arguments as you would with std::cout, but they are seperated by a comma instead of the operator.
	/// <para/>
	/// Example: Logger::Log(LogType::Log, "Hello ", "World!") will output "Hello World!" to the console.
	/// </summary>
	/// <param name="logType">The type of log message.</param>
	/// <param name="...args">The arguments used to create the log message in ltr order.</param>
	template<typename... Args>
	static void Log(const LogType logType, const Args&... args)
	{
		if (!Logger::_allowLogging) return;

		// Decide which color to use when logging based on the log type.
		std::cout << Logger::GetLogTypeColor(logType);

		// Add timestamp to the log message.
		const auto [hours, minutes, seconds] = Logger::GetLogTimestamp();
		std::cout << "["
			<< std::setfill('0') << std::setw(2) << hours << ":"
			<< std::setfill('0') << std::setw(2) << minutes << ":"
			<< std::setfill('0') << std::setw(2) << seconds
			<< "]";

		// Add the log type prefix to the log message.
		std::cout << Logger::GetLogTypePrefix(logType) << " ";

		// Fold expression to print all arguments in left-to-right order.
		(std::cout << ... << args);

		// Reset the style of the console after logging.
		std::cout << "\033[0m";
	}

	/// <summary>
	/// Logs a message to the console. Does not add a new line at the end.
	/// Pass the arguments as you would with std::cout, but they are seperated by a comma instead of the operator.
	/// You can also specify the caller of the log message, which will be displayed in the log message.
	/// <para/>
	/// Example: Logger::Log("Main", LogType::Log, "Hello ", "World!") will output "[Main] Hello World!" to the console.
	/// </summary>
	/// <param name="caller">Name of the caller. Can be helpful to identify where the log message was called from / relates to.</param>
	/// <param name="logType">The type of log message.</param>
	/// <param name="...args">The arguments used to create the log message in ltr order.</param>
	template<typename... Args>
	static void Log(const std::string& caller, const LogType logType, const Args&... args)
	{
		if (!Logger::_allowLogging) return;

		// Decide which color to use when logging based on the log type.
		std::cout << Logger::GetLogTypeColor(logType);

		// Add timestamp to the log message.
		const auto [hours, minutes, seconds] = Logger::GetLogTimestamp();
		std::cout << "["
			<< std::setfill('0') << std::setw(2) << hours << ":"
			<< std::setfill('0') << std::setw(2) << minutes << ":"
			<< std::setfill('0') << std::setw(2) << seconds
			<< "]";

		// Add the log type prefix to the log message.
		std::cout << Logger::GetLogTypePrefix(logType);

		// Specify the caller in the log message.
		std::cout << "[" << caller << "] ";

		// Fold expression to print all arguments in left-to-right order.
		(std::cout << ... << args);

		// Reset the style of the console after logging.
		std::cout << "\033[0m";
	}

	/// <summary>
	/// Logs a message to the console. Adds a new line at the end.
	/// Pass the arguments as you would with std::cout, but they are seperated by a comma instead of the operator.
	/// <para/>
	/// Example: Logger::LogLine(LogType::Log, "Hello ", "World!") will output "Hello World!" to the console, followed by a new line.
	/// </summary>
	/// <param name="logType">The type of log message.</param>
	/// <param name="...args">The arguments used to create the log message in ltr order.</param>
	template<typename... Args>
	static void LogLine(const LogType logType, const Args&... args)
	{
		if (!Logger::_allowLogging) return;

		Logger::Log(logType, args...);
		std::cout << std::endl;
	}

	/// <summary>
	/// Logs a message to the console. Adds a new line at the end.
	/// Pass the arguments as you would with std::cout, but they are seperated by a comma instead of the operator.
	/// You can also specify the caller of the log message, which will be displayed in the log message.
	/// <para/>
	/// Example: Logger::LogLine("Main", LogType::Log, "Hello ", "World!") will output "[Main] Hello World!" to the console, followed by a new line.
	/// </summary>
	/// <param name="caller">Name of the caller. Can be helpful to identify where the log message was called from / relates to.</param>
	/// <param name="logType">The type of log message.</param>
	/// <param name="...args">The arguments used to create the log message in ltr order.</param>
	template<typename... Args>
	static void LogLine(const std::string& caller, const LogType logType, const Args&... args)
	{
		if (!Logger::_allowLogging) return;

		Logger::Log(caller, logType, args...);
		std::cout << std::endl;
	}

	/// <summary>
	/// Allows or disallows logging of all messages to the console. 
	/// </summary>
	/// <param name="allowLogging"></param>
	static void AllowLogging(const bool allowLogging) { Logger::_allowLogging = allowLogging; }

private:
	static bool _allowLogging;
	static std::string GetLogTypeColor(const LogType logType); 
	static const std::tuple<unsigned int, unsigned int, unsigned int> GetLogTimestamp();
	static std::string GetLogTypePrefix(const LogType logType);
};

