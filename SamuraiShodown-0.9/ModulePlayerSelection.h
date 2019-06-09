#ifndef __MODULEPLAYERSELECTION_H__
#define __MODULEPLAYERSELECTION_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModulePlayerSelection : public Module
{
public:

	ModulePlayerSelection();
	~ModulePlayerSelection();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	
	struct Delay
	{
	bool countingdelay = false;
	int delayleft = 0;
	bool CountDelayInFrames(int delayframes);
	};

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* ui = nullptr;
	SDL_Rect background;
	SDL_Rect p1p2selector;
	SDL_Rect p1p2selectorwhite;
	SDL_Rect jubeiword;
	SDL_Rect japanword;

	Animation backgroundanim;

	Delay Timerend;
	Delay Timerendquick;
	Delay Timerselect;
	Delay Timerwiggle;

	bool showingp1p2 = false;
	bool selected1 = false;
	bool selected2 = false;
};





#endif // __MODULEPLAYERSELECTION_H__
