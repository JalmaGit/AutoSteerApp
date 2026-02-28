teer_GUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Gui
    Location
    Positioning
)

add_subdirectory(src)
add_executable(Autosteer_GUI main.cpp)

target_link_libraries(Autosteer_GUI
Qt6::Widgets
Qt6::Core
Qt6::Gui
Qt6::Location
Qt6::Positioning
guiLib
)

file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION "${CMAKE_BINARY_DIR}/bin")
