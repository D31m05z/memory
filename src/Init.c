
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

#include "Init.h"
#include "Engine.h"

/**
    * init_system : inicializálja a paramétereket
    * a gtk-t linux esetén
    * a hangot és a font bitmap-et
    * @return hibajelzés - 0: succes 1: fail
*/
int init_system(){
    srand(time(0));

    i_hover_card=NULL;
    i_actual_player=0;
    i_time=0;
    i_front_count=0;
    i_round=0;
    i_found=0;
    i_game_type = NORMAL;
    i_sziv = 0;
    i_halal = 0;

    i_width = 1024;
    i_height = 600;
    i_card_size = 128;
    i_refresh_rate = 60.0;




  if (!al_init()) {
       printf("error: init_allegro\n");
       return 1;
   }

#ifdef LINUX
   /* ez csak akkor működik ha az allegro inicializálás után tesszük be!
      linux esetén */
   gtk_init(NULL, NULL);
#endif

InfoMsg("PASS: ALLEGRO_INIT\n");

#ifdef SOUND
   if (!al_install_audio() || !al_reserve_samples(128)) {
      ErrorMsg("error: init_audio\n");
      return 1;
   }
InfoMsg("PASS: AUDIO_INIT\n");
#endif

InfoMsg("INIT: al_init_acodec_addon\n");
   al_init_acodec_addon();
InfoMsg("INIT: al_init_image_addon\n");
   al_init_image_addon();
InfoMsg("INIT: al_init_font_addon\n");
   al_init_font_addon();


    return 0;
}

/**
    * init_render : inicializálja a grafikus felületet
    * @return hibajelzés - 0: succes 1: fail
*/
int init_render(){
   i_display = al_create_display(i_width, i_height);
   if (!i_display) {
      ErrorMsg("error: create_display\n");
      return 1;
   }
   al_set_window_title(i_display, "BME-VIK MI 2011_11_5 : 1.NHF [MEMORY - V.0.5]");

    return 0;
}

/**
    * load_images : betölti a képeket
    * @return hibajelzés - 0: succes 1: fail
*/
int load_images(){
    int i;

    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    i_images[IMG_1]            = al_load_bitmap(GAME_PATH "images/00.jpg");
    i_images[IMG_2]            = al_load_bitmap(GAME_PATH "images/01.jpg");
    i_images[IMG_3]            = al_load_bitmap(GAME_PATH "images/02.jpg");
    i_images[IMG_4]            = al_load_bitmap(GAME_PATH "images/03.jpg");
    i_images[IMG_5]            = al_load_bitmap(GAME_PATH "images/04.jpg");
    i_images[IMG_6]            = al_load_bitmap(GAME_PATH "images/05.jpg");
    i_images[IMG_7]            = al_load_bitmap(GAME_PATH "images/06.jpg");
    i_images[IMG_8]            = al_load_bitmap(GAME_PATH "images/07.jpg");
    i_images[IMG_SZIV]         = al_load_bitmap(GAME_PATH "images/sziv.jpg");
    i_images[IMG_HALAL]        = al_load_bitmap(GAME_PATH "images/halal.jpg");

    i_images[IMG_BACK]         = al_load_bitmap(GAME_PATH "images/back.jpg");
    i_images[IMG_GLOW]         = al_load_bitmap(GAME_PATH "effects/glow.png");
    i_images[IMG_GLOW_OVERLAY] = al_load_bitmap(GAME_PATH "effects/background.png");

    i_images[IMG_TITLE_GAME]   = al_load_bitmap(GAME_PATH "logo/title_game.png");
    i_images[IMG_TITLE_LOGO]   = al_load_bitmap(GAME_PATH "logo/title_logo.png");
    i_images[IMG_LOGO]         = al_load_bitmap(GAME_PATH "logo/logo.png");

    for (i = 0; i < IMG_NUM; i++) {
      if (i_images[i] == NULL){
        char _ERROR_[128];
		sprintf(_ERROR_, "error: loading image - id:%d\n",i);
        ErrorMsg(_ERROR_);
      return 1;
      }
    }
    return 0;
}

/**
    * load_sounds : betölti a hangokat
    * @return hibajelzés - 0: succes 1: fail
*/
int load_sounds(){
   int i;

   i_sounds[SOUND_MUSIC]        = al_load_sample(GAME_PATH "sounds/music.ogg");
   i_sounds[SOUND_SELECT]       = al_load_sample(GAME_PATH "sounds/select.ogg");
   i_sounds[SOUND_SUCCES]       = al_load_sample(GAME_PATH "sounds/succes.wav");
   i_sounds[SOUND_FAIL]         = al_load_sample(GAME_PATH "sounds/fail.wav");

   for (i = 0; i < NUM_SOUNDS; i++) {
      if (i_sounds[i] == NULL){
           char _ERROR_[128];
            sprintf(_ERROR_, "error: loading sound - id:%d\n",i);
            ErrorMsg(_ERROR_);
          return 1;
      }
   }

   al_play_sample(i_sounds[SOUND_MUSIC], 1.0, 0.0, 1.0,ALLEGRO_PLAYMODE_LOOP, NULL);
   return 0;
}

/**
    * init_glow : inicializálja a glow efektet
    * @return hibajelzés - 0: succes 1: fail
*/
int init_glow(){
   init_images(&i_glow, IMG_GLOW, i_width, i_height, 1.0, 1.0);
   i_glow.align_y = 1.8;
   i_glow.r = i_glow.g = i_glow.b = 0.0;

   init_images(&i_glow_overlay, IMG_GLOW_OVERLAY, 0.0, 0.0, 1.0, 1.0);
   i_glow_overlay.align_x = 0.0;
   i_glow_overlay.align_y = 0.0;
   i_glow_overlay.r = i_glow_overlay.g = i_glow_overlay.b = 0.0;

   i_glow_color[PLAYER_1] = al_map_rgb(0xad, 0xad, 0xad); /* 0xad, 0xd8, 0x00 */
   i_glow_color[PLAYER_2]  = al_map_rgb(0xff, 0x00, 0x00);

   return 0;
}

