cmake_minimum_required(VERSION 3.0)

file(GLOB_RECURSE LIB_SRC "*.cpp" "*.c")

set( MUPDF_ROOT ${PROJECT_SOURCE_DIR}/deps/HKMuPDF)
include_directories(${MUPDF_ROOT}/include)
include_directories(${PROJECT_SOURCE_DIR}/deps/HKFreetype/include)
include_directories(${MUPDF_ROOT}/thirdparty/jpeg)
include_directories(${MUPDF_ROOT}/scripts/jpeg)
include_directories(${MUPDF_ROOT}/source/fitz)

set( HKPDF_ROOT ${PROJECT_SOURCE_DIR}/HKPDF)

include_directories(${HKPDF_ROOT})
include_directories(${HKPDF_ROOT}/HKPDF)
include_directories(${HKPDF_ROOT}/HKPDF/HKMuPDF)
include_directories(${HKPDF_ROOT}/HKPDF/HKColumn)
include_directories(${HKPDF_ROOT}/HKPDF/HKPDF)
include_directories(${HKPDF_ROOT}/HKPDF/HKPDFPage)
include_directories(${HKPDF_ROOT}/HKPDF/HKTable)
include_directories(${HKPDF_ROOT}/HKPDF/HKTextDevice)
include_directories(${HKPDF_ROOT}/HKPDF/v2.0)
include_directories(${HKPDF_ROOT}/HKPDF/pdf2html)


set( K2_ROOT ${PROJECT_SOURCE_DIR}/deps/HKK2)
include_directories(${K2_ROOT})
include_directories(${K2_ROOT}/k2pdfoptlib)
include_directories(${K2_ROOT}/willuslib)

include_directories(${PROJECT_SOURCE_DIR}/third)

set( JIEBA_ROOT ${PROJECT_SOURCE_DIR}/third/libcppjieba)
include_directories(${JIEBA_ROOT}/include)

add_library(libmupdf.so SHARED ${LIB_SRC})

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set_target_properties(libmupdf.so PROPERTIES PREFIX "" SUFFIX "")

find_library(
    # Sets the name of the path variable.
    log-lib

    # Specifies the name of the NDK library that
    # you want CMake to locate.
    log
)

target_link_libraries(libmupdf.so 
jnigraphics
${log-lib}
HKPDF
k2pdfopt
mupdf
mupdf_third
jpeg
freetype
minizip
)