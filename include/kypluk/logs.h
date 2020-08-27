#ifndef KYPLUK_LOGS_H
#define KYPLUK_LOGS_H

#include <string>

namespace kypluk {

class Logger {
public:
    enum class MsgType {
        Debug,
        Info,
        Warning,
        Critical,
        Fatal
    };

    using handler_type = void(*)(MsgType, std::string);

private:
    template<MsgType msgType>
    class Outputer {
        Logger& toOut;
    public:
        Outputer(Logger& toOut) : toOut(toOut) {}
        Outputer& operator << (std::string data) {
            toOut.print(msgType, data);
            return *this;
        }
    };

public:
    Outputer<MsgType::Debug> Debug;
    Outputer<MsgType::Info> Info;
    Outputer<MsgType::Warning> Warning;
    Outputer<MsgType::Critical> Critical;
    Outputer<MsgType::Fatal> Fatal;

    Logger(handler_type msgHandler) : messageHandler(msgHandler),
    Debug(*this), Info(*this), Warning(*this), Critical(*this), Fatal(*this)
    {
    }

    void setMessageHandler(Logger::handler_type newHandler) {
        this->messageHandler = newHandler;
    }

    void print(MsgType type, std::string data) {
        messageHandler(type, data);
    }

private:
    handler_type messageHandler;
};

}

#endif
