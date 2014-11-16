#ifndef FILEIO_HXX
#define FILEIO_HXX
#include <string>
namespace f
{
    bool readFile(std::string& file_location, std::string& destination);
    bool writeFile(std::string& file_location, std::string& data);
    void CreateDirectoryTree(std::string& dirloc, std::string& outfile);
}
#endif // FILEIO_HXX
