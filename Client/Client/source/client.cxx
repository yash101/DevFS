#include "../include/client.hxx"
#include <string>
#include <cstring>
#include <iostream>
#include <thread>
#include "../include/host.hxx"
#include "../lib/dlib/string.h"

client::Client::Client(std::string server_addr)
{
    sock.open(dlib::network_address(server_addr));
}

std::string client::Client::getFile(std::string location)
{
    h::log("Sending request [" + location + "]");
    sock << "get ";
    sock << location;
    sock << " ";
    std::string buffer;
    std::getline(sock, buffer, ' ');
    long long rlength = std::atoll(buffer.c_str());
    h::log("Content Length: " + dlib::cast_to_string(rlength));
    std::stringstream str;
    for(long long i = 0; i < rlength; i++)
    {
        if(sock.peek() == EOF)
        {
            return "";
        }
        str << (char) sock.get();
    }
    h::log("Completed Read!");
    return str.str();
}

bool client::Client::downloadFile(std::string remote_location, std::string local_location)
{
    std::ofstream fout(local_location.c_str());
    if(fout.is_open())
    {
        h::log("Sending request [" + remote_location + "]");
        sock << "get ";
        sock << remote_location;
        sock << " ";
        std::string buffer;
        std::getline(sock, buffer, ' ');
        long long rlength = std::atoll(buffer.c_str());
        h::log("Content Length: " + dlib::cast_to_string(rlength));
        for(long long i = 0; i < rlength; i++)
        {
            if(sock.peek() == EOF)
            {
                return false;
            }
            fout << (char) sock.get();
        }
        h::log("Completed Read!");
        fout.close();
        return true;
    }
    else
    {
        h::log("Unable to write to file: " + local_location);
        return false;
    }
}

void client::Client::putFile(std::string location, std::string data)
{
    sock << "put " << location << " " << data.size() << " " << data << " ";
}

void client::Client::close()
{
    sock << "quit";
}
