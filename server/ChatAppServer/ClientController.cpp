#include "ClientController.h"

ClientController::ClientController(io_service& service)
  : m_acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 5555))
  , m_socket(service)
  , m_historyManager(std::make_shared<HistoryManager>())
{
    startAccept();
}

void ClientController::startAccept()
{
    printf("Waiting for clients... \n");
    boost::shared_ptr<Connection> connection(new Connection(m_acceptor.get_io_service(), m_historyManager));
    connection->SetState(static_cast<ClientState*> (this));

    m_acceptor.async_accept(connection->socket(),
          boost::bind(&ClientController::acceptHandler, this, connection,
          boost::asio::placeholders::error));
}

void ClientController::acceptHandler(boost::shared_ptr<Connection> connection, const boost::system::error_code & err)
{
    m_listWithClients.push_back(connection);

    if (!err)
    {
        connection->start();
        startAccept();
    }
}

void ClientController::removeClient(std::string login)
{
    for (int i = 0; i < m_listWithClients.size(); ++i)
    {
        if(m_listWithClients.at(i)->getLogin() == login)
        {
            printf("ClientController::removeClient() login: %s \n", login.c_str());
            m_listWithClients.erase(m_listWithClients.begin() + i);
        }
    }
}

std::vector<std::string> ClientController::getClientList()
{
    std::vector<std::string> listWithConnectedClients;
    for (int i = 0; i < m_listWithClients.size(); ++i)
    {
        listWithConnectedClients.push_back(m_listWithClients.at(i)->getLogin());
    }
    return listWithConnectedClients;
}

void ClientController::deliverMessageToClient(const std::string& receiver, const std::string& message)
{
    for (int i = 0; i < m_listWithClients.size(); ++i)
    {
        if (m_listWithClients.at(i)->getLogin() == receiver)
        {
            m_listWithClients.at(i)->sendResponseToClient(message);
        }
    }
}