#ifndef __CONNECT__
#define __CONNECT__

#include <string.h>
#include <iostream>
#include <stdint.h>

using namespace std;

class connection 
{
	uint16_t d_http_port, d_local_port;
	string err; 
    int sock_fd;
public:
	connection();
	~connection();
	bool init(const string &, const string &);
	const string& exit_why();
    bool loop();
    bool respond();

};

#endif
