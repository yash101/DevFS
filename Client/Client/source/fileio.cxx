#include "../include/fileio.hxx"
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <map>
#include "../include/host.hxx"

namespace s
{
    struct Directory
    {
    public:
        int indent;
        std::vector<std::string> files;
        std::vector<std::string> directories;
        std::string directory;
        Directory(std::string addr)
        {
            directory = addr;
        }
    };
}

namespace t
{
    template<typename T> std::string toString(T data)
    {
        std::stringstream str;
        str << data;
        return str.str();
    }

    std::vector<std::string> getFolders(std::string dirloc)
    {
        DIR *dp;
        struct stat st;
        std::vector<std::string> folders;

        struct dirent *dirp;
        if((dp = opendir(dirloc.c_str())) == NULL)
        {
            h::log("Unable to open directory<" + dirloc + ">! Errno: " + t::toString(errno));
            return folders;
        }
        h::log("Opened directory!");

        while((dirp = readdir(dp)) != NULL)
        {
            stat(dirp->d_name, &st);

            if(S_ISDIR(st.st_mode))
            {
                folders.push_back(dirp->d_name);
            }
            h::log("In folder: " + t::toString(dirp->d_name));
        }

        h::log("Closed directory!");
        closedir(dp);
        return folders;
    }

    std::vector<std::string> getFiles(std::string dirloc)
    {
        DIR* dp;
        struct stat st;
        struct dirent *dirp;
        std::vector<std::string> filenames;
        if((dp = opendir(dirloc.c_str())) == NULL)
        {
            h::log("Unable to open directory<" + dirloc + ">!");
            return filenames;
        }
        else
        {
            while((dirp = readdir(dp)) != NULL)
            {
                stat(dirp->d_name, &st);
                if(!S_ISDIR(st.st_mode))
                {
                    filenames.push_back(std::string(dirp->d_name));
                }
            }
            return filenames;
        }
    }
}

void f::CreateDirectoryTree(std::string dirloc, std::string outputloc)
{
}

f::dirmap f::CreateDirectoryTree(std::string dirloc)
{
//    DIR *dp;
//    struct stat st;
//    f::dirmap output;

//    struct dirent *dirp;
//    if((dp = opendir(dirloc.c_str())) == NULL)
//    {
//        h::log("Unable to open directory<" + dirloc + ">! Errno: " + t::toString(errno));
//        return output;
//    }
//    h::log("Opened directory!");

//    while((dirp = readdir(dp)) != NULL)
//    {
//        stat(dirp->d_name, &st);

//        if(S_ISDIR(st.st_mode))
//        {
//            output[std::string(dirp->d_name)] = true;
//        }
//        h::log("In folder: " + t::toString(dirp->d_name));
//    }

//    h::log("Closed directory!");
//    closedir(dp);
//    return output;

    struct s::Directory root = s::Directory(dirloc);
    std::vector<std::string> disp;
    root.directories = t::getFolders(root.directory);
    root.files = t::getFiles(root.directory);
    std::vector<s::Directory> dirs;

    for(unsigned int i = 0; i < root.directories.size(); i++)
    {
        dirs.push_back(s::Directory(root.directories[i]));
        get
    }


    /*
   getfiles(root.dir,root.files);
    getfolders(root.dir,root.folders);

    cout << "hello\n";

    vector<Directory> dirs = vector<Directory>();

  for(int i = 0; i < (int) root.folders.size(); i++){
        dirs.push_back(Directory(root.folders[i]));

       getfiles(dirs[i].dir,dirs[i].files);
        getfolders(dirs[i].dir,dirs[i].folders);


        //infinate loop start
        for(int j = 0; j < (int) dirs[i].folders.size(); j++){
            dirs.push_back(Directory(dirs[i].folders[j]));

            getfiles(dirs[i].dir,dirs[i].files);
            getfolders(dirs[i].dir,dirs[i].folders);
        }
        //infinate loop end
    }*/
}

bool f::readFile(std::string& file_loc, std::string& destination)
{
    std::ifstream fin(file_loc.c_str());
    if(fin.is_open())
    {
        destination = t::toString(fin.rdbuf());
        fin.close();
        return true;
    }
    else
    {
        return false;
    }
}

bool f::writeFile(std::string& file_loc, std::string& data)
{
    std::ofstream fout(file_loc.c_str());
    if(fout.is_open())
    {
        fout << data;
        fout.close();
        return true;
    }
    else
    {
        return false;
    }
}
