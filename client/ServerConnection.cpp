#include "ServerConnection.h"

ServerConnection::ServerConnection()
    : sock_(service)
    , started_(true)
{

}

void ServerConnection::connect(ip::tcp::endpoint ep)
{
    sock_.connect(ep);
}

void ServerConnection::checkNewMessages()
{
    sock_.write_some(buffer(getJSONString("Login", this->username(), "data")));
    read_answer();

    while (true)
    {
        boost::this_thread::sleep(boost::posix_time::millisec(5000));
        sock_.write_some(buffer(getJSONString("checkNewMessages", "user", "data")));
        read_answer();
    }
}

void ServerConnection::setUsername(std::string username)
{
    m_CurrentUsername = username;
}

void ServerConnection::sendMessage(const std::string& message)
{
    sock_.write_some(buffer(getJSONString("sendMessage", "some_user", message)));
    read_answer();
}

std::string ServerConnection::username() const
{
    return m_CurrentUsername;
}

void ServerConnection::read_answer()
{
    already_read_ = 0;
    read(sock_, buffer(buff_), boost::bind(&ServerConnection::read_complete, this, _1, _2));
    process_msg();
}

void ServerConnection::process_msg()
{
    std::string msg(buff_, already_read_);
    std::cout << "Response from server: " << msg << std::endl;
}

size_t ServerConnection::read_complete(const boost::system::error_code & err, size_t bytes)
{
    if ( err)
        return 0;
    already_read_ = bytes;
    bool found = std::find(buff_, buff_ + bytes, '\n') < buff_ + bytes;
    return found ? 0 : 1;
}

std::string ServerConnection::getJSONString(const std::string requestType, const std::string& receiver, const std::string& message)
{
   Json::Value root;

   root["requestType"] = requestType;
   root["loginSender"] = m_CurrentUsername;
   root["loginReceiver"] = receiver;
   root["textMessage"] = message;

   return root.toStyledString();
}
