#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#include <jsoncpp/json/json.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

enum RequestType
{
    Authenticate,
    GetClientList,
    GetNewMessages,
    SendMessage
};

class RequestHandler
{

public:
    RequestHandler() { }

    std::string handleRequest(const std::string& request)
    {
        std::vector<std::string> g_requestTypes = { "Authenticate", "GetClientList", "GetNewMessages", "SendMessage" };
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
                case Authenticate:
                    printf("handle authenticate request \n");
                    break;
                case GetClientList:
                    printf("handle GetClientList request \n");
                    break;
                case GetNewMessages:
                    printf("handle GetNewMessages request \n");
                    break;
                case SendMessage:
                    printf("handle SendMessage request \n");
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

private:
};

#endif
