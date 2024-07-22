#include <gtest/gtest.h>
#include <storage/file_storage.h>
#include <filesystem>
#include <stdio.h>
#include <chrono>

using namespace lionio;

static std::string content = "hello world";

TEST(FileStorage, Save)
{
    FileStorage storage = FileStorage("tmp");
    std::string hello = content;
    storage.save("1.txt", hello.data(), hello.length());
    storage.save("2.txt", hello.data(), hello.length());
    storage.save("2/2/2.txt", hello.data(), hello.length());
    storage.save("3/2.txt", hello.data(), hello.length());
    storage.save("/4/2.txt", hello.data(), hello.length());
    storage.save("../../2.txt", hello.data(), hello.length());
    storage.save("./3.txt", hello.data(), hello.length());
    bool exist = storage.exist("1.txt");
    EXPECT_EQ(exist, true);
}

TEST(FileStorage, SaveIllegalPath)
{
    FileStorage storage = FileStorage("tmp");
    std::string hello = content;
    storage.save("../../5.txt", hello.data(), hello.length());
    std::shared_ptr<std::string> data = storage.get("5.txt");
    EXPECT_EQ(hello, *data);
}

TEST(FileStorage, SaveBench)
{
    FileStorage storage = FileStorage("tmp");
    std::string hello = content;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++)
    {
        char buf[50];
        snprintf(buf, sizeof(buf), "bench/%d.txt", i);
        std::string filename = buf;
        storage.save(filename, hello.data(), hello.length());
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto put_ns = end - start;
    auto put_ms = std::chrono::duration_cast<std::chrono::milliseconds>(put_ns);
    std::cout << "write used " << put_ns.count() << "ns " << put_ms.count() << "ms" << std::endl;
}

TEST(FileStorage, Get)
{
    FileStorage storage = FileStorage("tmp");
    std::string hello = content;
    std::shared_ptr<std::string> data = storage.get("1.txt");
    EXPECT_EQ(hello, *data.get());
}

TEST(FileStorage, GetFullPath)
{
    FileStorage storage = FileStorage("tmp");
    std::string hello = content;
    std::string path = storage.getFullPath("1.txt");
    std::cout << path << std::endl;
}

TEST(FileStorage, DelFile)
{
    FileStorage storage = FileStorage("tmp");
    std::string hello = content;
    bool success = storage.del("1.txt");
    bool again = storage.del("1.txt");
    EXPECT_EQ(success, !again);
}

TEST(FileStorage, DelBench)
{
    FileStorage storage = FileStorage("tmp");
    std::string hello = content;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; i++)
    {
        char buf[50];
        snprintf(buf, sizeof(buf), "bench/%d.txt", i);
        std::string filename = buf;
        storage.del(filename);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto put_ns = end - start;
    auto put_ms = std::chrono::duration_cast<std::chrono::milliseconds>(put_ns);
    std::cout << "del used " << put_ns.count() << "ns " << put_ms.count() << "ms" << std::endl;
}
