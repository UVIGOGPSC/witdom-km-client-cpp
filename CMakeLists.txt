cmake_minimum_required(VERSION 2.8.9)
project (SSP-client)

# Compiler variables
add_definitions(-std=c++11 -pipe -Wall -Wvla -O3 -fPIC)

# Sources
file(GLOB SOURCES barbican-clients/cpp/*.cpp integration-tests/cpp/*.cpp)
#set ( SOURCES main.cpp )

# Includes
file(GLOB POCO_INCLUDES "/usr/local/include/Poco")
file(GLOB SELF_INCLUDES barbican-clients/cpp integration-tests/cpp)
include_directories( ${POCO_INCLUDES} ${SELF_INCLUDES} )


file(GLOB INCLUDES "/usr/local/include/Poco/*")
include_directories( /usr/local/include/Poco $(INCLUDES) )

#For the shared library:
set ( PROJECT_LINK_LIBS libPocoFoundation.so 
						libPocoJSON.so 
						libPocoData.so 
						libPocoUtil.so 
						libPocoNet.so 
						libPocoNetSSL.so 
						libPocoCrypto.so 
						libPocoZip.so )
link_directories( /usr/local/lib )

#MESSAGE ( "${SOURCES}" )
#MESSAGE ( ${CMAKE_CURRENT_SOURCE_DIR} )

# Linker variables
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}")

add_executable(SSP-client ${SOURCES})
target_link_libraries(SSP-client ${PROJECT_LINK_LIBS} )
