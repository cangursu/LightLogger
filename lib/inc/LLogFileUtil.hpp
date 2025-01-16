
#ifndef __LIGHT_LOGGER_FILE_UTIL_HPP__
#define __LIGHT_LOGGER_FILE_UTIL_HPP__

#include <string>

class LLogFile
{
    public :

        int         Init(const std::string &basename, const std::string &path);
        int         FileNew(const std::string &name);
        void        FileClose();
        int         FileWrite(const std::string &content);
        void        FileMaxOffset(off_t offset) {_offMax = offset; }
        void        FileCompress(const std::string &fname);
        std::string FileCompressFName(const std::string &fname) {return fname + std::string(".gz"); }

    private :

        int         _fdLogFile = -1;
        std::string _path;
        std::string _fbasename;
        std::string _fname;
        off_t       _offMax = 536870912;
};


#endif //__LIGHT_LOGGER_FILE_UTIL_HPP__
