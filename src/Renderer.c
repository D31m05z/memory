
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
    * draw_image : kirajzol egy kártya oldalt
    * @param img : kirajzoldandó kép
    * @return nincs
*/
static void draw_image(const Image *img){
   ALLEGRO_BITMAP *bmp;
   ALLEGRO_COLOR tint;
   float cx, cy;

   bmp = i_images[img->image];
   cx = img->align_x * al_get_bitmap_width(bmp);
   cy = img->align_y * al_get_bitmap_height(bmp);
   tint = al_map_rgba_f(img->r, img->g, img->b, img->opacity);

   al_draw_tinted_scaled_rotated_bitmap(bmp, tint, cx, cy,
      img->x, img->y, img->scale_x, img->scale_y, img->angle, 0);

}

/**
    * draw_card : kirajzol egy kártyát
    * @param card : kirajzoldandó kártya
    * @return nincs
*/
static void draw_card(const Card *card){
   draw_image(&card->back);
   draw_image(&card->front);
}

/**
    * draw_menu : kirajzolja a menüt
    * @return nincs
*/
void draw_menu(){
   al_clear_to_color(al_map_rgb(0, 0, 0));

   al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_ONE);

   draw_image(&i_title_game);
   draw_image(&i_title_logo);
   draw_image(&i_logo_overlay);

   al_draw_textf(i_font, al_map_rgb(0xad, 0xd8, 0xe6), 100, 250, 0, "<ENTER> - START");
   al_draw_textf(i_font, al_map_rgb(0xad, 0xd8, 0xe6), 100, 300, 0, "<M>     - jatek mod : %s",i_game_type ? "EXTREM" : "NORMAL");
   al_draw_textf(i_font, al_map_rgb(0xad, 0xd8, 0xe6), 100, 350, 0, "<ESC>   - EXIT");

   al_flip_display();
}

/**
    * draw_screen : kirajzolja a pályát
    * @return nincs
*/
void draw_screen(){
   int i;

   al_clear_to_color(al_map_rgb(0, 0, 0));

   al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_ONE);

   draw_image(&i_glow);
   draw_image(&i_glow_overlay);

   for (i = 0; i < NUM_CELLS; i++)
      draw_card(&i_cards[i]);


    al_draw_textf(i_font, al_map_rgb(0xad, 0xd8, 0xe6), 2, 2, 0, "%s",i_players[0].name);
    al_draw_textf(i_font, al_map_rgb(0xad, 0xd8, 0xe6), 10, 50, 0, "%d",i_players[0].score);

    al_draw_textf(i_font, al_map_rgb(0xff, 0x00, 0x00), 800, 2, 0, "%s",i_players[1].name);
    al_draw_textf(i_font, al_map_rgb(0xff, 0x00, 0x00), 850, 50, 0, "%d",i_players[1].score);
    al_draw_textf(i_font, al_map_rgb(0x41, 0x69, 0xe1), 10, 550, 0, "round:%d",i_round);

#ifdef DEBUG
    al_draw_textf(i_font, al_map_rgb(0x41, 0x69, 0xe1), 270,550, 0, " f:%d h:%d s:%d a:%d",i_front_count,i_halal,i_sziv,i_actual_player);
#endif


    if(i_found== (i_game_type? 7: 8)){
        if(i_players[0].score>i_players[1].score)
             al_draw_textf(i_font, al_map_rgb(0xad, 0xd8, 0xe6), i_width/2-100, i_height/2, 0, "Nyert: %s !",i_players[0].name);
        else if(i_players[0].score<i_players[1].score)
             al_draw_textf(i_font, al_map_rgb(0xad, 0xd8, 0xe6), i_width/2-100, i_height/2, 0, "Nyert: %s !",i_players[1].name);
        else al_draw_textf(i_font, al_map_rgb(0xad, 0xd8, 0xe6), i_width/2-100, i_height/2, 0, "Dontetlen!");

        al_draw_textf(i_font, al_map_rgb(0xad, 0xd8, 0xe6), i_width/2-100, i_height/2+50, 0, "Kilepes : <ESC>");
        al_draw_textf(i_font, al_map_rgb(0xad, 0xd8, 0xe6), i_width/2-100, i_height/2+100, 0, "Uj jatek : <N>");
    }
   al_flip_display();
}
