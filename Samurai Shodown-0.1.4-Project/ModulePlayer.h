#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#define JUMPINGFRAMES 24
#define JUMP_INIT_VY 19.09 //initial velocity on the Y coord. //16.2
#define JUMP_INIT_AY 0.867 //initial acceleration on the Y coord. //0.867

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

public:
	Collider* body = nullptr;
	SDL_Texture* graphics = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation jump;
	Animation kick;
	Animation punch;
	Animation tornado;
	Animation hurtLow;
	iPoint position;
	bool jumping = false;
	bool doingAction = false;
	bool punching = false;
	bool kicking = false;
	bool tornading = false;
	int jumpingframe = 0;
	int groundlevelaux = 0;
	bool getsHit = false;
	bool hasjumped = false;
	char sAction;
	bool godMode = false;


	bool playerFlip = false;

};

#endif