
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

#ifndef _INIT_H_
#define _INIT_H_

#include "Platform.h"

enum {
    IMG_1,
    IMG_2,
    IMG_3,
    IMG_4,
    IMG_5,
    IMG_6,
    IMG_7,
    IMG_8,
    IMG_SZIV,
    IMG_HALAL,
    IMG_BACK,
    IMG_GLOW,
    IMG_GLOW_OVERLAY,
    IMG_TITLE_GAME,
    IMG_TITLE_LOGO,
    IMG_LOGO,
    IMG_NUM
};

enum {
    SOUND_MUSIC,
    SOUND_SELECT,
    SOUND_SUCCES,
    SOUND_FAIL,
    NUM_SOUNDS
};

int init_system();

int init_render();

int init_cards(int type);

int init_glow();

int init_menu();

int init_font();

int load_sounds();

int load_images();

ALLEGRO_FONT *i_font;
ALLEGRO_BITMAP *i_images[IMG_NUM];
ALLEGRO_SAMPLE *i_sounds[NUM_SOUNDS];


#endif // _INIT_H_
