cmake_minimum_required (VERSION 2.6) 
project (ORDER_SERVER)

FIND_PACKAGE( Boost 1.46 COMPONENTS program_options filesystem system REQUIRED )
find_package (Threads)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

include_directories (${ORDER_SERVER_SOURCE_DIR}) 

add_executable (Order_Server main.cpp mime_types.cpp reply.cpp server.cpp request_parser.cpp request_handler.cpp connection_manager.cpp connection.cpp drink_manager.cpp models/drink.cpp models/ingredient.cpp models/barbot.cpp models/tower.cpp models/order.cpp utils/table_printer.cpp)

TARGET_LINK_LIBRARIES( Order_Server ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

