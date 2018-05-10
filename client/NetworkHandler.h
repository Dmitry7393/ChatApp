#include <QThread>
#include "ServerConnection.h"

enum RequestType
{
    Authentication,
    GetClientList,
    GetNewMessages,
    SendMessage
};

class NetworkHandler : public QThread
{
    Q_OBJECT

public:
   NetworkHandler(boost::shared_ptr<ServerConnection> serv);
    ~NetworkHandler();

private:
    void run();

private:
    boost::shared_ptr<ServerConnection> m_ServerConnection;
};
