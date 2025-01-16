
#include "LLogFileUtil.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <zlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>


static void mkpath(const char *path, __mode_t mode)
{
    char buff[PATH_MAX];

    std::strncpy(buff, path, PATH_MAX - 1);
    size_t len = strlen(buff);
    if (buff[len - 1] == '/')
        buff[len - 1] = 0;

    for (char *p = buff + 1; *p; p++)
    {
        if (*p == '/')
        {
            *p = 0;
            mkdir(buff, mode);
            *p = '/';
        }
    }
    mkdir(buff, mode);
}


int LLogFile::Init(const std::string &basename, const std::string &path)
{
    _path = path;
    _path += '/';

    if (0 != ::access(_path.c_str(), F_OK))
        mkpath(_path.c_str(), DEFFILEMODE | S_IXUSR | S_IXGRP | S_IXOTH);

    return FileNew(basename);
}

int LLogFile::FileNew(const std::string &name)
{
    time_t now = time(nullptr);
    struct tm *tmNow = localtime (&now);

    FileClose();

    if(tmNow)
    {
        int idx = 0;
        do
        {
            _fbasename = name;
            std::ostringstream ss;
            ss << _fbasename    << "_" << std::setfill('0') << std::setw(4) << tmNow->tm_year+1900
                                << "_" << std::setfill('0') << std::setw(2) << tmNow->tm_mon+1
                                << "_" << std::setfill('0') << std::setw(2) << tmNow->tm_mday
                                << "_" << std::setfill('0') << std::setw(2) << tmNow->tm_hour
                                << "_" << std::setfill('0') << std::setw(2) << tmNow->tm_min
                                << "_" << std::setfill('0') << std::setw(2) << tmNow->tm_sec;
            if (idx)
                ss << "__" << idx;
            ss << ".log";

            _fname = _path + ss.str();
            std::string fnameZip = FileCompressFName(_fname);

            if ((0 != ::access(_fname.c_str(),  F_OK)) && (0 != ::access(fnameZip.c_str(), F_OK)))
                _fdLogFile = open(_fname.c_str(),  O_EXCL | O_CREAT | O_WRONLY, DEFFILEMODE );
            ++idx;
        } while ((idx < 251) && (-1 == _fdLogFile));
    }

    if (-1 == _fdLogFile)
    {
        std::cerr << "ERROR : \n";
        std::cerr << "ERROR : Unable to create log file " << _fname << "\n";
        std::cerr << "ERROR : \n";
        return -1;
    }

    return _fdLogFile;
}

int LLogFile::FileWrite(const std::string &content)
{
    if (-1 == _fdLogFile)
        FileNew(_fbasename);
    if (-1 == _fdLogFile)
    {
        std::cerr << "ERROR Unable to create a newlog file" << std::endl;
        return -1;
    }

    ssize_t sz = content.size();
    long pos = lseek(_fdLogFile, 0, SEEK_CUR);
    if (pos + sz > _offMax)
        FileNew(_fbasename);
    if (-1 == _fdLogFile)
    {
        std::cerr << "ERROR Unable to create a newlog file" << std::endl;
        return -2;
    }

    if (-1 == write(_fdLogFile, content.c_str(), sz))
    {
        std::cerr << "ERROR : \n";
        std::cerr << "ERROR : Unable to write log file\n";
        std::cerr << "ERROR : \n";
        return -3;
    }
    return 0;
}


void LLogFile::FileClose()
{
    if (-1 != _fdLogFile)
    {
        FileCompress(_fname);
        close(_fdLogFile);
    }
    _fdLogFile = -1;
}

void LLogFile::FileCompress(const std::string &fname)
{
    int fdSource = open(fname.c_str(), O_RDONLY);
    if (-1 != fdSource)
    {
        gzFile fdDest = gzopen(FileCompressFName(fname).c_str(), "wb9");
        if (Z_NULL != fdDest)
        {
            constexpr size_t buffSize = 1024;
            char buff[buffSize] {};
            ssize_t readed;
            while (0 < (readed = read(fdSource, buff, buffSize)))
            {
                /*size_t written = */gzwrite(fdDest, buff, readed);
                //std::cout << "readed=" << readed << ", written=" << written << std::endl;
            }
            gzclose(fdDest);
            remove(fname.c_str());
        }
        close(fdSource);
    }
}
