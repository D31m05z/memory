
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

#if defined(_WIN32)

void ErrorMsg(const char *string){
	MessageBoxA(NULL, string, "Error", MB_OK | MB_ICONERROR);
	printf("LOG: %s",string);
}

void WarningMsg(const char *string){
	MessageBoxA(NULL, string, "Warning", MB_OK | MB_ICONWARNING);
}

void InfoMsg(const char *string){
#ifdef DEBUG
	MessageBoxA(NULL, string, "Information", MB_OK | MB_ICONINFORMATION);
#endif
	printf(string);
}

#elif defined(LINUX)

/* hack, legutóbb így ment */
gboolean idle(gpointer data){
	gtk_main_quit();
	return FALSE;
}

void MessageBox(const char *string, const GtkMessageType msgType){
	GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT, msgType, GTK_BUTTONS_OK, string);
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
	g_idle_add(idle, NULL);
	gtk_main();
}

void ErrorMsg(const char *string){
	MessageBox(string, GTK_MESSAGE_ERROR);
	printf("LOG: %s",string);
}

void WarningMsg(const char *string){
	MessageBox(string, GTK_MESSAGE_WARNING);
}

void InfoMsg(const char *string){
#ifdef DEBUG
     MessageBox(string, GTK_MESSAGE_INFO);
#endif
	printf(string);
}

#elif defined(__APPLE__)

void ErrorMsg(const char *string){
	Str255 msg;
	c2pstrcpy(msg, string);

	SInt16 ret;
	StandardAlert(kAlertStopAlert, msg, NULL, NULL, &ret);
    printf("LOG: %s",string);
}

void WarningMsg(const char *string){
	Str255 msg;
	c2pstrcpy(msg, string);

	SInt16 ret;
	StandardAlert(kAlertCautionAlert, msg, NULL, NULL, &ret);
}

void InfoMsg(const char *string){
	Str255 msg;
	c2pstrcpy(msg, string);

#ifdef DEBUG
	SInt16 ret;
	StandardAlert(kAlertNoteAlert, msg, NULL, NULL, &ret);
#endif
	printf(string);
}

#endif
