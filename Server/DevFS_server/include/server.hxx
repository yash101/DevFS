#ifndef SERVER_HXX
#define SERVER_HXX
#include "../lib/dlib/server.h"
#include <iostream>
#include <fstream>
#include <sstream>
namespace srv
{
    class fs_server : public dlib::server_iostream
    {
    private:
        void on_connect(std::istream &in,                   //Handles the actual connection!
                        std::ostream &out,
                        const std::string &foreign_ip,
                        const std::string &local_ip,
                        unsigned short foreign_port,
                        unsigned short local_port,
                        dlib::uint64 connection_id);
    };
}
#endif // SERVER_HXX
