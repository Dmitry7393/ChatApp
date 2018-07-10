#include "ClientServerInteraction.h"

ClientServerInteraction::ClientServerInteraction(const std::string& serverIP, int port)
   : m_Endpoint(ip::address::from_string(serverIP), port),
     m_ServerConnection(new ServerConnection)
   //  m_ResponseHandler(new ResponseHandler)
{
    try
    {
        m_ServerConnection->connect(m_Endpoint);
    }
    catch(boost::system::system_error & err)
    {
        std::cout << err.what() << std::endl;
    }
}

void ClientServerInteraction::setGUIUpdater(GUIUpdater* updater)
{
    m_GUIUpdater = updater;
}

void ClientServerInteraction::setUsername(const std::string& username)
{
    m_Username = username;
}

std::string ClientServerInteraction::getUsername()
{
    return m_Username;
}

void ClientServerInteraction::readResponsesInSeparateThread()
{
    while (true)
    {
        handleResponse(m_ServerConnection->readResponse());
    }
}

void ClientServerInteraction::handleResponse(const std::string& response)
{
    std::vector<std::string> list;

    switch(ResponseHandler::getResponseType(response))
    {
        case ResponseType::ClientList:
            m_responseHandler.reset(new ClientListHandler);
            list = m_responseHandler->handle(response);
            m_GUIUpdater->updateClientListView(list);
            break;

        case ResponseType::DeliverMessage:
            m_responseHandler.reset(new MessageHandler);
            list = m_responseHandler->handle(response);
            m_GUIUpdater->updateMessageBrowser(list);
        default:
            break;
    }
}

void ClientServerInteraction::readDataFromServer()
{
    m_threadCheckDataFromServer = new std::thread(&ClientServerInteraction::readResponsesInSeparateThread, this);
}

void ClientServerInteraction::sendMessage(const std::string& message, const std::string& userReceiver)
{
    m_ServerConnection->sendRequestToServer(m_JSONHandler.createSendMessageRequest(m_Username, userReceiver, message));
}

void ClientServerInteraction::getClientList()
{
    m_ServerConnection->sendRequestToServer(m_JSONHandler.createClientListRequest(m_Username));
}

void ClientServerInteraction::sendRequestForMessages(const std::string& selectedUser)
{
    m_ServerConnection->sendRequestToServer(m_JSONHandler.createGetMessageWithUserRequest(m_Username, selectedUser));
}
