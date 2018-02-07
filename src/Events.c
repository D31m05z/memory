
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

#include "Events.h"
#include "Engine.h"
#include "Init.h"

/**
    * is_touched : Vizsgálom, hogy a kártya benne van-e a kattintási területben
    * @param card  : aktuális kártya, amit vizsgálunk
    * @param size  : kártya mérete n*n-es
    * @param x  : kattintási terület
    * @param y  : kattintási terület
    * @return Visszatérése igaz/hamis állítás: igaz, ha kártyára kattintottunk
*/
static bool is_touched(Card *card, float size, float x, float y){
   float half = size/2.0;
   return (card->x - half <= x && x < card->x + half
       &&  card->y - half <= y && y < card->y + half);
}

/**
    * get_touched_card : Vizsgálom, hogy a kártyák benne vannak-e a kattintási területben
    * @param x  : kattintási terület
    * @param y  : kattintási terület
    * @return Visszatérése igaz/hamis állítás: igaz, ha kártyára kattintottunk
*/
Card *get_touched_card(float x, float y){
   int i;

   for (i = 0; i < NUM_CELLS; i++) {
      if (is_touched(&i_cards[i], i_card_size, x, y))
         return &i_cards[i];
   }

   return false;
}

/**
    * select_card : Kártya kiválasztás fv.
    * Kiválasztás csak akkor lehet, ha a kártya állapota BACK azaz lefelé van fordítva.
    * Kiválasztás esetén növelni kell a felfordított kártyák számát. [ i_front_count++; ]
    * @param card  : Kiválasztott kártya
    * @return nincs
*/
void select_card(Card *card){
   if (card->status == BACK && card->life) {
      Image *img = &card->front;
      img->image = card->id;
      animation(img, &img->opacity,0.7, 0.15);

      img = &card->back;
      animation(img, &img->scale_x, 0.4, 0.3);
      animation(img, &img->scale_y, 0.4, 0.3);
      animation(img, &img->opacity, 0.0, 0.15);

      card->status  = FRONT;

      i_front_count++;

      if (card->id == IMG_SZIV || card->id == IMG_HALAL) process_extrem(card->id);
   }
}

/**
    * unselect_card : Leveszi a kiválasztást az aktuális kártyáról, ha fel volt fordítva.
    *  Állapotát átállítja : BACK
    * Csökkenti a felfordított kártyák számát. [  i_front_count--; ]
    * @param card  : Kiválasztott kártya
    * @return nincs
*/
void unselect_card(Card *card){
   if (card->status != BACK) {
      Image *img = &card->front;
      animation(img, &img->opacity, 0.0,0.15);

      img = &card->back;
      animation(img, &img->scale_x, 1.0, 0.3);
      animation(img, &img->scale_y, 1.0, 0.3);
      if(card->life==0){
           animation(img, &img->opacity, 0.2, 0.15);
        if(i_actual_player){
            animation(img, &img->x, 900, 0.3);
            animation(img, &img->y, (100+(i_players[i_actual_player].score*10)), 0.3);
        }else{
            animation(img, &img->x, 100, 0.3);
            animation(img, &img->y, (100+(i_players[i_actual_player].score*10)), 0.3);
        }
      }
      else
        animation(img, &img->opacity, 0.7, 0.15);



      card->status = BACK;
      i_front_count--;
   }
}

/**
    * unselect_all_cards : Az összes kártyát lefordítja
    * Meghívja az unselect_card() fv.-t, ami elvégzi a lefordításokat.
    * @return nincs
*/
void unselect_all_cards(){
   int i;

   for (i = 0; i < NUM_CELLS; i++)
      unselect_card(&i_cards[i]);
}

/**
    * on_mouse_down : Egér gomb lenyomás, kártya vizsgálat...
    * @param x  : egér kattintás x helye
    * @param y  : egér kattintás y helye
    * @param mbut  : mouse button = egér kattintás ,ha volt értéke 1 lesz
    * @return nincs
*/
void on_mouse_down(float x, float y, int mbut){
   Card *card;

   if (mbut == 1) {
      if ((card = get_touched_card(x, y)))
         select_card(card);
   }
}

/**
    * on_mouse_down : Egér mozgatás. Kártya effekt...
    * @param x  : egér x poziciója
    * @param y  : egér y poziciója
    * @return nincs
*/
void on_mouse_axes(float x, float y){
  Card *card = get_touched_card(x, y);

   if (card == i_hover_card)
      return;

   if (i_hover_card && i_hover_card->life && i_hover_card->status==BACK) {
      Image *img = &i_hover_card->back;
      animation(img, &img->opacity, 0.7, 0.2);

      img = &i_hover_card->back;
      animation(img, &img->scale_x, 1.0, 0.3);
      animation(img, &img->scale_y, 1.0, 0.3);
   }

   i_hover_card = card;

   if (i_hover_card && i_hover_card->life && i_hover_card->status==BACK) {
      Image *img = &i_hover_card->back;
      animation(img, &img->opacity, 1.0, 0.2);

      img = &card->back;
      animation(img, &img->scale_x, 1.1, 0.3);
      animation(img, &img->scale_y, 1.1, 0.3);
#ifdef SOUND
      al_play_sample(i_sounds[SOUND_SELECT], 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
#endif

   }
}
