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
	SDL_Rect background;

	Animation backgroundanim;
};

#endif // __MODULESCENECONGRATZ_H__
