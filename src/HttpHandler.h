#ifndef __HTTPHANDLER__
#define __HTTPHANDLER__

class HttpHandler
{
    const char* default_requst_line_11;
    const char* default_requst_line_10;
    const char* default_requst_line_09;
    const char* default_index_requst_line_11;
    const char* default_index_requst_line_10;
    const char* default_index_requst_line_09;
    
    const char* default_response_header_OK;
    const char* default_new_line;
    char* test_html;

    bool validate_request(const char* );
public:
    HttpHandler();
    ~HttpHandler();
    const char* get_response(const char*);
};

#endif
