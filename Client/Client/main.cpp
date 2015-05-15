#ifndef __cplusplus
#error("Your compiler MUST support C++ to build this!");
#endif

#include <iostream>
#include <csignal>
#include "include/host.hxx"
#include "include/client.hxx"
#include "lib/dlib/string.h"
#include <chrono>
#include <string>
#include <cstring>
#include "include/fileio.hxx"

int main()
{
    u_int64_t tm1 = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch()).count();
    h::boot();
    std::cout << "Log size: " << h::getLogSize() << std::endl;
    h::clearLog();
    std::cout << "Log size: " << h::getLogSize() << std::endl;
    client::Client cli("localhost:5432");
    cli.downloadFile("appb.cfg", "server.cfg");
    cli.downloadFile("file.dat", "file.dat");
    cli.close();
    u_int64_t tm2 = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::system_clock::now().time_since_epoch()).count();
    h::log("Time taken<nanoseconds>: " + dlib::cast_to_string(tm2 - tm1));

    f::dirmap d;
    f::CreateDirectoryTree(".");
    for(auto i = d.begin(); i != d.end(); i++)
    {
        std::cout << "Directory: " << i->first << std::endl;
    }
}
