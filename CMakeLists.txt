cmake_minimum_required(VERSION 3.8)

project(dmqtproject)

LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
INCLUDE(cmake/ModuleImport.cmake)
INCLUDE(cmake/ModuleCompileOptions.cmake)
ModuleSetCompileOptions()
ModuleSetWinCompilerFlags()

# Find includes in the build directories

set(QT_MODULES Core Gui Widgets Sql Network Multimedia Xml)
find_package(Qt5 REQUIRED COMPONENTS ${QT_MODULES})


IF(Qt5_FOUND)
    MESSAGE(STATUS "Qt5_FOUND ${QT5_LIBRARIES} ${Qt5_INCLUDE_DIRS}")
ENDIF(Qt5_FOUND)

include_directories(${Qt5_INCLUDE_DIRS})

# Turn on automatic invocation of the MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

IF (MSVC)
    add_definitions(/bigobj)
    add_definitions(/utf-8)
ENDIF()

# 搜索所有源文件
FILE(GLOB_RECURSE ST_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/ScreenTime/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/ScreenTime/*.h
)

FILE(GLOB_RECURSE UI_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/tools/ScreenTime/*.ui
)

# 添加资源文件
qt_add_resources(QT_RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tools/ScreenTime/ScreenTime.qrc)

# 添加生成的 UI 文件
qt_wrap_ui(UIS_HEADERS ${UI_FILES})

# 最终添加到目标
add_executable(ScreenTime ${ST_FILES} ${UI_FILES} ${UIS_HEADERS} ${QT_RESOURCES})

target_link_libraries(ScreenTime Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Sql)
