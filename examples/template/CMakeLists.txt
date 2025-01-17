set(SampleName template)

set(CMAKE_PREFIX_PATH "D:/QT6/6.7.0/mingw_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
file(GLOB SRC_BASE_LIST  "src/*.cpp")
file(GLOB UI_LIST      "UI/*.hpp"  "UI/myui.cpp"  "UI/myui.ui" )
list(APPEND SRC_BASE_LIST
        ${SRC_BASE_LIST}
        ${UI_LIST}
)
add_executable(${SampleName} ${SRC_BASE_LIST})
target_link_libraries(${SampleName}
        Qt::Core
        Qt::Gui
        Qt::Widgets
)




if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${SampleName} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${SampleName}>/plugins/platforms/")
        add_custom_command(TARGET ${SampleName} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${SampleName}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${SampleName} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${SampleName}>")
    endforeach (QT_LIB)
endif ()
