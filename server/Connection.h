#ifndef CONNECTION
#define CONNECTION

#include <memory>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "ClientState.h"
#include "ClientListHandler.h"
#include "SaveMessageHandler.h"
#include "GetMessageHandler.h"

using namespace boost::asio;
using boost::asio::ip::tcp;

class Connection : public boost::enable_shared_from_this<Connection>
{

public:
    Connection(boost::asio::io_service& io_service, std::shared_ptr<HistoryManager> historyManager);
    void start();
    tcp::socket& socket();
    void SetState(ClientState* state);
    std::string getLogin() { return m_Login; }
    void sendResponseToClient(const std::string& msg);

private:
    void readRequestFromClient();
    size_t readComplete(const boost::system::error_code& err, size_t bytes);
    void stop();
    void handleRequest(const boost::system::error_code& error, std::size_t bytes_transferred);
    void onWriteMessage(const boost::system::error_code& err, size_t bytes);
    std::unique_ptr<RequestHandler> createHandler(RequestType requestType);

private:
    tcp::socket m_Socket;
    char m_bufferForReading[1024];
    char m_bufferForWriting[1024];
    std::string m_Login;
    static ClientState* m_ClientState;
    bool m_readRequest;
    std::shared_ptr<HistoryManager> m_HistoryManager;
};

#endif
