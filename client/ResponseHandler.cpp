#include "ResponseHandler.h"

ResponseHandler::ResponseHandler() { }

ResponseType ResponseHandler::getResponseType(const std::string& request)
{
    std::vector<std::string> g_requestTypes = { "ClientList", "DeliverMessage" };
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(request, root))
    {
        std::cout << "Error: " << reader.getFormattedErrorMessages();
    }
    else
    {
        Json::Value jsonValueRequestType = root["responseType"];
        std::string requestType = jsonValueRequestType.asString();
        printf("responseType = %s \n", requestType.c_str());

        int index = std::find(g_requestTypes.begin(), g_requestTypes.end(), requestType) - g_requestTypes.begin();

        if (index >= g_requestTypes.size())
        {
            printf("Incorrect request type  \n");
          //  return 1;
        }

        switch (index)
        {
            case ClientList:
                return ResponseType::ClientList;
                break;
            case DeliverMessage:
                return ResponseType::DeliverMessage;
                break;
            default:
                printf("Incorrect request type \n");
                //return 1;
        }

        Json::Value jsonValueLogin = root["loginSender"];
        std::string m_Login = jsonValueLogin.asString();
        printf("login = %s \n", m_Login.c_str());
     }
}


