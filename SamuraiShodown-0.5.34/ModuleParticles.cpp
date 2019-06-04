#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
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
	//graphics = App->textures->Load("Assets/Sprites/jubei.png");

	// Tornado
	/*
	tornadoHao.anim.PushBack({ 919, 171, 48, 77 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 919, 171, 48, 77 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 968, 171, 49, 77 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 968, 171, 49, 77 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1015, 174, 83, 77 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1099, 174, 95, 77 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1192, 179, 94, 71 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1285, 183, 96, 67 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1379, 190, 95, 62 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1473, 191, 90, 58 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1563, 191, 89, 58 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1650, 183, 85, 65 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1733, 178, 57, 72 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1790, 174, 48, 75 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1840, 174, 48, 75 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1889, 172, 71, 77 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 1958, 172, 71, 77 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.PushBack({ 956, 263, 83, 77 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {});
	tornadoHao.anim.loop = true;
	tornadoHao.anim.speed = 0.2f;
	tornadoHao.speed.x = 3;
	tornadoHao.life = 6000;
	tornadoHao.anim.firstLoopFrame = 2.0f;
	*/

	tornadoHao.anim.PushBack({ 1012, 1740, 75, 39 }, 4, { 31,2 }, 0, {}, {}, {},0,0,0,0);
	tornadoHao.anim.PushBack({ 1094, 1740, 75, 39 }, 2, { 31,2 }, 0, {}, {}, {}, 0, 0, 0, 0);

	tornadoHao.anim.loop = true;
	tornadoHao.anim.speed = 0.2f;
	tornadoHao.speed.x = 3;
	tornadoHao.life = 6000;

	//Tornado Impact
	tornadoHaoImpact.anim.PushBack({ 1283, 1769, 34, 18 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	tornadoHaoImpact.anim.PushBack({ 1251, 1769, 33, 17 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	tornadoHaoImpact.anim.PushBack({ 1316, 1769, 33, 17 }, FRAMEDEPRUEBA, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);

	tornadoHaoImpact.anim.loop = true;
	tornadoHaoImpact.anim.speed = 0.3f;
	tornadoHaoImpact.life = 2000;
	tornadoHaoImpact.anim.firstLoopFrame = 1.0f;

	//low blood
	bloodLow.anim.PushBack({ 1336, 1412, 95, 46 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodLow.anim.PushBack({ 1432, 1411, 95, 46 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodLow.anim.PushBack({ 1526, 1411, 73, 51 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodLow.anim.PushBack({ 1600, 1410, 70, 45 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodLow.anim.PushBack({ 1668, 1411, 43, 32 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodLow.anim.loop = false;
	bloodLow.anim.speed = 0.8f;
	bloodLow.life = 325;

	bloodMid.anim.PushBack({ 1194, 1496, 36, 24 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodMid.anim.PushBack({ 1231, 1496, 48, 46 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodMid.anim.PushBack({ 1280, 1496, 51, 43 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodMid.anim.PushBack({ 1336, 1496, 42, 38 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodMid.anim.PushBack({ 1370, 1495, 23, 20 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodMid.anim.PushBack({ 1397, 1496, 20, 22 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodMid.anim.loop = false;
	bloodMid.anim.speed = 0.8f;
	bloodMid.life = 325;

	bloodHard.anim.PushBack({ 1799, 1394, 58, 32 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodHard.anim.PushBack({ 1858, 1394, 92, 54 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodHard.anim.PushBack({ 1951, 1394, 136, 62 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodHard.anim.PushBack({ 2089, 1388, 137, 76 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodHard.anim.PushBack({ 2257, 1371, 146, 64 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodHard.anim.PushBack({ 2405, 1371, 120, 42 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodHard.anim.PushBack({ 2531, 1379, 114, 24 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	bloodHard.anim.loop = false;
	bloodHard.anim.speed = 0.8f;
	bloodHard.life = 325;


	slash.anim.PushBack({ 1673, 1512, 45, 53 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	slash.anim.PushBack({ 1594, 1513, 54, 54 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	slash.anim.PushBack({ 1520, 1512, 53, 58 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	slash.anim.PushBack({ 1454, 1523, 42, 53 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);

	slash.anim.loop = false;
	slash.anim.speed = 0.8f;
	slash.life = 275;

	kick.anim.PushBack({ 1758, 2208, 26, 26 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	kick.anim.PushBack({ 1826, 2207, 28, 28 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	kick.anim.PushBack({ 1906, 2205, 30, 30 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	kick.anim.PushBack({ 1966, 2205, 30, 30 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);

	kick.anim.loop = false;
	kick.anim.speed = 0.8f;
	kick.life = 275;

	groundHit.anim.PushBack({ 1439, 1631, 23, 24 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	groundHit.anim.PushBack({ 1463, 1629, 26, 26 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	groundHit.anim.PushBack({ 1490, 1626, 28, 29 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	groundHit.anim.PushBack({ 1518, 1622, 34, 33 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	groundHit.anim.PushBack({ 1552, 1622, 36, 35 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	groundHit.anim.PushBack({ 1589, 1622, 38, 38 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);

	groundHit.anim.loop = false;
	groundHit.anim.speed = 0.8f;
	groundHit.life = 325;

	blocking.anim.PushBack({ 1634, 1918, 11, 11 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	blocking.anim.PushBack({ 1649, 1917, 16, 16 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	blocking.anim.PushBack({ 1670, 1914, 20, 20 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	blocking.anim.PushBack({ 1698, 1913, 22, 22 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	
	blocking.anim.loop = false;
	blocking.anim.speed = 0.8f;
	blocking.life = 275;

	swordFight.anim.PushBack({ 2164, 2048, 16, 16 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	swordFight.anim.PushBack({ 2187, 2045, 26, 21 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	swordFight.anim.PushBack({ 2221, 2031, 46, 32 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	swordFight.anim.PushBack({ 2284, 2050, 17, 16 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	swordFight.anim.PushBack({ 2308, 2045, 26, 21 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	swordFight.anim.PushBack({ 2350, 2048, 16, 16 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	swordFight.anim.PushBack({ 2378, 2041, 32, 26 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);

	swordFight.anim.loop = true;
	swordFight.anim.speed = 0.8f;
	swordFight.life = 650;

	swordFightEnd.anim.PushBack({ 2163, 2096, 48, 56 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	swordFightEnd.anim.PushBack({ 2238, 2249, 23, 23 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	swordFightEnd.anim.PushBack({ 2163, 2096, 48, 56 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	swordFightEnd.anim.PushBack({ 2360, 2097, 47, 59 }, 3, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);

	swordFightEnd.anim.loop = true;
	swordFightEnd.anim.speed = 0.8f;
	swordFightEnd.life = 300;

	spark.anim.PushBack({ 1947, 1908, 30, 32 }, 1, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	spark.anim.PushBack({ 2065, 1904, 48, 49 }, 1, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	spark.anim.PushBack({ 2456, 1911, 100, 99 },1, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	spark.anim.PushBack({ 2570, 1910, 75, 91 }, 1, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	spark.anim.PushBack({ 2663, 1910, 59, 91 }, 1, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);

	spark.anim.loop = true;
	spark.speed.x -= 1;
	spark.speed.y -= 1;
	spark.anim.speed = 2.8f;
	spark.life = 350;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{

	LOG("Unloading particles");
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	App->textures->Unload(graphics);

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

			App->render->Blit(App->player->graphics, p->position.x, p->position.y, p->fliped, &(p->anim.GetCurrentFrame()),1.0,true,true,true);
			if (p->fx_played == false)
			{
				// Play particle fx here
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, bool fliped, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			p->fliped = fliped;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type,20,10,10,5, this);
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
			AddParticle(tornadoHaoImpact, active[i]->position.x+30, active[i]->position.y+30, COLLIDER_NONE);
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