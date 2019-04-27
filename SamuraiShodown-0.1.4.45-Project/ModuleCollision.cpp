#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleCollision::ModuleCollision()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_ATTACK] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_ATTACK] = true;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_ATTACK] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_ATTACK] = false;

	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_ATTACK] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_ATTACK] = false;

	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_PLAYER_SHOT] = false; 
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_ENEMY_SHOT] = false; //there must be another collider type for the attacks that pierce shots
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_ENEMY_ATTACK] = false; //sword fight -> change to true
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_PLAYER_ATTACK] = false;


	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_PLAYER_SHOT] = false; //there must be another collider type for the attacks that pierce shots
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_ENEMY_SHOT] = false; 
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_ENEMY_ATTACK] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_PLAYER_ATTACK] = false; //sword fight -> change to true
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];

			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleCollision::Update()
{

	DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	if (App->input->keys[SDL_SCANCODE_F1] == KEY_STATE::KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;

	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;
		//case COLLIDER_WALL: // blue
			//App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			//break;
		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_PLAYER_ATTACK: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;
		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;
		case COLLIDER_ENEMY_ATTACK: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;

		}
	}
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	// TODO 0: Return true if there is an overlap
	return !((this->rect.x + this->rect.w < r.x || r.x + r.w < this->rect.x) ||  (this->rect.y + this->rect.h < r.y || r.y + r.h < this->rect.y));
}