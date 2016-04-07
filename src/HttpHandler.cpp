#include "HttpHandler.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

HttpHandler::HttpHandler()
{

    default_requst_line_11 = "GET / HTTP/1.1";
    default_requst_line_10 = "GET / HTTP/1.0";
    default_requst_line_09 = "GET / HTTP/0.9";
    default_index_requst_line_11 = "GET /index.html HTTP/1.1";
    default_index_requst_line_10 = "GET /index.html HTTP/1.0";
    default_index_requst_line_09 = "GET /index.html HTTP/0.9";


    default_response_header_OK = "HTTP/1.1 200 OK";
    default_new_line = "\n\n\r";
    test_html = new char[2048];
}

HttpHandler::~HttpHandler()
{

}

bool HttpHandler::validate_request(const char* request)
{
    bool bret = true;
    //Id request header have "GET" and " HTTP/1.1", It is a valid response
    if((NULL == strstr(request, "GET")) || (NULL == strstr(request, "HTTP/1.1")))  {
        //Set invaid request later
        return false;
    }
    return bret;
}

const char* HttpHandler::get_response(const char* request)
{
    char* response = new char[2048];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if(validate_request(request))   {
        strcat(response, default_response_header_OK);
        strcat(response, default_new_line);
        sprintf(test_html, "<html><body><h1>It works!now: %d-%d-%d %d:%d:%d\n</h1></body></html>", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
        strcat(response, test_html);
    }
    printf("Responding: %s\n", response);
    return response;
}
