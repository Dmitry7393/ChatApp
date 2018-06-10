#ifndef JSONHANDLER_H
#define JSONHANDLER_H
#include <vector>
#include <string>

#include <jsoncpp/json/json.h>

class JSONHandler
{

public:
    JSONHandler()
    {

    }

    std::string createAuthenticateRequest(const std::string& username)
    {
        Json::Value root;

        root["requestType"] = "Authenticate";
        root["username"] = username;

        return root.toStyledString();
    }

    std::string createClientListRequest(const std::string& username)
    {
        Json::Value root;

        root["requestType"] = "GetClientList";
        root["username"] = username;

        return root.toStyledString();
    }

    std::string createCheckNewMessagesRequest(const std::string& username)
    {
        Json::Value root;

        root["requestType"] = "GetNewMessages";
        root["username"] = username;

        return root.toStyledString();
    }

    std::string createSendMessageRequest(const std::string& username, const std::string& usernameReceiver, const std::string& message)
    {
        Json::Value root;

        root["requestType"] = "SendMessage";
        root["username"] = username;
        root["usernameReceiver"] = usernameReceiver;
        root["message"] = message;

        return root.toStyledString();
    }

    std::string createHistoryRequest()
    {

    }

private:

};

#endif
