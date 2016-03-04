#ifndef __SOC__
#define __SOC__

#include <netdb.h>

int bind_local(int sock_fd, const struct sockaddr *s, socklen_t , bool );

int reuse(int sock);

#endif
