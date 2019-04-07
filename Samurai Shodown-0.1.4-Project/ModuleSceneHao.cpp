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

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneHao::ModuleSceneHao()
{
	for (int i = 0; i < 4; i++)//haohmarubackground anim
	{
		for (int j = 0; j < 6; j++)
		{
			backgroundanim.PushBack({ (640 * j),416 * i,640,416 });
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


	// Colliders ---
	//App->collision->AddCollider({ 0, 224, 3930, 16 }, COLLIDER_WALL);

	// TODO 1: Add colliders for the first columns of the level

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


	App->audio->CleanUp();

	return true;
}

// Update: draw background
update_status ModuleSceneHao::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, -168, false, &(backgroundanim.GetCurrentFrame()), 1.0f);//hahomarubackground animation

	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		
		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_hao, App->scene_congrats, 2.0f);
		
	}


	return UPDATE_CONTINUE;
}