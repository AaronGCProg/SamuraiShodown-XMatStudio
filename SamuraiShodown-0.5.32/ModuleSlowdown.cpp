#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleSlowdown.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"

ModuleSlowdown::ModuleSlowdown()
{
}

ModuleSlowdown::~ModuleSlowdown()
{}


bool ModuleSlowdown::Start()
{
	return true;
}

update_status ModuleSlowdown::PostUpdate()
{
	if (slowing_down)
	{
		UpdateSlowdown();
	}

	return UPDATE_CONTINUE;
}
void ModuleSlowdown::StartSlowdown(int duration, int magnitude)
{
	slowdown_duration = duration;
	slowdown_magnitude = magnitude;
	slowing_down = true;
}

void ModuleSlowdown::UpdateSlowdown()
{

	if (slowdown_timer%slowdown_magnitude == 0) SDL_Delay(slowdown_duration);
	slowdown_timer++;

	if (slowdown_timer >= slowdown_duration)
	{
		slowing_down = false;
		slowdown_timer = 0;
	}
}
