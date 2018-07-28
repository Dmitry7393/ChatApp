#ifndef CHATHISTORY_H
#define CHATHISTORY_H
#include <vector>
#include <string>
#include <iostream>
#include <jsoncpp/json/json.h>

struct Message
{
    Message(const std::string& loginSender, const std::string& message)
        : m_LoginSender(loginSender)
        , m_Message(message)
    {
    }

    std::string m_LoginSender; //user, which has sent the message
    std::string m_Message;
};

class ChatHistory
{

public:
    ChatHistory();

    void setUsers(const std::string& login1, const std::string& login2);
    void saveMessage(const std::string& login, const std::string&  textMessage);
    bool checkHistoryExists(const std::string& loginSender, const std::string& loginReceiver);
    bool checkHistoryExists(const std::string& loginSender);
    std::string getInterlocutorName(const std::string& loginSender);
    std::vector<std::string> getMessages();

private:
    std::string m_Login1;
    std::string m_Login2;
    std::vector<Message> m_Messages;
};

#endif
