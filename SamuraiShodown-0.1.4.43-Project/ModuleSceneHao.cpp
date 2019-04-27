#include "Globals.h"
#include "Application.h"
#include "ModuleSceneUky.h"
#include "ModuleSceneHao.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleSceneCongrats.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"


#include <stdio.h> //for the sprintf_s function

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneHao::ModuleSceneHao()
{
	for (int i = 0; i < 4; i++)//haohmarubackground anim
	{
		for (int j = 0; j < 6; j++)
		{
			backgroundanim.PushBack({ (640 * j),416 * i,640,416 }, 9, { 0,0 }, 0, {}, {}, {});
		}
	}
	backgroundanim.speed = (0.1f);
}

ModuleSceneHao::~ModuleSceneHao()
{}

// Load assets
bool ModuleSceneHao::Start()
{
	LOG("Loading Hao Scene assets");

	bool ret = true;


	App->audio->soundtracks[0] = Mix_LoadMUS("Assets/Music/HaohmaruMusic.ogg");

	if (!App->audio->soundtracks[0]) {
		LOG("Mix_LoadMUS(\"HaohmaruMusic.ogg\"): %s\n", Mix_GetError());
	}
	else {
		graphics = App->textures->Load("Assets/Sprites/backgroundspritesheet1.png");
		Mix_PlayMusic(App->audio->soundtracks[0], 2);
	}



	// Enable (and properly disable) the player module
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();
	App->interface->Enable();


	App->collision->AddCollider({ -5, 0, 10, 416 }, COLLIDER_WALL);
	App->collision->AddCollider({ 635, 0, 10, 416 }, COLLIDER_WALL);

	return ret;
}

// Load assets
bool ModuleSceneHao::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading Hao scene stage");

	App->textures->Unload(graphics);
	App->player->Disable();
	App->player2->Disable();
	App->collision->Disable();
	App->interface->Disable();



	App->audio->CleanUp();

	return true;
}

// Update: draw background
update_status ModuleSceneHao::Update()
{

	if (App->player->position.x <= 5) { App->player->position.x = 5; }
	if (App->player->position.x + 73 >= 635) { App->player->position.x = 635 - 73; }
	if (App->player2->position.x <= 5) { App->player2->position.x = 5; }
	if (App->player2->position.x + 73 >= 635) { App->player2->position.x = 635 - 73; }
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, -168, false, &(backgroundanim.GetCurrentFrame()), 1.0f);//hahomarubackground animation


	//stage change when a round ends



	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_hao, App->scene_congrats, 2.0f);

	}

	return UPDATE_CONTINUE;
}