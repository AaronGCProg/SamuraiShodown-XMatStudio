#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneUky.h"
#include "ModuleSceneHao.h"
#include "ModuleSceneCongrats.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"
#include "ModuleFight.h"
#include "ModuleReferee.h"


#include <stdio.h> //for the sprintf_s function

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneUky::ModuleSceneUky()
{
	for (int i = 0; i < 3; i++)//haohmarubackground anim
	{
		if (i == 3) // A la fila 7
		{
			for (int j = 0; j < 1; j++) // Comença a partir de la columna 2, fins la columna 6 (0 - 2)
			{
				backgroundanim.PushBack({ (640 * j),416 * i,640,416 }, 10, { 0,0 }, 0, {}, {}, {});
			}
		}
		else
		{
			for (int j = 0; j < 2; j++) // Comença a partir de la columa 0, fins la columna 4
			{
				backgroundanim.PushBack({ (640 * j),416 * i,640,416 }, 10, { 0,0 }, 0, {}, {}, {});
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
	App->audio->soundtracks[0] = Mix_LoadMUS("Assets/Music/HaohmaruMusic.ogg");

	if (!App->audio->soundtracks[0]) {
		LOG("Mix_LoadMUS(\"HaohmaruMusic.ogg\"): %s\n", Mix_GetError());
	}
	else {
		graphics = App->textures->Load("Assets/Sprites/backgroundspritesheet1.png");
		Mix_PlayMusic(App->audio->soundtracks[0], 2);
	}



	// TODO 1: Enable (and properly disable) the player module
	App->referee->Enable();
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();
	App->interface->Enable();
	App->fight->Enable();

	// Colliders ---
	// TODO 1: Add colliders for the first columns of the level
	App->collision->AddCollider({ -5, 0, 10, 416 }, COLLIDER_WALL);
	App->collision->AddCollider({ 635, 0, 10, 416 }, COLLIDER_WALL);

	App->fight->startingtime = SDL_GetTicks();

	return true;
}

// UnLoad assets
bool ModuleSceneUky::CleanUp()
{
	LOG("Unloading Uky scene");
	App->textures->Unload(graphics);
	App->referee->Disable();
	App->player->Disable();
	App->player2->Disable();
	App->collision->Disable();
	App->interface->Disable();

	App->audio->CleanUp();

	if (App->fight->finalwin1 || App->fight->finalwin2) {
		App->fight->CleanUp();
		App->fight->Disable();

	}

	return true;
}

// Update: draw background
update_status ModuleSceneUky::Update()
{
	if (App->player->position.x <= 5) { App->player->position.x = 5; }
    if (App->player->position.x >= 635) { App->player->position.x = 635 ; }
    if (App->player2->position.x <= 5) { App->player2->position.x = 5; }
    if (App->player2->position.x >= 635) { App->player2->position.x = 635 ; }
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, -168, false, &(backgroundanim.GetCurrentFrame()), 1.0f); //ukyo background animation


	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		BattleEnd();
	}

	return UPDATE_CONTINUE;
}


void ModuleSceneUky::roundFinish() {
	Mix_FadeOutMusic(2000);
	App->fade->FadeToBlack(App->scene_uky, App->scene_uky, 2.0f); //BUG
	App->fight->played = 1;
	App->fight->firstWin = true;

}

void ModuleSceneUky::BattleEnd() {
	Mix_FadeOutMusic(2000);
	App->fade->FadeToBlack(App->scene_uky, App->scene_congrats, 2.0f); //BUG

}