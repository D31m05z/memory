#/** * * * BME-VIK-MI_2018_02_08 * * *|1.NHF|* * * * * * * * * *\
#*    _ _____   _____        __ _                              *
#*   (_)  __ \ / ____|      / _| |                             *
#*   |_| |__)| (___    ___ | |_| |___      ____ _ _ __ ___     *
#*   | |  _  / \___ \ / _ \|  _| __\ \ /\ / / _` | '__/ _ \    *
#*   | | | \ \ ____) | (_) | | | |_ \ V  V / (_| | | |  __/    *
#*   |_|_|  \_\_____/ \___/|_|  \__| \_/\_/ \__,_|_|  \___|    *
#*                                                             *
#*                   http://irsoftware.net                     *
#*                                                             *
#*              contact_adress: sk8Geri@gmail.com               *
#*                                                               *
#*       This file is a part of the work done by aFagylaltos.     *
#*         You are free to use the code in any way you like,      *
#*         modified, unmodified or copied into your own work.     *
#*        However, I would like you to consider the following:    *
#*                                                               *
#*  -If you use this file and its contents unmodified,         *
#*              or use a major part of this file,               *
#*     please credit the author and leave this note untouched.   *
#*  -If you want to use anything in this file commercially,      *
#*                please request my approval.                    *
#*                                                              *
#\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

cmake_minimum_required(VERSION 3.9)

project(memory)

set(CMAKE_CXX_STANDARD 11)

find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
pkg_search_module(ALLEGRO REQUIRED allegro-5 allegro-5.2)
pkg_search_module(ALLEGRO_IMAGE REQUIRED allegro_image-5 allegro_image-5.2)
pkg_search_module(ALLEGRO_AUDIO REQUIRED allegro_audio-5 allegro_audio-5.2)
pkg_search_module(ALLEGRO_ACODEC REQUIRED allegro_acodec-5 allegro_acodec-5.2)
pkg_search_module(ALLEGRO_DIALOG REQUIRED allegro_dialog-5 allegro_dialog-5.2)
pkg_search_module(ALLEGRO_FONT REQUIRED allegro_font-5 allegro_font-5.2)

add_executable(${PROJECT_NAME}
        src/Animation.c
        src/Engine.c
        src/Engine.h
        src/Events.c
        src/Events.h
        src/Init.c
        src/Init.h
        src/main.c
        src/Platform.c
        src/Platform.h
        src/Renderer.c)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(${PROJECT_NAME} PRIVATE "-Wall")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/W4 /WX /w14244")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${ALLEGRO_INCLUDE_DIRS} ${GTK2_INCLUDE_DIRS})

target_link_libraries(
        ${PROJECT_NAME}
        ${ALLEGRO_LIBRARIES}
        ${ALLEGRO_MAIN_LIBRARIES}
        ${ALLEGRO_IMAGE_LIBRARIES}
        ${ALLEGRO_AUDIO_LIBRARIES}
        ${ALLEGRO_ACODEC_LIBRARIES}
        ${ALLEGRO_DIALOG_LIBRARIES}
        ${ALLEGRO_FONT_LIBRARIES}
        ${GTK2_LIBRARIES})
