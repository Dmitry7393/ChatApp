#ifndef GUIUPDATER_H
#define GUIUPDATER_H
#include <string>
#include <vector>

class GUIUpdater
{

public:
    virtual void updateClientListView(const std::vector<std::string>& clientList) = 0;
    virtual void updateMessageBrowser(std::vector<std::string> messageList) = 0;

};

#endif
