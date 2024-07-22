## cmake tutorial 
https://cmake.org/cmake/help/latest/guide/tutorial/index.html 

sh build_deps.sh
mkdir build
cmake ..
make -j4


## vs code include path

${workspaceFolder}/third_party/googletest-1.11.0/googletest/include/
${workspaceFolder}/third_party/rocksdb-7.1.2/include
cmake --build . --target clean

## document
google test  https://google.github.io/googletest/
             https://google.github.io/googletest/primer.html
rocksdb build  https://github.com/facebook/rocksdb/blob/main/INSTALL.md
snappy: https://github.com/google/snappy
gflags: https://gflags.github.io/gflags/
zlib: https://www.zlib.net/
zstd: https://facebook.github.io/zstd/
lz4: https://github.com/lz4/lz4
bzip2: https://sourceware.org/bzip2/
drogon: https://github.com/drogonframework/drogon/wiki/CHN-02-%E5%AE%89%E8%A3%85 
libconfig: http://www.hyperrealm.com/libconfig/libconfig.html 


## todo 项目完成后提供windows版本