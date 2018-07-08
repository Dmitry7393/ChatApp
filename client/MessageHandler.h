#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <algorithm>

#include "ResponseHandler.h"

class MessageHandler : public ResponseHandler
{

public:
    MessageHandler() { }
    std::vector<std::string> handle(const std::string& jsonResponse)
    {
        printf("  ========= this is MessageHandler ========== \n");

        std::vector<std::string> list;
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

            Json::Value messages = root["messages"]; // array of messages
            printf(" messages.size() = %d \n", messages.size());
            for (int i = 0; i < messages.size(); i++)
            {
                std::cout << "    name: " << messages[i].asString() << "\n";
                list.push_back(messages[i].asString());
            }
        }
        return list;
    }
};

#endif
