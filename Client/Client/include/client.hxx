#ifndef CLIENT_HXX
#define CLIENT_HXX
#include <string>
#include "../lib/dlib/iosockstream.h"
namespace client
{
    class Client
    {
    private:
        dlib::iosockstream sock;
        std::string server_address;
    public:
        Client(std::string address);
        std::string getFile(std::string location);
        void putFile(std::string location, std::string data);
        bool downloadFile(std::string remote_location, std::string local_location);
        void close();
    };
}
#endif // CLIENT_HXX
