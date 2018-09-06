PROJECT(MDGATEWAY)

AUX_SOURCE_DIRECTORY(./ SRC_LIST)
SET(EXECUTABLE_OUTPUT_PATH ../bin)

ADD_DEFINITIONS(-g -O0 -W -Wall -DLINUX -D_REENTRANT -D_FILE_OFFSET_BITS=64 -DAC_HAS_INFO -DAC_HAS_WARNING -DAC_HAS_ERROR -DAC_HAS_CRITICAL -DTIXML_USE_STL -DHAVE_CXX_STDHEADERS -Wno-deprecated ${CMAKE_CXX_FLAGS})


INCLUDE_DIRECTORIES(
./
/usr/local/include
../public/include/svrutil2
../public/include/json
../public/include/trade/
../public/include/rauinc
../public/include/trade
../public/include/sqlapi
)

LINK_DIRECTORIES(
./
../public/lib/linux
/usr/local/lib
)

ADD_EXECUTABLE(aaa ${SRC_LIST})

TARGET_LINK_LIBRARIES(aaa pthread nnetutil nsvrutil dl json kcrypto
boost_thread z sqlapi)

