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
	SDL_Texture* ui2 = nullptr;
	SDL_Rect background;
	SDL_Rect p1p2selector;
	SDL_Rect p1p2selectorwhite;
	SDL_Rect jubeiword;
	SDL_Rect jubeiwordwhite;
	SDL_Rect japanword;
	SDL_Rect japanwordwhite;

	Animation backgroundanim;

	Delay Timerend;
	Delay Timerendquick;
	Delay Timerselect;
	Delay Timerwiggle;
	Delay Timerwhite1;
	Delay Timerwhite2;

	bool showingp1p2 = false;
	bool selected1 = false;
	bool selected2 = false;
	bool textwhite1 = false;
	bool textwhite2 = false;

	bool gowhite1 = false;
	bool gowhite2 = false;

};





#endif // __MODULEPLAYERSELECTION_H__
