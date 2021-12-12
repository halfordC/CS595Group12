#include "myKissGUI.hpp"
#include "midiModule.h"


//extern MidiModule* myMidiModule;

	myKissGUI::myKissGUI() 
	{
		/*
		kiss_textfont; kiss_buttonfont;
		kiss_normal; 
		kiss_prelight; kiss_active; kiss_bar;
		kiss_up; kiss_down; kiss_left; kiss_right; kiss_vslider;
		kiss_hslider; kiss_selected; kiss_unselected; kiss_combo;
		*/
		kiss_screen_width = 0; 
		kiss_screen_height = 0;
		kiss_textfont_size = 15;
		kiss_buttonfont_size = 12;
		kiss_click_interval = 140;
		kiss_progress_interval = 50;
		kiss_slider_padding = 2;
		kiss_edge = 2;
		kiss_border = 6;
		kiss_spacing = 0.5;
		kiss_white = { 255, 255, 255, 255 };
		kiss_black = { 0, 0, 0, 255 };
		kiss_green = { 0, 150, 0, 255 };
		kiss_blue = { 0, 0, 255, 255 };
		kiss_lightblue = { 200, 225, 255, 255 };

	}


	void myKissGUI::fillConnectedMidiDevices(kiss_array *inArray, MidiModule * myMidiModule) 
	{
		kiss_array_new(inArray);

		std::vector<std::string> midiInputDeviceNames; //make string array
		myMidiModule->getMidiDeviceNames(&midiInputDeviceNames); //throw all device names in string array

		//add all strings returned from connected midi devices to array. 
		for (auto i = midiInputDeviceNames.begin(); i != midiInputDeviceNames.end(); i++)
		{
			std::string convertBucket = *i;
			char* c = strcpy(new char[convertBucket.length() + 1], convertBucket.c_str());
			kiss_array_appendstring(inArray, 0, c, NULL);
		}

		if (midiInputDeviceNames.size() == 0) 
		{
			kiss_array_appendstring(inArray, 0, "No Connected Devices", NULL);

		}

	}

	void myKissGUI::fillMidiParam(kiss_array* inArray)
	{
		kiss_array_new(inArray);

		kiss_array_appendstring(inArray, 0, "Note On", NULL);
		kiss_array_appendstring(inArray, 0, "Note Off", NULL);
		kiss_array_appendstring(inArray, 0, "Control Change", NULL);
	}

	void myKissGUI::fillImageParam(kiss_array* inArray)
	{
		kiss_array_new(inArray);

		kiss_array_appendstring(inArray, 0, "Set X", NULL);
		kiss_array_appendstring(inArray, 0, "Set Y", NULL);
		kiss_array_appendstring(inArray, 0, "Set Width", NULL);
		kiss_array_appendstring(inArray, 0, "Set Height", NULL);
		kiss_array_appendstring(inArray, 0, "Set Size", NULL);
		kiss_array_appendstring(inArray, 0, "Set Rotation", NULL);
		kiss_array_appendstring(inArray, 0, "Set On/Off", NULL);

		kiss_array_appendstring(inArray, 0, "Scale X", NULL);
		kiss_array_appendstring(inArray, 0, "Scale Y", NULL);
		kiss_array_appendstring(inArray, 0, "Scale Width", NULL);
		kiss_array_appendstring(inArray, 0, "Scale Height", NULL);
		kiss_array_appendstring(inArray, 0, "Scale Size", NULL);
		kiss_array_appendstring(inArray, 0, "Scale Rotation", NULL);
	}

	bool myKissGUI::dropBoxcompare(kiss_entry clickedEntry, char* compare)
	{
		char* clicked = clickedEntry.text;
		int found = 0;
		int i = 0;//look through the text entry until a null terminator is found.
		while (found != 1)
		{
			if (clicked[i] == NULL)
			{
				found = 1;
			}
			i++;
			if (i == 199)
			{
				found = 2; //
			}
		}

		int clickedLength = i - 1;

		bool isSame = true;
		for (int j = 0; j < clickedLength; j++) 
		{
			if (clicked[j] != compare[j]) 
			{
				isSame = false;
			}
		}
		return isSame;
	}

	char* myKissGUI::kiss_getcwd(char* buf, int size)
	{
#ifdef _MSC_VER
		return _getcwd(buf, size);
#else
		return getcwd(buf, size);
#endif
	}

	int myKissGUI::kiss_chdir(char* path)
	{
#ifdef _MSC_VER
		return _chdir(path);
#else
		return chdir(path);
#endif
	}

	int myKissGUI::kiss_getstat(char* pathname, kiss_stat* buf)
	{
#ifdef _MSC_VER
#ifdef _WIN32
		return _stat32(pathname, buf);
#else
		return _stat64(pathname, buf);
#endif
#endif
#ifndef _MSC_VER
		return stat(pathname, buf);
#endif
	}

	/* Search pattern must end with * in Visual C */
	/*
	kiss_dir* myKissGUI::kiss_opendir(char* name)
	{
#ifdef _MSC_VER
		
		kiss_dir* dir;

		if (!name || strlen(name) > KISS_MAX_LENGTH - 2) return NULL;
		dir = malloc(sizeof(kiss_dir));
		dir->ent.d_name = NULL;
		strcpy(dir->name, name);
		dir->fhandle = (ptrdiff_t)_findfirst(dir->name, &dir->fdata);
		if ((int)dir->fhandle == -1) {
			free(dir);
			return NULL;
		}
		return dir;
#else

		return opendir(name);
#endif
	}
	*/

	kiss_dirent* myKissGUI::kiss_readdir(kiss_dir* dirp)
	{
#ifdef _MSC_VER
		if (dirp->ent.d_name &&
			(int)_findnext(dirp->fhandle, &dirp->fdata) == -1)
			return NULL;
		dirp->ent.d_name = dirp->fdata.name;
		return &dirp->ent;
#else
		return readdir(dirp);
#endif
	}

	int myKissGUI::kiss_closedir(kiss_dir* dirp)
	{
#ifdef _MSC_VER
		int n;

		if (!dirp || dirp->fhandle == -1) return -1;
		n = (int)_findclose(dirp->fhandle);
		free(dirp);
		return n;
#else
		return closedir(dirp);
#endif
	}

	int myKissGUI::kiss_isdir(kiss_stat s)
	{
#ifdef _MSC_VER
		return s.st_mode & _S_IFDIR;
#else
		return S_ISDIR(s.st_mode);
#endif
	}

	int myKissGUI::kiss_isreg(kiss_stat s)
	{
#ifdef _MSC_VER
		return s.st_mode & _S_IFREG;
#else
		return S_ISREG(s.st_mode);
#endif
	}
	int myKissGUI::kiss_makerect(SDL_Rect* rect, int x, int y, int w, int h)
	{
		if (!rect) return -1;
		rect->x = x;
		rect->y = y;
		rect->w = w;
		rect->h = h;
		return 0;
	}

	int myKissGUI::kiss_pointinrect(int x, int y, SDL_Rect* rect)
	{
		return x >= rect->x && x < rect->x + rect->w &&
			y >= rect->y && y < rect->y + rect->h;
	}

	int myKissGUI::kiss_utf8next(char* str, int index)
	{
		int i;

		if (!str || index < 0) return -1;
		if (!str[index]) return 0;
		for (i = 1; str[index + i]; i++)
			if ((str[index + i] & 128) == 0 ||
				(str[index + i] & 224) == 192 ||
				(str[index + i] & 240) == 224 ||
				(str[index + i] & 248) == 240)
				break;
		return i;
	}

	int myKissGUI::kiss_utf8prev(char* str, int index)
	{
		int i;

		if (!str || index < 0) return -1;
		if (!index) return 0;
		for (i = 1; index - i; i++)
			if ((str[index - i] & 128) == 0 ||
				(str[index - i] & 224) == 192 ||
				(str[index - i] & 240) == 224 ||
				(str[index - i] & 248) == 240)
				break;
		return i;
	}

	int myKissGUI::kiss_utf8fix(char* str)
	{
		int len, i;

		if (!str || !str[0]) return -1;
		len = strlen(str);
		for (i = len - 1; i >= 0 && len - 1 - i < 3; i--) {
			if ((str[i] & 224) == 192 && len - 1 - i < 1) str[i] = 0;
			if ((str[i] & 240) == 224 && len - 1 - i < 2) str[i] = 0;
			if ((str[i] & 248) == 240 && len - 1 - i < 3) str[i] = 0;
		}
		return 0;
	}

	char* myKissGUI::kiss_string_copy(char* dest, size_t size, char* str1, char* str2)
	{
		unsigned int len;
		char* p;

		if (!dest) return NULL;
		strcpy(dest, "");
		if (size < 2) return dest;
		if (str1) strncpy(dest, str1, size);
		dest[size - 1] = 0;
		len = strlen(dest);
		if (!str2 || size - 1 <= len) return dest;
		p = dest;
		strncpy(p + len, str2, size - len);
		dest[size - 1] = 0;
		kiss_utf8fix(dest);
		return dest;
	}

	int myKissGUI::kiss_string_compare(const void* a, const void* b)
	{
		return strcmp(*((char**)a), *((char**)b));
	}

	char* myKissGUI::kiss_backspace(char* str)
	{
		int len;

		if (!str) return NULL;
		if (!(len = strlen(str))) return NULL;
		str[len - 1] = 0;
		kiss_utf8fix(str);
		return str;
	}

	int myKissGUI::kiss_array_new(kiss_array* a)
	{
		if (!a) return -1;
		a->size = KISS_MIN_LENGTH;
		a->length = 0;
		a->ref = 1;
		a->data = (void**)malloc(KISS_MIN_LENGTH * sizeof(void*));
		a->id = (int*)malloc(KISS_MIN_LENGTH * sizeof(int));
		return 0;
	}

	void* myKissGUI::kiss_array_data(kiss_array* a, int index)
	{
		if (index < 0 || index >= a->size || !a) return NULL;
		return a->data[index];
	}

	int myKissGUI::kiss_array_id(kiss_array* a, int index)
	{
		if (!a || index < 0 || index >= a->size) return 0;
		return a->id[index];
	}

	int myKissGUI::kiss_array_assign(kiss_array* a, int index, int id, void* data)
	{
		if (!a || index < 0 || index >= a->length) return -1;
		free(a->data[index]);
		a->data[index] = data;
		a->id[index] = id;
		return 0;
	}

	int myKissGUI::kiss_array_append(kiss_array* a, int id, void* data)
	{
		int i;

		if (!a) return -1;
		if (a->length >= a->size) {
			a->size *= 2;
			a->data = (void**)realloc(a->data,
				a->size * sizeof(void*));
			a->id = (int*)realloc(a->id, a->size * sizeof(int));
			for (i = a->length; i < a->size; i++) {
				a->data[i] = NULL;
				a->id[i] = 0;
			}
		}
		a->data[a->length] = data;
		a->id[a->length] = id;
		++a->length;
		return 0;
	}

	int myKissGUI::kiss_array_appendstring(kiss_array* a, int id, char* text1, char* text2)
	{
		char* p;

		if (!a) return -1;
		p = (char*)malloc(KISS_MAX_LENGTH);
		kiss_string_copy(p, KISS_MAX_LENGTH, text1, text2);
		kiss_array_append(a, id, p);
		return 0;
	}

	int myKissGUI::kiss_array_insert(kiss_array* a, int index, int id, void* data)
	{
		int i;

		if (!a || index < 0 || index >= a->length) return -1;
		if (a->length >= a->size) {
			a->size *= 2;
			a->data = (void**)realloc(a->data,
				a->size * sizeof(void*));
			a->id = (int*)realloc(a->id, a->size * sizeof(int));
			for (i = a->length; i < a->size; i++) {
				a->data[i] = NULL;
				a->id[i] = 0;
			}
		}
		for (i = a->length - 1; i >= index; i--) {
			a->data[i + 1] = a->data[i];
			a->id[i + 1] = a->id[i];
		}
		a->data[index] = data;
		a->id[index] = id;
		++a->length;
		return 0;
	}

	int myKissGUI::kiss_array_remove(kiss_array* a, int index)
	{
		int i;

		if (!a || index < 0 || index >= a->length) return -1;
		free(a->data[index]);
		for (i = index; i < a->length - 1; i++) {
			a->data[i] = a->data[i + 1];
			a->id[i] = a->id[i + 1];
		}
		a->data[a->length - 1] = NULL;
		a->id[a->length - 1] = 0;
		--a->length;
		return 0;
	}

	int myKissGUI::kiss_array_free(kiss_array* a)
	{
		int i;

		if (!a || !a->ref) return -1;
		if (a->ref > 1) {
			--a->ref;
			return 0;
		}
		if (a->length)
			for (i = 0; i < a->length; i++)
				free(a->data[i]);
		free(a->data);
		free(a->id);
		a->data = NULL;
		a->id = NULL;
		a->size = 0;
		a->length = 0;
		a->ref = 0;
		return 0;
	}

	//if anything uses kiss_getticks(), use SDL_GetTicks() instead


	/* Can be rewritten for proportional fonts */
	int myKissGUI::kiss_maxlength(kiss_font font, int width, char* str1, char* str2)
	{
		char buf[KISS_MAX_LENGTH];
		int n, i;

		n = 0;
		if (!str1 && !str2) return -1;
		kiss_string_copy(buf, KISS_MAX_LENGTH, str1, str2);
		/* Maximum length + 1 for '\0', by the rule */
		for (i = 0; buf[i]; i += kiss_utf8next(buf, i))
			if (++n * font.advance > width)
				return i + 1;
		return i + 1;
	}

	/* Works also with proportional fonts */
	int myKissGUI::kiss_textwidth(kiss_font font, char* str1, char* str2)
	{
		char buf[KISS_MAX_LENGTH];
		int width;

		if (!str1 && !str2) return -1;
		kiss_string_copy(buf, KISS_MAX_LENGTH, str1, str2);
		TTF_SizeUTF8(font.font, buf, &width, NULL);
		return width;
	}

	int myKissGUI::kiss_renderimage(SDL_Renderer* renderer, kiss_image image,
		int x, int y, SDL_Rect* clip)
	{
		SDL_Rect dst;

		if (!renderer || !image.image) return -1;
		kiss_makerect(&dst, x, y, image.w, image.h);
		if (clip) dst.w = clip->w;
		if (clip) dst.h = clip->h;
		SDL_RenderCopy(renderer, image.image, clip, &dst);
		return 0;
	}

	int myKissGUI::kiss_rendertext(SDL_Renderer* renderer, char* text, int x, int y,
		kiss_font font, SDL_Color color)
	{
		SDL_Surface* surface;
		kiss_image image;

		if (!text || !renderer || !font.font) return -1;
		surface = TTF_RenderUTF8_Blended(font.font, text, color);
		image.image = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_QueryTexture(image.image, NULL, NULL, &image.w, &image.h);
		if (surface) SDL_FreeSurface(surface);
		kiss_renderimage(renderer, image, x, y, NULL);
		SDL_DestroyTexture(image.image);
		return 0;
	}

	int myKissGUI::kiss_fillrect(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Color color)
	{
		if (!renderer || !rect) return -1;
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, rect);
		return 0;
	}

	int myKissGUI::kiss_decorate(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Color color,
		int edge)
	{
		SDL_Rect outlinerect;
		int d, i;

		d = 2 * edge;
		if (!renderer || !rect || rect->w < d + 6 || rect->h < d + 6)
			return -1;
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		for (i = 0; i < 2; i++) {
			kiss_makerect(&outlinerect, rect->x + edge + i,
				rect->y + edge + i, rect->w - d - i - i,
				rect->h - d - i - i);
			SDL_RenderDrawRect(renderer, &outlinerect);
		}
		return 0;
	}

	int myKissGUI::kiss_image_new(kiss_image* image, char* fname, kiss_array* a,
		SDL_Renderer* renderer)
	{
		char buf[KISS_MAX_LENGTH];

		if (!image || !fname) return -1;
		kiss_string_copy(buf, KISS_MAX_LENGTH, RESDIR, fname);
		if (!(image->image = IMG_LoadTexture(renderer, buf))) {
			fprintf(stderr, "Cannot load image %s\n", fname);
			return -1;
		}
		if (a) kiss_array_append(a, TEXTURE_TYPE, image->image);
		SDL_QueryTexture(image->image, NULL, NULL, &image->w, &image->h);
		image->magic = KISS_MAGIC;
		return 0;
	}

	int myKissGUI::kiss_font_new(kiss_font* font, char* fname, kiss_array* a, int size)
	{
		char buf[KISS_MAX_LENGTH];

		if (!font || !fname) return -1;
		kiss_string_copy(buf, KISS_MAX_LENGTH, RESDIR, fname);
		if (!(font->font = TTF_OpenFont(buf, size))) {
			fprintf(stderr, "Cannot load font %s\n", fname);
			return -1;
		}
		if (a) kiss_array_append(a, FONT_TYPE, font->font);
		font->fontheight = TTF_FontHeight(font->font);
		font->spacing = (int)myKissGUI::kiss_spacing * font->fontheight;
		font->lineheight = font->fontheight + font->spacing;
		font->ascent = TTF_FontAscent(font->font);
		TTF_GlyphMetrics(font->font, 'W', NULL, NULL, NULL, NULL,
			&(font->advance));
		font->magic = KISS_MAGIC;
		return 0;
	}

	SDL_Renderer* myKissGUI::kiss_init(char* title, kiss_array* a, int w, int h)
	{
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Rect srect;
		int r;

		r = 0;
		SDL_Init(SDL_INIT_EVERYTHING);
		SDL_GetDisplayBounds(0, &srect);
		if (!a || w > srect.w || h > srect.h) {
			SDL_Quit();
			return NULL;
		}
		kiss_screen_width = w;
		kiss_screen_height = h;
		IMG_Init(IMG_INIT_PNG);
		TTF_Init();
		SDL_StartTextInput();
		kiss_array_new(a);
		window = SDL_CreateWindow(title, srect.w / 2 - w / 2,
			srect.h / 2 - h / 2, w, h, SDL_WINDOW_SHOWN);
		if (window) kiss_array_append(a, WINDOW_TYPE, window);
		renderer = SDL_CreateRenderer(window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer) kiss_array_append(a, RENDERER_TYPE, renderer);
		r += kiss_font_new(&kiss_textfont, "kissGUIAssets/kiss_font.ttf", a,
			kiss_textfont_size);
		r += kiss_font_new(&kiss_buttonfont, "kissGUIAssets/kiss_font.ttf", a,
			kiss_buttonfont_size);
		r += kiss_image_new(&kiss_normal, "kissGUIAssets/kiss_normal.png", a, renderer);
		r += kiss_image_new(&kiss_prelight, "kissGUIAssets/kiss_prelight.png", a, renderer);
		r += kiss_image_new(&kiss_active, "kissGUIAssets/kiss_active.png", a, renderer);
		r += kiss_image_new(&kiss_bar, "kissGUIAssets/kiss_bar.png", a, renderer);
		r += kiss_image_new(&kiss_vslider, "kissGUIAssets/kiss_vslider.png", a, renderer);
		r += kiss_image_new(&kiss_hslider, "kissGUIAssets/kiss_hslider.png", a, renderer);
		r += kiss_image_new(&kiss_up, "kissGUIAssets/kiss_up.png", a, renderer);
		r += kiss_image_new(&kiss_up_prelight, "kissGUIAssets/kiss_up_prelight.png", a, renderer);
		r += kiss_image_new(&kiss_down, "kissGUIAssets/kiss_down.png", a, renderer);
		r += kiss_image_new(&kiss_down_prelight, "kissGUIAssets/kiss_down_prelight.png", a, renderer);
		r += kiss_image_new(&kiss_left, "kissGUIAssets/kiss_left.png", a, renderer);
		r += kiss_image_new(&kiss_right, "kissGUIAssets/kiss_right.png", a, renderer);
		r += kiss_image_new(&kiss_combo, "kissGUIAssets/kiss_combo.png", a, renderer);
		r += kiss_image_new(&kiss_selected, "kissGUIAssets/kiss_selected.png", a, renderer);
		r += kiss_image_new(&kiss_tabSelected, "kissGUIAssets/kiss_tabSelected.png", a, renderer);
		r += kiss_image_new(&kiss_tabHover, "kissGUIAssets/kiss_tabHover.png", a, renderer);
		r += kiss_image_new(&kiss_tabNormal, "kissGUIAssets/kiss_tab.png", a, renderer);
		r += kiss_image_new(&kiss_unselected, "kissGUIAssets/kiss_unselected.png", a,
			renderer);
		if (r) {
			kiss_clean(a);
			return NULL;
		}
		return renderer;
	}

	int myKissGUI::kiss_clean(kiss_array* a)
	{
		int i;

		if (!a) return -1;
		if (a->length)
			for (i = a->length - 1; i >= 0; i--) {
				if (kiss_array_id(a, i) == FONT_TYPE)
					TTF_CloseFont((TTF_Font*)
						kiss_array_data(a, i));
				else if (kiss_array_id(a, i) == TEXTURE_TYPE)
					SDL_DestroyTexture((SDL_Texture*)
						kiss_array_data(a, i));
				else if (kiss_array_id(a, i) == RENDERER_TYPE)
					SDL_DestroyRenderer((SDL_Renderer*)
						kiss_array_data(a, i));
				else if (kiss_array_id(a, i) == WINDOW_TYPE)
					SDL_DestroyWindow((SDL_Window*)
						kiss_array_data(a, i));
				else if (kiss_array_id(a, i) == ARRAY_TYPE)
					kiss_array_free((kiss_array*)
						kiss_array_data(a, i));
				else
					free(a->data[i]);
			}
		a->length = 0;
		kiss_array_free(a);
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		return 0;
	}
	int myKissGUI::kiss_window_new(kiss_window* window, kiss_window* wdw, int decorate,
		int x, int y, int w, int h)
	{
		if (!window) return -1;
		window->bg = kiss_white;
		kiss_makerect(&window->rect, x, y, w, h);
		window->decorate = decorate;
		window->visible = 0;
		window->focus = 1;
		window->wdw = wdw;
		return 0;
	}

	int myKissGUI::kiss_window_event(kiss_window* window, SDL_Event* event, int* draw)
	{
		if (!window || !window->visible || !event) return 0;
		if (event->type == SDL_WINDOWEVENT &&
			event->window.event == SDL_WINDOWEVENT_EXPOSED)
			*draw = 1;
		if (!window->focus && (!window->wdw ||
			(window->wdw && !window->wdw->focus)))
			return 0;
		if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&window->rect))
			return 1;
		return 0;
	}

	int myKissGUI::kiss_window_draw(kiss_window* window, SDL_Renderer* renderer)
	{
		if (window && window->wdw) window->visible = window->wdw->visible;
		if (!window || !window->visible || !renderer) return 0;
		kiss_fillrect(renderer, &window->rect, window->bg);
		if (window->decorate)
			kiss_decorate(renderer, &window->rect, kiss_blue, kiss_edge);
		return 1;
	}

	int myKissGUI::kiss_label_new(kiss_label* label, kiss_window* wdw, char* text,
		int x, int y)
	{
		if (!label || !text) return -1;
		if (label->font.magic != KISS_MAGIC) label->font = kiss_textfont;
		label->textcolor = kiss_black;
		kiss_makerect(&label->rect, x, y, 0, 0);
		kiss_string_copy(label->text, KISS_MAX_LABEL, text, NULL);
		label->visible = 0;
		label->wdw = wdw;
		return 0;
	}

	int myKissGUI::kiss_label_draw(kiss_label* label, SDL_Renderer* renderer)
	{
		char buf[KISS_MAX_LABEL], * p;
		int len, y;

		if (label && label->wdw) label->visible = label->wdw->visible;
		if (!label || !label->visible || !renderer) return 0;
		y = label->rect.y + label->font.spacing / 2;
		len = strlen(label->text);
		if (len > KISS_MAX_LABEL - 2)
			label->text[len - 1] = '\n';
		else
			strcat(label->text, "\n");
		for (p = label->text; *p; p = strchr(p, '\n') + 1) {
			kiss_string_copy(buf, strcspn(p, "\n") + 1, p, NULL);
			kiss_rendertext(renderer, buf, label->rect.x, y,
				label->font, label->textcolor);
			y += label->font.lineheight;
		}
		label->text[len] = 0;
		return 1;
	}

	int myKissGUI::kiss_button_new(kiss_button* button, kiss_window* wdw, char* text,
		int x, int y)
	{
		if (!button || !text) return -1;
		if (button->font.magic != KISS_MAGIC) button->font = kiss_buttonfont;
		if (button->normalimg.magic != KISS_MAGIC)
			button->normalimg = kiss_normal;
		if (button->activeimg.magic != KISS_MAGIC)
			button->activeimg = kiss_active;
		if (button->prelightimg.magic != KISS_MAGIC)
			button->prelightimg = kiss_prelight;
		kiss_makerect(&button->rect, x, y, button->normalimg.w,
			button->normalimg.h);
		button->textcolor = kiss_white;
		kiss_string_copy(button->text, KISS_MAX_LENGTH, text, NULL);
		button->textx = x + button->normalimg.w / 2 -
			kiss_textwidth(button->font, text, NULL) / 2;
		button->texty = y + button->normalimg.h / 2 -
			button->font.fontheight / 2;
		button->active = 0;
		button->prelight = 0;
		button->visible = 0;
		button->focus = 0;
		button->wdw = wdw;
		return 0;
	}

	int myKissGUI::kiss_button_event(kiss_button* button, SDL_Event* event, int* draw)
	{
		if (!button || !button->visible || !event) return 0;
		if (event->type == SDL_WINDOWEVENT &&
			event->window.event == SDL_WINDOWEVENT_EXPOSED)
			*draw = 1;
		if (!button->focus && (!button->wdw ||
			(button->wdw && !button->wdw->focus)))
			return 0;
		if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&button->rect)) {
			button->active = 1;
			*draw = 1;
		}
		else if (event->type == SDL_MOUSEBUTTONUP &&
			kiss_pointinrect(event->button.x, event->button.y,
				&button->rect) && button->active) {
			button->active = 0;
			*draw = 1;
			return 1;
		}
		else if (event->type == SDL_MOUSEMOTION &&
			kiss_pointinrect(event->motion.x, event->motion.y,
				&button->rect)) {
			button->prelight = 1;
			*draw = 1;
		}
		else if (event->type == SDL_MOUSEMOTION &&
			!kiss_pointinrect(event->motion.x, event->motion.y,
				&button->rect)) {
			button->prelight = 0;
			*draw = 1;
			if (button->active) {
				button->active = 0;
				return 1;
			}
		}
		return 0;
	}

	int myKissGUI::kiss_button_draw(kiss_button* button, SDL_Renderer* renderer)
	{
		if (button && button->wdw) button->visible = button->wdw->visible;
		if (!button || !button->visible || !renderer) return 0;
		if (button->active)
			kiss_renderimage(renderer, button->activeimg, button->rect.x,
				button->rect.y, NULL);
		else if (button->prelight && !button->active)
			kiss_renderimage(renderer, button->prelightimg,
				button->rect.x, button->rect.y, NULL);
		else
			kiss_renderimage(renderer, button->normalimg, button->rect.x,
				button->rect.y, NULL);
		kiss_rendertext(renderer, button->text, button->textx, button->texty,
			button->font, button->textcolor);
		return 1;
	}

	int myKissGUI::kiss_upbutton_new(kiss_upbutton* button, kiss_window* wdw, int x, int y)
	{
		if (!button) return -1;
		//if (button->font.magic != KISS_MAGIC) button->font = kiss_buttonfont;
		if (button->normalimg.magic != KISS_MAGIC)
			button->normalimg = kiss_up;
		if (button->activeimg.magic != KISS_MAGIC)
			button->activeimg = kiss_up;
		if (button->prelightimg.magic != KISS_MAGIC)
			button->prelightimg = kiss_up_prelight;
		kiss_makerect(&button->rect, x, y, button->normalimg.w,
			button->normalimg.h);
		//button->textcolor = kiss_white;
		//kiss_string_copy(button->text, KISS_MAX_LENGTH, text, NULL);
		//button->textx = x + button->normalimg.w / 2 -
		//	kiss_textwidth(button->font, text, NULL) / 2;
		//button->texty = y + button->normalimg.h / 2 -
		//	button->font.fontheight / 2;
		button->active = 0;
		button->prelight = 0;
		button->visible = 0;
		button->focus = 0;
		button->wdw = wdw;
		return 0;
	}

	int myKissGUI::kiss_upbutton_event(kiss_upbutton* button, SDL_Event* event, int* draw)
	{
		if (!button || !button->visible || !event) return 0;
		if (event->type == SDL_WINDOWEVENT &&
			event->window.event == SDL_WINDOWEVENT_EXPOSED)
			*draw = 1;
		if (!button->focus && (!button->wdw ||
			(button->wdw && !button->wdw->focus)))
			return 0;
		if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&button->rect)) {
			button->active = 1;
			*draw = 1;
		}
		else if (event->type == SDL_MOUSEBUTTONUP &&
			kiss_pointinrect(event->button.x, event->button.y,
				&button->rect) && button->active) {
			button->active = 0;
			*draw = 1;
			return 1;
		}
		else if (event->type == SDL_MOUSEMOTION &&
			kiss_pointinrect(event->motion.x, event->motion.y,
				&button->rect)) {
			button->prelight = 1;
			*draw = 1;
		}
		else if (event->type == SDL_MOUSEMOTION &&
			!kiss_pointinrect(event->motion.x, event->motion.y,
				&button->rect)) {
			button->prelight = 0;
			*draw = 1;
			if (button->active) {
				button->active = 0;
				return 1;
			}
		}
		return 0;
	}

	int myKissGUI::kiss_upbutton_draw(kiss_upbutton* button, SDL_Renderer* renderer)
	{
		if (button && button->wdw) button->visible = button->wdw->visible;
		if (!button || !button->visible || !renderer) return 0;
		if (button->active)
			kiss_renderimage(renderer, button->activeimg, button->rect.x,
				button->rect.y, NULL);
		else if (button->prelight && !button->active)
			kiss_renderimage(renderer, button->prelightimg,
				button->rect.x, button->rect.y, NULL);
		else
			kiss_renderimage(renderer, button->normalimg, button->rect.x,
				button->rect.y, NULL);
		//kiss_rendertext(renderer, button->text, button->textx, button->texty,
		//	button->font, button->textcolor);
		return 1;
	}


	int myKissGUI::kiss_downbutton_new(kiss_downbutton* button, kiss_window* wdw, int x, int y)
	{
		if (!button) return -1;
		//if (button->font.magic != KISS_MAGIC) button->font = kiss_buttonfont;
		if (button->normalimg.magic != KISS_MAGIC)
			button->normalimg = kiss_down;
		if (button->activeimg.magic != KISS_MAGIC)
			button->activeimg = kiss_down;
		if (button->prelightimg.magic != KISS_MAGIC)
			button->prelightimg = kiss_down_prelight;
		kiss_makerect(&button->rect, x, y, button->normalimg.w,
			button->normalimg.h);
		//button->textcolor = kiss_white;
		//kiss_string_copy(button->text, KISS_MAX_LENGTH, text, NULL);
		//button->textx = x + button->normalimg.w / 2 -
		//	kiss_textwidth(button->font, text, NULL) / 2;
		//button->texty = y + button->normalimg.h / 2 -
		//	button->font.fontheight / 2;
		button->active = 0;
		button->prelight = 0;
		button->visible = 0;
		button->focus = 0;
		button->wdw = wdw;
		return 0;
	}

	int myKissGUI::kiss_downbutton_event(kiss_downbutton* button, SDL_Event* event, int* draw)
	{
		if (!button || !button->visible || !event) return 0;
		if (event->type == SDL_WINDOWEVENT &&
			event->window.event == SDL_WINDOWEVENT_EXPOSED)
			*draw = 1;
		if (!button->focus && (!button->wdw ||
			(button->wdw && !button->wdw->focus)))
			return 0;
		if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&button->rect)) {
			button->active = 1;
			*draw = 1;
		}
		else if (event->type == SDL_MOUSEBUTTONUP &&
			kiss_pointinrect(event->button.x, event->button.y,
				&button->rect) && button->active) {
			button->active = 0;
			*draw = 1;
			return 1;
		}
		else if (event->type == SDL_MOUSEMOTION &&
			kiss_pointinrect(event->motion.x, event->motion.y,
				&button->rect)) {
			button->prelight = 1;
			*draw = 1;
		}
		else if (event->type == SDL_MOUSEMOTION &&
			!kiss_pointinrect(event->motion.x, event->motion.y,
				&button->rect)) {
			button->prelight = 0;
			*draw = 1;
			if (button->active) {
				button->active = 0;
				return 1;
			}
		}
		return 0;
	}

	int myKissGUI::kiss_downbutton_draw(kiss_downbutton* button, SDL_Renderer* renderer)
	{
		if (button && button->wdw) button->visible = button->wdw->visible;
		if (!button || !button->visible || !renderer) return 0;
		if (button->active)
			kiss_renderimage(renderer, button->activeimg, button->rect.x,
				button->rect.y, NULL);
		else if (button->prelight && !button->active)
			kiss_renderimage(renderer, button->prelightimg,
				button->rect.x, button->rect.y, NULL);
		else
			kiss_renderimage(renderer, button->normalimg, button->rect.x,
				button->rect.y, NULL);
		//kiss_rendertext(renderer, button->text, button->textx, button->texty,
		//	button->font, button->textcolor);
		return 1;
	}

	int myKissGUI::kiss_selectbutton_new(kiss_selectbutton* selectbutton, kiss_window* wdw,
		int x, int y)
	{
		if (!selectbutton) return -1;
		if (selectbutton->selectedimg.magic != KISS_MAGIC)
			selectbutton->selectedimg = kiss_selected;
		if (selectbutton->unselectedimg.magic != KISS_MAGIC)
			selectbutton->unselectedimg = kiss_unselected;
		kiss_makerect(&selectbutton->rect, x, y, selectbutton->selectedimg.w,
			selectbutton->selectedimg.h);
		selectbutton->selected = 0;
		selectbutton->focus = 0;
		selectbutton->wdw = wdw;
		return 0;
	}

	int myKissGUI::kiss_selectbutton_event(kiss_selectbutton* selectbutton,
		SDL_Event* event, int* draw)
	{
		if (!selectbutton || !selectbutton->visible || !event) return 0;
		if (event->type == SDL_WINDOWEVENT &&
			event->window.event == SDL_WINDOWEVENT_EXPOSED)
			*draw = 1;
		if (!selectbutton->focus && (!selectbutton->wdw ||
			(selectbutton->wdw && !selectbutton->wdw->focus)))
			return 0;
		if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&selectbutton->rect)) {
			selectbutton->selected ^= 1;
			*draw = 1;
			return 1;
		}
		return 0;
	}

	int myKissGUI::kiss_selectbutton_draw(kiss_selectbutton* selectbutton,
		SDL_Renderer* renderer)
	{
		if (selectbutton && selectbutton->wdw)
			selectbutton->visible = selectbutton->wdw->visible;
		if (!selectbutton || !selectbutton->visible || !renderer) return 0;
		if (selectbutton->selected)
			kiss_renderimage(renderer, selectbutton->selectedimg,
				selectbutton->rect.x, selectbutton->rect.y, NULL);
		else
			kiss_renderimage(renderer, selectbutton->unselectedimg,
				selectbutton->rect.x, selectbutton->rect.y, NULL);
		return 1;
	}

	
	int myKissGUI::kiss_tab_new(kiss_tab* tab, kiss_window* wdw, char* text,
		int x, int y)
	{
		if (!tab || !text) return -1;
		if (tab->font.magic != KISS_MAGIC) tab->font = kiss_buttonfont;
		if (tab->normalimg.magic != KISS_MAGIC)
			tab->normalimg = kiss_tabNormal;
		if (tab->selectedimg.magic != KISS_MAGIC)
			tab->selectedimg = kiss_tabSelected;
		if (tab->hoverimg.magic != KISS_MAGIC)
			tab->hoverimg = kiss_tabHover;
		kiss_makerect(&tab->rect, x, y, tab->normalimg.w,
			tab->normalimg.h);
		tab->textcolor = kiss_black;
		kiss_string_copy(tab->text, KISS_MAX_LENGTH, text, NULL);
		tab->textx = x + tab->normalimg.w / 2 -
			kiss_textwidth(tab->font, text, NULL) / 2;
		tab->texty = y + tab->normalimg.h / 2 -
			tab->font.fontheight / 2;
		tab->active = 0;
		tab->prelight = 0;
		tab->visible = 0;
		tab->focus = 0;
		tab->wdw = wdw;
		return 0;
	}
	
	int myKissGUI::kiss_tab_event(kiss_tab* tab,
		SDL_Event* event, int* draw)
	{
		if (!tab || !tab->visible || !event) return 0;
		if (event->type == SDL_WINDOWEVENT &&
			event->window.event == SDL_WINDOWEVENT_EXPOSED)
			*draw = 1;
		if (!tab->focus && (!tab->wdw ||
			(tab->wdw && !tab->wdw->focus)))
			return 0;
		if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&tab->rect)) {
			tab->active = 1;
			*draw = 1;
		}
		else if (event->type == SDL_MOUSEBUTTONUP &&
			kiss_pointinrect(event->button.x, event->button.y,
				&tab->rect) && tab->active) {
			tab->active = 0;
			*draw = 1;
			return 1;
		}
		else if (event->type == SDL_MOUSEMOTION &&
			kiss_pointinrect(event->motion.x, event->motion.y,
				&tab->rect)) {
			tab->prelight = 1;
			*draw = 1;
		}
		else if (event->type == SDL_MOUSEMOTION &&
			!kiss_pointinrect(event->motion.x, event->motion.y,
				&tab->rect)) {
			tab->prelight = 0;
			*draw = 1;
			if (tab->active) {
				tab->active = 0;
				return 1;
			}
		}
		return 0;

	}
	
	int myKissGUI::kiss_tab_draw(kiss_tab* tab, SDL_Renderer* renderer)
	{
		if (tab && tab->wdw) tab->visible = tab->wdw->visible;
		if (!tab || !tab->visible || !renderer) return 0;
		if (tab->active)
			kiss_renderimage(renderer, tab->selectedimg, tab->rect.x,
				tab->rect.y, NULL);
		else if (tab->prelight && !tab->active)
			kiss_renderimage(renderer, tab->hoverimg,
				tab->rect.x, tab->rect.y, NULL);
		else
			kiss_renderimage(renderer, tab->normalimg, tab->rect.x,
				tab->rect.y, NULL);
		kiss_rendertext(renderer, tab->text, tab->textx, tab->texty,
			tab->font, tab->textcolor);
		return 1;
	}

	int myKissGUI::kiss_vscrollbar_new(kiss_vscrollbar* vscrollbar, kiss_window* wdw,
		int x, int y, int h)
	{
		if (!vscrollbar) return -1;
		if (vscrollbar->up.magic != KISS_MAGIC)
			vscrollbar->up = kiss_up;
		if (vscrollbar->down.magic != KISS_MAGIC)
			vscrollbar->down = kiss_down;
		if (vscrollbar->vslider.magic != KISS_MAGIC)
			vscrollbar->vslider = kiss_vslider;
		if (vscrollbar->up.h + vscrollbar->down.h + 2 * kiss_edge +
			2 * kiss_slider_padding + vscrollbar->vslider.h > h)
			return -1;
		kiss_makerect(&vscrollbar->uprect, x, y + kiss_edge,
			vscrollbar->up.w, vscrollbar->up.h + kiss_slider_padding);
		kiss_makerect(&vscrollbar->downrect, x, y + h - vscrollbar->down.h -
			kiss_slider_padding - kiss_edge, vscrollbar->down.w,
			vscrollbar->down.h + kiss_slider_padding);
		kiss_makerect(&vscrollbar->sliderrect, x, y + vscrollbar->uprect.h +
			kiss_edge, vscrollbar->vslider.w, vscrollbar->vslider.h);
		vscrollbar->maxpos = h - 2 * kiss_slider_padding - 2 * kiss_edge -
			vscrollbar->up.h - vscrollbar->down.h -
			vscrollbar->vslider.h;
		vscrollbar->fraction = 0.;
		vscrollbar->step = 0.1;
		vscrollbar->upclicked = 0;
		vscrollbar->downclicked = 0;
		vscrollbar->sliderclicked = 0;
		vscrollbar->lasttick = 0;
		vscrollbar->visible = 0;
		vscrollbar->focus = 0;
		vscrollbar->wdw = wdw;
		return 0;
	}

	void myKissGUI::vnewpos(kiss_vscrollbar* vscrollbar, double step, int* draw)
	{
		*draw = 1;
		vscrollbar->fraction += step;
		vscrollbar->lasttick = SDL_GetTicks();
		if (vscrollbar->fraction < -0.000001) vscrollbar->fraction = 0.;
		if (vscrollbar->fraction > 0.999999) vscrollbar->fraction = 1.;
		vscrollbar->sliderrect.y = vscrollbar->uprect.y +
			vscrollbar->uprect.h + (int)(vscrollbar->fraction *
				vscrollbar->maxpos + 0.5);
		if (vscrollbar->fraction > 0.000001 &&
			vscrollbar->fraction < 0.999999)
			return;
		vscrollbar->upclicked = 0;
		vscrollbar->downclicked = 0;
	}

	int myKissGUI::kiss_vscrollbar_event(kiss_vscrollbar* vscrollbar, SDL_Event* event,
		int* draw)
	{
		if (!vscrollbar || !vscrollbar->visible) return 0;
		if (!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))) {
			vscrollbar->upclicked = 0;
			vscrollbar->downclicked = 0;
			vscrollbar->lasttick = 0;
		}
		else if (vscrollbar->upclicked && SDL_GetTicks() >
			vscrollbar->lasttick + kiss_click_interval) {
			vnewpos(vscrollbar, -vscrollbar->step, draw);
			return 1;
		}
		else if (vscrollbar->downclicked && SDL_GetTicks() >
			vscrollbar->lasttick + kiss_click_interval) {
			vnewpos(vscrollbar, vscrollbar->step, draw);
			return 1;
		}
		if (!event) return 0;
		if (event->type == SDL_WINDOWEVENT &&
			event->window.event == SDL_WINDOWEVENT_EXPOSED)
			*draw = 1;
		if (!vscrollbar->focus && (!vscrollbar->wdw ||
			(vscrollbar->wdw && !vscrollbar->wdw->focus)))
			return 0;
		if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&vscrollbar->uprect) && vscrollbar->step > 0.000001) {
			if (vscrollbar->fraction > 0.000001) {
				vscrollbar->upclicked = 1;
				if (vscrollbar->wdw) vscrollbar->wdw->focus = 0;
				vscrollbar->focus = 1;
			}
			vscrollbar->lasttick = SDL_GetTicks() -
				kiss_click_interval - 1;
		}
		else if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&vscrollbar->downrect) && vscrollbar->step > 0.000001) {
			if (vscrollbar->fraction < 0.999999) {
				vscrollbar->downclicked = 1;
				if (vscrollbar->wdw) vscrollbar->wdw->focus = 0;
				vscrollbar->focus = 1;
			}
			vscrollbar->lasttick = SDL_GetTicks() -
				kiss_click_interval - 1;
		}
		else if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&vscrollbar->sliderrect) && vscrollbar->step > 0.000001) {
			if (vscrollbar->wdw) vscrollbar->wdw->focus = 0;
			vscrollbar->focus = 1;
			vscrollbar->sliderclicked = 1;
		}
		else if (event->type == SDL_MOUSEBUTTONUP) {
			vscrollbar->upclicked = 0;
			vscrollbar->downclicked = 0;
			vscrollbar->lasttick = 0;
			if (vscrollbar->wdw) vscrollbar->wdw->focus = 1;
			vscrollbar->focus = 0;
			vscrollbar->sliderclicked = 0;
		}
		else if (event->type == SDL_MOUSEMOTION &&
			(event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
			vscrollbar->sliderclicked) {
			vnewpos(vscrollbar, 1. * event->motion.yrel /
				vscrollbar->maxpos, draw);
			return 1;
		}
		return 0;
	}

	int myKissGUI::kiss_vscrollbar_draw(kiss_vscrollbar* vscrollbar, SDL_Renderer* renderer)
	{
		if (vscrollbar && vscrollbar->wdw)
			vscrollbar->visible = vscrollbar->wdw->visible;
		if (!vscrollbar || !vscrollbar->visible || !renderer) return 0;
		vscrollbar->sliderrect.y = vscrollbar->uprect.y +
			vscrollbar->uprect.h + (int)(vscrollbar->fraction *
				vscrollbar->maxpos);
		kiss_renderimage(renderer, vscrollbar->up, vscrollbar->uprect.x,
			vscrollbar->uprect.y, NULL);
		kiss_renderimage(renderer, vscrollbar->down, vscrollbar->downrect.x,
			vscrollbar->downrect.y + kiss_slider_padding, NULL);
		kiss_renderimage(renderer, vscrollbar->vslider,
			vscrollbar->sliderrect.x, vscrollbar->sliderrect.y, NULL);
		return 1;
	}

	int myKissGUI::kiss_hscrollbar_new(kiss_hscrollbar* hscrollbar, kiss_window* wdw,
		int x, int y, int w)
	{
		if (!hscrollbar) return -1;
		if (hscrollbar->left.magic != KISS_MAGIC)
			hscrollbar->left = kiss_left;
		if (hscrollbar->right.magic != KISS_MAGIC)
			hscrollbar->right = kiss_right;
		if (hscrollbar->hslider.magic != KISS_MAGIC)
			hscrollbar->hslider = kiss_hslider;
		if (hscrollbar->left.w + hscrollbar->right.w + 2 * kiss_edge +
			2 * kiss_slider_padding + hscrollbar->hslider.w > w)
			return -1;
		kiss_makerect(&hscrollbar->leftrect, x + kiss_edge, y,
			hscrollbar->left.w + kiss_slider_padding,
			hscrollbar->left.h);
		kiss_makerect(&hscrollbar->rightrect, x + w - hscrollbar->right.w -
			kiss_slider_padding - kiss_edge, y,
			hscrollbar->right.w + kiss_slider_padding,
			hscrollbar->right.h);
		kiss_makerect(&hscrollbar->sliderrect, x + hscrollbar->leftrect.w +
			kiss_edge, y, hscrollbar->hslider.w, hscrollbar->hslider.h);
		hscrollbar->maxpos = w - 2 * kiss_slider_padding - 2 * kiss_edge -
			hscrollbar->left.w - hscrollbar->right.w -
			hscrollbar->hslider.w;
		hscrollbar->fraction = 0.;
		hscrollbar->step = 0.1;
		hscrollbar->leftclicked = 0;
		hscrollbar->rightclicked = 0;
		hscrollbar->sliderclicked = 0;
		hscrollbar->lasttick = 0;
		hscrollbar->visible = 0;
		hscrollbar->focus = 0;
		hscrollbar->wdw = wdw;
		return 0;
	}

	void myKissGUI::hnewpos(kiss_hscrollbar* hscrollbar, double step, int* draw)
	{
		*draw = 1;
		hscrollbar->fraction += step;
		hscrollbar->lasttick = SDL_GetTicks();
		if (hscrollbar->fraction < -0.000001) hscrollbar->fraction = 0.;
		if (hscrollbar->fraction > 0.999999) hscrollbar->fraction = 1.;
		hscrollbar->sliderrect.x = hscrollbar->leftrect.x +
			hscrollbar->leftrect.w + (int)(hscrollbar->fraction *
				hscrollbar->maxpos + 0.5);
		if (hscrollbar->fraction > 0.000001 &&
			hscrollbar->fraction < 0.999999)
			return;
		hscrollbar->leftclicked = 0;
		hscrollbar->rightclicked = 0;
	}

	int myKissGUI::kiss_hscrollbar_event(kiss_hscrollbar* hscrollbar, SDL_Event* event,
		int* draw)
	{
		if (!hscrollbar || !hscrollbar->visible) return 0;
		if (!(SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))) {
			hscrollbar->leftclicked = 0;
			hscrollbar->rightclicked = 0;
			hscrollbar->lasttick = 0;
		}
		else if (hscrollbar->leftclicked && SDL_GetTicks() >
			hscrollbar->lasttick + kiss_click_interval) {
			hnewpos(hscrollbar, -hscrollbar->step, draw);
			return 1;
		}
		else if (hscrollbar->rightclicked && SDL_GetTicks() >
			hscrollbar->lasttick + kiss_click_interval) {
			hnewpos(hscrollbar, hscrollbar->step, draw);
			return 1;
		}
		if (!event) return 0;
		if (event->type == SDL_WINDOWEVENT &&
			event->window.event == SDL_WINDOWEVENT_EXPOSED)
			*draw = 1;
		if (!hscrollbar->focus && (!hscrollbar->wdw ||
			(hscrollbar->wdw && !hscrollbar->wdw->focus)))
			return 0;
		if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&hscrollbar->leftrect)) {
			if (hscrollbar->fraction > 0.000001) {
				hscrollbar->leftclicked = 1;
				if (hscrollbar->wdw) hscrollbar->wdw->focus = 0;
				hscrollbar->focus = 1;
			}
			hscrollbar->lasttick = SDL_GetTicks() -
				kiss_click_interval - 1;
		}
		else if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&hscrollbar->rightrect) && hscrollbar->step > 0.000001) {
			if (hscrollbar->fraction < 0.999999) {
				hscrollbar->rightclicked = 1;
				if (hscrollbar->wdw) hscrollbar->wdw->focus = 0;
				hscrollbar->focus = 1;
			}
			hscrollbar->lasttick = SDL_GetTicks() -
				kiss_click_interval - 1;
		}
		else if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&hscrollbar->sliderrect) && hscrollbar->step > 0.000001) {
			if (hscrollbar->wdw) hscrollbar->wdw->focus = 0;
			hscrollbar->focus = 1;
			hscrollbar->sliderclicked = 1;
		}
		else if (event->type == SDL_MOUSEBUTTONUP) {
			hscrollbar->leftclicked = 0;
			hscrollbar->rightclicked = 0;
			hscrollbar->lasttick = 0;
			if (hscrollbar->wdw) hscrollbar->wdw->focus = 1;
			hscrollbar->focus = 0;
			hscrollbar->sliderclicked = 0;
		}
		else if (event->type == SDL_MOUSEMOTION &&
			(event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) &&
			hscrollbar->sliderclicked) {
			hnewpos(hscrollbar, 1. * event->motion.xrel /
				hscrollbar->maxpos, draw);
			return 1;
		}
		return 0;
	}

	int myKissGUI::kiss_hscrollbar_draw(kiss_hscrollbar* hscrollbar, SDL_Renderer* renderer)
	{
		if (hscrollbar && hscrollbar->wdw)
			hscrollbar->visible = hscrollbar->wdw->visible;
		if (!hscrollbar || !hscrollbar->visible || !renderer) return 0;
		hscrollbar->sliderrect.x = hscrollbar->leftrect.x +
			hscrollbar->leftrect.w + (int)(hscrollbar->fraction *
				hscrollbar->maxpos);
		kiss_renderimage(renderer, hscrollbar->left, hscrollbar->leftrect.x,
			hscrollbar->leftrect.y, NULL);
		kiss_renderimage(renderer, hscrollbar->right,
			hscrollbar->rightrect.x + kiss_slider_padding,
			hscrollbar->rightrect.y, NULL);
		kiss_renderimage(renderer, hscrollbar->hslider,
			hscrollbar->sliderrect.x, hscrollbar->sliderrect.y, NULL);
		return 1;
	}

	int myKissGUI::kiss_progressbar_new(kiss_progressbar* progressbar, kiss_window* wdw,
		int x, int y, int w)
	{
		if (!progressbar || w < 2 * kiss_border + 1) return -1;
		if (progressbar->bar.magic != KISS_MAGIC)
			progressbar->bar = kiss_bar;
		progressbar->bg = kiss_white;
		kiss_makerect(&progressbar->rect, x, y, w,
			progressbar->bar.h + 2 * kiss_border);
		kiss_makerect(&progressbar->barrect, x + kiss_border,
			y + kiss_border, 0, progressbar->bar.h);
		progressbar->width = w - 2 * kiss_border;
		progressbar->fraction = 0.;
		progressbar->step = 0.02;
		progressbar->lasttick = 0;
		progressbar->run = 0;
		progressbar->visible = 0;
		progressbar->wdw = wdw;
		return 0;
	}

	int myKissGUI::kiss_progressbar_event(kiss_progressbar* progressbar, SDL_Event* event,
		int* draw)
	{
		if (!progressbar || !progressbar->visible) return 0;
		if (progressbar->run && SDL_GetTicks() > progressbar->lasttick +
			kiss_progress_interval) {
			progressbar->fraction += progressbar->step;
			if (progressbar->fraction > 0.999999) {
				progressbar->run = 0;
				progressbar->fraction = 1.;
			}
			progressbar->lasttick = SDL_GetTicks();
			*draw = 1;
		}
		return 1;
	}

	int myKissGUI::kiss_progressbar_draw(kiss_progressbar* progressbar,
		SDL_Renderer* renderer)
	{
		SDL_Rect clip;

		if (progressbar && progressbar->wdw)
			progressbar->visible = progressbar->wdw->visible;
		if (!progressbar || !progressbar->visible || !renderer)
			return 0;
		kiss_fillrect(renderer, &progressbar->rect, progressbar->bg);
		kiss_decorate(renderer, &progressbar->rect, kiss_blue, kiss_edge);
		progressbar->barrect.w = (int)(progressbar->width *
			progressbar->fraction + 0.5);
		kiss_makerect(&clip, 0, 0, progressbar->barrect.w,
			progressbar->barrect.h);
		kiss_renderimage(renderer, progressbar->bar, progressbar->barrect.x,
			progressbar->barrect.y, &clip);
		return 1;
	}

	int myKissGUI::kiss_entry_new(kiss_entry* entry, kiss_window* wdw, int decorate,
		char* text, int x, int y, int w)
	{
		if (!entry || !text) return -1;
		if (entry->font.magic != KISS_MAGIC) entry->font = kiss_textfont;
		if (w < 2 * kiss_border + entry->font.advance) return -1;
		entry->bg = kiss_white;
		entry->normalcolor = kiss_black;
		entry->activecolor = kiss_blue;
		entry->textwidth = w - 2 * kiss_border;
		kiss_string_copy(entry->text, kiss_maxlength(entry->font,
			entry->textwidth, text, NULL), text, NULL);
		kiss_makerect(&entry->rect, x, y, w, entry->font.fontheight +
			2 * kiss_border);
		entry->decorate = decorate;
		entry->textx = x + kiss_border;
		entry->texty = y + kiss_border;
		entry->active = 0;
		entry->visible = 0;
		entry->focus = 0;
		entry->wdw = wdw;
		return 0;
	}

	int myKissGUI::kiss_entry_event(kiss_entry* entry, SDL_Event* event, int* draw)
	{
		if (!entry || !entry->visible || !event) return 0;
		if (event->type == SDL_WINDOWEVENT &&
			event->window.event == SDL_WINDOWEVENT_EXPOSED)
			*draw = 1;
		if (!entry->focus && (!entry->wdw ||
			(entry->wdw && !entry->wdw->focus)))
			return 0;
		if (event->type == SDL_MOUSEBUTTONDOWN && !entry->active &&
			kiss_pointinrect(event->button.x, event->button.y,
				&entry->rect)) {
			entry->active = 1;
			if (entry->wdw) entry->wdw->focus = 0;
			entry->focus = 1;
			*draw = 1;
		}
		else if (event->type == SDL_KEYDOWN && entry->active &&
			event->key.keysym.scancode == SDL_SCANCODE_RETURN) {
			entry->active = 0;
			if (entry->wdw) entry->wdw->focus = 1;
			entry->focus = 0;
			*draw = 1;
			return 1;
		}
		else if (event->type == SDL_TEXTINPUT && entry->active) {
			if (kiss_textwidth(entry->font, entry->text,
				event->text.text) < entry->textwidth &&
				strlen(entry->text) + strlen(event->text.text) <
				KISS_MAX_LENGTH)
				strcat(entry->text, event->text.text);
			*draw = 1;
		}
		else if (event->type == SDL_KEYDOWN && entry->active &&
			event->key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
			kiss_backspace(entry->text);
			*draw = 1;
		}
		else if (event->type == SDL_KEYDOWN && entry->active &&
			(event->key.keysym.mod & KMOD_CTRL) &&
			event->key.keysym.scancode == SDL_SCANCODE_U) {
			strcpy(entry->text, "");
			*draw = 1;
		}
		//so we can past filepaths
		else if (event->key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL && entry->active) {
			if (kiss_textwidth(entry->font, entry->text,
				event->text.text) < entry->textwidth &&
				strlen(entry->text) + strlen(event->text.text) <
				KISS_MAX_LENGTH)
				strcpy(entry->text, SDL_GetClipboardText());
			*draw = 1;
		}
		return 0;
	}

	int myKissGUI::kiss_entry_draw(kiss_entry* entry, SDL_Renderer* renderer)
	{
		SDL_Color color;

		if (entry && entry->wdw) entry->visible = entry->wdw->visible;
		if (!entry || !entry->visible || !renderer) return 0;
		kiss_fillrect(renderer, &entry->rect, entry->bg);
		color = kiss_blue;
		if (entry->active) color = kiss_green;
		if (entry->decorate)
			kiss_decorate(renderer, &entry->rect, color, kiss_edge);
		color = entry->normalcolor;
		if (entry->active) color = entry->activecolor;
		kiss_rendertext(renderer, entry->text, entry->textx, entry->texty,
			entry->font, color);
		return 1;
	}

	int myKissGUI::kiss_textbox_new(kiss_textbox* textbox, kiss_window* wdw, int decorate,
		kiss_array* a, int x, int y, int w, int h)
	{
		if (!textbox || !a) return -1;
		if (textbox->font.magic != KISS_MAGIC) textbox->font = kiss_textfont;
		if (h - 2 * kiss_border < textbox->font.lineheight) return -1;
		textbox->bg = kiss_white;
		textbox->textcolor = kiss_black;
		textbox->hlcolor = kiss_lightblue;
		kiss_makerect(&textbox->rect, x, y, w, h);
		kiss_makerect(&textbox->textrect, x + kiss_border,
			y + kiss_border, w - 2 * kiss_border, h - 2 * kiss_border);
		textbox->decorate = decorate;
		textbox->array = a;
		textbox->firstline = 0;
		textbox->maxlines = (h - 2 * kiss_border) / textbox->font.lineheight;
		textbox->textwidth = w - 2 * kiss_border;
		textbox->highlightline = -1;
		textbox->selectedline = -1;
		textbox->visible = 0;
		textbox->focus = 0;
		textbox->wdw = wdw;
		return 0;
	}

	int myKissGUI::textbox_numoflines(kiss_textbox* textbox)
	{
		int numoflines;

		numoflines = textbox->maxlines;
		if (textbox->array->length - textbox->firstline < textbox->maxlines)
			numoflines = textbox->array->length - textbox->firstline;
		return numoflines;
	}

	int myKissGUI::kiss_textbox_event(kiss_textbox* textbox, SDL_Event* event, int* draw)
	{
		int texty, textmaxy, numoflines;

		if (!textbox || !textbox->visible || !event || !textbox->array ||
			!textbox->array->length)
			return 0;
		if (event->type == SDL_WINDOWEVENT &&
			event->window.event == SDL_WINDOWEVENT_EXPOSED)
			*draw = 1;
		if (!textbox->focus && (!textbox->wdw ||
			(textbox->wdw && !textbox->wdw->focus)))
			return 0;
		if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&textbox->textrect)) {
			numoflines = textbox_numoflines(textbox);
			texty = event->button.y - textbox->textrect.y;
			textmaxy = numoflines * textbox->font.lineheight;
			if (texty < textmaxy) {
				textbox->selectedline =
					texty / textbox->font.lineheight;
				return 1;
			}
		}
		else if (event->type == SDL_MOUSEMOTION &&
			kiss_pointinrect(event->motion.x, event->motion.y,
				&textbox->textrect)) {
			numoflines = textbox_numoflines(textbox);
			texty = event->motion.y - textbox->textrect.y;
			textmaxy = numoflines * textbox->font.lineheight;
			textbox->highlightline = -1;
			if (texty < textmaxy)
				textbox->highlightline =
				texty / textbox->font.lineheight;
			*draw = 1;
		}
		else if (event->type == SDL_MOUSEMOTION &&
			!kiss_pointinrect(event->motion.x, event->motion.y,
				&textbox->textrect)) {
			textbox->highlightline = -1;
			*draw = 1;
		}
		return 0;
	}

	int myKissGUI::kiss_textbox_draw(kiss_textbox* textbox, SDL_Renderer* renderer)
	{
		SDL_Rect highlightrect;
		char buf[KISS_MAX_LENGTH];
		int numoflines, i;

		if (textbox && textbox->wdw)
			textbox->visible = textbox->wdw->visible;
		if (!textbox || !textbox->visible || !renderer) return 0;
		kiss_fillrect(renderer, &textbox->rect, textbox->bg);
		if (textbox->decorate)
			kiss_decorate(renderer, &textbox->rect, kiss_blue,
				kiss_edge);
		if (textbox->highlightline >= 0) {
			kiss_makerect(&highlightrect, textbox->textrect.x,
				textbox->textrect.y +
				textbox->highlightline * textbox->font.lineheight,
				textbox->textrect.w, textbox->font.lineheight);
			kiss_fillrect(renderer, &highlightrect, textbox->hlcolor);
		}
		if (!textbox->array || !textbox->array->length) return 0;
		numoflines = textbox_numoflines(textbox);
		for (i = 0; i < numoflines; i++) {
			kiss_string_copy(buf, kiss_maxlength(textbox->font,
				textbox->textwidth,
				(char*)kiss_array_data(textbox->array,
					textbox->firstline + i), NULL),
				(char*)kiss_array_data(textbox->array,
					textbox->firstline + i), NULL);
			kiss_rendertext(renderer, buf, textbox->textrect.x,
				textbox->textrect.y + i * textbox->font.lineheight +
				textbox->font.spacing / 2, textbox->font,
				textbox->textcolor);
		}
		return 1;
	}

	int myKissGUI::kiss_combobox_new(kiss_combobox* combobox, kiss_window* wdw,
		char* text, kiss_array* a, int x, int y, int w, int h)
	{
		if (!combobox || !a || !text) return -1;
		if (combobox->combo.magic != KISS_MAGIC)
			combobox->combo = kiss_combo;
		kiss_entry_new(&combobox->entry, wdw, 1, text, x, y, w);
		strcpy(combobox->text, combobox->entry.text);
		kiss_window_new(&combobox->window, NULL, 0, x,
			y + combobox->entry.rect.h, w +
			combobox->vscrollbar.up.w, h);
		if (kiss_textbox_new(&combobox->textbox, &combobox->window, 1,
			a, x, y + combobox->entry.rect.h, w, h) == -1)
			return -1;
		if (kiss_vscrollbar_new(&combobox->vscrollbar, &combobox->window,
			x + combobox->textbox.rect.w, combobox->textbox.rect.y,
			combobox->textbox.rect.h) == -1)
			return -1;
		combobox->visible = 0;
		combobox->wdw = wdw;
		combobox->vscrollbar.step = 0.;
		if (combobox->textbox.array->length - combobox->textbox.maxlines > 0)
			combobox->vscrollbar.step = 1. /
			(combobox->textbox.array->length -
				combobox->textbox.maxlines);
		return 0;
	}

	int myKissGUI::kiss_combobox_event(kiss_combobox* combobox, SDL_Event* event, int* draw)
	{
		int firstline, index;

		if (!combobox || !combobox->visible) return 0;
		if (kiss_vscrollbar_event(&combobox->vscrollbar, event,
			draw) && combobox->textbox.array->length -
			combobox->textbox.maxlines >= 0) {
			combobox->vscrollbar.step = 0.;
			if (combobox->textbox.array->length -
				combobox->textbox.maxlines > 0)
				combobox->vscrollbar.step = 1. /
				(combobox->textbox.array->length -
					combobox->textbox.maxlines);
			firstline = (int)((combobox->textbox.array->length -
				combobox->textbox.maxlines) *
				combobox->vscrollbar.fraction + 0.5);
			if (firstline >= 0) combobox->textbox.firstline = firstline;
			*draw = 1;
		}
		if (!event) return 0;
		if (event->type == SDL_WINDOWEVENT &&
			event->window.event == SDL_WINDOWEVENT_EXPOSED)
			*draw = 1;
		if (event->type == SDL_MOUSEBUTTONDOWN &&
			kiss_pointinrect(event->button.x, event->button.y,
				&combobox->entry.rect)) {
			combobox->window.visible = 1;
			*draw = 1;
		}
		if (kiss_entry_event(&combobox->entry, event, draw)) {
			combobox->window.visible = 0;
			strcpy(combobox->text, combobox->entry.text);
			*draw = 1;
			return 1;
		}
		else if (kiss_textbox_event(&combobox->textbox, event, draw)) {
			combobox->window.visible = 0;
			combobox->entry.active = 0;
			if (combobox->entry.wdw) combobox->entry.wdw->focus = 1;
			combobox->entry.focus = 0;
			index = combobox->textbox.firstline +
				combobox->textbox.selectedline;
			kiss_string_copy(combobox->entry.text,
				kiss_maxlength(combobox->textbox.font,
					combobox->entry.textwidth,
					(char*)kiss_array_data(combobox->textbox.array,
						index), NULL),
				(char*)kiss_array_data(combobox->textbox.array,
					index), NULL);
			*draw = 1;
			return 1;
		}
		return 0;
	}

	int myKissGUI::kiss_combobox_draw(kiss_combobox* combobox, SDL_Renderer* renderer)
	{
		if (combobox && combobox->wdw)
			combobox->visible = combobox->wdw->visible;
		if (!combobox || !combobox->visible || !renderer) return 0;
		kiss_renderimage(renderer, combobox->combo,
			combobox->entry.rect.x + combobox->entry.rect.w,
			combobox->entry.rect.y + combobox->entry.rect.h -
			combobox->combo.h - kiss_edge, NULL);
		kiss_entry_draw(&combobox->entry, renderer);
		kiss_window_draw(&combobox->window, renderer);
		kiss_vscrollbar_draw(&combobox->vscrollbar, renderer);
		kiss_textbox_draw(&combobox->textbox, renderer);
		return 1;
	}