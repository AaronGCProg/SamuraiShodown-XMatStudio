#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneHao.h"
#include "ModuleSceneCongrats.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"
#include "ModuleFight.h"
#include "ModuleReferee.h"
#include "ModuleFadeToBlack.h"


#include <stdio.h> //for the sprintf_s function



ModuleSceneHao::ModuleSceneHao()
{
	for (int i = 0; i < 3; i++)//haohmarubackground anim
	{
		if (i == 3) 
		{
			for (int j = 0; j < 1; j++) 
			{
				backgroundanim.PushBack({ (640 * j),416 * i,640,416 }, 10, { 0,0 }, 0, {}, {}, {});
			}
		}
		else
		{
			for (int j = 0; j < 2; j++) 
			{
				backgroundanim.PushBack({ (640 * j),416 * i,640,416 }, 10, { 0,0 }, 0, {}, {}, {});
			}
		}
	}

	backgroundanim.speed = (0.1f);

}

ModuleSceneHao::~ModuleSceneHao()
{}

// Load assets
bool ModuleSceneHao::Start()
{

	graphics = App->textures->Load("Assets/Sprites/backgroundspritesheet1.png");

	App->referee->Enable();
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();
	App->interface->Enable();
	App->fight->Enable();

	App->audio->soundtracks[0] = Mix_LoadMUS("Assets/Music/HaohmaruMusic.ogg");

	if (!App->audio->soundtracks[0]) {
		LOG("Mix_LoadMUS(\"HaohmaruMusic.ogg\"): %s\n", Mix_GetError());
	}
	else {

		Mix_PlayMusic(App->audio->soundtracks[0], 2);
	}


	App->fight->startingtime = SDL_GetTicks();

	return true;
}

// UnLoad assets
bool ModuleSceneHao::CleanUp()
{
	LOG("Unloading HAO scene");

	App->audio->CleanUp();

	if (App->fight->finalwin1 || App->fight->finalwin2) {
		App->fight->Disable();
	}

	App->interface->Disable();
	App->collision->Disable();
	App->player2->Disable();
	App->player->Disable();
	App->referee->Disable();

	App->textures->Unload(graphics);
	

	return true;
}

// Update: draw background
update_status ModuleSceneHao::Update()
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


void ModuleSceneHao::roundFinish() {
	Mix_FadeOutMusic(2000);
	App->fade->FadeToBlack(App->scene_hao, App->scene_hao, 2.0f); //BUG
	App->fight->played = 1;
	App->fight->firstWin = true;

}

void ModuleSceneHao::BattleEnd() {
	Mix_FadeOutMusic(2000);
	App->fight->played = 1;
	App->fade->FadeToBlack(App->scene_hao, App->scene_congrats, 2.0f); //BUG

}