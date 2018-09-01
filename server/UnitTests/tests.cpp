#include "HistoryManager.h"
#include "GetMessageHandler.h"
#include "ClientListHandler.h"
#include "SaveMessageHandler.h"
#include <gtest/gtest.h>
#include <string>

using namespace std;

TEST(checkDatabase, checkChatHistory)
{
    ChatHistory chatHistory;
    chatHistory.setUsers("user1", "user2");

    ASSERT_EQ(false, chatHistory.checkHistoryExists("user1", "user4"));
    ASSERT_EQ(true, chatHistory.checkHistoryExists("user1", "user2"));
    ASSERT_EQ(false, chatHistory.checkHistoryExists("user2", "user4"));
    ASSERT_EQ(false, chatHistory.checkHistoryExists("user1", "user3"));

    ASSERT_EQ(false, chatHistory.checkHistoryExists("user5"));

    chatHistory.saveMessage("user1", "Message from user1");
    chatHistory.saveMessage("user1", "Second message from user1");

    ASSERT_EQ("user1 : Second message from user1", chatHistory.getMessages().at(1));
}

TEST(checkDatabase, addingNewMessage)
{
    HistoryManager manager;
    manager.saveMessage("userSender", "userReceiver", "some_text_message");
    std::vector<std::string> listWithMessages = manager.getMessagesBetweenTwoUsers("userSender", "userReceiver");
    char* expectedResult = "userSender : some_text_message";

    ASSERT_STREQ(expectedResult, listWithMessages.at(0).c_str());

    manager.saveMessage("userReceiver", "userSender", "message from second user");

    ASSERT_STREQ("userReceiver : message from second user", manager.getMessagesBetweenTwoUsers("userSender", "userReceiver").at(1).c_str());
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


TEST(checkRequestHandler, getRequestTypeSendMessage)
{
    std::string request =  "{ \"message\" : \"some_message\", \"requestType\" : \"SendMessage\", \"username\" : \"testuser\", \"usernameReceiver\" : \"testuser2\"  } ";
    std::shared_ptr<HistoryManager> m_HistoryManager(new HistoryManager);
    std::unique_ptr<RequestHandler> requestHandler(new SaveMessageHandler(m_HistoryManager));
    requestHandler->handle(request);
    std::vector<std::string> history = m_HistoryManager->getMessagesBetweenTwoUsers("testuser", "testuser2");

    std::vector<std::string> expectedHistory = { "testuser : some_message" };

    ASSERT_EQ(RequestType::SendMessage, RequestHandler::getRequestType(request));
}

TEST(checkRequestHandler, getRequestTypeGetClientList)
{
    std::string request =  "{ \"requestType\" : \"GetClientList\", \"username\" : \"dmitry\" } ";
    RequestType expectedRequestType = RequestType::GetClientList;

    ASSERT_EQ(expectedRequestType, RequestHandler::getRequestType(request));
}

TEST(checkRequestHandler, checkClientListHandler)
{
    ClientListHandler clientListHandler;
    std::vector<std::string> listWithConnectedClients = { "user1", "user2", "user3" };
    clientListHandler.setClientList(listWithConnectedClients);

    ASSERT_EQ("{\n   \"responseType\" : \"ClientList\",\n   \"usernames\" : [ \"user1\", \"user2\", \"user3\" ]\n}\n", clientListHandler.handle(""));
}

TEST(checkRequestHandler, checkGetMessageHandler)
{
    std::shared_ptr<HistoryManager> manager(new HistoryManager);
    manager->saveMessage("user1", "user2", "Text from user1 to user2");
    manager->saveMessage("user1", "user2", "second message");

    GetMessageHandler handler(manager);

    std::string jsonRequest = "{ \"requestType\" : \"GetMessageWithUser\", \"username\" : \"user1\", \"usernameReceiver\" : \"user2\" }";

    ASSERT_STREQ("{\n   \"messages\" : [ \"user1 : Text from user1 to user2\", \"user1 : second message\" ],\n   \"responseType\" : \"DeliverMessage\"\n}\n", handler.handle(jsonRequest).c_str());
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
