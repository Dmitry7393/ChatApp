#ifndef CLIENTSERVERINTERACTION_H
#define CLIENTSERVERINTERACTION_H
#include <string>
#include <vector>
#include <QObject>
#include "NetworkHandler.h"
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

signals:
    void updateClientList(const std::vector<std::string>&);
  //  void updateMessageBrowser(std::vector<std::string> messages);

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
    std::vector<std::string> getMessagesWithClient(const std::string& selectedUser);

private:
    std::string m_Username;
    ip::tcp::endpoint m_Endpoint;
    boost::shared_ptr<ServerConnection> m_ServerConnection;
    NetworkHandler m_NetworkHandler;
    JSONHandler m_JSONHandler;

    std::thread* m_threadCheckDataFromServer;
    GUIUpdater* m_GUIUpdater;
    //boost::shared_ptr<ResponseHandler> m_ResponseHandler;

};

#endif
