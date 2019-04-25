#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneUky.h"
#include "ModuleSceneHao.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"

#include <stdio.h> //for the sprintf_s function

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneUky::ModuleSceneUky()
{
	for (int i = 7; i <= 8; i++)//ukyo background anim
	{

		if (i == 7) // A la fila 7
		{
			for (int j = 2; j < 6; j++) // Comença a partir de la columna 2, fins la columna 6 (0 - 2)
			{
				backgroundanim.PushBack({ (640 * j),416 * i,640,416 }, 9);
			}
		}
		else if (i == 8) // A la fila 8
		{
			for (int j = 0; j < 4; j++) // Comença a partir de la columa 0, fins la columna 4
			{
				backgroundanim.PushBack({ (640 * j),416 * i,640,416 }, 9);
			}
		}	
	}
	backgroundanim.speed = (0.1f);
}

ModuleSceneUky::~ModuleSceneUky()
{}

// Load assets
bool ModuleSceneUky::Start()
{
	LOG("Loading Uky scene");
	bool roundfinish = false;
	App->audio->soundtracks[1] = Mix_LoadMUS("Assets/Music/UkyoMusic.ogg");

	startingtime = SDL_GetTicks();

	if (!App->audio->soundtracks[1]) {
		LOG("Mix_LoadMUS(\"UkyoMusic.ogg\"): %s\n", Mix_GetError());
	}
	else {
		graphics = App->textures->Load("Assets/Sprites/backgroundspritesheet1.png");
		Mix_PlayMusic(App->audio->soundtracks[1], 2);
	}

	font_time = App->fonts->Load("Assets/Fonts/TimeTile.png", "0123456789", 1);

	

	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();
	// Colliders ---
	// TODO 1: Add colliders for the first columns of the level
	App->collision->AddCollider({ -5, 0, 10, 416 }, COLLIDER_WALL);
	App->collision->AddCollider({ 635, 0, 10, 416 }, COLLIDER_WALL);

	return true;
}

// UnLoad assets
bool ModuleSceneUky::CleanUp()
{
	LOG("Unloading Uky scene");
	App->textures->Unload(graphics);
	App->fonts->UnLoad(font_time);
	App->player->Disable();
	App->player2->Disable();
	App->collision->Disable();

	App->audio->CleanUp();

	return true;
}

// Update: draw background
update_status ModuleSceneUky::Update()
{
	if (App->player->position.x <= 5) { App->player->position.x = 5; }
	if (App->player->position.x + 73 >= 635) { App->player->position.x = 635 - 73; }
	if (App->player2->position.x <= 5) { App->player2->position.x = 5; }
	if (App->player2->position.x + 73 >= 635) { App->player2->position.x = 635 - 73; }
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, -168, false, &(backgroundanim.GetCurrentFrame()), 1.0f); //ukyo background animation

	actualtime = 90 - ((SDL_GetTicks() - startingtime) / 1000);// gets the time since the start of the module in seconds
	if (actualtime < 0) { actualtime = 0; roundfinish = true; }//condition to end the stage 
	//(roundfinish doesn't do anything at the moment)

		//ends the round if a players healthbar goes to 0
	if (App->player->health >= HEALTH_VALUE || App->player2->health >= HEALTH_VALUE) { roundfinish = true; }

	//stage change when a round ends
	if (roundfinish)
	{
		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_uky, App->scene_hao, 2.0f); //BUG
	}


	// TODO 2: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
	
		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_uky, App->scene_hao, 2.0f);

	}

	sprintf_s(time_text, 10, "%7d", actualtime);
	App->fonts->BlitText((SCREEN_WIDTH / 2), 5, 0, time_text);

	return UPDATE_CONTINUE;
}