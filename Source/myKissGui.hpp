#pragma once

#ifndef MYKISSGUI_H
#define MYKISSGUI_H

#ifndef RESDIR
#define RESDIR ""
#endif

#if defined(_MSC_VER)
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#elif defined(__APPLE__)
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#endif
#include <sys/types.h>
#ifdef _MSC_VER
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#include <dirent.h>
#endif
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

#include "midiModule.h"

#define KISS_MAX_LENGTH 200
#define KISS_MIN_LENGTH 10
#define KISS_MAX_LABEL 500
#define KISS_MAGIC 12345

enum {
	OTHER_TYPE, WINDOW_TYPE, RENDERER_TYPE, TEXTURE_TYPE, SURFACE_TYPE,
	FONT_TYPE, STRING_TYPE, ARRAY_TYPE
};

#ifdef _MSC_VER
#ifdef _WIN32
typedef struct _stat32 kiss_stat;
#else
typedef struct _stat64 kiss_stat;
#endif

typedef struct kiss_dirent {
	char* d_name;
} kiss_dirent;

typedef struct kiss_dir {
	ptrdiff_t fhandle;
	struct _finddata_t fdata;
	kiss_dirent ent;
	char name[KISS_MAX_LENGTH];
} kiss_dir;
#else
typedef struct stat kiss_stat;
typedef struct dirent kiss_dirent;
typedef DIR kiss_dir;
#endif

/* Length is number of elements, size is allocated size */
typedef struct kiss_array {
	void** data;
	int* id;
	int length;
	int size;
	int ref;
} kiss_array;

typedef struct kiss_image {
	SDL_Texture* image;
	int magic;
	int w;
	int h;
} kiss_image;

typedef struct kiss_font {
	TTF_Font* font;
	int magic;
	int fontheight;
	int spacing;
	int lineheight;
	int advance;
	int ascent;
} kiss_font;

typedef struct kiss_window {
	int visible;
	int focus;
	SDL_Rect rect;
	int decorate;
	SDL_Color bg;
	struct kiss_window* wdw;
} kiss_window;

typedef struct kiss_label {
	int visible;
	SDL_Rect rect;
	char text[KISS_MAX_LABEL];
	SDL_Color textcolor;
	kiss_font font;
	kiss_window* wdw;
} kiss_label;

typedef struct kiss_button {
	int visible;
	int focus;
	SDL_Rect rect;
	int textx;
	int texty;
	char text[KISS_MAX_LENGTH];
	int active;
	int prelight;
	SDL_Color textcolor;
	kiss_font font;
	kiss_image normalimg;
	kiss_image activeimg;
	kiss_image prelightimg;
	kiss_window* wdw;
} kiss_button;

typedef struct kiss_upbutton {
	int visible;
	int focus;
	SDL_Rect rect;
	int active;
	int prelight;
	kiss_image normalimg;
	kiss_image activeimg;
	kiss_image prelightimg;
	kiss_window* wdw;
}kiss_upbutton;

typedef struct kiss_downbutton {
	int visible;
	int focus;
	SDL_Rect rect;
	int active;
	int prelight;
	kiss_image normalimg;
	kiss_image activeimg;
	kiss_image prelightimg;
	kiss_window* wdw;
}kiss_downbutton;

typedef struct kiss_tab {
	int visible;
	int focus;
	SDL_Rect rect;
	int textx;
	int texty;
	char text[KISS_MAX_LENGTH];
	int active;
	int prelight;
	SDL_Color textcolor;
	kiss_font font;
	kiss_image normalimg;
	kiss_image selectedimg;
	kiss_image hoverimg;
	kiss_window* wdw;
} kiss_tab;

typedef struct kiss_selectbutton {
	int visible;
	int focus;
	SDL_Rect rect;
	int selected;
	kiss_image selectedimg;
	kiss_image unselectedimg;
	kiss_window* wdw;
} kiss_selectbutton;



typedef struct kiss_vscrollbar {
	int visible;
	int focus;
	SDL_Rect uprect;
	SDL_Rect downrect;
	SDL_Rect sliderrect;
	int maxpos;
	double fraction;
	double step;
	unsigned int lasttick;
	int downclicked;
	int upclicked;
	int sliderclicked;
	kiss_image up;
	kiss_image down;
	kiss_image vslider;
	kiss_window* wdw;
} kiss_vscrollbar;

typedef struct kiss_hscrollbar {
	int visible;
	int focus;
	SDL_Rect leftrect;
	SDL_Rect rightrect;
	SDL_Rect sliderrect;
	int maxpos;
	double fraction;
	double step;
	unsigned int lasttick;
	int leftclicked;
	int rightclicked;
	int sliderclicked;
	kiss_image left;
	kiss_image right;
	kiss_image hslider;
	kiss_window* wdw;
} kiss_hscrollbar;

