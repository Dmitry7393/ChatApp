#include "ClientServerInteraction.h"

ClientServerInteraction::ClientServerInteraction(const std::string& serverIP, int port)
   : m_Endpoint(ip::address::from_string(serverIP), port),
     m_ServerConnection(new ServerConnection),
     m_NetworkHandler(m_ServerConnection)
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

    printf("m_Username = %s \n", m_Username.c_str());
    m_ServerConnection->setUsername(m_Username);
    //m_ServerConnection->sendMessage(ui->m_LineEditMessage->text().toStdString());
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
    printf("  handleResponse response = %s \n", response.c_str());

    ResponseHandler* respHandler;
    std::vector<std::string> list;

    switch(ResponseHandler::getResponseType(response))
    {
        case ResponseType::ClientList:
            printf("invoke method of m_GUIUpdater \n");

            respHandler = new ClientListHandler();
            list = respHandler->handle(response);

            m_GUIUpdater->updateClientListView(list);

            //emit updateClientList(list);
            break;

        case ResponseType::DeliverMessage:
            respHandler = new MessageHandler();
            list = respHandler->handle(response);
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

std::vector<std::string> ClientServerInteraction::getMessagesWithClient(const std::string& selectedUser)
{
    m_ServerConnection->sendRequestToServer(m_JSONHandler.createGetMessageWithUserRequest(m_Username, selectedUser));
    std::vector<std::string> list;
   /* Json::Value root;
    Json::Reader reader;
   /* if (!reader.parse(m_MessagesToAllUsers, root))
    {
        std::cout << "Error: " << reader.getFormattedErrorMessages();
    }
    else
    {
        Json::Value jsonValueResponseType = root["responseType"];
        std::string responseType = jsonValueResponseType.asString();
        printf("---- responseType = %s \n", responseType.c_str());

        Json::Value history = root["history"]; // array of history
        printf(" history.size() = %d \n", history.size());
        for (int i = 0; i < history.size(); i++)
        {
           //std::cout << "    history2: " << history2[i].asString() << "\n";
           Json::Value block = history[i];
           Json::Value jsonUsername = block["username"];

           std::string username = jsonUsername.asString();
           printf("---- username = %s \n", username.c_str());

           if(username == selectedUser)
           {
               Json::Value messages = block["messages"];
               for (int j = 0; j < messages.size(); j++)
               {
                   std::cout << "     messages[i]: " <<  messages[j].asString() << "\n";
                   list.push_back(messages[j].asString());
               }
           }
        }
    }*/
    return list;
}
