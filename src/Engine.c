
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

#include "Engine.h"
#include "Init.h"

/**
    * find_id : megkeres nekünk egy azonosítot
    * @param type : megadja milyen típusu kártyát keresünk.
    * @return visszatér az keresett tömbben lévő index számmal
*/
static int find_id(int type){
    int i;
        for (i = 0; i < NUM_CELLS; i++)
            if(i_cards[i].id == type) return i;

    return -1;
}

/**
    * check : megnézi volt-e pár
    * @return nincs
*/
static void check(){
    int i,j;
       for (i = 0; i < NUM_CELLS-1; i++){
            if(i_cards[i].status==FRONT){
                for (j = i+1; j < NUM_CELLS; j++){
                    if(i_cards[j].status==FRONT){
                        if(i_cards[i].id==i_cards[j].id){

                            i_cards[i].life=0;
                            i_cards[j].life=0;
#ifdef SOUND
                            al_play_sample(i_sounds[SOUND_SUCCES], 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
#endif
                            i_players[i_actual_player].score++;
                            i_found++;
                        }else{
#ifdef SOUND
                            al_play_sample(i_sounds[SOUND_FAIL], 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
#endif
                            i_actual_player=!i_actual_player;
                            change_player(i_actual_player,i_actual_player ? 900 : 0);
                        }
                    }
                }
            }
       }
}

/**
    * update_status : Frissíti a játék állapotát
    * @return nincs
*/
void update_status(){
    static float save_time;
    static int saved=0;

    if(i_front_count==2 || i_sziv || i_halal ){
        if(!saved)
        save_time=i_time;
        saved=1;
    }else saved = 0;

    if(((save_time+1)<i_time) && (saved || i_sziv || i_halal )) {
        if(i_sziv){
            i_sziv = 0;
            unselect_card(&i_cards[find_id((IMG_SZIV))]);
        }else{
            check();
            unselect_all_cards();
            i_round++;
        }

        if(i_halal){
            i_actual_player=!i_actual_player;
            change_player(i_actual_player,i_actual_player ? 900 : 0);
            i_halal = 0;
        }
    }
}

/**
    * process_extrem : extrém esetek feldolgozása
    * @param type : Bekéri a kártya típusát
    * @return nincs
*/
void process_extrem(int type){
    switch(type){
        case IMG_SZIV:
#ifdef SOUND
            al_play_sample(i_sounds[SOUND_SUCCES], 0.7, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
#endif
            i_players[i_actual_player].score++;
            i_cards[find_id((IMG_SZIV))].life = 0;
            i_sziv = 1;

            break;
        case IMG_HALAL:
#ifdef SOUND
            al_play_sample(i_sounds[SOUND_FAIL], 0.2, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
#endif
            if(i_players[i_actual_player].score != 0)
                i_players[i_actual_player].score--;

            if(i_front_count == 1)
                i_halal = 1;

            break;
    }
}

/**
    * reset : kezdő állapot
    * @param type : Bekéri a játék típusát
    * @return nincs
*/
void reset(int type){
    int i;

    i_players[0].score=0;
    i_players[1].score=0;

    i_found=0;
    i_round=0;
    i_front_count=0;

    i_actual_player = 0;

    init_cards(type);
    change_player(i_actual_player, 0);

    for (i = 0; i < NUM_CELLS; i++) {
        animation(&i_cards[i].back, &i_cards[i].back.opacity, 0.7, 2.0);
    }
}

/**
    * start_about : menü kezdő állapota
    * @return nincs
*/
void start_about(){
   i_title_game.x=1000;

   i_col = al_map_rgb(0xaf, 0xaf, 0xaf);

   animation_color(&i_title_game, i_col, 1.0);
   animation(&i_title_game, &i_title_game.x, 200, 1.0);

   i_title_logo.x=0;
   animation_color(&i_title_logo, i_col, 1.0);
   animation(&i_title_logo, &i_title_logo.x, 800, 1.0);

   animation_color(&i_logo_overlay, i_col, 1.0);
   animation(&i_logo_overlay, &i_logo_overlay.opacity,1.0, 4.0);
}

/**
    * change_player : játékost vált
    * @param type : szín tömb indexének száma
    * @param x    : hova tolja el az efektet
    * @return nincs
*/
void change_player(int type, float x){
   animation_color(&i_glow, i_glow_color[type], 1.0);
   animation(&i_glow, &i_glow.x, x, 1.0);

   animation_color(&i_glow_overlay, i_glow_color[type], 1.0);
   animation(&i_glow_overlay, &i_glow_overlay.opacity,1.0, 4.0);
}
