#include "../include/server.hxx"
#include "../include/host.hxx"
#include <string>
#include <cstring>
#include <fstream>

inline bool operator==(std::string x, std::string y)
{
    return !strcmp(x.c_str(), y.c_str());
}

inline long long fsize(std::string loc)
{
    std::ifstream fin(loc.c_str(), std::ios::binary | std::ios::ate);
    long long x = fin.tellg();
    fin.close();
    return x;
}

void srv::fs_server::on_connect(std::istream& in,
                                std::ostream& out,
                                const std::string& foreign_ip,
                                const std::string& local_ip,
                                unsigned short foreign_port,
                                unsigned short local_port,
                                dlib::uint64 connection_id)
{
    h::log("Client connected. IP: " + foreign_ip);
    h::log("Client connection id: " + dlib::cast_to_string(connection_id));
    std::string buffer;
    while(true)
    {
        //get [filename]
        std::getline(in, buffer, ' ');
        if(buffer == "get")
        {
            std::getline(in, buffer, ' ');
            out << fsize(buffer) << " ";
            h::log("got a get request [" + dlib::cast_to_string(buffer) + "]");
            std::ifstream fin(buffer);
            if(fin.is_open())
            {
                while(fin.peek() != EOF)
                {
                    out << (char) fin.get();
                }
                fin.close();
            }
            h::log("Completed get request!");
            continue;
        }

        //put [filename] [length] [data]
        if(buffer == "put")
        {
            std::getline(in, buffer, ' ');
            h::log("Put requested: " + buffer + "!");
            std::ofstream fout(buffer.c_str());
            std::getline(in, buffer, ' ');
            long long length = std::atoll(buffer.c_str());
            if(fout.is_open())
            {
                for(long long i = 0; i < length; i++)
                {
                    fout.put((char) in.get());
                }
                fout.close();
            }
            h::log("Completed put request!");
            continue;
        }

        if(buffer == "quit")
        {
            return;
        }
    }
    h::log("Outside of the loop!");
}
