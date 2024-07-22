cd third_party/bzip2-1.0.8
make -j2
cd ..
cd zlib-1.2.12
./configure
make -j2
cd ..
cd lz4-1.9.3
make -j2
cd ..
cd zstd-1.5.2
make -j2
cd ..
cd snappy-1.1.9
mkdir -p build
cd build
cmake -DSNAPPY_BUILD_TESTS=OFF -DSNAPPY_BUILD_BENCHMARKS=OFF ..
make -j2
cd ..
cd ..
cd libuuid-1.0.3
./configure
make
cd ..
export DEPS_STATIC_LIBS="-I$(pwd)/bzip2-1.0.8 -I$(pwd)/lz4-1.9.3/lib -I$(pwd)/zstd-1.5.2/lib -I$(pwd)/zlib-1.2.12 -I$(pwd)/snappy-1.1.9 -I$(pwd)/snappy-1.1.9/build "
export DEPS_STATIC_LIBS="${DEPS_STATIC_LIBS} -DBZIP2 -DZLIB -DLZ4 -DZSTD -DSNAPPY "
cd rocksdb-7.1.2
cd build_tools
sed -i '.bak' 's/# Default to fbcode gcc on internal fb machines/COMMON_FLAGS="$DEPS_STATIC_LIBS $COMMON_FLAGS"/' build_detect_platform
##sed -i '.bak' 's/# Default to fbcode gcc on internal fb machines/PLATFORM_CXXFLAGS="$PLATFORM_CXXFLAGS $DEPS_STATIC_LIBS"/' build_detect_platform
cd ..
make static_lib -j8
cd ..
cd drogon
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
cd ..
cd ..
cd ..
mkdir -p build 
cd build 
cmake ..
make -j4
