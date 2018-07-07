#include "JSONHandler.h"

JSONHandler::JSONHandler()
{

}

std::string JSONHandler::createClientListRequest(const std::string& username)
{
    Json::Value root;

    root["requestType"] = "GetClientList";
    root["username"] = username;

    return root.toStyledString();
}

std::string JSONHandler::createGetMessageWithUserRequest(const std::string& username, const std::string& usernameReceiver)
{
    Json::Value root;

    root["requestType"] = "GetMessageWithUser";
    root["username"] = username;
    root["usernameReceiver"] = usernameReceiver;

    return root.toStyledString();
}

std::string JSONHandler::createSendMessageRequest(const std::string& username, const std::string& usernameReceiver, const std::string& message)
{
    Json::Value root;

    root["requestType"] = "SendMessage";
    root["username"] = username;
    root["usernameReceiver"] = usernameReceiver;
    root["message"] = message;

    return root.toStyledString();
}

std::string createPingServerRequest(const std::string& username, const std::string& userNameReceiver)
{
    Json::Value root;

    root["requestType"] = "PingServer";
    root["username"] = username;

    return root.toStyledString();
}
