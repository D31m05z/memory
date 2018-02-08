
/** * * * BME-VIK-MI_2011_10_17 * * *|1.NHF|* * * * * * * * * *\
*    _ _____   _____        __ _                              *
*   (_)  __ \ / ____|      / _| |                             *
*   |_| |__)| (___    ___ | |_| |___      ____ _ _ __ ___     *
*   | |  _  / \___ \ / _ \|  _| __\ \ /\ / / _` | '__/ _ \    *
*   | | | \ \ ____) | (_) | | | |_ \ V  V / (_| | | |  __/    *
*   |_|_|  \_\_____/ \___/|_|  \__| \_/\_/ \__,_|_|  \___|    *
*                                                             *
*                   http://irsoftware.net                     *
*                                                             *
*              contact_adress: sk8Geri@gmail.com               *
*                                                               *
*       This file is a part of the work done by aFagylaltos.     *
*         You are free to use the code in any way you like,      *
*         modified, unmodified or copied into your own work.     *
*        However, I would like you to consider the following:    *
*                                                               *
*  -If you use this file and its contents unmodified,         *
*              or use a major part of this file,               *
*     please credit the author and leave this note untouched.   *
*  -If you want to use anything in this file commercially,      *
*                please request my approval.                    *
*                                                              *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#include <stdio.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#if defined(_WIN32)
//#   include <windows.h>
#elif defined(__linux__)
#   include <stdio.h>
#   include <gtk/gtk.h>
#elif defined(__APPLE__)
#include <CoreServices/CoreServices.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#endif


#define GAME_PATH "../base/"
#define MAX_ANIMS 10

enum {
    SUCCES, FAIL
};

/*
typedef unsigned char uint8;
typedef   signed char  int8;

typedef unsigned short uint16;
typedef   signed short  int16;

typedef unsigned int uint32;
typedef   signed int  int32;

typedef unsigned char ubyte;
typedef unsigned short ushort;
typedef unsigned int uint;

#ifdef _WIN32
	typedef   signed __int64  int64;
	typedef unsigned __int64 uint64;
#else
	typedef   signed long long  int64;
	typedef unsigned long long uint64;
#endif
*/

#ifdef _DEBUG
#  define DEBUG
#endif

/*- HSZK-s gépeken szedd ki!!-- */
#define SOUND

/* ---------------------------- */



void ErrorMsg(const char *string);

void WarningMsg(const char *string);

void InfoMsg(const char *string);


#endif // _PLATFORM_H_
