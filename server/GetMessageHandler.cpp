#include "GetMessageHandler.h"

GetMessageHandler::GetMessageHandler(std::shared_ptr<HistoryManager> historyManager)
    : m_historyManager(historyManager)
{

}

std::string GetMessageHandler::handle(const std::string& jsonRequest)
{
     std::string loginSender = parseJSONValue(jsonRequest, JSONData::username);
     std::string loginReceiver = parseJSONValue(jsonRequest, JSONData::usernameReceiver);

     std::vector<std::string> messages = m_historyManager->getMessagesBetweenTwoUsers(loginSender, loginReceiver);
     Json::Value root;

     root["responseType"] = "DeliverMessage";
     Json::Value listMessageNode = root["messages"];

     for (int i = 0; i < messages.size(); ++i)
     {
         listMessageNode.append(messages.at(i));
     }
     root["messages"] = listMessageNode;
     return root.toStyledString();
 }
