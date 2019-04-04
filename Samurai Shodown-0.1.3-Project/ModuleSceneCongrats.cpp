#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneUky.h"
#include "ModuleSceneHao.h"
#include "ModuleSceneWelcome.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneCongrats.h"
#include "ModuleAudio.h"


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


	App->audio->soundtracks[3] = Mix_LoadMUS("Assets/Music/BattleEnd.ogg");

	if (!App->audio->soundtracks[3]) {
		LOG("Mix_LoadMUS(\"BattleEnd.ogg\"): %s\n", Mix_GetError());
	}
	else {
		graphics = App->textures->Load("Assets/Sprites/congrats.png");
		Mix_PlayMusic(App->audio->soundtracks[3], 2);
	}



	return true;
}

// UnLoad assets
bool ModuleSceneCongrats::CleanUp()
{
	LOG("Unloading Congrats scene");
	App->textures->Unload(graphics);

	App->audio->CleanUp();

	return true;
}

// Update: draw background
update_status ModuleSceneCongrats::Update()
{

	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, false ,&background); //Welcome Image


	// TODO 2: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_congrats, App->scene_welcome, 2.0f);

	}

	return UPDATE_CONTINUE;
}