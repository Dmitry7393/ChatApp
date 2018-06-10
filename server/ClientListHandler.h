#ifndef CLIENTLIST_HANDLER_H
#define CLIENTLIST_HANDLER_H
#include <jsoncpp/json/json.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>

#include "RequestHandler.h"

class ClientListHandler : public RequestHandler
{

public:
    ClientListHandler() { }

    std::string handle(const std::string& jsonRequest)
    {
        Json::Value root;

        root["responseType"] = "ClientList";
        Json::Value listClientNode = root["usernames"];

        for (int i = 0; i < m_ClientList.size(); ++i)
        {
            listClientNode.append(m_ClientList.at(i));
        }
        root["usernames"] = listClientNode;
        return root.toStyledString();
    }

};

#endif
