#ifndef GETMESSAGE_HANDLER_H
#define GETMESSAGE_HANDLER_H

#include "RequestHandler.h"

class GetMessageHandler : public RequestHandler
{
public:
    GetMessageHandler() { }

    std::string handle(const std::string& jsonRequest)
    {
         printf("===================== GetMessageHandler ========================== \n");

         std::string loginSender = parseJSONValue(jsonRequest, JSONData::username);
         printf("  loginSender = %s \n", loginSender.c_str());
         std::string loginReceiver = parseJSONValue(jsonRequest, JSONData::usernameReceiver);
         printf("  loginReceiver = %s \n", loginReceiver.c_str());

         std::vector<std::string> messages = m_HistoryManager->getMessagesBetweenTwoUsers(loginSender, loginReceiver);
         Json::Value root;

         root["responseType"] = "DeliverMessage";
         Json::Value listMessageNode = root["messages"];

         for (int i = 0; i < messages.size(); ++i)
         {
             printf(" apppend message = %s \n", messages.at(i).c_str());
             listMessageNode.append(messages.at(i));
         }
         root["messages"] = listMessageNode;
         return root.toStyledString();
     }
};

#endif
