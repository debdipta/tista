#!/bin/bash

usage()
{
    echo "./build.sh -D 1"
    echo "./build.sh -D 2"
    echo "./build.sh -D 3"
    exit
}

clean()
{
    clear
    echo "Removing log files"
    if [[ -f "/tmp/logger/logger.log" ]]
    then
        rm -f "/tmp/logger/logger.log"
    fi
}

##MAIN
#
clean
echo "Cleaning previous build"
make clean
debug_level=1


#getopt for command line args
while getopts ":D:" __arg; do
    case "${__arg}" in 
        D) debug_level=${OPTARG} 
            ((debug_level ==1 || debug_level == 2 || debug_level == 3 )) || usage;;
        *) debug_level=1;;  #default log level is ine
    esac
done
shift $((OPTIND-1))

echo "Start building"

#preparing debug flag to be ON
__debug_level="DEBUGL${debug_level}"

make debug_level=$__debug_level
