#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleAttack.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleAttack::ModuleAttack()
{
	for (uint i = 0; i < MAX_ACTIVE_ATTACKS; ++i)
		active[i] = nullptr;
}

ModuleAttack::~ModuleAttack()
{}

bool ModuleAttack::Start()
{
	LOG("ModuleAttack Start!");
	return true;
}

bool ModuleAttack::CleanUp()
{
	LOG("Unloading Attacks");

	for (uint i = 0; i < MAX_ACTIVE_ATTACKS; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleAttack::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_ATTACKS; ++i)
	{
		Attack* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;

		}
		else if (SDL_GetTicks() >= p->born)
		{
			
			if (p->fx_played == false)
			{
				// Play particle fx here
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleAttack::addAttack(SDL_Rect hitbox, COLLIDER_TYPE collider_type, float attackFrames, float delay)
{
	for (uint i = 0; i < MAX_ACTIVE_ATTACKS; ++i)
	{
		if (active[i] == nullptr)
		{
			Attack* p = new Attack();
			p->born = (SDL_GetTicks());
			p->position.x = hitbox.x;
			p->position.y = hitbox.y;
			p->hitbox = hitbox;
			p->delay = (delay / 60) * 1000;
			p->life = ((attackFrames / 60) * 1000)+delay;
			p->collider_type = collider_type;
			active[i] = p;
			break;
		}
	}
}

void ModuleAttack::printHitbox(Attack * const attack) {

	attack->collider = App->collision->AddCollider(attack->hitbox, attack->collider_type, this);


}

void ModuleAttack::OnCollision(Collider* c1, Collider* c2)
{
	//Here goes the "less frames" system when you hit an enemy
	
	for (uint i = 0; i < MAX_ACTIVE_ATTACKS; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			delete active[i];
			active[i] = nullptr;
			break;

		}
	}
	
	
}
// -------------------------------------------------------------
// -------------------------------------------------------------

Attack::Attack()
{
	position.SetToZero();
}


Attack::~Attack()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Attack::Update()
{
	if (collider == nullptr && SDL_GetTicks()  - born > delay)
		App->attack->printHitbox(this);


	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}