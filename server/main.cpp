#include "boost/asio.hpp"
#include "boost/archive/binary_oarchive.hpp"
#include "boost/archive/binary_iarchive.hpp"
#include <jsoncpp/json/json.h>

#include <iostream>
#include <stdexcept>

using boost::asio::io_service;
using boost::asio::ip::tcp;
using namespace std;

class Server
{
public:
    Server()
    {
    }

    void launchServer()
    {
        io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 5555));
        std::cout << "Server: Waiting for connections..." << std::endl;
        tcp::iostream s;
        acceptor.accept(*s.rdbuf());
        std::cout << "Server: Connection established." << std::endl;
        boost::archive::binary_iarchive iarchive{ s };

        std::string requestFromClient;
        iarchive >> requestFromClient;
        std::cout << " requestFromClient = " << requestFromClient << std::endl;

        Json::Value root;
        Json::Reader reader;
        if (!reader.parse(requestFromClient, root))
        {
            cout << "Error: " << reader.getFormattedErrorMessages();
        }
        else
        {
            Json::Value jsonValue = root["requestType"];
            std::string requestType = jsonValue.asString();
            printf(" requestType = %s \n", requestType.c_str());
        }

        boost::archive::binary_oarchive oarchive{ s };
        s.close();
    }
};


int main(int argc, char* argv[])
{
    Server server;
    server.launchServer();
}
