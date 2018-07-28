#include "HistoryManager.h"
#include "GetMessageHandler.h"
#include "ClientListHandler.h"
#include "SaveMessageHandler.h"
#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(checkDatabase, addingNewMessage)
{
    HistoryManager manager;
    manager.saveMessage("userSender", "userReceiver", "some_text_message");
    std::vector<std::string> listWithMessages = manager.getMessagesBetweenTwoUsers("userSender", "userReceiver");
    char* expectedResult = "userSender : some_text_message";

    ASSERT_STREQ(expectedResult, listWithMessages.at(0).c_str());
}

TEST(checkRequestHandler, checkRequestTypeClientList)
{
    std::string request =  "{ \"requestType\" : \"GetClientList\", \"username\" : \"dmitry\" } ";
    RequestType expectedRequestType = RequestType::GetClientList;

    ASSERT_EQ(expectedRequestType, RequestHandler::getRequestType(request));
}

TEST(checkRequestHandler, checkRequestTypeSendMessage)
{
    std::string request =  "{ \"message\" : \"aaaaaaaaaaaaaaaaa\", \"requestType\" : \"SendMessage\", \"username\" : \"dmitry\", \"usernameReceiver\" : \"dmitry\"  } ";
    RequestType expectedRequestType = RequestType::SendMessage;

    ASSERT_EQ(expectedRequestType, RequestHandler::getRequestType(request));
}

TEST(checkRequestHandler, checkReceivingUsername)
{
    std::string request =  "{ \"message\" : \"aaaaaaaaaaaaaaaaa\", \"requestType\" : \"SendMessage\", \"username\" : \"testuser\", \"usernameReceiver\" : \"dmitry\"  } ";
    std::string expectedUsername = "testuser";

    std::shared_ptr<HistoryManager> m_HistoryManager(new HistoryManager);
    std::unique_ptr<RequestHandler> requestHandler(new GetMessageHandler(m_HistoryManager));
    ASSERT_STREQ(expectedUsername.c_str(), requestHandler->getClientName(request).c_str());
}


TEST(checkRequestHandler, getRequestType)
{
    std::string request =  "{ \"message\" : \"some_message\", \"requestType\" : \"SendMessage\", \"username\" : \"testuser\", \"usernameReceiver\" : \"testuser2\"  } ";
    std::shared_ptr<HistoryManager> m_HistoryManager(new HistoryManager);
    std::unique_ptr<RequestHandler> requestHandler(new SaveMessageHandler(m_HistoryManager));
    requestHandler->handle(request);
    std::vector<std::string> history = m_HistoryManager->getMessagesBetweenTwoUsers("testuser", "testuser2");

    std::vector<std::string> expectedHistory = { "testuser : some_message" };
    printf("  hhh(0) = %s \n", history.at(0).c_str());

   // ASSERT_EQ(expectedRequestType, RequestHandler::getRequestType(request));
}

/*
TEST(checkRequestHandler, getRequestType)
{
    std::string request =  "{ \"requestType\" : \"GetClientList\", \"username\" : \"dmitry\" } ";
    RequestType expectedRequestType = RequestType::GetClientList;

    ASSERT_EQ(expectedRequestType, RequestHandler::getRequestType(request));
}

*/
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
