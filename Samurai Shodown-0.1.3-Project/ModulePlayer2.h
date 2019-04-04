#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#define JUMPINGFRAMES 24
#define JUMP_INIT_VY 19.09 //initial velocity on the Y coord. //16.2
#define JUMP_INIT_AY 0.867 //initial acceleration on the Y coord. //0.867

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture * graphics = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation jump;
	Animation kick;
	Animation punch;
	iPoint position;
	bool jumping = false;
	bool doingAction = false;
	bool punching = false;
	bool kicking = false;
	int jumpingframe = 0;
	int groundlevelaux = 0;
	bool hasjumped = false;
	char sAction;

	bool playerFlip = false;
};

#endif
