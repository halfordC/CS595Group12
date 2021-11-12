#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

#include "UserGUI.hpp"
//#include "kiss_sdl.h"
#include "myKissGui.hpp"

using std::cout; using std::cin;
using std::endl; using std::string;


UserGUI::UserGUI(const char* p_title) :mode(), window(NULL), renderer(NULL)
{
	/* Get current display mode to initialize a window with native screen resolution. */
	if (SDL_GetCurrentDisplayMode(0, &mode) != 0)
	{
		cout << "Failed to get current display mode. Error: " << SDL_GetError() << endl;
	}
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mode.w, mode.h, SDL_WINDOW_HIDDEN); //title, xpos, ypos, width, height, and show the window.
	if (window == NULL)
	{
		cout << "Window failed to init. Error: " << SDL_GetError() << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //render to window, use default graphics driver, and use hardware acceleration if availible.
	if (renderer == NULL)
	{
		cout << "Renderer failed to init. Error: " << SDL_GetError() << endl;
	}

	cout << "GUI strated" << endl;
	kissGUI = new myKissGUI();

	initializeScene();
}

/* This method will show the RenderWindow in the native resolution of the system. It will be fullscreen
   and borderless. This method should be triggered by the "START" button on the GUI. */
void UserGUI::enterViewMode()
{
	/*
	SDL_SetWindowSize(window, mode.w, mode.h);
	SDL_ShowWindow(window);
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	*/

	//just to get a cool example screenshot
	SDL_SetWindowSize(window, 640, 480);
	SDL_SetWindowPosition(window, 50, 50);
	SDL_ShowWindow(window);
}

/* This method clears and sets up a new sprites vector for rendering. This Method
	 should be called any time a change is made to the current scene directory
	 and any time the directory changes. */
int UserGUI::initializeScene()
{
	char message[KISS_MAX_LENGTH];
	strcpy(message, "Hello World!");
	kissGUI->kiss_array_new(&objects); //init all the stuff that kiss expects in an array
	kissGUI->kiss_window_new(&window1, NULL, 1, 0, 0, kissGUI->kiss_screen_width, kissGUI->kiss_screen_height);
	kissGUI->kiss_label_new(&label, &window1, message, 20, 20);
	label.textcolor.r = 255;
	window1.visible = 1;
	
	/*
	//kiss_array objects, a1, a2;
	//kiss_window window1, window2;
	kiss_label label1 = { 0 }, label2 = { 0 }, label_sel = { 0 },
		label_res = { 0 };
	kiss_button button_ok1 = { 0 }, button_ok2 = { 0 }, button_cancel = { 0 };
	kiss_textbox textbox1 = { 0 }, textbox2 = { 0 };
	kiss_vscrollbar vscrollbar1 = { 0 }, vscrollbar2 = { 0 };
	kiss_progressbar progressbar = { 0 };
	kiss_entry entry = { 0 };
	int textbox_width, textbox_height, window2_width, window2_height,
		draw, quit;

	quit = 0;
	draw = 1;
	textbox_width = 250;
	textbox_height = 250;
	window2_width = 400;
	window2_height = 168;
	renderer = kissGUI->kiss_init("kiss_sdl example 1", &objects, 640, 480);
	if (!renderer) return 1;
	kissGUI->kiss_array_new(&a1);
	kissGUI->kiss_array_append(&objects, ARRAY_TYPE, &a1);
	kissGUI->kiss_array_new(&a2);
	kissGUI->kiss_array_append(&objects, ARRAY_TYPE, &a2);

	/* Arrange the widgets nicely relative to each other */
	/*
	kissGUI->kiss_window_new(&window1, NULL, 1, 0, 0, 500,
		500);
		*/
	/*
	kissGUI->kiss_textbox_new(&textbox1, &window1, 1, &a1, kissGUI->kiss_screen_width / 2 -
		(2 * textbox_width + 2 * kissGUI->kiss_up.w - kissGUI->kiss_edge) / 2,
		3 * kissGUI->kiss_normal.h, textbox_width, textbox_height);

	kissGUI->kiss_vscrollbar_new(&vscrollbar1, &window1, textbox1.rect.x +
		textbox_width, textbox1.rect.y, textbox_height);
	kissGUI->kiss_textbox_new(&textbox2, &window1, 1, &a2,
		vscrollbar1.uprect.x + kissGUI->kiss_up.w, textbox1.rect.y,
		textbox_width, textbox_height);
	kissGUI->kiss_vscrollbar_new(&vscrollbar2, &window1, textbox2.rect.x +
		textbox_width, vscrollbar1.uprect.y, textbox_height);
	kissGUI->kiss_label_new(&label1, &window1, "Folders", textbox1.rect.x +
		kissGUI->kiss_edge, textbox1.rect.y - kissGUI->kiss_textfont.lineheight);
	kissGUI->kiss_label_new(&label2, &window1, "Files", textbox2.rect.x +
		kissGUI->kiss_edge, textbox1.rect.y - kissGUI->kiss_textfont.lineheight);
	kissGUI->kiss_label_new(&label_sel, &window1, "", textbox1.rect.x +
		kissGUI->kiss_edge, textbox1.rect.y + textbox_height +
		kissGUI->kiss_normal.h);
	kissGUI->kiss_entry_new(&entry, &window1, 1, "kiss", textbox1.rect.x,
		label_sel.rect.y + kissGUI->kiss_textfont.lineheight,
		2 * textbox_width + 2 * kissGUI->kiss_up.w + kissGUI->kiss_edge);
	kissGUI->kiss_button_new(&button_cancel, &window1, "Cancel",
		entry.rect.x + entry.rect.w - kissGUI->kiss_edge - kissGUI->kiss_normal.w,
		entry.rect.y + entry.rect.h + kissGUI->kiss_normal.h);
	kissGUI->kiss_button_new(&button_ok1, &window1, "OK", button_cancel.rect.x -
		2 * kissGUI->kiss_normal.w, button_cancel.rect.y);
	kissGUI->kiss_window_new(&window2, NULL, 1, kissGUI->kiss_screen_width / 2 -
		window2_width / 2, kissGUI->kiss_screen_height / 2 -
		window2_height / 2, window2_width, window2_height);
	kissGUI->kiss_label_new(&label_res, &window2, "", window2.rect.x +
		kissGUI->kiss_up.w, window2.rect.y + kissGUI->kiss_vslider.h);
	label_res.textcolor = kissGUI->kiss_blue;
	kissGUI->kiss_progressbar_new(&progressbar, &window2, window2.rect.x +
		kissGUI->kiss_up.w - kissGUI->kiss_edge, window2.rect.y + window2.rect.h / 2 -
		kissGUI->kiss_bar.h / 2 - kissGUI->kiss_border,
		window2.rect.w - 2 * kissGUI->kiss_up.w + 2 * kissGUI->kiss_edge);
	kissGUI->kiss_button_new(&button_ok2, &window2, "OK", window2.rect.x +
		window2.rect.w / 2 - kissGUI->kiss_normal.w / 2,
		progressbar.rect.y + progressbar.rect.h +
		2 * kissGUI->kiss_vslider.h);
		*/
	return 0;
}

/* This method will render the sprites that are held in the sprite vector to the screen.
	 Sprites are going to be rendered with the center of their rect at the x and y percentages that are
	 stored. This method should be called by main in the main program loop. */
void UserGUI::render()
{
	SDL_RenderClear(renderer);
	kissGUI->kiss_window_draw(&window1, renderer);
	kissGUI->kiss_label_draw(&label, renderer);
	SDL_RenderPresent(renderer);
}

void UserGUI::cleanUp()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}