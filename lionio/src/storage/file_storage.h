#pragma once
#include <memory>
#include <iostream>
#include <string>
#include "common.h"

namespace lionio
{
    class FileStorage
    {
    public:
        FileStorage(const std::string &path);
        ~FileStorage();

    public:
        bool save(const std::string &key, const char *data, size_t length);
        std::shared_ptr<std::string> get(const std::string &key);
        bool exist(const std::string &key);
        std::string getFullPath(const std::string &key);
        bool del(const std::string &key);
    private:
        DISABLE_COPY_ADN_ASSIGN(FileStorage);
    private:
        std::string path;
    };
}