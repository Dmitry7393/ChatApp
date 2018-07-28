#include "ChatHistory.h"

ChatHistory::ChatHistory()
{

}

void ChatHistory::setUsers(const std::string& login1, const std::string& login2)
{
    m_Login1 = login1;
    m_Login2 = login2;
}

void ChatHistory::saveMessage(const std::string& login, const std::string& textMessage)
{
    m_Messages.emplace_back(login, textMessage);
}

bool ChatHistory::checkHistoryExists(const std::string& loginSender, const std::string& loginReceiver)
{
    if ((loginSender == m_Login1 && loginReceiver == m_Login2)
       || (loginSender == m_Login2 && loginReceiver == m_Login1))
    {
        return true;
    }
    return false;
}

bool ChatHistory::checkHistoryExists(const std::string& loginSender)
{
    if (loginSender == m_Login1 || loginSender == m_Login2)
    {
        return true;
    }
    return false;
}

std::string ChatHistory::getInterlocutorName(const std::string& loginSender)
{
    if (loginSender == m_Login1)
    {
        return m_Login2;
    }
    return m_Login1;
}

std::vector<std::string> ChatHistory::getMessages()
{
    std::vector<std::string> allMessages;
    for (int i = 0; i < m_Messages.size(); ++i)
    {
        allMessages.push_back(m_Messages.at(i).m_LoginSender + " : " + m_Messages.at(i).m_Message);
    }
    return allMessages;
}
