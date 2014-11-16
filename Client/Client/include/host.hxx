#ifndef HOST_HXX
#define HOST_HXX
#include <string>
namespace h
{
    void boot();
    bool getCfg(std::string x);
    void putCfg(std::string callname);
    void log(std::string in);
    void setCfg(std::string x, bool val);
    void clearLog();
    long long getLogSize();
}
#endif // HOST_HXX
