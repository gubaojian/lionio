#include <gtest/gtest.h>
#include <storage/storage.h>
#include <storage/rocksdb_storage.h>
#include <zstd.h>

using namespace lionio;

static std::string content = "hello rocksdb";

TEST(RocksDBStorage, SaveFileTest)
{
    RocksDBStorage storage = RocksDBStorage("tmp");
    std::string key = "hello";
    std::string value = "world";
    storage.save(key, value.data(), value.length());
    std::shared_ptr<std::string> data = storage.get(key);
    EXPECT_EQ(value, *data);
}

TEST(FileStorage, SaveBench)
{
    RocksDBStorage storage = RocksDBStorage("tmp");
    std::string hello = content;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++)
    {
        char buf[50];
        snprintf(buf, sizeof(buf), "bench/%d.txt", i);
        std::string key = buf;
        storage.save(key, hello.data(), hello.length());
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto put_ns = end - start;
    auto put_ms = std::chrono::duration_cast<std::chrono::milliseconds>(put_ns);
    std::cout << "write used " << put_ns.count() << "ns " << put_ms.count() << "ms" << std::endl;
}