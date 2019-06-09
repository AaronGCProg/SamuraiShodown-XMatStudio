#ifndef __MODULENEO_H__
#define __MODULENEO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleNEO : public Module
{
public:
	ModuleNEO();
	~ModuleNEO();

	bool Start();
	update_status Update();
	bool CleanUp();
	float position = SCREEN_HEIGHT;
	float positionx = SCREEN_WIDTH / 2;
	float positiony = SCREEN_HEIGHT / 2.5;

	int r = 225;
	int g = 225;
	int b = 225;

	int countX = 0;
	int countY = 0;
	int count = 0;

	bool neoEnd = false;
	bool xmatEnd = false;
public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect neo;
	SDL_Rect xmat;
	SDL_Rect neoAux;
	SDL_Rect background;

	Animation NEO;
	Animation Xmat;
};

#endif // __MODULESCENEWELC_H__

