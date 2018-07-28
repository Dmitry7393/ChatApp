#include "ClientController.h"

int main(int argc, char* argv[])
{
    boost::asio::io_service service;
    ClientController clientController(service);
    service.run();

   /* printf(" ============ 1 \n");
    for (int i = 0; i < 4000; ++i)
    {
        printf(" rrrrrrrrrr \n");
    }*/
}