typedef struct kiss_progressbar {
	int visible;
	SDL_Rect rect;
	SDL_Rect barrect;
	int width;
	double fraction;
	double step;
	SDL_Color bg;
	unsigned int lasttick;
	int run;
	kiss_image bar;
	kiss_window* wdw;
} kiss_progressbar;

typedef struct kiss_entry {
	int visible;
	int focus;
	SDL_Rect rect;
	int decorate;
	int textx;
	int texty;
	char text[KISS_MAX_LENGTH];
	int active;
	int textwidth;
	int selection[4];
	int cursor[2];
	SDL_Color normalcolor;
	SDL_Color activecolor;
	SDL_Color bg;
	kiss_font font;
	kiss_window* wdw;
} kiss_entry;

typedef struct kiss_textbox {
	int visible;
	int focus;
	SDL_Rect rect;
	int decorate;
	kiss_array* array;
	SDL_Rect textrect;
	int firstline;
	int maxlines;
	int textwidth;
	int highlightline;
	int selectedline;
	int selection[4];
	int cursor[2];
	SDL_Color textcolor;
	SDL_Color hlcolor;
	SDL_Color bg;
	kiss_font font;
	kiss_window* wdw;
} kiss_textbox;

typedef struct kiss_combobox {
	int visible;
	char text[KISS_MAX_LENGTH];
	kiss_entry entry;
	kiss_window window;
	kiss_vscrollbar vscrollbar;
	kiss_textbox textbox;
	kiss_image combo;
	kiss_window* wdw;
} kiss_combobox;



class myKissGUI
{
public:
	myKissGUI();
	void fillConnectedMidiDevices(kiss_array* inArray, MidiModule *myMidiModule);
	void fillMidiParam(kiss_array* inArray);
	void fillImageParam(kiss_array* inArray);
	bool dropBoxcompare(kiss_entry clickedEntry, char* compare);
	char* kiss_getcwd(char* buf, int size);
	int kiss_chdir(char* path);
	int kiss_getstat(char* pathname, kiss_stat* buf);
	//	kiss_dir* kiss_opendir(char* name);
	kiss_dirent* kiss_readdir(kiss_dir* dirp);
	int kiss_closedir(kiss_dir* dirp);
	int kiss_isdir(kiss_stat s);
	int kiss_isreg(kiss_stat s);
	int kiss_makerect(SDL_Rect* rect, int x, int y, int h, int w);
	int kiss_pointinrect(int x, int y, SDL_Rect* rect);
	int kiss_utf8next(char* str, int index);
	int kiss_utf8prev(char* str, int index);
	int kiss_utf8fix(char* str);
	char* kiss_string_copy(char* dest, size_t size, char* str1, char* str2);
	int kiss_string_compare(const void* a, const void* b);
	char* kiss_backspace(char* str);
	int kiss_array_new(kiss_array* a);
	void* kiss_array_data(kiss_array* a, int index);
	int kiss_array_id(kiss_array* a, int index);
	int kiss_array_assign(kiss_array* a, int index, int id, void* data);
	int kiss_array_append(kiss_array* a, int id, void* data);
	int kiss_array_appendstring(kiss_array* a, int id, char* text1, char* text2);
	int kiss_array_insert(kiss_array* a, int index, int id, void* data);
	int kiss_array_remove(kiss_array* a, int index);
	int kiss_array_free(kiss_array* a);
	int kiss_maxlength(kiss_font font, int width, char* str1, char* str2);
	int kiss_textwidth(kiss_font font, char* str1, char* str2);
	int kiss_renderimage(SDL_Renderer* renderer, kiss_image image,
		int x, int y, SDL_Rect* clip);
	int kiss_rendertext(SDL_Renderer* renderer, char* text, int x, int y,
		kiss_font font, SDL_Color color);
	int kiss_fillrect(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Color color);
	int kiss_decorate(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Color color,
		int edge);
	int kiss_image_new(kiss_image* image, char* fname, kiss_array* a,
		SDL_Renderer* renderer);
	int kiss_font_new(kiss_font* font, char* fname, kiss_array* a, int size);
	SDL_Renderer* kiss_init(char* title, kiss_array* a, int w, int h);
	int kiss_clean(kiss_array* a);
	int kiss_window_new(kiss_window* window, kiss_window* wdw, int decorate,
		int x, int y, int w, int h);
	int kiss_window_event(kiss_window* window, SDL_Event* event, int* draw);
	int kiss_window_draw(kiss_window* window, SDL_Renderer* renderer);
	int kiss_label_new(kiss_label* label, kiss_window* wdw, char* text,
		int x, int y);
	int kiss_label_draw(kiss_label* label, SDL_Renderer* renderer);
	int kiss_button_new(kiss_button* button, kiss_window* wdw, char* text,
		int x, int y);
	int kiss_button_event(kiss_button* button, SDL_Event* event, int* draw);
	int kiss_button_draw(kiss_button* button, SDL_Renderer* renderer);

