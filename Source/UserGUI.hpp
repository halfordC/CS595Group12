#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include "myKissGui.hpp"
#include "midiModule.h"
#include "RenderWindow.hpp"
#include "Scene.h"

class UserGUI
{
public:
	UserGUI(char* p_title, MidiModule* myMidiModule);
	void render();
	void cleanUp();
	std::vector<Scene*> getCurrentSceneArray();
	void guiEvent(SDL_Event* e, MidiModule* myMidiModule, RenderWindow *myRenderWindow, SDL_Renderer* renderer);
	void selectMidiDropdownEvent(SDL_Event* e, MidiModule * myMidiModule);
	void addBindingEvent(SDL_Event* e);
	void removeBindingEvent(SDL_Event* e);

	void addSceneEvent(SDL_Event* e);
	void sceneTabEvent(SDL_Event* e);
	void scrollEvent(SDL_Event* e);
	void startEvent(SDL_Event* e, RenderWindow* myRenderWindow);


	std::filesystem::path selectedDirectory;
	myKissGUI* kissGUI;
	kiss_window window;
	
	kiss_array objects;
	kiss_button addScene;
	kiss_button addBinding;
	kiss_button removeBinding;
	kiss_combobox midiDeviceDrop;
	char message[KISS_MAX_LENGTH];
	kiss_label label;
	kiss_array connectedMidiDevices; //This will need to be changed as devices are connected and disconnected.
	kiss_array midiParamList;
	kiss_array imageParamList;

	kiss_button startButton;
	kiss_array path;
	kiss_textbox filePath;
	kiss_button browsePath;
	kiss_button midiLearn;
	kiss_entry filePathEntry;

	std::vector<Scene*> sceneArray; //max of 15 scenes. If we can can't make Horizontal scroll tabs, we'll just make 3. 
	kiss_tab sceneTab[15];
	kiss_tab plusTab;
	


	kiss_upbutton scrollUp;
	kiss_downbutton scrollDown;
	int sceneIndex;

	int addSceneFlag; //This is 1 when a new scene has been added, and translator must be updated. 

private:
	SDL_Renderer* renderer;
	SDL_Event e;
	int listenFilter;
	int addSceneIndex;
	int currentSceneTab;
	int addSceneTabIndex;
	int currentSceneTabX;
	int staticSceneTabY;
};