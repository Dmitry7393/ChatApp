#ifndef CHATHISTORY_H
#define CHATHISTORY_H
#include <vector>
#include <string>
#include <iostream>
#include <jsoncpp/json/json.h>

struct Message
{
    std::string m_LoginSender; //user, which has sent the message
    std::string m_Message;

    bool m_WasReceived;
    bool wasReceived()
    {
        return m_WasReceived;
    }

    bool m_WasRead;
    bool wasRead()
    {
        return m_WasRead;
    }
   // DateTime time;
};

class ChatHistory
{

public:
    ChatHistory() { }

    void setUsers(const std::string& login1, const std::string& login2)
    {
        m_Login1 = login1;
        m_Login2 = login2;
    }

    void saveMessage(const std::string& login, std::string textMessage)
    {
        Message message;
        message.m_LoginSender = login;
        message.m_Message = textMessage;
        m_Messages.push_back(message);
    }

    bool checkHistoryExists(const std::string& loginSender, const std::string& loginReceiver)
    {
        printf(" checkHistoryExists m_Login1 = %s \n", m_Login1.c_str());
        printf(" checkHistoryExists m_Login2 = %s \n", m_Login2.c_str());

        if ((loginSender == m_Login1 && loginReceiver == m_Login2)
           || (loginSender == m_Login2 && loginReceiver == m_Login1))
        {
            return true;
        }
        return false;
    }

    bool checkHistoryExists(const std::string& loginSender)
    {
        printf(" checkHistoryExists m_Login1 = %s \n", m_Login1.c_str());
        printf(" checkHistoryExists m_Login2 = %s \n", m_Login2.c_str());

        if (loginSender == m_Login1 || loginSender == m_Login2)
        {
            return true;
        }
        return false;
    }

    std::string getInterlocutorName(const std::string& loginSender)
    {
        if (loginSender == m_Login1)
        {
            return m_Login2;
        }
        return m_Login1;
    }

    std::vector<std::string> getMessages()
    {
        std::vector<std::string> allMessages;
        for (int i = 0; i < m_Messages.size(); ++i)
        {
            allMessages.push_back(m_Messages.at(i).m_LoginSender + " : " + m_Messages.at(i).m_Message);
        }
        return allMessages;
    }

private:
    std::string m_Login1;
    std::string m_Login2;
    std::vector<Message> m_Messages;
};

#endif