	int kiss_upbutton_new(kiss_upbutton* button, kiss_window* wdw, int x, int y);
	int kiss_upbutton_event(kiss_upbutton* button, SDL_Event* event, int* draw);
	int kiss_upbutton_draw(kiss_upbutton* button, SDL_Renderer* renderer);

	int kiss_downbutton_new(kiss_downbutton* button, kiss_window* wdw, int x, int y);
	int kiss_downbutton_event(kiss_downbutton* button, SDL_Event* event, int* draw);
	int kiss_downbutton_draw(kiss_downbutton* button, SDL_Renderer* renderer);

	int kiss_selectbutton_new(kiss_selectbutton* selectbutton, kiss_window* wdw,
		int x, int y);
	int kiss_selectbutton_event(kiss_selectbutton* selectbutton,
		SDL_Event* event, int* draw);
	int kiss_selectbutton_draw(kiss_selectbutton* selectbutton,
		SDL_Renderer* renderer);
	int kiss_tab_new(kiss_tab* tab, kiss_window* wdw, char* text,
		int x, int y);
	int kiss_tab_event(kiss_tab* tab,
		SDL_Event* event, int* draw);
	int kiss_tab_draw(kiss_tab* tab, SDL_Renderer* renderer);
	int kiss_vscrollbar_new(kiss_vscrollbar* vscrollbar, kiss_window* wdw,
		int x, int y, int h);
	void vnewpos(kiss_vscrollbar* vscrollbar, double step, int* draw);
	int kiss_vscrollbar_event(kiss_vscrollbar* vscrollbar, SDL_Event* event,
		int* draw);
	int kiss_vscrollbar_draw(kiss_vscrollbar* vscrollbar,
		SDL_Renderer* renderer);
	int kiss_hscrollbar_new(kiss_hscrollbar* hscrollbar, kiss_window* wdw,
		int x, int y, int w);
	void hnewpos(kiss_hscrollbar* hscrollbar, double step, int* draw);
	int kiss_hscrollbar_event(kiss_hscrollbar* hscrollbar, SDL_Event* event,
		int* draw);
	int kiss_hscrollbar_draw(kiss_hscrollbar* hscrollbar,
		SDL_Renderer* renderer);
	int kiss_progressbar_new(kiss_progressbar* progressbar, kiss_window* wdw,
		int x, int y, int w);
	int kiss_progressbar_event(kiss_progressbar* progressbar, SDL_Event* event,
		int* draw);
	int kiss_progressbar_draw(kiss_progressbar* progressbar,
		SDL_Renderer* renderer);
	int kiss_entry_new(kiss_entry* entry, kiss_window* wdw, int decorate,
		char* text, int x, int y, int w);
	int kiss_entry_event(kiss_entry* entry, SDL_Event* event, int* draw);
	int kiss_entry_draw(kiss_entry* entry, SDL_Renderer* renderer);
	int kiss_textbox_new(kiss_textbox* textbox, kiss_window* wdw, int decorate,
		kiss_array* a, int x, int y, int w, int h);
	int textbox_numoflines(kiss_textbox* textbox);

	int kiss_textbox_event(kiss_textbox* textbox, SDL_Event* event, int* draw);
	int kiss_textbox_draw(kiss_textbox* textbox, SDL_Renderer* renderer);
	int kiss_combobox_new(kiss_combobox* combobox, kiss_window* wdw,
		char* text, kiss_array* a, int x, int y, int w, int h);
	int kiss_combobox_event(kiss_combobox* combobox, SDL_Event* event,
		int* draw);
	int kiss_combobox_draw(kiss_combobox* combobox, SDL_Renderer* renderer);

	kiss_font kiss_textfont, kiss_buttonfont;
	kiss_image kiss_normal, kiss_prelight, kiss_active, kiss_bar,
		kiss_up, kiss_up_prelight, kiss_down, kiss_down_prelight, kiss_left, 
		kiss_right, kiss_vslider,kiss_hslider, kiss_selected, kiss_unselected, kiss_combo,
		kiss_tabSelected, kiss_tabHover, kiss_tabNormal;
	int kiss_screen_width, kiss_screen_height;
	int kiss_textfont_size = 15;
	int kiss_buttonfont_size = 12;
	int kiss_click_interval = 140;
	int kiss_progress_interval = 50;
	int kiss_slider_padding = 2;
	int kiss_edge = 2;
	int kiss_border = 6;
	double kiss_spacing = 0.5;
	SDL_Color kiss_white = { 255, 255, 255, 255 };
	SDL_Color kiss_black = { 0, 0, 0, 255 };
	SDL_Color kiss_green = { 0, 150, 0, 255 };
	SDL_Color kiss_blue = { 0, 0, 255, 255 };
	SDL_Color kiss_lightblue = { 200, 225, 255, 255 };

private:

};

#endif