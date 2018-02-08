
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

#include "Platform.h"
#include "Init.h"
#include "Events.h"
#include "Init.h"
#include "Engine.h"


/**
    * main_loop : Egér mozgatás. Kártya effekt...
    * @param queue  : Az allegro eseménykezelő pointere
    * @return nincs
*/
static void main_loop(ALLEGRO_EVENT_QUEUE *queue) {
    ALLEGRO_EVENT event;

    bool redraw = true;
    bool done = false;

    for (;;) {

        if (redraw) {
            i_time = al_get_time();
            animation_updates(i_time);

            if (i_game_status == GAME) {
                draw_screen();
                update_status();
            } else if (i_game_status == MENU) {
                draw_menu();
            }
            redraw = false;
        }

        al_wait_for_event(queue, &event);

        if (event.timer.source == i_refresh_timer) {
            redraw = true;
            continue;
        }

        switch (event.type) {
            case ALLEGRO_EVENT_MOUSE_AXES:
                if (i_game_status == GAME)on_mouse_axes(event.mouse.x, event.mouse.y);
                continue;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (i_front_count < 2 && i_game_status == GAME && !i_halal && !i_sziv)
                    on_mouse_down(event.mouse.x, event.mouse.y, event.mouse.button);
                continue;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    if (i_game_status == GAME) {
                        i_game_status = MENU;
                        start_about();
                    } else if (i_game_status == MENU)
                        done = true;
                    break;
                } else if (event.keyboard.keycode == ALLEGRO_KEY_N) {
                    if (i_found == (i_game_type ? 7 : 8))
                        reset(i_game_type);
                } else if (event.keyboard.keycode == ALLEGRO_KEY_M) {
                    if (i_game_status == MENU) i_game_type = !i_game_type;
                } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    if (i_game_status == MENU) {
                        i_game_status = GAME;
                        reset(i_game_type);
                    }
                }
        }
        if (done)break;
    }
}


/**
    * main : Belépési pont
    * @param argc  : Paraméterek száma
    * @param argv  : Paramétereket tartalamzó karaktertömb pointerek
    * @return nincs
*/
int main(int argc, char *argv[]) {

    i_game_status = MENU;

    printf("--------BME-VIK MI 2011_11_5 : 1.NHF [MEMORY - V.0.5]--------\n");
    printf("START GAME\n");


    if ((init_system()) == FAIL) {
        ErrorMsg("error: init_system\n");
        exit(-1);
    }
    InfoMsg("PASS: SYSTEM_INIT\n");

    if ((init_render()) == FAIL) {
        ErrorMsg("error: init_render\n");
        exit(-1);
    }
    InfoMsg("PASS: RENDER_INIT\n");

    if ((load_images()) == FAIL) {
        ErrorMsg("error: load_images\n");
        exit(-1);
    }
    InfoMsg("PASS: IMAGES_LOAD\n");

#ifdef SOUND
    if ((load_sounds()) == FAIL) {
        ErrorMsg("error: load_sounds\n");
        exit(-1);
    }
    InfoMsg("PASS: SOUNDS_LOAD\n");
#endif

    if ((init_glow()) == FAIL) {
        ErrorMsg("error: init_glow\n");
        exit(-1);
    }

    if ((init_menu()) == FAIL) {
        ErrorMsg("error: init_menu\n");
        exit(-1);
    }

    if ((init_font()) == FAIL) {
        ErrorMsg("error: init_font\n");
        exit(-1);
    }
    InfoMsg("PASS: FONT_INIT\n");

    if (argc > 2) {
        i_players[0].name = argv[1];
        i_players[1].name = argv[2];
    } else {
        i_players[0].name = "Player1";
        i_players[1].name = "Player2";
    }

    start_about();

    al_install_keyboard();
    al_install_mouse();

    i_refresh_timer = al_create_timer(1.0 / i_refresh_rate);

    i_queue = al_create_event_queue();
    al_register_event_source(i_queue, al_get_display_event_source(i_display));
    al_register_event_source(i_queue, al_get_keyboard_event_source());
    al_register_event_source(i_queue, al_get_mouse_event_source());
    al_register_event_source(i_queue, al_get_timer_event_source(i_refresh_timer));

    al_start_timer(i_refresh_timer);

    InfoMsg("-------------------------------------------------------------\n");
    main_loop(i_queue);

    InfoMsg("DESTROY\n");
    al_destroy_font(i_font);
    InfoMsg("exiting...\n");

    return 0;
}
