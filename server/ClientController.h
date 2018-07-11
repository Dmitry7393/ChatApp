#ifndef CLIENT_CONTROLLER
#define CLIENT_CONTROLLER

#include "Connection.h"
#include "HistoryManager.h"

class ClientController : public ClientState
{

public:
    ClientController(io_service& service);
    void removeClient(std::string login);
    std::vector<std::string> getClientList();
    void deliverMessageToClient(const std::string& receiver, const std::string& message);

private:
    void startAccept();
    void acceptHandler(boost::shared_ptr<Connection> connection, const boost::system::error_code & err);

private:
    ip::tcp::acceptor m_acceptor;
    ip::tcp::socket m_socket;
    char m_bufferForReading[1024];
    char m_bufferForWriting[1024];
    std::string m_login;

    std::vector<boost::shared_ptr<Connection> > m_listWithClients;
    std::shared_ptr<HistoryManager> m_historyManager;
};

#endif
