#ifndef CONNECTION
#define CONNECTION

#include <memory>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
using namespace boost::asio;
using boost::asio::ip::tcp;

#include "ClientState.h"
#include "ClientListHandler.h"
#include "SaveMessageHandler.h"
#include "GetMessageHandler.h"

class Connection : public boost::enable_shared_from_this<Connection>
{

public:
    Connection(boost::asio::io_service& io_service);
    void start();
    tcp::socket& socket();
    void SetState(ClientState* state);
    std::string getLogin() { return m_Login; }

    std::shared_ptr<HistoryManager> m_HistoryManager;

private:

  void readRequestFromClient();
  size_t readComplete(const boost::system::error_code & err, size_t bytes);
  void stop();
  void handleRequest(const boost::system::error_code& error, std::size_t bytes_transferred);
  void sendResponseToClient(const std::string& msg);
  void onWriteMessage(const boost::system::error_code& err, size_t bytes);
  RequestHandler* createHandler(RequestType requestType);

private:
    tcp::socket m_Socket;
    enum { max_msg = 1024 };
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    std::string m_Login;

private:
    static ClientState* m_ClientState;


};

#endif
