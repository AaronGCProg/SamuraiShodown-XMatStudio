#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include <cstdlib>
#include <time.h>

//Include scenes___________________________ Trying to resize the camera
#include"ModuleSceneWelcome.h"
#include "ModuleSceneHanzo.h"
#include "ModuleSceneCongrats.h"
#include "ModuleReferee.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModuleInterface.h"
#include "ModuleFight.h"


ModuleRender::ModuleRender() : Module()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;

	camera_offset.x = camera_offset.y = 0;

	srand(time(NULL));
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

	if (REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	if (renderer == NULL)
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

	SDL_RenderSetLogicalSize(renderer, 304, 224);

	int speed = 1;


	if (shaking)
		UpdateCameraShake();

	dist = abs(App->player->position.x - App->player2->position.x);
	//Escale Logic------------------- (1 zoom out/1.5 zoom in)

	switch (zoomingstates)
	{
	case 1://zoomout
		if (escala > 1.0)
		{
			escala -= 0.015f;

			if (App->player->playerFlip)App->player->position.x -= 1.5;//Player1 moves away
			else App->player->position.x += 1.5;

			if (App->player2->playerFlip)App->player2->position.x -= 1.5;//Player2 moves away
			else App->player2->position.x += 1.5;
		}

		if (escala <= 1.0) { escala = 1.0; zoomed = false; zoomingstates = 0; }
		break;

	case 2://zoomin
		if (escala < 1.5)
		{
			escala += 0.015f;

			if (App->player->playerFlip)App->player->position.x += 0.5;//Player1 moves away
			else App->player->position.x -= 0.5;

			if (App->player2->playerFlip)App->player2->position.x += 0.5;//Player2 moves away
			else App->player2->position.x -= 0.5;

		}
		if (escala >= 1.5) { escala = 1.5; zoomed = true; zoomingstates = 0; }
		break;

	case 0:
		if (dist > 300 && zoomed) zoomingstates = 1;
		if (dist < 100 && !zoomed)zoomingstates = 2;
		break;
	}

	if (App->player->position.x < App->player2->position.x)
		camera.x = (-App->player->position.x - (dist / 2) + (SCREEN_WIDTH / 2))*speed;
	else
		camera.x = (-App->player2->position.x - (dist / 2) + (SCREEN_WIDTH / 2))*speed;
	//camerax= (postition of player center)+(medium point between player 1 & 2) -...


	if (App->player->position.x < (-camera.x / speed)) App->player->position.x = (-camera.x / speed);//camera borders
	if (App->player2->position.x < (-camera.x / speed)) App->player2->position.x = (-camera.x / speed);
	if (App->player->position.x > ((-camera.x / speed) + (SCREEN_WIDTH))) App->player->position.x = (-camera.x / speed) + (SCREEN_WIDTH);//camera borders
	if (App->player2->position.x > ((-camera.x / speed) + (SCREEN_WIDTH))) App->player2->position.x = (-camera.x / speed) + (SCREEN_WIDTH);

	if (camera.x > 0)camera.x = 0;//camera goes in negative

	if (camera.x <= ((SCREEN_WIDTH -392)*SCREEN_SIZE*escala*0.959595f)) camera.x = ((SCREEN_WIDTH - 392)*SCREEN_SIZE*escala*0.959595f);//width of the map


	camera.h = SCREEN_HEIGHT;
	camera.w = SCREEN_WIDTH;

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	if (renderer != nullptr)
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);//turns the border rectangles to black
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	if (renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, bool fliped, SDL_Rect* section, float speed, bool use_camera, bool rescalable, bool player)
{

	bool ret = true;

	SDL_Rect rect;
	if (use_camera)
	{
		rect.x = (int)((camera.x + camera_offset.x) * speed) + x * SCREEN_SIZE;
		rect.y = (int)((camera.y + camera_offset.y) * speed) + y * SCREEN_SIZE;

	}
	else
	{
		rect.x = x * SCREEN_SIZE;
		rect.y = y * SCREEN_SIZE;
	}


	if (section != NULL)
	{
		rect.w = section->w;
		rect.h = section->h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	if (rescalable) {
		float playerescale = escala - (PLAYER_ESCALE*(escala - 0.5));//sets the player scale to 1 when he's in zoomin and to 0.75 when zoomout


		if (player)
		{
			rect.w = (rect.w)*playerescale;
			rect.h = (rect.h)*playerescale;
			rect.x = (x*SCREEN_SIZE) + ((camera_offset.x+camera.x)*speed);
			rect.y = (y*SCREEN_SIZE);
		}
		else
		{
			rect.w = (rect.w)*escala;
			rect.h = (rect.h)*escala;

			rect.x = (((camera_offset.x + camera.x) *speed) + x * SCREEN_SIZE)*escala;//escales in the x direction
			rect.y = (((camera_offset.y + camera.y) * speed) + y * SCREEN_SIZE)*escala - ((escala - 1) * 200);//escales in the y direction and moves it down to match the floor

		}


	}
	else if (App->scene_welcome->IsEnabled() == true || App->scene_congrats->IsEnabled() == true) //on menus
	{
		rect.w = SCREEN_WIDTH * SCREEN_SIZE;
		rect.h = SCREEN_HEIGHT * SCREEN_SIZE;
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

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)((camera.x + camera_offset.x) + rect.x * SCREEN_SIZE);
		rec.y = (int)((camera.y + camera_offset.y) + rect.y * SCREEN_SIZE);
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

void ModuleRender::StartCameraShake(int duration, float magnitude)
{
	shake_duration = duration;
	shake_magnitude = magnitude;
	shaking = true;
}

void ModuleRender::UpdateCameraShake()
{

	camera_offset.x = (rand() % ((int)shake_magnitude * 2) - shake_magnitude)*(escala-0.5);
	camera_offset.y = (rand() % ((int)shake_magnitude * 2) - shake_magnitude)*(escala - 0.5);

	shake_timer++;

	if (shake_timer >= shake_duration)
	{
		shaking = false;
		camera_offset.x = 0;
		camera_offset.y = 0;
		shake_timer = 0;
	}

}
