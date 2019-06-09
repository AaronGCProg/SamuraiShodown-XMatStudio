#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;
	bool fliped = false;



	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);


	void AddParticle(const Particle& particle, int x, int y, bool fliped, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	uint last_particle = 0;

public:

	Particle* active[MAX_ACTIVE_PARTICLES];
	Particle tornadoHao;
	Particle bloodLow;
	Particle bloodMid;
	Particle bloodHard;
	Particle kick;
	Particle slash;
	Particle groundHit;
	Particle blocking;
	Particle swordFight;
	Particle swordFightEnd;
	Particle spark;
	Particle tornadoHaoImpact;
	Particle swordDrop;
	Particle swordGround;
	Particle swordDrop2;
	Particle swordGround2;

};

#endif // __MODULEPARTICLES_H__
