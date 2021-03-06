#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H
#include "ChatHistory.h"

class HistoryManager
{
public:
    bool saveMessage(const std::string& loginSender, const std::string& loginReceiver, const std::string& message)
    {
        int index = findHistory(loginSender, loginReceiver);
        printf("HistoryManager::saveMessage index = %d \n", index);
        if (index == -1)
        {
            ChatHistory newChatHistory;
            newChatHistory.setUsers(loginSender, loginReceiver);
            newChatHistory.saveMessage(loginSender, message);
            m_chatHistory.push_back(newChatHistory);
        }
        else
        {
            m_chatHistory.at(index).saveMessage(loginSender, message);
        }
        return true;
    }

    std::string retrieveHistory(const std::string& loginSender)
    {
        Json::Value root;
        root["responseType"] = "SendMessage";

        Json::Value history;
        for (int i = 0; i < m_chatHistory.size(); ++i)
        {
            if (m_chatHistory.at(i).checkHistoryExists(loginSender))
            {
                Json::Value historyWithUser;
                historyWithUser["username"] = m_chatHistory.at(i).getInterlocutorName(loginSender);

                Json::Value listMessageNode;
                std::vector<std::string> messages = m_chatHistory.at(i).getMessages();
                for (int j = 0; j < messages.size(); ++j)
                {
                    listMessageNode.append(messages.at(j));
                }
                historyWithUser["messages"] = listMessageNode;
                history.append(historyWithUser);
            }
        }
        root["history"] = history;

        std::cout << root << "\n";
        return root.toStyledString();
    }

private:
    // if history was not found - return -1
    int findHistory(const std::string& login1, const std::string& login2)
    {
        for (int i = 0; i < m_chatHistory.size(); ++i)
        {
            if (m_chatHistory.at(i).checkHistoryExists(login1, login2))
            {
                 return i;
            }
        }
        return -1;
    }

private:
    std::vector<ChatHistory> m_chatHistory;
};

#endif
