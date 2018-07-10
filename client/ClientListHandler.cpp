#include "ClientListHandler.h"

ClientListHandler::ClientListHandler()
{

}

std::vector<std::string> ClientListHandler::handle(const std::string& jsonResponse)
{
    std::vector<std::string> list;

    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(jsonResponse, root))
    {
        std::cout << "Error: " << reader.getFormattedErrorMessages();
    }
    else
    {
        Json::Value userNames = root["usernames"];
        for (int i = 0; i < userNames.size(); i++)
        {
            list.push_back(userNames[i].asString());
        }
    }
    return list;
}
