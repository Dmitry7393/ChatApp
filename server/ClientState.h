#ifndef CLIENTSTATE_H
#define CLIENTSTATE_H

#include <string>

class ClientState
{
public:
    ClientState() { }
    virtual void StateChanged(std::string login) = 0;
    virtual std::vector<std::string> getClientList() = 0;
};

#endif // CLIENTSTATE_H
