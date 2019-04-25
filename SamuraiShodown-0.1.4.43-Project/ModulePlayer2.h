#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#define JUMPINGFRAMES 60
#define JUMP_INIT_VY 14 //initial velocity on the Y coord. //16.2
#define JUMP_INIT_AY 0.46666666666 //initial acceleration on the Y coord. //0.867

#define JUMP_TIME 3000
#define PUNCH_TIME 1000

#define HEALTH_VALUE 259



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

	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture * graphics = nullptr;
	SDL_Texture* ui = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation jump;
	Animation kick;
	Animation punch;
	Animation hurtLow;
	Animation tornado;
	iPoint position;
	Collider* body = nullptr;
	bool jumping = false;
	bool doingAction = false;
	bool punching = false;
	bool kicking = false;
	int jumpingframe = 0;
	int groundlevelaux = 0;
	bool tornading = false;
	bool hasjumped = false;
	bool getsHit = false;
	char sAction;

	bool playerFlip = false;
	int health = 100;
};

#endif
