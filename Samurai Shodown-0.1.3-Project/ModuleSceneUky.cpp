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

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneUky::ModuleSceneUky()
{
	for (int i = 7; i <= 8; i++)//ukyo background anim
	{

		if (i == 7) // A la fila 7
		{
			for (int j = 2; j < 6; j++) // Comença a partir de la columna 2, fins la columna 6 (0 - 2)
			{
				backgroundanim.PushBack({ (640 * j),416 * i,640,416 });
			}
		}
		else if (i == 8) // A la fila 8
		{
			for (int j = 0; j < 4; j++) // Comença a partir de la columa 0, fins la columna 4
			{
				backgroundanim.PushBack({ (640 * j),416 * i,640,416 });
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

	App->audio->soundtracks[1] = Mix_LoadMUS("Assets/Music/UkyoMusic.ogg");

	if (!App->audio->soundtracks[1]) {
		LOG("Mix_LoadMUS(\"UkyoMusic.ogg\"): %s\n", Mix_GetError());
	}
	else {
		graphics = App->textures->Load("Assets/Sprites/backgroundspritesheet1.png");
		Mix_PlayMusic(App->audio->soundtracks[1], 2);
	}

	

	// TODO 1: Enable (and properly disable) the player module
	App->player->Enable();
	App->player2->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneUky::CleanUp()
{
	LOG("Unloading Uky scene");
	App->textures->Unload(graphics);
	App->player->Disable();
	App->player2->Disable();

	App->audio->CleanUp();

	return true;
}

// Update: draw background
update_status ModuleSceneUky::Update()
{

	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, -168, false, &(backgroundanim.GetCurrentFrame()), 1.0f); //ukyo background animation

	// TODO 2: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
	
		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_uky, App->scene_hao, 2.0f);

	}

	return UPDATE_CONTINUE;
}