#ifndef CLIENTLISTHANDLER_H
#define CLIENTLISTHANDLER_H
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <algorithm>

#include "ResponseHandler.h"

class ClientListHandler : public ResponseHandler
{

public:
    ClientListHandler();
    std::vector<std::string> handle(const std::string& jsonResponse);
};

#endif
