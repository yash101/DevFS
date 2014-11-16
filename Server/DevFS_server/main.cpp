#ifndef __cplusplus
#error("Your compiler MUST support C++ to build this!");
#endif

#include <iostream>
#include <csignal>
#include "include/host.hxx"
#include "include/server.hxx"

int main()
{
    h::boot();
    srv::fs_server serv;
    serv.set_listening_port(5432);
    serv.start();
}
