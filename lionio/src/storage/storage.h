#pragma once
#include <stddef.h>
#include <string>
#include <vector>
#include <memory>
#include "common.h"
#include "rocksdb_storage.h"
#include "file_storage.h"

namespace lionio
{
    enum EntryType
    {
        Auto,
        File,
        Rocksdb,
        NotFound,
    };

    struct EntryItem
    {
        EntryType entryType;
        std::shared_ptr<std::string> content; /* data */
        std::shared_ptr<std::string> fullPath; /* full path */
    };


    class Storage
    {
    public:
        Storage(const std::string& path);
        virtual ~Storage(){};

    public:
        void setRocksDBValueLimitSize(size_t size){
            rocksdbValueLimitSize = size;
        }

    public:
         bool save(EntryType dest, const std::string& filename, const char *data, size_t length);
         std::shared_ptr<EntryItem> get(const std::string &filename);
    private:
        DISABLE_COPY_ADN_ASSIGN(Storage);
    private:
        std::unique_ptr<RocksDBStorage> rocksdbStorage;
        std::unique_ptr<FileStorage> fileStorage;
        size_t  rocksdbValueLimitSize = 1024*1024*32; //32MB
    };

    static std::string randFileKey(const std::string& suffix);

};
