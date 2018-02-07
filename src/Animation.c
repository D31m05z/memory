
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

#include "Platform.h"
#include "Engine.h"

/**
    * next_animation : következő animációra lépés
    * @param img : Az animálni kívánt kép
    * @return következő animció, amit végre kell hajtani
*/
static Anim *next_animation(Image *img){
   unsigned i;

   for (i = 0; i < MAX_ANIMS; i++) {
      if (img->anims[i].value == NULL)
         return &img->anims[i];
   }
   return NULL;
}

/**
    * null_all_animations : kinullázza az animációban található értéket!
    * Ez jelzi, hogy még nem volt , és még szerepelnie kell!
    * @param img  : nullázni kívánt kép, ami tartalmazza a hozzá kapcsolódó animációkat
    * @param value : érték
    * @param s_time : kezdeti idő
    * @param s_value : kezdő érték
    * @return nincs
*/
static void null_all_animations(Image *img, float *value, float s_time,float s_value){
   unsigned i;

   for (i = 0; i < MAX_ANIMS; i++) {
      Anim *anim = &img->anims[i];

      if (anim->value != value)
         continue;

      if (anim->e_time > s_time) {
         anim->e_time = s_time;
         anim->e_value = s_value;
      }

      if (anim->s_time >= s_time ||
         anim->s_time >= anim->e_time)
      {
         img->anims[i].value = NULL;
      }
   }
}

/**
    * animation : animáció kezelő fv.
    * Itt történik meg az animáció kezdetbeni kinullázása, hogy tudjuk, még nem szerepelt.
    * Itt történik a képhez tartozó animációk feldolgozása
    * @param img  : nullázni kívánt kép, ami tartalmazza a hozzá kapcsolódó animációkat
    * @param value : érték
    * @param e_value : végső érték, amibe megyünk
    * @param duration : mennyi idő alatt történjen meg az animáció
    * @return nincs
*/
void animation(Image *img, float *value, float e_value, float duration){
   float s_time = al_get_time() ;
   Anim *anim;


   null_all_animations(img, value, s_time, *value);

   anim = next_animation(img);
   anim->value = value;
   anim->s_value = *value;
   anim->e_value = e_value;
   anim->s_time = s_time;
   anim->e_time = s_time + duration;
}
/**
    * animation_color : szinek animálásáért felelős fv.
    * @param img  : animálni kívánt kép
    * @param color : milyen színbe akarunk menni
    * @param duration : mennyi idő alatt történjen meg az animáció
    * @return nincs
*/
void animation_color(Image *img, const ALLEGRO_COLOR color, float duration){
   float r, g, b;

   al_unmap_rgb_f(color, &r, &g, &b);

   animation(img, &img->r, r,duration);
   animation(img, &img->g, g,duration);
   animation(img, &img->b, b,duration);
}

/**
    * update_anim : animációk fő feldolgozása, frissítése, lejátszása
    * @param anim  : aktuális animáció, amit épp feldolgozunk/lejátszunk
    * @param now : aktuális idő, kell hogy meg tudjuk állapítani mennyi idő telt el!
    * @return nincs
*/
static void update_anim(Anim *anim, float now){
   float dt, t, range;

   if (!anim->value)
      return;

   if (now < anim->s_time)
      return;

   dt = now - anim->s_time;
   t = dt / (anim->e_time - anim->s_time);

   if (t >= 1.0) {
      *anim->value = anim->e_value;
      anim->value = NULL;
      return;
   }

   range = anim->e_value - anim->s_value;
   *anim->value = anim->s_value + -t*(t-2) * range;
}

/**
    * update_image_anims : képekhez tartozó animációk feldolgozása
    * @param img  : aktuális animáció, amit épp elküldünk feldolgozni/lejátszani
    * @param now : aktuális idő, kell hogy meg tudjuk állapítani mennyi idő telt el!
    * @return nincs
*/
static void update_image_anims(Image *img, float now){
   int i;

   for (i = 0; i < MAX_ANIMS; i++)
      update_anim(&img->anims[i], now);
}

/**
    * update_card_anims : kép-párok-hoz tartozó animációk, kártya eleje/hátúlja
    * kártya felfordítása/lefordítása, pár találása , kártyák kijelölése animációk
    * @param card  : aktuális animáció, amit épp elküldünk feldolgozni/lejátszani
    * @param now : aktuális idő, kell hogy meg tudjuk állapítani mennyi idő telt el!
    * @return nincs
*/
static void update_card_anims(Card *card, float now){
   update_image_anims(&card->back, now);
   update_image_anims(&card->front, now);
}

/**
    * animation_updates : Fő animációs ciklus beindító fv.
    * Itt adjuk meg az animációk frissítéseit, és átadjuk az aktuális időt.
    * main_loop fv. hívja meg a rajzolás előtt!
    * @param now : aktuális idő, kell hogy meg tudjuk állapítani mennyi idő telt el!
    * @return nincs
*/
void animation_updates(float now){
   int i;

/* --- cards --- */

   for (i = 0; i < NUM_CELLS; i++)
      update_card_anims(&i_cards[i], now);

/* --- game --- */

   update_image_anims(&i_glow, now);
   update_image_anims(&i_glow_overlay, now);

/* --- menu --- */

   update_image_anims(&i_title_game,now);
   update_image_anims(&i_title_logo,now);
   update_image_anims(&i_logo_overlay,now);
}
