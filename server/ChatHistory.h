#ifndef CHATHISTORY_H
#define CHATHISTORY_H
#include <vector>
#include <string>

struct Message
{
    std::string loginSender; //user, which has sent the message
    std::string message;
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

    void setUser1(std::string login1)
    {
        m_Login1 = login1;
    }

    void setUser2(std::string login2)
    {
        m_Login2 = login2;
    }

    void saveMessage(std::string login, std::string textMessage)
    {
       /* Message message;
        message.setSender(login);
        message.setMessage(textMessage);
        m_Messages.push_back(message);*/
    }

    //user requests new messages every 5 seconds
    /*JSONString getNewMessages()
    {
        for (int i = 0; i < m_Messages.size(); ++i)
        {
            if (m_Message[i].wasReceived() == false)
            {
                // pack to json
            }
        }
    }*/

private:
    std::string m_Login1;
    std::string m_Login2;
    std::vector<Message> m_Messages;
};

/*
class HistoryManager
{
    std::vector<ChatHistory> m_chatHistory;

    // if history was not found - return -1
    int findHistory(string login1, string login2)
    {
        for (int i = 0; i < chatHistory.size(); ++i)
        {
            if (chatHistory[i].login1 == login1 && chatHistory[i].login2 == login2)
            {
                 return i;
            }
        }
        return -1;
    }

    void saveMessage(string login1, string login2, string textMessage)
    {
        int index = findHistory(login1, login2);
        if (index == -1)
        {
            ChatHistory newChatHistory;
            newChatHistory.setUser1(login1);
            newChatHistroy.setUser2(login2);
            newChatHistory.saveMessage(login1, textMessage);
            m_chatHistory.push_back(newChatHistory);
        }
        else
        {
            m_chatHistory.saveMessage(login1, textMessage);
        }
    }

    ChatHistory retrieveHistory(string& login1, string& login2)
    {

    }

}
*/

//using of HistoryManager
/*HistoryManager historyManager;
historyManager.saveMessage(string loginSender, string loginReceiver, string message);

JSONString chatHistory = historyManager.retrieveHistory(string login1, string login2);
*/
#endif
