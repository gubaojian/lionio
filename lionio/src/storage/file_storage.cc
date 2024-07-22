
#include "file_storage.h"
#include <fstream>
#include <filesystem>

namespace lionio
{
    inline std::string replaceAll(std::string fileName,
                                  const std::string &replace, const std::string &with)
    {
        if (!replace.empty())
        {
            std::size_t pos = 0;
            while ((pos = fileName.find(replace, pos)) != std::string::npos)
            {
                fileName.replace(pos, replace.length(), with);
            }
        }
        return fileName;
    }
    inline std::string getFileName(const std::string &path, const std::string &name)
    {
        std::string fileName = replaceAll(name, "..", "");
        if (fileName.at(0) == '/')
        {
            return path + fileName;
        }
        return path + "/" + fileName;
    }

    inline std::string getParentPath(const std::string &path, const std::string &fileName)
    {
        int pos = fileName.find_last_of('/');
        if (pos <= 0)
        {
            return path;
        }

        return fileName.substr(0, pos);
    }

    FileStorage::FileStorage(const std::string &path_)
    {
        path = path_ + "/files";
        std::filesystem::path filePath = path;
        if (!std::filesystem::exists(filePath))
        {
            std::filesystem::create_directories(filePath);
        }
    }

    FileStorage::~FileStorage()
    {
    }

    std::shared_ptr<std::string> FileStorage::get(const std::string &key)
    {
        std::string fileName = getFileName(path, key);
        std::filesystem::path filePath = fileName;
        if (!std::filesystem::exists(filePath))
        {
            return std::make_shared<std::string>();
        }
        std::ifstream in(fileName, std::ios_base::in | std::ios_base::binary);
        std::string fileData((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        std::shared_ptr<std::string> data = std::make_shared<std::string>(std::move(fileData));
        in.close();
        return data;
    }

    std::string FileStorage::getFullPath(const std::string &key)
    {
        std::string fileName = getFileName(path, key);
        return fileName;
    }

    bool FileStorage::exist(const std::string &key) {
        std::string fileName = getFileName(path, key);
        return std::filesystem::exists(fileName);
    }

    bool FileStorage::save(const std::string &key, const char *data, size_t length)
    {
        std::string fileName = getFileName(path, key);
        std::filesystem::path parentPath = getParentPath(path, fileName);
        if (!std::filesystem::exists(parentPath))
        {
            std::filesystem::create_directories(parentPath);
        }

        std::ofstream out(fileName, std::ios_base::out | std::ios_base::binary);
        out.write(data, length);
        out.close();
        return true;
    }

    bool FileStorage::del(const std::string &key)
    {
        std::string fileName = getFileName(path, key);
        std::filesystem::path filePath = fileName;
        if (std::filesystem::exists(filePath))
        {
            return std::filesystem::remove(filePath);
        }
        return false;
    }

}