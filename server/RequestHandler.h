#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#include <jsoncpp/json/json.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>

#include "HistoryManager.h"

enum RequestType
{
    GetClientList,
    GetMessageWithUser,
    SendMessage,
    PingServer
};

enum JSONData
{
    requestType,
    username,
    usernameReceiver,
    message
};

class RequestHandler
{

public:
    std::vector<std::string> m_ClientList;
    RequestHandler();

    virtual std::string handle(const std::string& jsonRequest) = 0;
    std::string parseJSONValue(const std::string& jsonString, JSONData jsonData);
    static RequestType getRequestType(const std::string& request);
    std::string getClientName(const std::string& request);

public:
    std::shared_ptr<HistoryManager> m_HistoryManager;
};

#endif
