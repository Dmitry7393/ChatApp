#ifndef SERVERCONNECTION
#define SERVERCONNECTION

#include <iostream>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
using namespace boost::asio;

class ServerConnection
{
public:
    ServerConnection();

    void connect(ip::tcp::endpoint ep);
    void sendRequestToServer(const std::string& request);
    std::string readResponse();

private:
    size_t readComplete(const boost::system::error_code & err, size_t bytes);

private:
    io_service m_service;
    ip::tcp::socket m_socket;
    int m_alreadyRead;
    char m_buffer[1024];
    bool m_started;
    pthread_t m_threadReadResponseFromServer;
};

#endif
