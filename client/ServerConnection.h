#ifndef SERVERCONNECTION
#define SERVERCONNECTION

#include <iostream>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <jsoncpp/json/json.h>
using namespace boost::asio;

struct ServerConnection
{
    ServerConnection();

    void connect(ip::tcp::endpoint ep);
    void checkNewMessages();

    void sendMessage(const std::string& message);
    void setUsername(std::string username);

    std::string username() const;

private:
    void read_answer();
    void process_msg();
    size_t read_complete(const boost::system::error_code & err, size_t bytes);
    std::string getJSONString(const std::string requestType, const std::string& receiver, const std::string& message);

private:
    io_service service;

    ip::tcp::socket sock_;
    enum { max_msg = 1024 };
    int already_read_;
    char buff_[max_msg];
    bool started_;
    std::string m_CurrentUsername;
};

#endif