#ifndef CLIENTSERVERINTERACTION_H
#define CLIENTSERVERINTERACTION_H
#include <string>
#include <vector>

#include "NetworkHandler.h"
#include "Message.h"
#include "JSONHandler.h"

class ClientServerInteraction
{

public:
    ClientServerInteraction(const std::string& serverIP, int port)
       : m_Endpoint(ip::address::from_string(serverIP), port),
         m_ServerConnection(new ServerConnection),
         m_NetworkHandler(m_ServerConnection)
    {
        try
        {
            m_ServerConnection->connect(m_Endpoint);
        }
        catch(boost::system::system_error & err)
        {
            std::cout << err.what() << std::endl;
        }

        printf("m_Username = %s \n", m_Username.c_str());
        m_ServerConnection->setUsername(m_Username);
        //m_ServerConnection->sendMessage(ui->m_LineEditMessage->text().toStdString());
    }

    void setUsername(const std::string& username)
    {
        m_Username = username;
    }

    std::string getUsername()
    {
        return m_Username;
    }

    int authenticate()
    {
        m_ServerConnection->sendRequestToServer(m_JSONHandler.createAuthenticateRequest(m_Username));
    }

    void sendMessage(const std::string& message, const std::string& userReceiver)
    {
        m_ServerConnection->sendRequestToServer(m_JSONHandler.createSendMessageRequest(m_Username, userReceiver, message));
    }

    std::vector<std::string> getClientList()
    {
        std::vector<std::string> list;
        std::string resp = m_ServerConnection->sendRequestToServer(m_JSONHandler.createClientListRequest(m_Username));
        printf("RESPONSE FROM SERVER = \n");
        std::cout << resp << "\n";

        printf("--------------------- parse ------------------- \n");
        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(resp, root))
        {
            std::cout << "Error: " << reader.getFormattedErrorMessages();
        }
        else
        {
            Json::Value jsonValueResponseType = root["responseType"];
            std::string responseType = jsonValueResponseType.asString();
            printf("---- responseType = %s \n", responseType.c_str());

            Json::Value userNames = root["usernames"]; // array of usernames
            printf(" userNames.size() = %d \n", userNames.size());
            for (int i = 0; i < userNames.size(); i++)
            {
                std::cout << "    name: " << userNames[i].asString() << "\n";
                list.push_back(userNames[i].asString());
            }
        }
        return list;
    }

    std::string m_MessagesToAllUsers;
    void getMessages()
    {
        std::string resp = m_ServerConnection->sendRequestToServer(m_JSONHandler.createCheckNewMessagesRequest(m_Username));

        m_MessagesToAllUsers = resp;
        printf("RESPONSE FROM SERVER = \n");
        std::cout << resp << "\n";
    }

    std::vector<std::string> getMessagesWithClient(const std::string& selectedUser)
    {
        std::vector<std::string> list;
        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(m_MessagesToAllUsers, root))
        {
            std::cout << "Error: " << reader.getFormattedErrorMessages();
        }
        else
        {
            Json::Value jsonValueResponseType = root["responseType"];
            std::string responseType = jsonValueResponseType.asString();
            printf("---- responseType = %s \n", responseType.c_str());

            Json::Value history = root["history"]; // array of history
            printf(" history.size() = %d \n", history.size());
            for (int i = 0; i < history.size(); i++)
            {
               //std::cout << "    history2: " << history2[i].asString() << "\n";
               Json::Value block = history[i];
               Json::Value jsonUsername = block["username"];

               std::string username = jsonUsername.asString();
               printf("---- username = %s \n", username.c_str());

               if(username == selectedUser)
               {
                   Json::Value messages = block["messages"];
                   for (int j = 0; j < messages.size(); j++)
                   {
                       std::cout << "     messages[i]: " <<  messages[j].asString() << "\n";
                       list.push_back(messages[j].asString());
                   }
               }
            }
        }
        return list;
    }

private:
    std::string m_Username;
    ip::tcp::endpoint m_Endpoint;
    boost::shared_ptr<ServerConnection> m_ServerConnection;
    NetworkHandler m_NetworkHandler;
    JSONHandler m_JSONHandler;
};

#endif
