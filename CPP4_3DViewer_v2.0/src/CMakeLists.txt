cmake_minimum_required(VERSION 3.5)

project(3D_Viewer VERSION 2.0 LANGUAGES C CXX)

set(EXECUTABLE ${PROJECT_NAME}.app)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OpenGL_GL_PREFERENCE LEGACY)

if(NOT WIN32)
    string(ASCII 27 Esc)
    set(ColourReset "${Esc}[m")
    set(ColourBold "${Esc}[1m")
    set(Red "${Esc}[31m")
    set(Green "${Esc}[32m")
    set(Yellow "${Esc}[33m")
    set(Blue "${Esc}[34m")
    set(Magenta "${Esc}[35m")
    set(Cyan "${Esc}[36m")
    set(White "${Esc}[37m")
    set(BoldRed "${Esc}[1;31m")
    set(BoldGreen "${Esc}[1;32m")
    set(BoldYellow "${Esc}[1;33m")
    set(BoldBlue "${Esc}[1;34m")
    set(BoldMagenta "${Esc}[1;35m")
    set(BoldCyan "${Esc}[1;36m")
    set(BoldWhite "${Esc}[1;37m")
endif()

find_package(OpenGL REQUIRED)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets, OpenGL)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)

# target_include_directories(${EXECUTABLE} PUBLIC OpenGL/)
# find_package(Widgets REQUIRED)
# find_package(OpenGLWidgets REQUIRED)
# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets, OpenGL)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
set(ModelFiles)
file(GLOB ModelFiles "model/*")

set(ViewFiles)
file(GLOB ViewFiles "view/*")

set(ControllerFiles)
file(GLOB ControllerFiles "controller/*")

set(GIF_SRC
    include/gif/gifimage/qgifglobal.h
    include/gif/gifimage/qgifimage_p.h
    include/gif/gifimage/qgifimage.cpp
    include/gif/gifimage/qgifimage.h
    include/gif/3rdParty/giflib/dgif_lib.c
    include/gif/3rdParty/giflib/egif_lib.c
    include/gif/3rdParty/giflib/gif_err.c
    include/gif/3rdParty/giflib/gif_font.c
    include/gif/3rdParty/giflib/gif_hash.c
    include/gif/3rdParty/giflib/gif_hash.h
    include/gif/3rdParty/giflib/gif_lib_private.h
    include/gif/3rdParty/giflib/gif_lib.h
    include/gif/3rdParty/giflib/gifalloc.c
    include/gif/3rdParty/giflib/quantize.c
)

set(PROJECT_SOURCES main.cc ${ViewFiles} ${GIF_SRC})

# set(LIBFiles)
# file(GLOB LIBFiles ${ModelFiles})

# set(LIB_SRC ${LIBFiles})
set(LIB_SRC ${ModelFiles} ${ControllerFiles})
option(USE_STATIC "Use static library" ON)

add_library(_${PROJECT_NAME} STATIC ${LIB_SRC})
target_compile_options(_${PROJECT_NAME} PUBLIC -Werror -O2 -fPIC)

message(STATUS "${BoldBlue}OS: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Cmake: ${CMAKE_VERSION}")
message(STATUS "Qt version ${QT_VERSION_MAJOR}")
message(STATUS "Project ${PROJECT_NAME} v${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
message(STATUS "Compile with static library ${USE_STATIC}")
message(STATUS "Library\n ${Cyan}${LIB_SRC}${BoldBlue}")
message(STATUS "Sources\n ${Cyan}${PROJECT_SOURCES}\n${ColourReset}")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${EXECUTABLE} MANUAL_FINALIZATION ${PROJECT_SOURCES})
else()
    add_executable(${EXECUTABLE} ${PROJECT_SOURCES})
endif()

target_link_libraries(${EXECUTABLE} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${EXECUTABLE} PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets)
target_link_libraries(${EXECUTABLE} PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL)
target_link_libraries(${EXECUTABLE} PUBLIC _${PROJECT_NAME})

# target_link_libraries(3D_Viewer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
set_target_properties(${EXECUTABLE} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${EXECUTABLE})
endif()

# macx{
# QT+= core gui openglwidgets
# LIBS+= -framework GLUT -framework OpenGL -framework Cocoa}
# else{
# QT+= core gui opengl
# LIBS+= -lOpenGL -lGLU -lglut
# }