#include "LogReporter.h"
std::string LogReporter::Message::MessageTypeToString() {
	static std::map<MessageType, std::string> messageTypeMap = {
		{MessageType::error, "Error"},
		{MessageType::log, "Log"},
		{MessageType::warning, "Warning"}
	};
	auto it = messageTypeMap.find(type);
	if (it != messageTypeMap.end()) {
		return it->second;
	}
	return "Unknown";
}

void LogReporter::Error(const std::string& _log)
{
	LogReporter::Message mess(_log, MessageType::error);
	allLogs.push(mess);
}
void LogReporter::Log(const std::string& _log)
{
	LogReporter::Message mess(_log, MessageType::log);
	allLogs.push(mess);
}
void LogReporter::Warning(const std::string& _log)
{
	LogReporter::Message mess(_log, MessageType::warning);
	allLogs.push(mess);
}

std::string LogReporter::popNextMessage()
{
	if (allLogs.empty()) return "";
	const std::string message = allLogs.front().MessageTypeToString()  + ": " + allLogs.front().content;
	allLogs.pop();
	return message;
}
size_t LogReporter::getMessageCount()
{
	return allLogs.size();
}
std::queue<LogReporter::Message>  LogReporter::allLogs;