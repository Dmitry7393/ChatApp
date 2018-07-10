#ifndef CLIENTSERVERINTERACTION_H
#define CLIENTSERVERINTERACTION_H
#include <string>
#include <vector>
#include <QObject>

#include "ServerConnection.h"
#include "Message.h"
#include "JSONHandler.h"
#include "GUIUpdater.h"
#include <thread>

#include "ClientListHandler.h"
#include "MessageHandler.h"

class ClientServerInteraction : public QObject {
Q_OBJECT

public:
    ClientServerInteraction(const std::string& serverIP, int port);

public:
    void setGUIUpdater(GUIUpdater* updater);
    void setUsername(const std::string& username);
    std::string getUsername();
    void readResponsesInSeparateThread();
    void handleResponse(const std::string& response);
    void readDataFromServer();

    //requests to server
    void sendMessage(const std::string& message, const std::string& userReceiver);
    void getClientList();
    void sendRequestForMessages(const std::string& selectedUser);

private:
    std::string m_Username;
    ip::tcp::endpoint m_Endpoint;
    boost::shared_ptr<ServerConnection> m_ServerConnection;
    JSONHandler m_JSONHandler;

    std::thread* m_threadCheckDataFromServer;
    GUIUpdater* m_GUIUpdater;
    std::unique_ptr<ResponseHandler> m_responseHandler;

};

#endif
