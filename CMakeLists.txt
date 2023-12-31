cmake_minimum_required(VERSION 3.5)

project(window VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        day.h
        room.h
        admin.h
        phongmay.h
        ID1.txt
        ID2.txt
        ID3.txt
        ID4.txt
        ID5.txt
        ID6.txt
        ID7.txt
        ID8.txt
        ID9.txt
        ID10.txt
        TT1.txt
        TT2.txt
        TT3.txt
        TT4.txt
        TT5.txt
        TT6.txt
        TT7.txt
        TT8.txt
        TT9.txt
        TT10.txt
        Time1.txt
        Time2.txt
        Time3.txt
        Time4.txt
        Time5.txt
        Time6.txt
        Time7.txt
        Time8.txt
        Time9.txt
        Time10.txt
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(window
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}






    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET window APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(window SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(window
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(window PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.window)
endif()
set_target_properties(window PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS window
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(window)
endif()
