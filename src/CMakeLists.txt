cmake_minimum_required(VERSION 3.1...3.13)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(snomcontrol-app LANGUAGES CXX VERSION 0.2.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Widgets Network WebEngineWidgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


include_directories(../3rdparty/SingleApplication-3.0.14/)
#add_compile_definitions(QAPPLICATION_CLASS=QApplication)
add_definitions(-DQAPPLICATION_CLASS=QApplication)

add_executable(snomcontrol main.cpp buttons.ui mainwindow.h requesthandler.cpp settings.h settingsdialog.ui mainwindow.ui requesthandler.h settingsdialog.cpp mainwindow.cpp  settings.cpp  settingsdialog.h webwidget.cpp webwidget.h webwidget.ui ../3rdparty/SingleApplication-3.0.14/singleapplication.h ../3rdparty/SingleApplication-3.0.14/singleapplication.cpp ../3rdparty/SingleApplication-3.0.14/singleapplication_p.h ../3rdparty/SingleApplication-3.0.14/singleapplication_p.cpp ../resources/snomcontrol.qrc)
target_link_libraries(snomcontrol Qt5::Core Qt5::Widgets Qt5::Network Qt5::WebEngineWidgets)

#set_target_properties(snomcontrol PROPERTIES CXX_EXTENSIONS OFF)

install(TARGETS snomcontrol DESTINATION bin)
if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

    install(FILES org.ballessay.snomcontrol.desktop DESTINATION share/applications )

    install(FILES ../resources/snomcontrol.png DESTINATION share/icons/hicolor/256x256/apps)


endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")

