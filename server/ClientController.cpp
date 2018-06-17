#include "ClientController.h"

ClientController::ClientController(io_service& service)
  : m_Acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 5555))
  , m_Socket(service)
  , m_HistoryManager(new HistoryManager)
{
    startAccept();
}

void ClientController::startAccept()
{
    printf("ClientController::startAccept() Waiting for clients... \n");
    boost::shared_ptr<Connection> connection(new Connection(m_Acceptor.get_io_service()));
    connection->m_HistoryManager = m_HistoryManager;
    connection->SetState((ClientState*) this);

    m_Acceptor.async_accept(connection->socket(),
          boost::bind(&ClientController::acceptHandler, this, connection,
          boost::asio::placeholders::error));
}

void ClientController::acceptHandler(boost::shared_ptr<Connection> connection, const boost::system::error_code & err)
{
    printf("ClientController::acceptHandler - new client \n");
    m_ListWithClients.push_back(connection);

    printf("******************* LIST WITH CLIENTS ******************* \n");
    for (int i = 0; i < m_ListWithClients.size(); ++i)
    {
        printf(" i = %d     %s \n", i, m_ListWithClients.at(i)->socket().remote_endpoint().address().to_string().c_str());
    }

    if (!err)
    {
        connection->start();
    }

    startAccept();
}

void ClientController::StateChanged(std::string login)
{
    printf(" ClientController::StateChanged() login = %s \n", login.c_str());
    for (int i = 0; i < m_ListWithClients.size(); ++i)
    {
        if(m_ListWithClients.at(i)->getLogin() == login)
        {
            printf(" remove from list user with login: %s \n", login.c_str());
            m_ListWithClients.erase(m_ListWithClients.begin() + i);
        }
    }
}

std::vector<std::string> ClientController::getClientList()
{
    std::vector<std::string> listWithConnectedClients;
    for (int i = 0; i < m_ListWithClients.size(); ++i)
    {
        listWithConnectedClients.push_back(m_ListWithClients.at(i)->getLogin());
        printf("client =========== %s \n", m_ListWithClients.at(i)->getLogin().c_str());
    }
    return listWithConnectedClients;
}

void ClientController::deliverMessageToClient(const std::string& receiver, const std::string& message)
{
    printf("ClientController::deliverMessageToClient message = %s \n", message.c_str());
    for (int i = 0; i < m_ListWithClients.size(); ++i)
    {
        if (m_ListWithClients.at(i)->getLogin() == receiver)
        {
            printf("ClientController::deliverMessageToClient call sendResponseToClient \n");
            m_ListWithClients.at(i)->call_ReadRequest = false;
            m_ListWithClients.at(i)->sendResponseToClient("{  \n" + message + " }");
        }
    }
    printf("ClientController::deliverMessageToClient end of method \n");
}
