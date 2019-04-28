#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneHao.h"
#include "ModuleSceneWelcome.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleSceneCongrats.h"
#include "ModuleAudio.h"
#include "ModuleFight.h"
#include "ModuleFadeToBlack.h"



ModuleSceneCongrats::ModuleSceneCongrats()
{
	background.w = 640;
	background.h = 480;

}

ModuleSceneCongrats::~ModuleSceneCongrats()
{}

// Load assets
bool ModuleSceneCongrats::Start()
{

	LOG("Loading Congrats scene");

	int startingtime = SDL_GetTicks();

	graphics = App->textures->Load("Assets/Sprites/congrats.png");

	App->audio->soundtracks[3] = Mix_LoadMUS("Assets/Music/BattleEnd.ogg");

	if (!App->audio->soundtracks[3]) {
		LOG("Mix_LoadMUS(\"BattleEnd.ogg\"): %s\n", Mix_GetError());
	}
	else {
		
		Mix_PlayMusic(App->audio->soundtracks[3], 2);
	}

	return true;
}

// UnLoad assets
bool ModuleSceneCongrats::CleanUp()
{
	LOG("Unloading Congrats scene");

	App->audio->CleanUp();
	App->fight->Disable();

	App->textures->Unload(graphics);


	return true;
}

// Update: draw background
update_status ModuleSceneCongrats::Update()
{

	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, false ,&background, NULL, true); //Welcome Image


	// TODO 2: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_congrats, App->scene_welcome, 2.0f);

	}

	if ((SDL_GetTicks() - startingtime) > 12000) {
		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_congrats, App->scene_welcome, 2.0f); //BUG
	}

	return UPDATE_CONTINUE;
}