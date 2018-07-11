#ifndef SAVEMESSAGE_HANDLER_H
#define SAVEMESSAGE_HANDLER_H

#include "RequestHandler.h"

class SaveMessageHandler : public RequestHandler
{
public:
    SaveMessageHandler(std::shared_ptr<HistoryManager> historyManager);
    std::string handle(const std::string& jsonRequest);
    std::string createSendMessageResponse();

private:
    std::shared_ptr<HistoryManager> m_historyManager;
};

#endif
