cmake_minimum_required(VERSION 3.5)

set(APPNAME snomcontrol)

project(${APPNAME}-app LANGUAGES CXX VERSION 0.2.0)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

IF(MSVC)
    SET(OPTIONS WIN32)
ENDIF(MSVC)

add_executable(${APPNAME} ${OPTIONS} main.cpp buttons.ui mainwindow.h requesthandler.cpp settings.h settingsdialog.ui mainwindow.ui requesthandler.h settingsdialog.cpp mainwindow.cpp  settings.cpp  settingsdialog.h webwidget.cpp webwidget.h webwidget.ui ../3rdparty/SingleApplication-3.0.14/singleapplication.h ../3rdparty/SingleApplication-3.0.14/singleapplication.cpp ../3rdparty/SingleApplication-3.0.14/singleapplication_p.h ../3rdparty/SingleApplication-3.0.14/singleapplication_p.cpp ../resources/snomcontrol.qrc)

find_package(Qt5 COMPONENTS Widgets Network WebEngineWidgets)

target_link_libraries(${APPNAME} Qt5::Core Qt5::Widgets Qt5::Network Qt5::WebEngineWidgets)
target_compile_definitions(${APPNAME} PRIVATE QAPPLICATION_CLASS=QApplication)
target_include_directories(${APPNAME} PRIVATE ../3rdparty/SingleApplication-3.0.14/)

set_target_properties(${APPNAME} PROPERTIES CXX_EXTENSIONS OFF)


include(GNUInstallDirs)
install(TARGETS ${APPNAME}
  EXPORT ${APPNAME}-targets
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

    install(FILES org.ballessay.snomcontrol.desktop DESTINATION share/applications)
    install(FILES ../resources/snomcontrol.png DESTINATION share/icons/hicolor/256x256/apps)
    install(FILES ../resources/snomcontrol.appdata.xml DESTINATION share/metainfo)

endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

