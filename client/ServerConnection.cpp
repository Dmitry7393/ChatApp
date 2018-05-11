#include "ServerConnection.h"

ServerConnection::ServerConnection()
    : sock_(service)
    , started_(true)
{

}

void ServerConnection::connect(ip::tcp::endpoint ep)
{
    sock_.connect(ep);
}

void ServerConnection::setUsername(std::string username)
{
    m_CurrentUsername = username;
}

void ServerConnection::sendRequestToServer(const std::string& request)
{
    sock_.write_some(buffer(request));
    read_answer();
}

std::string ServerConnection::username() const
{
    return m_CurrentUsername;
}

void ServerConnection::read_answer()
{
    already_read_ = 0;
    read(sock_, buffer(buff_), boost::bind(&ServerConnection::read_complete, this, _1, _2));
    process_msg();
}

void ServerConnection::process_msg()
{
    std::string msg(buff_, already_read_);
    std::cout << "Response from server: " << msg << std::endl;
}

size_t ServerConnection::read_complete(const boost::system::error_code & err, size_t bytes)
{
    if ( err)
        return 0;
    already_read_ = bytes;
    bool found = std::find(buff_, buff_ + bytes, '\n') < buff_ + bytes;
    return found ? 0 : 1;
}
