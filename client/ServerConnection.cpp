#include "ServerConnection.h"

ServerConnection::ServerConnection()
    : m_socket(m_service)
    , m_started(true)
{

}

std::string ServerConnection::readResponse()
{
    m_alreadyRead = 0;
    read(m_socket, buffer(m_buffer), boost::bind(&ServerConnection::readComplete, this, _1, _2));
    std::string response(m_buffer, m_alreadyRead);
    return response;
}

void ServerConnection::connect(ip::tcp::endpoint ep)
{
    m_socket.connect(ep);
}

void ServerConnection::sendRequestToServer(const std::string& request)
{
    try
    {
        m_socket.write_some(buffer(request));
    }
    catch(const boost::system::system_error& ex)
    {
        printf("ServerConnection::sendRequestToServer Failed to send request to server \n");
    }
}

size_t ServerConnection::readComplete(const boost::system::error_code & err, size_t bytes)
{
    if ( err)
        return 0;

    int count = 0;
    bool found = false;
    m_alreadyRead = bytes;

    for (size_t i = 0; i < bytes; ++i)
    {
        if (m_buffer[i] == '{')
        {
            count++;
        }
        if (m_buffer[i] == '}')
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
