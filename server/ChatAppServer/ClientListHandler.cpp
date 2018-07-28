#include "ClientListHandler.h"

ClientListHandler::ClientListHandler()
{

}

std::string ClientListHandler::handle(const std::string& jsonRequest)
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
