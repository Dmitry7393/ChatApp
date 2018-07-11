#include "Connection.h"

Connection::Connection(boost::asio::io_service& io_service)
  : m_Socket(io_service)
  , m_readRequest(true)
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
    printf("Connection::readRequestFromClient() m_clientIPAddress = %s \n", m_clientIPAddress.c_str());
    if (m_readRequest)
    {
        m_readRequest = false;
        async_read(m_Socket, buffer(read_buffer_),
                   boost::bind(&Connection::readComplete, shared_from_this(), _1, _2),
                   boost::bind(&Connection::handleRequest, shared_from_this(), _1, _2));
    }
}

size_t Connection::readComplete(const boost::system::error_code & err, size_t bytes)
{
       if ( err)
       {
           printf("Connection::readComplete - error \n");
           return 0;
       }


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
            printf("Connection::createHandler  GetClientList \n");
            return new ClientListHandler;

        case GetMessageWithUser:
            printf("Connection::createHandler  GetMessageWithUser \n");
            return new GetMessageHandler;

        case SendMessage:
            printf("Connection::createHandler SendMessage \n");
            return new SaveMessageHandler;

        case PingServer:
            printf("Connection::createHandler PingServer \n");

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
    printf("Connection::handleRequest bytes_transferred=%d \n", bytes_transferred);
    printf("Connection::handleRequest Client ip: %s \n", m_Socket.remote_endpoint().address().to_string().c_str());
    m_clientIPAddress = m_Socket.remote_endpoint().address().to_string();
    std::string requestFromClient(read_buffer_, bytes_transferred);
    printf("Connection::handleRequest RequestFromClient: \n %s \n", requestFromClient.c_str());

    RequestHandler* requestHandler = createHandler(RequestHandler::getRequestType(requestFromClient));
    requestHandler->m_HistoryManager = m_HistoryManager;
    m_Login = requestHandler->getClientName(requestFromClient);
    requestHandler->m_ClientList = m_ClientState->getClientList();

    std::string responseToClient = requestHandler->handle(requestFromClient);

    std::string userName = requestHandler->parseJSONValue(requestFromClient, JSONData::username);
    std::string usernameReceiver = requestHandler->parseJSONValue(requestFromClient, JSONData::usernameReceiver);
    std::string message = requestHandler->parseJSONValue(requestFromClient, JSONData::message);
    printf("Connection::handleRequest   userName = %s \n", userName.c_str());
    printf("Connection::handleRequest   usernameReceiver = %s \n", usernameReceiver.c_str());
    printf("Connection::handleRequest   message = %s \n", message.c_str());

    if (RequestHandler::getRequestType(requestFromClient) == RequestType::SendMessage)
    {
        if (userName != usernameReceiver)
        {
            requestHandler = new GetMessageHandler();
            requestHandler->m_HistoryManager = m_HistoryManager;
            m_ClientState->deliverMessageToClient(usernameReceiver, requestHandler->handle(requestFromClient));
        }
        else
        {
            printf("Connection::handleRequest - message was not sent \n");
        }
    }

    printf("Connection::handleRequest call sendResponseTo current Client responseToClient = %s | \n", responseToClient.c_str());

    sendResponseToClient(responseToClient);
    m_readRequest = true;
}


void Connection::sendResponseToClient(const std::string& msg)
{
    printf("Connection::sendResponseToClient msg = %s | m_clientIPAddress = %s | \n", msg.c_str(), m_clientIPAddress.c_str());
    std::copy(msg.begin(), msg.end(), write_buffer_);
    m_Socket.async_write_some( buffer(write_buffer_, msg.size()),
                          boost::bind(&Connection::onWriteMessage, shared_from_this(), _1, _2));
}

void Connection::onWriteMessage(const boost::system::error_code& err, size_t bytes)
{
    printf("Connection::onWriteMessage \n");
    readRequestFromClient();
}
