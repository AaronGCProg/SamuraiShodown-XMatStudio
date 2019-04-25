#ifndef __MODULEINTERFACE_H__
#define __MODULEINTERFACE_H__

#include "Module.h"
#include "Globals.h"


class ModuleInterface : public Module
{
public:
	ModuleInterface();
	~ModuleInterface();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* ui = nullptr;
	SDL_Rect ko = { 33, 66, 28, 22 };
	SDL_Rect pow = { 33, 53, 16, 11 };
	SDL_Rect powbar = { 225, 65, 65, 9 };



	//text vars

	int font_time = -1;
	int font_name = -1;
	char time_text[10];
	int startingtime = 0;
	int actualtime = 0;
	bool roundfinish = false;


};

#endif // __MODULEINTERFACE_H__