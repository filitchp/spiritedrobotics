cmake_minimum_required (VERSION 2.6) 
project (KITCHEN_SERVER) 

FIND_PACKAGE( Boost 1.50 COMPONENTS program_options system REQUIRED )
find_package (Threads)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

include_directories (${KITCHEN_SERVER_SOURCE_DIR}) 

add_executable (Kitchen_Server main.cpp mime_types.cpp reply.cpp server.cpp request_parser.cpp request_handler.cpp connection_manager.cpp connection.cpp ) 

TARGET_LINK_LIBRARIES( Kitchen_Server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

