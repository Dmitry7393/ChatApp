#include "ClientController.h"

ClientController::ClientController(io_service& service)
  : m_Acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 5555))
  , m_Socket(service)
{
    startAccept();
}

void ClientController::startAccept()
{
    printf("Waiting for clients... \n");
    boost::shared_ptr<Connection> connection(new Connection(m_Acceptor.get_io_service()));
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
