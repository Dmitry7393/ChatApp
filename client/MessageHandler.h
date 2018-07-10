#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <algorithm>

#include "ResponseHandler.h"

class MessageHandler : public ResponseHandler
{

public:
    MessageHandler();
    std::vector<std::string> handle(const std::string& jsonResponse);
};

#endif
