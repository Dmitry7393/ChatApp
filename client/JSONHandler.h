#ifndef JSONHANDLER_H
#define JSONHANDLER_H
#include <vector>
#include <string>

#include <jsoncpp/json/json.h>

class JSONHandler
{

public:
    JSONHandler();

    std::string createClientListRequest(const std::string& username);
    std::string createGetMessageWithUserRequest(const std::string& username, const std::string& userNameReceiver);

    std::string createSendMessageRequest(const std::string& username,
                                         const std::string& usernameReceiver,
                                         const std::string& message);

    std::string createPingServerRequest(const std::string& username, const std::string& userNameReceiver);
};

#endif
