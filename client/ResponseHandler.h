#ifndef RESPONSEHANDLER_H
#define RESPONSEHANDLER_H
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <algorithm>

enum ResponseType
{
    ClientList,
    DeliverMessage
};

class ResponseHandler
{

public:
    ResponseHandler() { }

    ResponseType m_ResponseType;

    static ResponseType getResponseType(const std::string& request)
    {
        std::vector<std::string> g_requestTypes = { "ClientList", "DeliverMessage" };
        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(request, root))
        {
            std::cout << "Error: " << reader.getFormattedErrorMessages();
        }
        else
        {
            Json::Value jsonValueRequestType = root["responseType"];
            std::string requestType = jsonValueRequestType.asString();
            printf("responseType = %s \n", requestType.c_str());

            int index = std::find(g_requestTypes.begin(), g_requestTypes.end(), requestType) - g_requestTypes.begin();

            if (index >= g_requestTypes.size())
            {
                printf("Incorrect request type  \n");
              //  return 1;
            }

            switch (index)
            {
                case ClientList:
                    return ResponseType::ClientList;
                    break;
                case DeliverMessage:
                    return ResponseType::DeliverMessage;
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

    ResponseType getResponseType()
    {
        return m_ResponseType;
    }

    std::vector<std::string> handle(const std::string& jsonResponse)
    {
        std::vector<std::string> list;
      //  m_ResponseType = ResponseType::UpdateClientList;

        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(jsonResponse, root))
        {
            std::cout << "Error: " << reader.getFormattedErrorMessages();
        }
        else
        {
            Json::Value jsonValueResponseType = root["responseType"];
            std::string responseType = jsonValueResponseType.asString();
            printf("---- responseType = %s \n", responseType.c_str());

            Json::Value userNames = root["usernames"]; // array of usernames
            printf(" userNames.size() = %d \n", userNames.size());
            for (int i = 0; i < userNames.size(); i++)
            {
                std::cout << "    name: " << userNames[i].asString() << "\n";
                list.push_back(userNames[i].asString());
            }
        }
        return list;
    }


};

#endif
