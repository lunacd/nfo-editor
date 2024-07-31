add_executable(nfo-editor
    nfo_editor.cpp
)

#target_sources(nfo-editor PRIVATE FILE_SET HEADERS FILES
#    nfo_editor_metadata.h
#)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(nfo-editor PRIVATE fmt::fmt)

find_package(imgui CONFIG REQUIRED)
target_link_libraries(nfo-editor PRIVATE imgui::imgui)
