#ifndef __MODULEATTACK_H__
#define __MODULEATTACK_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_ATTACKS 10

struct Collider;

struct Attack
{
	Collider* collider = nullptr;
	COLLIDER_TYPE collider_type = COLLIDER_NONE;
	uint fx = 0;
	iPoint position;
	float born = 0;
	float life = 0;
	float delay = 0;
	bool fx_played = false;
	SDL_Rect hitbox;


	Attack();
	~Attack();
	bool Update();
};

class ModuleAttack : public Module
{
public:
	ModuleAttack();
	~ModuleAttack();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	void addAttack(SDL_Rect hitbox, COLLIDER_TYPE collider_type = COLLIDER_NONE, float attackFrames = 0, float delayFrames = 0);
	void printHitbox(Attack* const attack);

private:

	Attack* active[MAX_ACTIVE_ATTACKS];

};

#endif // __MODULEATTACK_H__
