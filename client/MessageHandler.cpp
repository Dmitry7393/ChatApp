#include "MessageHandler.h"

MessageHandler::MessageHandler()
{

}

std::vector<std::string> MessageHandler::handle(const std::string& jsonResponse)
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
        Json::Value messages = root["messages"];
        for (int i = 0; i < messages.size(); i++)
        {
            list.push_back(messages[i].asString());
        }
    }
    return list;
}
