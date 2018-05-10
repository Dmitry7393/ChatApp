#include "ClientController.h"

int main(int argc, char* argv[])
{
    boost::asio::io_service service;
    ClientController clientController(service);
    service.run();
}
