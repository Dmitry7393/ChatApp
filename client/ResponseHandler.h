#ifndef RESPONSEHANDLER_H
#define RESPONSEHANDLER_H
#include <string>
#include <vector>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <algorithm>

enum ResponseType
{
    ClientList,
    DeliverMessage
};

class ResponseHandler
{
public:
    ResponseHandler();
    static ResponseType getResponseType(const std::string& request);
    virtual std::vector<std::string> handle(const std::string& jsonResponse) = 0;
};

#endif
