cmake_minimum_required(VERSION 3.26)
project(Lab6_11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#[[set(CMAKE_PREFIX_PATH "D:\\Downloads\\QT\\Files\\6.9.0\\mingw_64")]]

set (CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")

#[[find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)]]

include_directories(${CMAKE_SOURCE_DIR}/Domeniu
        ${CMAKE_SOURCE_DIR}/Validator
        ${CMAKE_SOURCE_DIR}/Exceptii
        ${CMAKE_SOURCE_DIR}/Repository
        ${CMAKE_SOURCE_DIR}/Service
        ${CMAKE_SOURCE_DIR}/UI)

add_executable(Lab6_11 main.cpp
        Domeniu/Oferta.cpp Domeniu/Oferta.h
        Teste/Teste.cpp Teste/Teste.h
        Validator/ValidatorOferta.cpp Validator/ValidatorOferta.h
        Exceptii/Exceptii.h
        Repository/Repository.h
        Repository/FileRepository.h
        Service/ServiceOferta/ServiceOferta.cpp Service/ServiceOferta/ServiceOferta.h
        Service/ServiceCos/ServiceCos.cpp Service/ServiceCos/ServiceCos.h
        UI/InterfataConsola/Consola.cpp UI/InterfataConsola/Consola.h
        UI/InterfataQT/InterfataQT.cpp UI/InterfataQT/InterfataQT.h
        Service/Undo/ActiuneUndo.h)

#[[target_link_libraries(Lab6_11
        Qt::Core
        Qt::Gui
        Qt::Widgets
)]]

#[[
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
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt6${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()]]
