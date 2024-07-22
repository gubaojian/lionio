#include "storage.h"
#include <filesystem>
#include <uuid.h>
#include <sstream>
#include <random>

namespace lionio
{

    Storage::Storage(const std::string &path)
    {
        rocksdbStorage = std::unique_ptr<RocksDBStorage>(new RocksDBStorage(path));
        fileStorage = std::unique_ptr<FileStorage>(new FileStorage(path));
    }

    bool Storage::save(EntryType dest, const std::string &filename, const char *data, size_t length)
    {
        if (dest == EntryType::Auto)
        {
            if (length > rocksdbValueLimitSize)
            {
                dest = lionio::EntryType::Rocksdb;
            }
            else
            {
                dest = lionio::EntryType::File;
            }
        }
        if (dest == lionio::EntryType::File)
        {
            return fileStorage->save(filename, data, length);
        }
        else
        {
            return rocksdbStorage->save(filename, data, length);
        }
        return false;
    }

    std::shared_ptr<EntryItem> Storage::get(const std::string &filename)
    {
        std::shared_ptr<EntryItem> entry = std::make_shared<EntryItem>();
        entry->content = rocksdbStorage->get(filename);
        if (entry->content->length() <= 0)
        {
            entry->fullPath = std::make_shared<std::string>(fileStorage->getFullPath(filename));
            entry->entryType = lionio::EntryType::File;
            if (!fileStorage->exist(filename))
            {
                entry->entryType = lionio::EntryType::NotFound;
            }
        }
        else
        {
            entry->entryType = lionio::EntryType::Rocksdb;
        }
        return entry;
    }

    static std::string randFileKey(const std::string &suffix)
    {
        uuid_t dest;
        char uuidHex[48];
        uuid_generate(dest);
        uuid_unparse(dest, uuidHex);
        std::string uuid(uuidHex);
        std::ostringstream os;
        os << ((char)(rand() % 26 + 'a'));
        os << rand() % 10;
        os << '/';
        os << uuid;
        int pos = suffix.find_last_of('.');
        if (pos >= 0) {
            os << suffix.substr(pos);
        }
        return os.str();
    }

}
