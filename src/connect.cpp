#include "connect.h"
#include <errno.h>
#include <sys/socket.h> 
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include "soc.h"
#include "logger.h"
extern int errno;

connection::connection() : d_http_port(8080), d_local_port(80),
                            sock_fd(-1)
{

}

connection::~connection()
{

}

const string& connection::exit_why()
{
	return err.c_str();
}

bool connection::init(const string &local_port, const string &laddr)
{
    printf("addr=%s local_port=%s\n", laddr.c_str(), local_port.c_str());
	int r = 0;
	int family = AF_INET, type = SOCK_STREAM;
	sock_fd = socket(family, type, 0);
	if( sock_fd < 0 )
	{
		err = "connection::init::socket:"; 
		err += strerror(errno);
		return false;
	}
	d_local_port = strtoul(local_port.c_str(), NULL, 10);
	
	addrinfo hint, *ai = NULL;
	memset(&hint, 0, sizeof(hint));
	hint.ai_family = family;
	hint.ai_socktype = SOCK_STREAM;
//	#if ((r = getaddrinfo(laddr.c_str(), local_port.c_str(), &hint, &ai)) != 0) {
	if ((r = getaddrinfo( INADDR_ANY, local_port.c_str(), &hint, &ai)) != 0) {
		err = "connection::init::getaddrinfo:";
		return false;
	}

	if (bind_local(sock_fd, ai->ai_addr, ai->ai_addrlen, 1) < 0) {
		err = "connection::init::bind_local";
		return false;
	}	
	return true;
}

bool connection::respond(int accept_fd)
{
    printf("connection::respond responding\n");
    int lbuf = 2048, lrecv = -1;
    char buf[lbuf];
    memset(buf, 0, lbuf);
    while( (lrecv = recv(accept_fd, buf, lbuf, 0)) > 0) {
        //if( (lrecv = recv(accept_fd, buf, lbuf, 0)) == -1)
        printf("Received=%d bytes\n%s", lrecv, buf );
        send(accept_fd, "Hunn\n", strlen("Hunn\n"), 0); 
        memset(buf, 0, lbuf);
    }
    printf("Exiting...\n");
    close(accept_fd);
    exit(EXIT_SUCCESS);
}

bool connection::loop()
{
    struct sockaddr_in clientaddr;
    socklen_t addrlen = sizeof(&clientaddr);
    int i = 0, afd = -1;
    for(;;) {

        afd = accept(sock_fd, (struct sockaddr *)&clientaddr, &addrlen);
        if (afd < 0) {
            printf("Heavy Load %s\n", strerror(errno));
                break;
        }
        else    printf("New connection accepted\n");
        if ( fork()==0 )    {
            respond(afd);
        }
    } //Keep Running until close
    return false;
}
