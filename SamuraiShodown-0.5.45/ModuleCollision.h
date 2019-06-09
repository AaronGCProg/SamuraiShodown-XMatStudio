#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 50

#include "Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_PLAYER_ATTACK,
	COLLIDER_ENEMY_ATTACK,
	COLLIDER_GRAB,


	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback = nullptr;
	int damage = NULL;
	int delayPlayer = NULL; // We'll use this to set the player animation delay when he doesn't land a hit, as well for the player knockback when the attack is landed.
	int delayEnemy = NULL;	//Same as above
	int attackType = NULL; //We'll use this to set the attack type: punch, slash, kick... To set the sound effects & particles

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, int damage, int delayPlayer, int delayEnemy, int attackType, Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		damage(damage),
		delayPlayer(delayPlayer),
		delayEnemy(delayEnemy),
		attackType(attackType),
		callback(callback)
	{}
	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	void setType(COLLIDER_TYPE type1)
	{
		type = type1;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate() override;
	update_status Update() override;
	update_status PostUpdate() override;
	bool CleanUp() override;

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, int damage = 0, int delayPlayer = 0, int delayEnemy = 0, int attackType = 0, Module* callback = nullptr);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = false;
};

#endif // __ModuleCollision_H__