set(SampleName Aliyun)

set(CMAKE_PREFIX_PATH "D:/QT6/6.7.0/mingw_64")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)
file(GLOB SRC_BASE_LIST  "src/*.cpp" "src/*.hpp")
file(GLOB UI_LIST      "UI/*.hpp"  "UI/*.cpp"  "UI/*.ui"  )
list(APPEND SRC_BASE_LIST
        ${SRC_BASE_LIST}
        ${UI_LIST}
)
include_directories("D:/Eclipse_Paho_C/include")
#set(QRC_SOURCE_FILE resource/QQlogin.qrc)
#qt_add_resources(SOURCES  ${QRC_SOURCE_FILE})

add_executable(${SampleName} ${SRC_BASE_LIST}  "resource/1.qrc"
        src/MYClient.cpp
        src/MYClient.hpp)
target_link_libraries(${SampleName} PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
ax_include_link(${SampleName})
target_link_libraries(${SampleName}  PRIVATE  "D:/Eclipse_Paho_C/bin/libpaho-mqtt3a.dll")









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
