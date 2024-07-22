cd third_party/bzip2-1.0.8
make clean
cd ..
cd zlib-1.2.12
make clean
cd ..
cd lz4-1.9.3
make clean
cd ..
cd zstd-1.5.2
make clean
cd ..
cd snappy-1.1.9
rf -rf build
cd ..
cd libuuid-1.0.3
make clean
cd ..
export DEPS_STATIC_LIBS="-I$(pwd)/bzip2-1.0.8 -I$(pwd)/lz4-1.9.3/lib -I$(pwd)/zstd-1.5.2/lib -I$(pwd)/zlib-1.2.12 "
cd rocksdb-7.1.2
##cd build_tools
## sed -i '.bak' 's/# Default to fbcode gcc on internal fb machines/COMMON_FLAGS="$DEPS_STATIC_LIBS $COMMON_FLAGS"/' build_detect_platform
##sed -i '.bak' 's/# Default to fbcode gcc on internal fb machines/PLATFORM_CXXFLAGS="$PLATFORM_CXXFLAGS $DEPS_STATIC_LIBS"/' build_detect_platform
##cd ..
make clean
cd ..
cd drogon
rf -rf build
cd ..
cd ..
rm -rf build