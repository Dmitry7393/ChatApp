#include "ServerConnection.h"


ServerConnection::ServerConnection()
    : sock_(service)
    , started_(true)
{

}

std::string ServerConnection::readResponse()
{
    printf("--------------- READER ------------------- \n");
    already_read_ = 0;
    read(sock_, buffer(buff_), boost::bind(&ServerConnection::readComplete, this, _1, _2));
    std::string response(buff_, already_read_);
    return response;
}

void ServerConnection::connect(ip::tcp::endpoint ep)
{
    //check error code
    sock_.connect(ep);
}

void ServerConnection::setUsername(std::string username)
{
    m_CurrentUsername = username;
}

void ServerConnection::sendRequestToServer(const std::string& request)
{
    printf("ServerConnection::sendRequestToServer: request = %s \n", request.c_str());
    sock_.write_some(buffer(request));
}

std::string ServerConnection::username() const
{
    return m_CurrentUsername;
}

size_t ServerConnection::readComplete(const boost::system::error_code & err, size_t bytes)
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
