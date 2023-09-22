#pragma once
#include <queue>
#include <iostream>
#include <map>

class LogReporter
{
	enum MessageType
	{
		error,
		log,
		warning
	};
	struct Message
	{
	public:
		const std::string content;
		MessageType type;
		Message(const std::string& contentValue, MessageType typeValue) : content(contentValue), type(typeValue) {}
		std::string MessageTypeToString();
	};
	static std::queue<Message> allLogs;
	
public:
	static void Error(const std::string& _log);
	static void Log(const std::string& _log);
	static void Warning(const std::string& _log);

	static std::string popNextMessage();
	static size_t getMessageCount();
};