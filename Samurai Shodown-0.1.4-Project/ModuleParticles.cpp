#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Assets/Sprites/haohmaru.png");

	// Tornado
	tornadoHao.anim.PushBack({ 919, 171, 48, 77 });
	tornadoHao.anim.PushBack({ 919, 171, 48, 77 });
	tornadoHao.anim.PushBack({ 968, 171, 49, 77 });
	tornadoHao.anim.PushBack({ 968, 171, 49, 77 });
	tornadoHao.anim.PushBack({ 1015, 174, 83, 77 });
	tornadoHao.anim.PushBack({ 1099, 174, 95, 77 });
	tornadoHao.anim.PushBack({ 1192, 179, 94, 71 });
	tornadoHao.anim.PushBack({ 1285, 183, 96, 67 });
	tornadoHao.anim.PushBack({ 1379, 190, 95, 62 });
	tornadoHao.anim.PushBack({ 1473, 191, 90, 58 });
	tornadoHao.anim.PushBack({ 1563, 191, 89, 58 });
	tornadoHao.anim.PushBack({ 1650, 183, 85, 65 });
	tornadoHao.anim.PushBack({ 1733, 178, 57, 72 });
	tornadoHao.anim.PushBack({ 1790, 174, 48, 75 });
	tornadoHao.anim.PushBack({ 1840, 174, 48, 75 });
	tornadoHao.anim.PushBack({ 1889, 172, 71, 77 });
	tornadoHao.anim.PushBack({ 1958, 172, 71, 77 });
	tornadoHao.anim.PushBack({ 956, 263, 83, 77 });
	tornadoHao.anim.loop = true;
	tornadoHao.anim.speed = 0.2f;
	tornadoHao.speed.x = 3;
	tornadoHao.life = 6000;
	tornadoHao.anim.firstLoopFrame = 2.0f;


	//Tornado Impact
	tornadoHaoImpact.anim.PushBack({ 1038, 264, 52, 178 });
	tornadoHaoImpact.anim.PushBack({ 1089, 264, 60, 178 });
	tornadoHaoImpact.anim.PushBack({ 1154, 264, 49, 178 });
	tornadoHaoImpact.anim.PushBack({ 1089, 264, 60, 178 }); //Flip
	tornadoHaoImpact.anim.PushBack({ 1154, 264, 49, 178 }); //Flip

	tornadoHaoImpact.anim.loop = true;
	tornadoHaoImpact.anim.speed = 0.3f;
	tornadoHaoImpact.life = 2000;
	tornadoHaoImpact.anim.firstLoopFrame = 1.0f;



	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
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
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, false, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				// Play particle fx here
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			AddParticle(tornadoHaoImpact, active[i]->position.x, active[i]->position.y-101, COLLIDER_NONE);
			delete active[i];
			active[i] = nullptr;
			break;

		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}


bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}