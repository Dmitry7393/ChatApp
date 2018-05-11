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

    int authenticate()
    {
        m_ServerConnection->sendRequestToServer(m_JSONHandler.createAuthenticateRequest(m_Username));
    }

    void sendMessage(const std::string& msg)
    {
        m_ServerConnection->sendRequestToServer(m_JSONHandler.createSendMessageRequest(m_Username, "toUser3", msg));
    }

    std::vector<std::string> getClientList()
    {

    }

    std::vector<Message> getMessages()
    {

    }


private:
    std::string m_Username;
    ip::tcp::endpoint m_Endpoint;
    boost::shared_ptr<ServerConnection> m_ServerConnection;
    NetworkHandler m_NetworkHandler;
    JSONHandler m_JSONHandler;
};

#endif
