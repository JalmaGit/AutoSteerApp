set(sources
    "MyApp.cpp"
    "MapWidget.cpp"
)

add_library(guiLib ${sources})
target_link_libraries(guiLib PUBLIC
    Qt6::Widgets
    Qt6::Core
    Qt6::Gui
    Qt6::Location
    Qt6::Positioning
)

target_include_directories(guiLib PUBLIC "${CMAKE_SOURCE_DIR}/include")