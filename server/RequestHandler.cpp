#include "RequestHandler.h"

RequestHandler::RequestHandler()
{

}

std::string RequestHandler::parseJSONValue(const std::string& jsonString, JSONData jsonData)
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

RequestType RequestHandler::getRequestType(const std::string& request)
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
            return RequestType::PingServer;
        }

        switch (index)
        {
            case GetClientList:
                return RequestType::GetClientList;
                break;
            case GetMessageWithUser:
                return RequestType::GetMessageWithUser;
                break;
            case SendMessage:
                return RequestType::SendMessage;
                break;
            case PingServer:
                return RequestType::PingServer;
                break;
            default:
                printf("Incorrect request type - return default \n");
                return RequestType::PingServer;
        }
     }
}

std::string RequestHandler::getClientName(const std::string& request)
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

void RequestHandler::setClientList(std::vector<std::string> clientList)
{
    m_ClientList = clientList;
}
