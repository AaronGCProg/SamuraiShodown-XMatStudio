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

#include <stdio.h> //for the sprintf_s function

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneHao::ModuleSceneHao()
{
	for (int i = 0; i < 4; i++)//haohmarubackground anim
	{
		for (int j = 0; j < 6; j++)
		{
			backgroundanim.PushBack({ (640 * j),416 * i,640,416 },9);
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

	startingtime = SDL_GetTicks();
	
	App->audio->soundtracks[0] = Mix_LoadMUS("Assets/Music/HaohmaruMusic.ogg");

	if (!App->audio->soundtracks[0]) {
		LOG("Mix_LoadMUS(\"HaohmaruMusic.ogg\"): %s\n", Mix_GetError());
	}
	else {
		graphics = App->textures->Load("Assets/Sprites/backgroundspritesheet1.png");
		Mix_PlayMusic(App->audio->soundtracks[0], 2);
	}

	font_time = App->fonts->Load("Assets/Fonts/TimeTile.png", "0123456789", 1);

	ui = App->textures->Load("Assets/Sprites/UIspritesheet2.png");
	

	// Enable (and properly disable) the player module
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();


	// Colliders ---
	//App->collision->AddCollider({ 0, 224, 3930, 16 }, COLLIDER_WALL);


	return ret;
}

// Load assets
bool ModuleSceneHao::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading Hao scene stage");

	App->textures->Unload(graphics);
	App->textures->Unload(ui);
	App->fonts->UnLoad(font_time);
	App->player->Disable();
	App->player2->Disable();
	App->collision->Disable();



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

	SDL_Rect ko = { 33, 66, 28, 22 };
	App->render->Blit(ui, (SCREEN_WIDTH / 2) - 14, 10, false, &ko, NULL, true); // KO UI (Crear un módulo de interfaz)


	actualtime = 90 - ((SDL_GetTicks() - startingtime) / 1000);// gets the time since the start of the module in seconds
	if (actualtime < 0) { actualtime = 0; roundfinish = true; }//condition to end the stage 
	//(roundfinish doesn't do anything at the moment)

		//ends the round if a players healthbar goes to 0
	if (App->player->health >= HEALTH_VALUE || App->player2->health >= HEALTH_VALUE) { roundfinish = true; }

	//stage change when a round ends
	if (roundfinish)
	{
		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_hao, App->scene_congrats, 2.0f); //BUG
	}


	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {
		
		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_hao, App->scene_congrats, 2.0f);
		
	}

	sprintf_s(time_text, 10, "%7d", actualtime);
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 15, 40, 0, time_text);

	return UPDATE_CONTINUE;
}