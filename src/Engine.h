
/** * * * BME-VIK-MI_2011_10_17 * * *|1.NHF|* * * * * * * * * *\
*    _ _____   _____        __ _                              *
*   (_)  __ \ / ____|      / _| |                             *
*   |_| |__)| (___    ___ | |_| |___      ____ _ _ __ ___     *
*   | |  _  / \___ \ / _ \|  _| __\ \ /\ / / _` | '__/ _ \    *
*   | | | \ \ ____) | (_) | | | |_ \ V  V / (_| | | |  __/    *
*   |_|_|  \_\_____/ \___/|_|  \__| \_/\_/ \__,_|_|  \___|    *
*                                                             *
*                   http://irsoftware.co.cc                   *
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

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Platform.h"
#include <stdio.h>

typedef struct Player Player;
typedef struct Anim Anim;
typedef struct Card Card;
typedef struct Image Image;

/* játék típusa */
enum {
    NORMAL,
    EXTREM
};

/* Játék állapota */
enum {
  MENU,
  GAME,
  EXIT
};

/* Kártyák állapota */
enum  {
    BACK,           /* Le van fordítva, azaz a hátulját látjuk */
    FRONT           /* Fel van fordítva */
};

/* Játékosok [ ez a későbiekben fontos, ha akarunk 3 játékos üzemmódot írni hozzá! ] */
enum {
   PLAYER_1,
   PLAYER_2,
   NUM_PLAYERS
};

struct Player {
    int score;      /* elért pontok a játék során */
    char *name;     /* játékos neve */
};

/* Pálya 4x4-es */
enum {
   CELL_X    = 4,
   CELL_Y    = 4,
   NUM_CELLS  = CELL_X * CELL_Y
};

/* ///////////////////////////////////////////////// */

struct Anim {
   float       *value;
   float       s_value;      /* start value */
   float       e_value;      /* end value */
   float       s_time;       /* start time */
   float       e_time;       /* end time */
};

struct Image {
   unsigned    image;
   float       x, scale_x, align_x;
   float       y, scale_y, align_y;
   float       angle;
   float       r, g, b;
   float       opacity;
   Anim        anims[MAX_ANIMS];
};
/* ///////////////////////////////////////////////// */

/*  Kártya */
struct Card {
   unsigned    status;      /* A kártya helyzete BACK vagy FRONT */
   float       x;           /* A kártya helye */
   float       y;
   Image       back;         /* kártya hátulja   : textúra */
   Image       front;        /* kártya eleje : textúra */
   unsigned    id;          /* kártya azonosító id: 0-7 ig 8 db kártya van a játékban */
   unsigned    life;        /* kártya élete, azaz hogy megtalálták-e már a párját avagy sem */
};

/* ----Scene--------------------- */
Card           *i_hover_card;
Card           i_cards[NUM_CELLS];   /* kártyák */
/* ------------------------------ */

/* ----Effects------------------- */
Image          i_glow;
Image          i_glow_overlay;
ALLEGRO_COLOR  i_glow_color[NUM_PLAYERS];
ALLEGRO_COLOR  i_col;							/* szinek a menuhoz*/

Image          i_title_game;
Image          i_title_logo;
Image          i_logo_overlay;
/* ------------------------------ */

/* ----Player-------------------- */
Player          i_players[NUM_PLAYERS];     /* játékosok */
int             i_actual_player;            /* aktuális játékos : jelen esetben vagy 0 vagy 1 */
/* ------------------------------ */

/* ----Game---------------------- */
float           i_time;                     /* eltelt idő */
int             i_front_count;              /* hány kártya van felfordítva, ha kettő akkor már megnéztünk egy párt */
int             i_round;                    /* hány kör ment le */
int             i_found;                    /* hány pár ment ki már */
int             i_game_status;              /* játék állapota */
int             i_game_type;                /* játék típusa */
int             i_sziv;                     /* szivet találtunk */
int             i_halal;                    /* halál mezőre léptünk */
/* ------------------------------ */

/* ----Display------------------- */
int             i_width;                    /* ablak szélessége */
int             i_height;                   /* ablak magassága */
float           i_card_size;                /* kártya mérete */
float           i_refresh_rate;             /* ablak frissítése FPS-ben : Frame per Sec */

ALLEGRO_EVENT_QUEUE *i_queue;
ALLEGRO_DISPLAY		*i_display;             /* ablak */
ALLEGRO_TIMER		*i_refresh_timer;       /* frissítési időzitő */
/* ------------------------------ */


/* /////ANIMATION////////////////// */
void animation(Image *img, float *value, float e_value, float duration);
void animation_color(Image *img, const ALLEGRO_COLOR color, float duration);
void animation_updates(float now);

int init_images(Image *img, int image, float x, float y, float scale, float opacity);
void unselect_card(Card *card);
/* //////////////////////////////// */

/* /////GAME/////////////////////// */
void update_status(void);
void reset(int type);
void start_about();
void change_player(int type, float x);
void process_extrem(int type);
/* //////////////////////////////// */

/* /////SCENEs///////////////////// */
Card *get_touched_card(float x, float y);
void select_card(Card *card);
void draw_screen();
void draw_menu();
/* //////////////////////////////// */



#endif // _ENGINE_H_
