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
        printf("  loginSender = %s \n", loginSender);
        //std::string loginReceiver = parseJSONValue(jsonRequest, JSONData::usernameReceiver);

        return m_HistoryManager->retrieveHistory(loginSender);
       /* std::vector<std::string> messages = m_HistoryManager->retrieveHistory(loginSender, "dmitry");
        Json::Value root;

        root["responseType"] = "GetMessages";
        Json::Value listMessageNode = root["messages"];

        for (int i = 0; i < messages.size(); ++i)
        {
            listMessageNode.append(messages.at(i));
        }
        root["messages"] = listMessageNode;
        return root.toStyledString();*/
    }
};

#endif
