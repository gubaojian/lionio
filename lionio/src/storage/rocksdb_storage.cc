#include "rocksdb_storage.h"
#include <filesystem>
#include <iostream>

namespace lionio
{
    RocksDBStorage::RocksDBStorage(const std::string &path_str)
    {
        rocksdb::Options options;
        options.create_if_missing = true;
        options.compression = rocksdb::CompressionType::kLZ4Compression;
        std::filesystem::path path = path_str;
        if (!std::filesystem::exists(path))
        {
            std::filesystem::create_directory(path);
        }

        rocksdb::Status status = rocksdb::DB::Open(options, path.string() + "/rocksdb", &db);
        if (!status.ok())
        {
            std::cerr << status.ToString() << std::endl;
        }
    }

    RocksDBStorage::~RocksDBStorage()
    {
        delete db;
    }

    bool RocksDBStorage::save(const std::string &fileKey, const char *data, size_t length)
    {
        rocksdb::Slice key(fileKey);
        rocksdb::Slice value(data, length);
        rocksdb::Status status = db->Put(rocksdb::WriteOptions(), key, value);
        return status.ok();
    }

    bool RocksDBStorage::exist(const std::string& fileKey){
        rocksdb::Slice key(fileKey);
        std::shared_ptr<std::string> value = std::make_shared<std::string>();
        rocksdb::Status status = db->Get(rocksdb::ReadOptions(), db->DefaultColumnFamily(), key, value.get());
        return status.ok();
    }

    std::shared_ptr<std::string> RocksDBStorage::get(const std::string &key)
    {
        std::shared_ptr<std::string> value = std::make_shared<std::string>();
        db->Get(rocksdb::ReadOptions(), db->DefaultColumnFamily(), key, value.get());
        return value;
    }

    bool RocksDBStorage::del(const std::string &fileKey)
    {
        rocksdb::Slice key(fileKey);
        rocksdb::Status status = db->Delete(rocksdb::WriteOptions(), key);
        return status.ok();
    }
}