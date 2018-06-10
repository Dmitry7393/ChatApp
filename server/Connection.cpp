#include "Connection.h"

Connection::Connection(boost::asio::io_service& io_service)
  : m_Socket(io_service)
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

RequestHandler* Connection::createHandler(RequestType requestType)
{
    switch (requestType)
    {
        case GetClientList:
            printf("-------------- GetClientList \n");
            return new ClientListHandler;

        case GetNewMessages:
            printf("-------------- GetNewMessages \n");
            return new GetMessageHandler;

        case SendMessage:
            printf("-------------- SendMessage \n");
            return new SaveMessageHandler;
        default:
            break;
    }
}

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
    printf("RequestFromClient: \n %s \n", requestFromClient.c_str());

    RequestHandler* requestHandler = createHandler(RequestHandler::getRequestType(requestFromClient));
    requestHandler->m_HistoryManager = m_HistoryManager;
    m_Login = requestHandler->getClientName(requestFromClient);
    requestHandler->m_ClientList = m_ClientState->getClientList();

    std::string responseToClient = requestHandler->handle(requestFromClient);

    if (responseToClient.length() > 0)
    {
        printf(" INVOKE sendResponseToClient %s \n", responseToClient.c_str());
        sendResponseToClient(responseToClient);
    }
}

void Connection::sendResponseToClient(const std::string& msg)
{
   std::copy(msg.begin(), msg.end(), write_buffer_);
   m_Socket.async_write_some( buffer(write_buffer_, msg.size()),
                          boost::bind(&Connection::onWriteMessage, shared_from_this(), _1, _2));
}

void Connection::onWriteMessage(const boost::system::error_code& err, size_t bytes)
{
    readRequestFromClient();
}
