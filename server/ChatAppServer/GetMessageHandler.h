#ifndef GETMESSAGE_HANDLER_H
#define GETMESSAGE_HANDLER_H

#include "RequestHandler.h"

class GetMessageHandler : public RequestHandler
{

public:
    GetMessageHandler(std::shared_ptr<HistoryManager> historyManager);
    std::string handle(const std::string& jsonRequest);

private:
    std::shared_ptr<HistoryManager> m_historyManager;
};

#endif
