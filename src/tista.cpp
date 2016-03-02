#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "logger.h"
#include "config.h"
#include <cerrno>

namespace Config    {
    int http_port = 8080;
    int cores = 1;
}
extern int errno;

void die(const char *s)
{
    fflush(stdout);
    perror(s);
    exit(errno);
}

void usage()
{
    printf("** usage of tista 8888\n");
    printf("./tista -n <number of cores> \
                    -h <http port>\n");
    die("invalid usage\n");
}

int main(int argc, char* argv[])
{
    LOG(L1, "Hello World!! -- level one");
    LOG(L2, "Hello World!! -- level two");
    int opt = 0;

    //Get Optional parameters for server startup
    while((opt = getopt(argc, argv, ":n:h:iT")) != -1)   {
        printf("%d", opt);
        switch(opt) {
            case 'n':
                Config::cores = atoi(optarg);
                break;
            case 'h':
                Config::http_port = atoi(optarg);
                break;
            default:
                usage();
                break;
        }
    }
    printf("tista: cpu =%d http_port=%d\n", Config::cores, Config::http_port);
    return 0;
}
