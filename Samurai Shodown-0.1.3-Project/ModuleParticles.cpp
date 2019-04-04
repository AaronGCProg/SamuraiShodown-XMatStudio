#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

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

	/* Explosion particle
	explosion.anim.PushBack({ 274, 296, 33, 30 });
	explosion.anim.PushBack({ 313, 296, 33, 30 });
	explosion.anim.PushBack({ 346, 296, 33, 30 });
	explosion.anim.PushBack({ 382, 296, 33, 30 });
	explosion.anim.PushBack({ 419, 296, 33, 30 });
	explosion.anim.PushBack({ 457, 296, 33, 30 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f */

	/* TODO 2: Create the template for a new particle "laser"
	laser.anim.PushBack({ 200, 121, 32, 10 });
	laser.anim.PushBack({ 233, 120, 32, 12 });
	laser.anim.loop = true;
	laser.anim.speed = 0.3f;
	laser.speed.x = 3;
	laser.life = 5000;*/

	// Tornado
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
	tornadoHao.anim.speed = 0.3f;
	tornadoHao.speed.x = 3;
	tornadoHao.life = 6000;


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
				p->fx_played = true;
				// Play particle fx here
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

	active[last_particle++] = p;
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

	return ret;
}