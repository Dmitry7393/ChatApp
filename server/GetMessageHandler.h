#ifndef GETMESSAGE_HANDLER_H
#define GETMESSAGE_HANDLER_H

#include "RequestHandler.h"

class GetMessageHandler : public RequestHandler
{
public:
    GetMessageHandler();
    std::string handle(const std::string& jsonRequest);
};

#endif
