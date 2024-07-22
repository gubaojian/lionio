#include <gtest/gtest.h>
#include <rocksdb/db.h>
#include <rocksdb/slice.h>
#include <rocksdb/options.h>
#include <chrono>
#include <unistd.h>
#include <filesystem>

#define LZ4 1

TEST(RocksDBTest, DefaultTest) {
    rocksdb::DB *db;
    rocksdb::Options options;
    options.create_if_missing = true;    
    std::filesystem::path path = "tmp";
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
    }
    
    rocksdb::Status status = rocksdb::DB::Open(options, path.string() + "/testdb", &db);
     if (!status.ok()) std::cerr << status.ToString() << std::endl;
     assert(status.ok());
     db->Put(rocksdb::WriteOptions(), "hello", "world");
     usleep(1000);
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<100000; i++ ){
        std::ostringstream os;
        os <<  i;
        os << "hello key " << i;
        rocksdb::Slice key(os.str());
        rocksdb::Slice value("hello world rocksdb");
        db->Put(rocksdb::WriteOptions(), key, value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto put_ns =  end - start;
    auto put_ms =  std::chrono::duration_cast< std::chrono::milliseconds >(put_ns);
    usleep(1000);
    std::cout << "write used " << put_ns.count() << "ns " << put_ms.count() << "ms" << std::endl;
     usleep(1000);
    auto gstart = std::chrono::high_resolution_clock::now();
    for(int i=0; i<100000; i++ ){
        std::ostringstream os;
        os <<  i;
        os << "hello key " << i;
        std::string key = os.str();
        std::string value;
        db->Get(rocksdb::ReadOptions(), db->DefaultColumnFamily(), key, &value);
    }
    auto gend = std::chrono::high_resolution_clock::now();
    auto get_ns =  gend - gstart;
    auto get_ms =  std::chrono::duration_cast< std::chrono::milliseconds >(get_ns);
    std::cout << "get used " << get_ns.count() << "ns " << get_ms.count() << "ms" << std::endl;
    usleep(1000);
    
    delete db;
}

TEST(RocksDBTest, DefaultPinnableSliceTest) {
    rocksdb::DB *db;
    rocksdb::Options options;
    options.create_if_missing = true;    
    std::filesystem::path path = "tmp";
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
    }
    
    rocksdb::Status status = rocksdb::DB::Open(options, path.string() + "/pinnabledb", &db);
     if (!status.ok()) std::cerr << status.ToString() << std::endl;
     assert(status.ok());
     db->Put(rocksdb::WriteOptions(), "hello", "world");
     usleep(1000);
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<100000; i++ ){
        std::ostringstream os;
        os <<  i;
        os << "hello key " << i;
        rocksdb::Slice key(os.str());
        rocksdb::Slice value("hello world rocksdb");
        db->Put(rocksdb::WriteOptions(), key, value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto put_ns =  end - start;
    auto put_ms =  std::chrono::duration_cast< std::chrono::milliseconds >(put_ns);
    usleep(1000);
    std::cout << "write used " << put_ns.count() << "ns " << put_ms.count() << "ms" << std::endl;
     usleep(1000);
    auto gstart = std::chrono::high_resolution_clock::now();
    for(int i=0; i<100000; i++ ){
        std::ostringstream os;
        os <<  i;
        os << "hello key " << i;
        std::string key = os.str();
        rocksdb::PinnableSlice value;
        db->Get(rocksdb::ReadOptions(), db->DefaultColumnFamily(),  key, &value);
    }
    auto gend = std::chrono::high_resolution_clock::now();
    auto get_ns =  gend - gstart;
    auto get_ms =  std::chrono::duration_cast< std::chrono::milliseconds >(get_ns);
    std::cout << "get used " << get_ns.count() << "ns " << get_ms.count() << "ms" << std::endl;
    usleep(1000);
    
    delete db;
}

TEST(RocksDBTest, DefaultLZ4Test) {
    rocksdb::DB *db;
    rocksdb::Options options;
    options.create_if_missing = true;  
    options.compression = rocksdb::CompressionType::kLZ4Compression;
    std::filesystem::path path = "tmp";
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
    }
    
    rocksdb::Status status = rocksdb::DB::Open(options, path.string() + "/lz4db", &db);
     if (!status.ok()) std::cerr << status.ToString() << std::endl;
     assert(status.ok());
     db->Put(rocksdb::WriteOptions(), "hello", "world");
     usleep(1000);
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<100000; i++ ){
        std::ostringstream os;
        os <<  i;
        os << "hello key " << i;
        rocksdb::Slice key(os.str());
        rocksdb::Slice value("hello world rocksdb");
        db->Put(rocksdb::WriteOptions(), key, value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto put_ns =  end - start;
    auto put_ms =  std::chrono::duration_cast< std::chrono::milliseconds >(put_ns);
    usleep(1000);
    std::cout << "write used " << put_ns.count() << "ns " << put_ms.count() << "ms" << std::endl;
     usleep(1000);
    auto gstart = std::chrono::high_resolution_clock::now();
    for(int i=0; i<100000; i++ ){
        std::ostringstream os;
        os <<  i;
        os << "hello key " << i;
        std::string key = os.str();
        rocksdb::PinnableSlice value;
        db->Get(rocksdb::ReadOptions(), db->DefaultColumnFamily(),  key, &value);
    }
    auto gend = std::chrono::high_resolution_clock::now();
    auto get_ns =  gend - gstart;
    auto get_ms =  std::chrono::duration_cast< std::chrono::milliseconds >(get_ns);
    std::cout << "get used " << get_ns.count() << "ns " << get_ms.count() << "ms" << std::endl;
    usleep(1000);
    
    delete db;
}


TEST(RocksDBTest, DefaultZSTDTest) {
    rocksdb::DB *db;
    rocksdb::Options options;
    options.create_if_missing = true;  
    options.compression = rocksdb::CompressionType::kZSTD;
    std::filesystem::path path = "tmp";
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
    }
    
    rocksdb::Status status = rocksdb::DB::Open(options, path.string() + "/zstddb", &db);
     if (!status.ok()) std::cerr << status.ToString() << std::endl;
     assert(status.ok());
     db->Put(rocksdb::WriteOptions(), "hello", "world");
     usleep(1000);
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<100000; i++ ){
        std::ostringstream os;
        os <<  i;
        os << "hello key " << i;
        rocksdb::Slice key(os.str());
        rocksdb::Slice value("hello world rocksdb");
        db->Put(rocksdb::WriteOptions(), key, value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto put_ns =  end - start;
    auto put_ms =  std::chrono::duration_cast< std::chrono::milliseconds >(put_ns);
    usleep(1000);
    std::cout << "write used " << put_ns.count() << "ns " << put_ms.count() << "ms" << std::endl;
     usleep(1000);
    auto gstart = std::chrono::high_resolution_clock::now();
    for(int i=0; i<100000; i++ ){
        std::ostringstream os;
        os <<  i;
        os << "hello key " << i;
        std::string key = os.str();
        rocksdb::PinnableSlice value;
        db->Get(rocksdb::ReadOptions(), db->DefaultColumnFamily(),  key, &value);
    }
    auto gend = std::chrono::high_resolution_clock::now();
    auto get_ns =  gend - gstart;
    auto get_ms =  std::chrono::duration_cast< std::chrono::milliseconds >(get_ns);
    std::cout << "get used " << get_ns.count() << "ns " << get_ms.count() << "ms" << std::endl;
    usleep(1000);
    
    delete db;
}

TEST(RocksDBTest, DefaultZlibTest) {
    rocksdb::DB *db;
    rocksdb::Options options;
    options.create_if_missing = true;  
    options.compression = rocksdb::CompressionType::kZlibCompression;
    std::filesystem::path path = "tmp";
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
    }
    
    rocksdb::Status status = rocksdb::DB::Open(options, path.string() + "/zlibdb", &db);
     if (!status.ok()) std::cerr << status.ToString() << std::endl;
     assert(status.ok());
     db->Put(rocksdb::WriteOptions(), "hello", "world");
     usleep(1000);
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<100000; i++ ){
        std::ostringstream os;
        os <<  i;
        os << "hello key " << i;
        rocksdb::Slice key(os.str());
        rocksdb::Slice value("hello world rocksdb");
        db->Put(rocksdb::WriteOptions(), key, value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto put_ns =  end - start;
    auto put_ms =  std::chrono::duration_cast< std::chrono::milliseconds >(put_ns);
    usleep(1000);
    std::cout << "write used " << put_ns.count() << "ns " << put_ms.count() << "ms" << std::endl;
     usleep(1000);
    auto gstart = std::chrono::high_resolution_clock::now();
    for(int i=0; i<100000; i++ ){
        std::ostringstream os;
        os <<  i;
        os << "hello key " << i;
        std::string key = os.str();
        rocksdb::PinnableSlice value;
        db->Get(rocksdb::ReadOptions(), db->DefaultColumnFamily(),  key, &value);
    }
    auto gend = std::chrono::high_resolution_clock::now();
    auto get_ns =  gend - gstart;
    auto get_ms =  std::chrono::duration_cast< std::chrono::milliseconds >(get_ns);
    std::cout << "get used " << get_ns.count() << "ns " << get_ms.count() << "ms" << std::endl;
    usleep(1000);
    
    delete db;
}

TEST(RocksDBTest, DefaultSnappyTest) {
    rocksdb::DB *db;
    rocksdb::Options options;
    options.create_if_missing = true;  
    options.compression = rocksdb::CompressionType::kSnappyCompression;
    std::filesystem::path path = "tmp";
    if (!std::filesystem::exists(path)) {
        std::filesystem::create_directory(path);
    }
    
    rocksdb::Status status = rocksdb::DB::Open(options, path.string() + "/snappydb", &db);
     if (!status.ok()) std::cerr << status.ToString() << std::endl;
     assert(status.ok());
     db->Put(rocksdb::WriteOptions(), "hello", "world");
     usleep(1000);
    auto start = std::chrono::high_resolution_clock::now();
    for(int i=0; i<100000; i++ ){
        std::ostringstream os;
        os <<  i;
        os << "hello key " << i;
        rocksdb::Slice key(os.str());
        rocksdb::Slice value("hello world rocksdb");
        db->Put(rocksdb::WriteOptions(), key, value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto put_ns =  end - start;
    auto put_ms =  std::chrono::duration_cast< std::chrono::milliseconds >(put_ns);
    usleep(1000);
    std::cout << "write used " << put_ns.count() << "ns " << put_ms.count() << "ms" << std::endl;
     usleep(1000);
    auto gstart = std::chrono::high_resolution_clock::now();
    for(int i=0; i<100000; i++ ){
        std::ostringstream os;
        os <<  i;
        os << "hello key " << i;
        std::string key = os.str();
        rocksdb::PinnableSlice value;
        db->Get(rocksdb::ReadOptions(), db->DefaultColumnFamily(),  key, &value);
    }
    auto gend = std::chrono::high_resolution_clock::now();
    auto get_ns =  gend - gstart;
    auto get_ms =  std::chrono::duration_cast< std::chrono::milliseconds >(get_ns);
    std::cout << "get used " << get_ns.count() << "ns " << get_ms.count() << "ms" << std::endl;
    usleep(1000);
    delete db;
}
