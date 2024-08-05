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
    NfoEditorAutocomplete.cpp
    NfoEditorQtBridge.cpp
)

target_include_directories(nfo-editor PRIVATE .)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(nfo-editor PRIVATE fmt::fmt)

find_package(PkgConfig REQUIRED)
pkg_check_modules(marisa REQUIRED IMPORTED_TARGET marisa)
target_link_libraries(nfo-editor PRIVATE PkgConfig::marisa)

target_link_libraries(nfo-editor PRIVATE Qt6::Qml Qt6::Quick Qt6::Widgets)

qt_import_qml_plugins(nfo-editor)
