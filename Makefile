
#/** * * * BME-VIK-MI_2011_10_17 * * *|1.NHF|* * * * * * * * * *\
#*    _ _____   _____        __ _                              *
#*   (_)  __ \ / ____|      / _| |                             *
#*   |_| |__)| (___    ___ | |_| |___      ____ _ _ __ ___     *
#*   | |  _  / \___ \ / _ \|  _| __\ \ /\ / / _` | '__/ _ \    *
#*   | | | \ \ ____) | (_) | | | |_ \ V  V / (_| | | |  __/    *
#*   |_|_|  \_\_____/ \___/|_|  \__| \_/\_/ \__,_|_|  \___|    *
#*                                                             *
#*                   http://irsoftware.co.cc                   *
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

CC = gcc -Wall -ansi -DLINUX -mmmx `pkg-config --cflags --libs gtk+-2.0 allegro-5`
RELEASE = -O2 -ffast-math
DEBUG = -g -D_DEBUG

FW_PATH  = src
APP_NAME = memory

FW_ANIM = $(FW_PATH)/Animation.c
FW_APP = $(FW_PATH)/Engine.c $(FW_PATH)/Init.c $(FW_PATH)/Renderer.c
FW_PLATFORM = $(FW_PATH)/Platform.c $(FW_PATH)/Events.c
FW = $(FW_ANIM) $(FW_APP) $(FW_PLATFORM)
APP = $(FW_PATH)/main.c

LIB_SYSTEM = -lallegro -lallegro_main -lallegro_dialog
LIB_GRAPHICS = -lallegro_image -lallegro_color -lallegro_primitives
LIB_AUDIO =  -lallegro_audio -lallegro_acodec
LIB_FONT = -lallegro_font 
LIBS = $(LIB_SYSTEM) $(LIB_GRAPHICS) $(LIB_AUDIO) $(LIB_FONT)

rel: $(APP) $(FW)
	$(CC) $(RELEASE) $(APP) $(FW) -o $(APP_NAME) $(LIBS)
dbg: $(APP) $(FW)
	$(CC) $(DEBUG) $(APP) $(FW) -o $(APP_NAME) $(LIBS)

clean:
	@rm $(APP_NAME)
