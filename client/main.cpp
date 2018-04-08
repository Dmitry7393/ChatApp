#include "boost/asio.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"
#include <jsoncpp/json/json.h>
#include <iostream>

using boost::asio::io_service;
using boost::asio::ip::tcp;
using namespace std;

class Client
{
public:
    void sendMessageToServer()
    {
        Json::Value root;

        root["requestType"] = "getUsersList";
        root["clientData"]["login"] = "mylogin";
        root["clientData"]["password"] = "some password";

        std::cout << root << "\n";

        tcp::iostream s("localhost", "5555");
        boost::archive::binary_oarchive oarchive{ s };

        std::string requestFromClient = root.toStyledString();

        oarchive << requestFromClient;
        s.flush();

        boost::archive::binary_iarchive iarchive{ s };
        int result;
        iarchive >> result;
   }
};

int main(int argc, char* argv[])
{
    Client client;
    client.sendMessageToServer();
    return 0;
}

