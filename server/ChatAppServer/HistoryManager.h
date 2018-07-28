#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H
#include "ChatHistory.h"

class HistoryManager
{
public:
    bool saveMessage(const std::string& loginSender, const std::string& loginReceiver, const std::string& message);
    std::string retrieveHistory(const std::string& loginSender);
    std::vector<std::string> getMessagesBetweenTwoUsers(const std::string& loginSender, const std::string& loginReceiver);

private:
    // if history was not found - return -1
    int findHistory(const std::string& login1, const std::string& login2);

private:
    std::vector<ChatHistory> m_chatHistory;
};

#endif
