#include "NetworkHandler.h"

NetworkHandler::NetworkHandler(boost::shared_ptr<ServerConnection> serverConnection)
    : m_ServerConnection(serverConnection)
{

}

void NetworkHandler::run()
{
    //m_ServerConnection->checkNewMessages();
}

NetworkHandler::~NetworkHandler()
{

}
