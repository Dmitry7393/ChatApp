#include "Connection.h"

Connection::Connection(boost::asio::io_service& io_service, std::shared_ptr<HistoryManager> historyManager)
  : m_Socket(io_service)
  , m_readRequest(true)
  , m_HistoryManager(historyManager)
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
    if (m_readRequest)
    {
        m_readRequest = false;
        async_read(m_Socket, buffer(m_bufferForReading),
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
           if (m_bufferForReading[i] == '{')
           {
               count++;
           }
           if (m_bufferForReading[i] == '}')
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

std::unique_ptr<RequestHandler> Connection::createHandler(RequestType requestType)
{
    switch (requestType)
    {
        case GetClientList:
            printf("Connection::createHandler  GetClientList \n");
            return std::unique_ptr<RequestHandler>(new ClientListHandler);

        case GetMessageWithUser:
            printf("Connection::createHandler  GetMessageWithUser \n");
            return std::unique_ptr<RequestHandler>(new GetMessageHandler(m_HistoryManager));

        case SendMessage:
            printf("Connection::createHandler SendMessage \n");
            return std::unique_ptr<RequestHandler>(new SaveMessageHandler(m_HistoryManager));

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
       m_ClientState->removeClient(m_Login);
       stop();
       return;
    }

    std::string requestFromClient(m_bufferForReading, bytes_transferred);
    printf("Connection::handleRequest RequestFromClient: \n %s \n", requestFromClient.c_str());

    std::unique_ptr<RequestHandler> requestHandler = createHandler(RequestHandler::getRequestType(requestFromClient));

    m_Login = requestHandler->getClientName(requestFromClient);
    requestHandler->setClientList(m_ClientState->getClientList());

    std::string responseToClient = requestHandler->handle(requestFromClient);

    std::string userName = requestHandler->parseJSONValue(requestFromClient, JSONData::username);
    std::string usernameReceiver = requestHandler->parseJSONValue(requestFromClient, JSONData::usernameReceiver);

    printf("Connection::handleRequest   userName = %s \n", userName.c_str());
    printf("Connection::handleRequest   usernameReceiver = %s \n", usernameReceiver.c_str());

    if (RequestHandler::getRequestType(requestFromClient) == RequestType::SendMessage)
    {
        if (userName != usernameReceiver)
        {
            requestHandler.reset(new GetMessageHandler(m_HistoryManager));
            m_ClientState->deliverMessageToClient(usernameReceiver, requestHandler->handle(requestFromClient));
        }
        else
        {
            printf("Connection::handleRequest - message was not sent \n");
        }
    }

    sendResponseToClient(responseToClient);
    m_readRequest = true;
}


void Connection::sendResponseToClient(const std::string& msg)
{
    std::copy(msg.begin(), msg.end(), m_bufferForWriting);
    m_Socket.async_write_some( buffer(m_bufferForWriting, msg.size()),
                          boost::bind(&Connection::onWriteMessage, shared_from_this(), _1, _2));
}

void Connection::onWriteMessage(const boost::system::error_code& err, size_t bytes)
{
    readRequestFromClient();
}
