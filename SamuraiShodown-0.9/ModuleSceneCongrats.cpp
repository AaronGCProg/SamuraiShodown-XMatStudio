#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneHanzo.h"
#include "ModuleSceneWelcome.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleSceneCongrats.h"
#include "ModuleAudio.h"
#include "ModuleFight.h"
#include "ModuleFadeToBlack.h"



ModuleSceneCongrats::ModuleSceneCongrats()
{

}

ModuleSceneCongrats::~ModuleSceneCongrats()
{}

// Load assets
bool ModuleSceneCongrats::Start()
{

	LOG("Loading Congrats scene");

	int startingtime = SDL_GetTicks();

	graphics = App->textures->Load("Assets/Sprites/congratsJubei.png");

	App->audio->soundtracks[3] = Mix_LoadMUS("Assets/Music/BattleEnd.ogg");


	jubei = { 306, 1, 141, 164 };
	jubeiAux = { -300 , 39 , 141 * SCREEN_SIZE, 164 * SCREEN_SIZE };

	loser = { 340, 168, 85, 72 };
	loserAux = { -380, 90 , 85 * SCREEN_SIZE, 72 * SCREEN_SIZE };

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

	moving = 0;
	App->audio->CleanUp();
	App->fight->Disable();

	App->textures->Unload(graphics);


	return true;
}

// Update: draw background
update_status ModuleSceneCongrats::Update()
{

	// Draw everything --------------------------------------	


	App->render->Blit(graphics, 0, 0, false, &background, NULL); //Welcome Image

	
	SDL_RenderCopy(App->render->renderer, graphics, &jubei, &jubeiAux);
	SDL_RenderCopy(App->render->renderer, graphics, &loser, &loserAux);

	


	if (jubeiAux.x < 130)
		jubeiAux.x += 2;

	if (loserAux.x < 40)
		loserAux.x += 2;

	

	// TODO 2: make so pressing SPACE the HONDA stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || App->input->controller_player1_Start_pressed == true) {

		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_congrats, App->scene_welcome, 2.0f);

	}

	return UPDATE_CONTINUE;
}