#ifndef __ModuleReferee_H__
#define __ModuleReferee_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2Qeue.h"

struct SDL_Texture;
struct collider;

class ModuleReferee : public Module
{
public:
	ModuleReferee();
	~ModuleReferee();

	bool Start();
	update_status Update();
	bool CleanUp();


public:
	
	SDL_Texture* graphics = nullptr;
	SDL_Texture* ui = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation redFlag;
	Animation whiteFlag;
	iPoint position;
	Animation* current_animation;

	bool playerFlip = false;
	
}; 

#endif
