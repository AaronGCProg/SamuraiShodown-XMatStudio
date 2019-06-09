#ifndef __MODULESCENECONGRATZ_H__
#define __MODULESCENECONGRATZ_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleSceneCongrats : public Module
{
public:
	ModuleSceneCongrats();
	~ModuleSceneCongrats();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;

	SDL_Rect background = { 1, 1, 305, 225 };
	SDL_Rect jubei = { 306, 1, 141, 164 };
	SDL_Rect loser = { 340, 168, 85, 72 };

	SDL_Rect jubeiAux;
	SDL_Rect loserAux;

	int startingtime = 0;
	int moving = 0;;
};

#endif // __MODULESCENECONGRATZ_H__
