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
#include "ModuleAudio.h"


ModuleSceneWelcome::ModuleSceneWelcome()
{
	background.w = 640;
	background.h = 480;
	background.x = 0;
	background.y = 0;

}

ModuleSceneWelcome::~ModuleSceneWelcome()
{}

// Load assets
bool ModuleSceneWelcome::Start()
{

	LOG("Loading Welcome scene");

	App->audio->soundtracks[2] = Mix_LoadMUS("Assets/Music/WelcomeMusic.ogg");

	if (!App->audio->soundtracks[2]) {
		LOG("Mix_LoadMUS(\"WelcomeMusic.ogg\"): %s\n", Mix_GetError());
	}
	else {
		graphics = App->textures->Load("Assets/Sprites/welcome.png");
		Mix_PlayMusic(App->audio->soundtracks[2], 2);
	}

	
	
	return true;
}

// UnLoad assets
bool ModuleSceneWelcome::CleanUp()
{
	LOG("Unloading Welcome scene");

	App->textures->Unload(graphics);
	
	App->audio->CleanUp();

	return true;
}

// Update: draw background
update_status ModuleSceneWelcome::Update()
{

	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, false, &background, NULL, true); //Welcome Image
	

	// TODO 2: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_welcome, App->scene_uky, 2.0f);
	}

	return UPDATE_CONTINUE;
}