/**
    * init_menu : inicializálja a menüt és a logot
    * @return hibajelzés - 0: succes 1: fail
*/
int init_menu(){
   init_images(&i_title_game, IMG_TITLE_GAME, i_width, i_height, 1.0, 1.0);
   i_title_game.align_y = 1.6;
   i_title_game.x=1000;
   i_title_game.r = i_title_game.g = i_title_game.b = 0.0;

   init_images(&i_title_logo, IMG_TITLE_LOGO, i_width, i_height, 1.0, 1.0);
   i_title_logo.align_y = 0.9;
   i_title_logo.x=0;
   i_title_logo.r = i_title_logo.g = i_title_logo.b = 0.0;


   init_images(&i_logo_overlay, IMG_LOGO, 0.0, 0.0, 1.0, 1.0);
   i_logo_overlay.align_x = 0.0;
   i_logo_overlay.align_y = 0.0;
   i_logo_overlay.r = i_logo_overlay.g = i_logo_overlay.b = 0.0;

    return 0;
}

/**
    * init_font : inicializálja a font-ot
    * @return hibajelzés - 0: succes 1: fail
*/
int init_font(){
   i_font = al_load_font(GAME_PATH "fonts/bmpfont.tga", 0, 0);
   if (!i_font) {
        ErrorMsg("error: loading 'fonts/bmpfont.tga'\n");
        return 1;
    }

    return 0;
}

/**
    * init_images   : inicializálja a képeket
    * @param img    : képre mutató pointer
    * @param image  : betöltendő  kép ID
    * @param x      : X-tengelyen lévő poziciója
    * @param y      : X-tengelyen lévő pozitiója
    * @param scale  : mérete
    * @param opacity: átlátszóság  1.0f a teljesen telített
    * @return hibajelzés - 0: succes 1: fail
*/
int init_images(Image *img, int image, float x, float y, float scale, float opacity){
   int i;

   img->image = image;
   img->x = x;
   img->y = y;
   img->scale_x = img->scale_y = scale;
   img->align_x = img->align_y = 0.5;
   img->angle = 0.0;
   img->r = img->g = img->b = 1.0;
   img->opacity = opacity;

   for (i = 0; i < MAX_ANIMS; i++)
      img->anims[i].value = NULL;

      return 0;
}

/**
    * switch_img_type : kicserél egy kártyatípust
    * @param type    : milyen típusra cseréljük a 4. indexű típust
    * @return nincs
*/
static void switch_img_type(int type){
    int i;
     for (i = 0; i < NUM_CELLS; i++)
            if(i_cards[i].id == 4){
                i_cards[i].id=type;
                break;
            }
}

/**
    * init_cards : kártyák inicializálása
    * @param type  : milyen a játék típusa : NORAML / EXTREM
    * @return hibajelzés - 0: succes 1: fail
*/
int init_cards(int type){
   const float card_w = i_card_size ;
   const float card_x = 250 + card_w/2.0;
   const float card_y = 80;

   int i,j;
   int offsetX = 0;
   int offsetY = 0;

   int akt;
   int exist=1;
   int ids[16];


InfoMsg("CREATING: CARDs\n");
   for (i = 0; i < NUM_CELLS; i++) {
      int tx = i % CELL_X;
      int ty = i / CELL_X;
      float px = card_x + tx * card_w;
      float py = card_y + ty * card_w;

      i_cards[i].status = BACK;
      i_cards[i].x = px+offsetX*10;
      i_cards[i].y = py+offsetY*10;
      i_cards[i].life = 1;


      init_images(&i_cards[i].back, IMG_BACK, px+offsetX*10, py+offsetY*10, 1.0, 0.0);
      init_images(&i_cards[i].front, IMG_BACK, px+offsetX*10, py+offsetY*10, 1.0, 0.0);

          offsetX++;
          if(!((i+1)%4)){
              offsetX=0;
              offsetY++;
          }
   }

for(i=0;i<16;i++)ids[i]=-1;

InfoMsg("GENEARTING: RANDOM_IDs\n");
    for(i=0;i<16;i++){
        exist=1;
        while(exist){
         akt=ids[i]=(rand()%16);
         exist=0;
         for(j=0;j<i;j++){
#ifdef DEBUG
             printf("%d %d\n",akt,ids[j]);
#endif
         if(akt==ids[j])exist=1;
         }
        }
    }

#ifdef DEBUG
        printf("\n\n");
#endif

    for(i=0;i<16;i++){
#ifdef DEBUG
        printf("%d ",ids[i]);
#endif
        if(ids[i]>7)ids[i]-=8;
    }



   for (i = 0; i < NUM_CELLS; i++)
       i_cards[i].id=ids[i];


#ifdef DEBUG
    printf("\n----------\n");
    for(i=0;i<16;i++){
        printf("%d ",i_cards[i].id);
        if(!((i+1)%4)) printf("\n");
    }
    printf("\n\n");
#endif


   if(type){
      switch_img_type(IMG_SZIV);   /* 8 */
      switch_img_type(IMG_HALAL);  /* 9 */


#ifdef DEBUG
    printf("\n----------\n");
    for(i=0;i<16;i++){
        printf("%d ",i_cards[i].id);
        if(!((i+1)%4)) printf("\n");
    }
    printf("\n\n");
#endif

   }

    return 0;
}

