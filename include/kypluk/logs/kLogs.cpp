#include "kLogs.h"

using namespace kypluk;

Logger::Logger(handler_t msgHandler) : messageHandler(msgHandler),
    Debug(*this), Info(*this), Warning(*this), Critical(*this), Fatal(*this) 
{

}

void Logger::print(MsgType type, std::string data) {
    messageHandler(type, data);
}

void Logger::setMessageHandler(Logger::handler_t newHandler) {
    this->messageHandler = newHandler;
}