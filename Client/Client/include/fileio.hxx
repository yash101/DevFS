#ifndef FILEIO_HXX
#define FILEIO_HXX
#include <string>
#include <vector>
#include <map>
namespace f
{
    typedef std::map<std::string, bool> dirmap;
    bool readFile(std::string& file_location, std::string& destination);
    bool writeFile(std::string& file_location, std::string& data);
    void CreateDirectoryTree(std::string dirloc, std::string outfile);
    dirmap CreateDirectoryTree(std::string dirloc);
}
#endif // FILEIO_HXX
