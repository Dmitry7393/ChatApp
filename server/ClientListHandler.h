#ifndef CLIENTLIST_HANDLER_H
#define CLIENTLIST_HANDLER_H
#include <jsoncpp/json/json.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <memory>

#include "RequestHandler.h"

class ClientListHandler : public RequestHandler
{

public:
    ClientListHandler();
    std::string handle(const std::string& jsonRequest);
};

#endif
