## cmake version
cmake_minimum_required(VERSION 2.8.12)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)


set(CMAKE_BUILD_TYPE Debug)

## project name
project(lionio)

enable_testing()
# add third party library
add_subdirectory(third_party)
include_directories(src)
include_directories(${gtest_build_include_dirs})

include_directories(${CMAKE_SOURCE_DIR}/third_party/googletest-1.11.0/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/third_party/zlib-1.2.12  
                    ${CMAKE_BINARY_DIR}/third_party/zlib-1.2.12)
                    
                   
include_directories(${CMAKE_SOURCE_DIR}/third_party/lz4-1.9.3/lib) 
include_directories(${CMAKE_SOURCE_DIR}/third_party/zstd-1.5.2/lib)  

include_directories(${CMAKE_SOURCE_DIR}/third_party/rocksdb-7.1.2/include)  

include_directories(${CMAKE_SOURCE_DIR}/third_party/libuuid-1.0.3/)  



set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})

find_library(ROCKSDB_LIB rocksdb ${CMAKE_SOURCE_DIR}/third_party/rocksdb-7.1.2/)

find_library(BZ2_LIB bz2 ${CMAKE_SOURCE_DIR}/third_party/bzip2-1.0.8/)

find_library(ZLIB_LIB z ${CMAKE_SOURCE_DIR}/third_party/zlib-1.2.12/)


find_library(LZ4_LIB lz4 ${CMAKE_SOURCE_DIR}/third_party/lz4-1.9.3/lib)

find_library(ZSTD_LIB zstd ${CMAKE_SOURCE_DIR}/third_party/zstd-1.5.2)

find_library(SNAPPY_LIB snappy ${CMAKE_SOURCE_DIR}/third_party/snappy-1.1.9/build)

find_library(NOT_LIB not2 ${CMAKE_SOURCE_DIR}/third_party/bzip2-1.0.8/)

find_library(UUID_STATIC_LIB uuid ${CMAKE_SOURCE_DIR}/third_party/libuuid-1.0.3/.libs/)

message("${SNAPPY_LIB} ${CMAKE_SOURCE_DIR}/third_party/snappy-1.1.9/build")
message("try found rocksdb lib try found ${ROCKSDB_LIB} ${NOT_LIB}")
message("uuid ${UUID_STATIC_LIB} libfff")


if(NOT EXISTS ${ROCKSDB_LIB})
   message(FATAL_ERROR "rocksdb static library not found, please run build_deps.sh")
else()
   message("find rocksdb static ${ROCKSDB_LIB}")
endif()



##find_library(ROCKSDB_LIB rocksdb /Users/efurture/code/lionio/lionio/third_party/rocksdb-7.1.2/librocksdb.a)
## /rocksdb-7.1.2/

set(STORAGE_SOURCES
  src/storage/file_storage.cc  
  src/storage/rocksdb_storage.cc
  src/storage/storage.cc)


add_executable(
  hello_test
  test/hello_test.cc
)

target_link_libraries(
  hello_test
  gtest_main
)


add_subdirectory(test)


## executable 
add_executable(lionio  main.cc)


target_link_libraries(
  lionio
)
target_link_libraries(
  lionio
  ${ROCKSDB_LIB}
  ${BZ2_LIB}
)


add_executable(
  rocksdb_test
  test/rocksdb/rocksdb_test.cc
  ${STORAGE_SOURCES}
)

add_executable(
  filestorage_test
  test/storage/file_storage_test.cc
  ${STORAGE_SOURCES}
)

add_executable(
  rocksdb_storage_test
  test/storage/rocksdb_storage_test.cc
  ${STORAGE_SOURCES}
)

add_executable(
  uuid_test
  test/uuid/uuid_test.cc
)

target_link_libraries(
  rocksdb_test
  gtest_main
  ${ZLIB_LIB}
  ${ROCKSDB_LIB}
  ${BZ2_LIB}
  ${CMAKE_SOURCE_DIR}/third_party/lz4-1.9.3/lib/liblz4.a
  ${CMAKE_SOURCE_DIR}/third_party/zstd-1.5.2/lib/libzstd.a
  ${SNAPPY_LIB}
  ${CMAKE_SOURCE_DIR}/third_party/snappy-1.1.9/build/libsnappy.a
)


target_link_libraries(
  filestorage_test
  gtest_main
  ${ZLIB_LIB}
  ${ROCKSDB_LIB}
  ${BZ2_LIB}
  ${CMAKE_SOURCE_DIR}/third_party/lz4-1.9.3/lib/liblz4.a
  ${CMAKE_SOURCE_DIR}/third_party/zstd-1.5.2/lib/libzstd.a
  ${SNAPPY_LIB}
  ${CMAKE_SOURCE_DIR}/third_party/snappy-1.1.9/build/libsnappy.a
)

target_link_libraries(
  rocksdb_storage_test
  gtest_main
  ${ZLIB_LIB}
  ${ROCKSDB_LIB}
  ${BZ2_LIB}
  ${CMAKE_SOURCE_DIR}/third_party/lz4-1.9.3/lib/liblz4.a
  ${CMAKE_SOURCE_DIR}/third_party/zstd-1.5.2/lib/libzstd.a
  ${SNAPPY_LIB}
  ${CMAKE_SOURCE_DIR}/third_party/snappy-1.1.9/build/libsnappy.a
)

target_link_libraries(
  uuid_test
  gtest_main
  ${UUID_STATIC_LIB}
)

