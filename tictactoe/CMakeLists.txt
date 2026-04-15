cmake_minimum_required(VERSION 3.16)

project(tictactoe VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick WebSockets)

qt_standard_project_setup(REQUIRES 6.10)

qt_add_executable(apptictactoe
    main.cpp
)

qt_add_qml_module(apptictactoe
    URI tictactoe
    QML_FILES
        Main.qml
        SOURCES Tictactoe.h Tictactoe.cpp
        QML_FILES StartScreen.qml
        QML_FILES GameScreen.qml
        QML_FILES GameOverScreen.qml
        QML_FILES ConnectScreen.qml
        QML_FILES WaitingScreen.qml
        SOURCES gamemanager.h gamemanager.cpp
        SOURCES gameserver.h gameserver.cpp
        SOURCES gameclient.h gameclient.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apptictactoe PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apptictactoe
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apptictactoe
    PRIVATE Qt6::Quick
    PRIVATE Qt6::WebSockets
)

install(TARGETS apptictactoe
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
