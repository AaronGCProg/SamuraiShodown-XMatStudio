#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneHanzo.h"
#include "ModuleSceneWelcome.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameControllers.h"


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

	graphics = App->textures->Load("Assets/Sprites/welcome.png");

	App->audio->soundtracks[2] = Mix_LoadMUS("Assets/Music/WelcomeMusic.ogg");

	if (!App->audio->soundtracks[2]) {
		LOG("Mix_LoadMUS(\"WelcomeMusic.ogg\"): %s\n", Mix_GetError());
	}
	else {		
		Mix_PlayMusic(App->audio->soundtracks[2], 2);
	}

	
	
	return true;
}

// UnLoad assets
bool ModuleSceneWelcome::CleanUp()
{
	LOG("Unloading Welcome scene");

	App->audio->CleanUp();

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneWelcome::Update()
{

	// Draw everything --------------------------------------	
	App->render->Blit(graphics, 0, 0, false, &background, NULL, true); //Welcome Image
	

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || App->controllers->controller_player1_Start_pressed == true) {

		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_welcome, App->scene_hanzo, 2.0f);
	}

	return UPDATE_CONTINUE;
}