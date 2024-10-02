cmake_minimum_required(VERSION 3.5)

project(3D_Viewer VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Поиск пакетов Qt5 и Qt6 с соответствующими компонентами
find_package(Qt6 COMPONENTS Widgets OpenGLWidgets QUIET)
find_package(Qt5 COMPONENTS Widgets OpenGL QUIET)

# Установка версии Qt
if(Qt6_FOUND)
    set(QT_VERSION_MAJOR 6)
    set(QT_LIBRARIES Qt6::Widgets Qt6::OpenGLWidgets)
elseif(Qt5_FOUND)
    set(QT_VERSION_MAJOR 5)
    set(QT_LIBRARIES Qt5::Widgets Qt5::OpenGL)
else()
    message(FATAL_ERROR "Neither Qt5 nor Qt6 found")
endif()

# Добавление путей к заголовочным файлам
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/giflib
    ${CMAKE_CURRENT_SOURCE_DIR}/gifimage
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}  
)

set(PROJECT_SOURCES
    main.cc
    mainwindow.cc
    mainwindow.h
    mainwindow.ui
    display.cc
    display.h
    giflib/dgif_lib.c
    giflib/egif_lib.c
    giflib/gif_err.c
    giflib/gif_font.c
    giflib/gif_hash.c
    giflib/gif_hash.h
    giflib/gif_lib.h
    giflib/gif_lib_private.h
    giflib/gifalloc.c
    giflib/quantize.c
    gifimage/qgifglobal.h
    gifimage/qgifimage_p.h
    gifimage/qgifimage.h
    gifimage/qgifimage.cpp
    controller.cc
    controller.h
    preferences.cc
    preferences.h
    preferences.ui
    interactions.cc
    interactions.h
    interactions.ui
    ../Backend/model/s21_builder.h
    ../Backend/model/s21_model.h
    ../Backend/model/s21_observer.h
#    ../Backend/back.h
#    ../Backend/athen.c
#    ../Backend/files.c
#    ../Backend/free.c
)

if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_add_executable(3D_Viewer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(3D_Viewer SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(3D_Viewer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

add_library(viewer STATIC IMPORTED)
set_target_properties(viewer PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../viewer.a)

target_link_libraries(3D_Viewer PRIVATE ${QT_LIBRARIES} viewer)

# Установка идентификатора пакета для iOS или macOS
if(${QT_VERSION_MAJOR} EQUAL 5 AND Qt5_VERSION VERSION_LESS 5.15.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.3D_Viewer)
elseif(${QT_VERSION_MAJOR} EQUAL 6 AND Qt6_VERSION VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.3D_Viewer)
endif()

set_target_properties(3D_Viewer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS 3D_Viewer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_finalize_executable(3D_Viewer)
endif()
