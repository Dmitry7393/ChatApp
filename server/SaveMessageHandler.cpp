#include "SaveMessageHandler.h"

SaveMessageHandler::SaveMessageHandler()
{

}

std::string SaveMessageHandler::handle(const std::string& jsonRequest)
{
    printf("===================== SaveMessageHandler ========================== \n");
    std::string loginSender = parseJSONValue(jsonRequest, JSONData::username);
    std::string loginReceiver = parseJSONValue(jsonRequest, JSONData::usernameReceiver);
    std::string message = parseJSONValue(jsonRequest, JSONData::message);

    printf("loginSender = %s \n", loginSender.c_str());
    printf("loginReceiver = %s \n", loginReceiver.c_str());
    printf("message = %s \n", message.c_str());

    if (m_HistoryManager->saveMessage(loginSender, loginReceiver, message))
    {
        return createSendMessageResponse();
    }
}

std::string SaveMessageHandler::createSendMessageResponse()
{
    Json::Value root;

    root["requestType"] = "SendMessage";
    root["status"] = "ok";

    return root.toStyledString();
}
