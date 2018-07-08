#ifndef CLIENTLISTHANDLER_H
#define CLIENTLISTHANDLER_H
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <algorithm>

#include "ResponseHandler.h"

class ClientListHandler : public ResponseHandler
{

public:
    ClientListHandler() { }

    std::vector<std::string> handle(const std::string& jsonResponse)
    {
        printf("  ========= this is ClientListHandler ========== \n");
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
