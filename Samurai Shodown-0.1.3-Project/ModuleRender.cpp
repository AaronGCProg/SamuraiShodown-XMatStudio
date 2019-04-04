#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
//Include scenes___________________________ Trying to resize the camera
#include"ModuleSceneWelcome.h"
#include "ModuleSceneHao.h"
#include "ModuleSceneUky.h"
#include "ModuleSceneCongrats.h"
ModuleRender::ModuleRender() : Module()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()	
{
	int speed = 3;

	if(App->input->keyboard[SDL_SCANCODE_I] == 1)
		camera.y += speed;

	if(App->input->keyboard[SDL_SCANCODE_K] == 1)
		camera.y -= speed;

	if(App->input->keyboard[SDL_SCANCODE_J] == 1)
		camera.x += speed;

	if(App->input->keyboard[SDL_SCANCODE_L] == 1)
		camera.x -= speed;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, bool fliped, SDL_Rect* section, float speed)
{


	bool ret = true;
	
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed) + y * SCREEN_SIZE;
	

	if(section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	//scale renderer based on the stage of the game (Else --> main scale for battle stages, if--> screen scaled to fit the image)
	if (App->scene_welcome->IsEnabled()==true ||App->scene_congrats->IsEnabled()==true) //on menus
	{
		rect.w = SCREEN_WIDTH*SCREEN_SIZE;
		rect.h =  SCREEN_HEIGHT*SCREEN_SIZE;
	}
	else //Inside game
	{
		rect.w *= SCREEN_SIZE;
		rect.h *= SCREEN_SIZE;
	}

	if (fliped == true) {

		if (SDL_RenderCopyEx(renderer, texture, section, &rect, NULL, NULL, SDL_FLIP_HORIZONTAL) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}
	}
	else {

		if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}
	}

	return ret;
}

