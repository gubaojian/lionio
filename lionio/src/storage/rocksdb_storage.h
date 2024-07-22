#pragma once
#include <memory>
#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/options.h>
#include "common.h"

namespace lionio
{
  class RocksDBStorage
  {
  public:
    RocksDBStorage(const std::string &path);
    bool save(const std::string &key, const char *data, size_t length);
    std::shared_ptr<std::string> get(const std::string &key);
    bool exist(const std::string &key);
    bool del(const std::string &key);

  public:
    virtual ~RocksDBStorage();

  private:
    DISABLE_COPY_ADN_ASSIGN(RocksDBStorage);

  private:
    rocksdb::DB *db;
  };

}
