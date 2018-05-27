#include "Connection.h"

Connection::Connection(boost::asio::io_service& io_service)
  : m_Socket(io_service)
  , m_RequestHandler(new RequestHandler)
{

}

void Connection::start()
{
    readRequestFromClient();
}

void Connection::SetState(ClientState* state)
{
    m_ClientState = state;
}

void Connection::readRequestFromClient()
{
     async_read(m_Socket, buffer(read_buffer_),
                boost::bind(&Connection::readComplete, shared_from_this(), _1, _2),
                boost::bind(&Connection::handleRequest, shared_from_this(), _1, _2));
}

size_t Connection::readComplete(const boost::system::error_code & err, size_t bytes)
{
       if ( err)
           return 0;

       int count = 0;
       bool found = false;

       for (size_t i = 0; i < bytes; ++i)
       {
           if (read_buffer_[i] == '{')
           {
               count++;
           }
           if (read_buffer_[i] == '}')
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

tcp::socket& Connection::socket()
{
    return m_Socket;
}

void Connection::stop()
{
    m_Socket.close();
}

ClientState* Connection::m_ClientState = NULL;

void Connection::handleRequest(const boost::system::error_code& error, std::size_t bytes_transferred)
   {
       if (error)
       {
           printf("Connection::handleRequest error \n");
           m_ClientState->StateChanged(m_Login);
           stop();
           return;
       }
       printf("Server::handleRequest() bytes_transferred=%d \n", bytes_transferred);
       printf("Client ip: %s \n", m_Socket.remote_endpoint().address().to_string().c_str());
       std::string requestFromClient(read_buffer_, bytes_transferred);
       m_RequestHandler->handleRequest(requestFromClient);

       printf("RequestFromClient: \n %s \n", requestFromClient.c_str());

       sendResponseToClient();
}


void Connection::sendResponseToClient()
 {
     std::string resp("SOME RESPONSE FROM SERVER  \n");
     writeMessage(resp);
 }

void Connection::writeMessage(const std::string& msg)
{
   std::copy(msg.begin(), msg.end(), write_buffer_);
   m_Socket.async_write_some( buffer(write_buffer_, msg.size()),
                          boost::bind(&Connection::onWriteMessage, shared_from_this(), _1, _2));
}

void Connection::onWriteMessage(const boost::system::error_code& err, size_t bytes)
{
    readRequestFromClient();
}
