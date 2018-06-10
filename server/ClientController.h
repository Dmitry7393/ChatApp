#ifndef CLIENT_CONTROLLER
#define CLIENT_CONTROLLER

#include "Connection.h"
#include "HistoryManager.h"

class ClientController : public ClientState
{

public:
    ClientController(io_service& service);
    void StateChanged(std::string login);
    std::vector<std::string> getClientList();

private:
    void startAccept();
    void acceptHandler(boost::shared_ptr<Connection> connection, const boost::system::error_code & err);

private:
    ip::tcp::acceptor m_Acceptor;
    ip::tcp::socket m_Socket;
    enum { max_msg = 1024 };
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    std::string m_Login;

    std::vector<boost::shared_ptr<Connection> > m_ListWithClients;
    std::shared_ptr<HistoryManager> m_HistoryManager;
};

#endif
