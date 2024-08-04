set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS .)

# Qt requires C++17
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Core Qml Quick Widgets)

qt_add_executable(nfo-editor
    NfoEditor.cpp
    qml/NfoEditor.qrc
)

#target_sources(nfo-editor PRIVATE FILE_SET HEADERS FILES
#    nfo_editor_metadata.h
#)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(nfo-editor PRIVATE fmt::fmt)

target_link_libraries(nfo-editor PRIVATE Qt6::Qml Qt6::Quick Qt6::Widgets)

qt_import_qml_plugins(nfo-editor)
