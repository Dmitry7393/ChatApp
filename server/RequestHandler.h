#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#include <jsoncpp/json/json.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>

#include "HistoryManager.h"

enum RequestType
{
    GetClientList,
    GetMessageWithUser,
    SendMessage,
    PingServer
};

enum JSONData
{
    requestType,
    username,
    usernameReceiver,
    message
};

class RequestHandler
{

public:
    std::vector<std::string> m_ClientList;
    RequestHandler() { }

    virtual std::string handle(const std::string& jsonRequest) = 0;

    std::string parseJSONValue(const std::string& jsonString, JSONData jsonData)
    {
        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(jsonString, root))
        {
            std::cout << "Error: " << reader.getFormattedErrorMessages();
        }
        else
        {
            Json::Value jsonValue;
            switch (jsonData)
            {
                case requestType:
                    jsonValue = root["RequestType"];
                    return jsonValue.asString();
                break;
                case username:
                    jsonValue = root["username"];
                    return jsonValue.asString();

                case usernameReceiver:
                    jsonValue = root["usernameReceiver"];
                    return jsonValue.asString();

                case message:
                    jsonValue = root["message"];
                    return jsonValue.asString();
                default:
                    return "";
            }
        }
    }

    static RequestType getRequestType(const std::string& request)
    {
        std::vector<std::string> g_requestTypes = { "GetClientList", "GetMessageWithUser", "SendMessage", "PingServer" };
        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(request, root))
        {
            std::cout << "Error: " << reader.getFormattedErrorMessages();
        }
        else
        {
            Json::Value jsonValueRequestType = root["requestType"];
            std::string requestType = jsonValueRequestType.asString();
            printf("requestType = %s \n", requestType.c_str());

            int index = std::find(g_requestTypes.begin(), g_requestTypes.end(), requestType) - g_requestTypes.begin();

            if (index >= g_requestTypes.size())
            {
                printf("Incorrect request type  \n");
              //  return 1;
            }

            switch (index)
            {
                case GetClientList:
                    printf("handle GetClientList request \n");
                    return RequestType::GetClientList;
                    break;
                case GetMessageWithUser:
                    printf("handle GetNewMessages request \n");
                    return RequestType::GetMessageWithUser;
                    break;
                case SendMessage:
                    printf("handle SendMessage request \n");
                    return RequestType::SendMessage;
                    break;
                case PingServer:
                    printf("handle SendMessage request \n");
                    return RequestType::PingServer;
                    break;
                default:
                    printf("Incorrect request type \n");
                    //return 1;
            }

            Json::Value jsonValueLogin = root["loginSender"];
            std::string m_Login = jsonValueLogin.asString();
            printf("login = %s \n", m_Login.c_str());
         }
    }

    std::string getClientName(const std::string& request)
    {
        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(request, root))
        {
            std::cout << "Error: " << reader.getFormattedErrorMessages();
        }
        else
        {
            Json::Value jsonValueLogin = root["username"];
            return jsonValueLogin.asString();
        }
    }

public:
    std::shared_ptr<HistoryManager> m_HistoryManager;
};

#endif
