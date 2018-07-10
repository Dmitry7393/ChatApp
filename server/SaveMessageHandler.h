#ifndef SAVEMESSAGE_HANDLER_H
#define SAVEMESSAGE_HANDLER_H

#include "RequestHandler.h"

class SaveMessageHandler : public RequestHandler
{
public:
    SaveMessageHandler();
    std::string handle(const std::string& jsonRequest);
    std::string createSendMessageResponse();
};

#endif
