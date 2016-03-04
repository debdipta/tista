#include "soc.h"
#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "logger.h"

extern int errno;

int bind_local(int sock_fd, const struct sockaddr *s, socklen_t slen, bool do_listen)
{
	if(reuse(sock_fd) < 0)
		return -1;
	if(bind(sock_fd, s, slen) < 0)
	{
		printf("ERROR: %s\n", strerror(errno));
		return -1;
	}
	if(do_listen)	{
		if(listen(sock_fd, 2) < 0)
		{
			printf("Error in Listen\n");
			return -1;
		}
	}
	return 1;
}

int reuse(int sock)
{
	int val = 1;
	socklen_t len = sizeof(val);
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &val, len) < 0) {
		printf("Error in reuse\n");
		return -1;
	}
	return 1;
}
