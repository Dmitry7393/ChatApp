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

std::string ServerConnection::sendRequestToServer(const std::string& request)
{
    sock_.write_some(buffer(request));
    return read_answer();
}

std::string ServerConnection::username() const
{
    return m_CurrentUsername;
}

std::string ServerConnection::read_answer()
{
    already_read_ = 0;
    read(sock_, buffer(buff_), boost::bind(&ServerConnection::read_complete, this, _1, _2));
    std::string msg(buff_, already_read_);
    return msg;
}

size_t ServerConnection::read_complete(const boost::system::error_code & err, size_t bytes)
{
    if ( err)
        return 0;

    int count = 0;
    bool found = false;
    already_read_ = bytes;

    for (size_t i = 0; i < bytes; ++i)
    {
        if (buff_[i] == '{')
        {
            count++;
        }
        if (buff_[i] == '}')
        {
            count--;
            if (count == 0)
            {
                found = true;
                break;
            }
        }
    }

    return found ? 0 : 1;
}
