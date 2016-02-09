#include <stdio.h>
#include "logger.h"


int main(int argc, char * argv[])
{
    LOG(L1, "Hello World!! -- level one");
    LOG(L2, "Hello World!! -- level two");
    //logger::getInstance()->write_file("This is test");
    return 0;
}
