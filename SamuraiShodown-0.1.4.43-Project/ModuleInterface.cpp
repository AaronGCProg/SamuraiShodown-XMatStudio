#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneUky.h"
#include "ModuleSceneHao.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"

#include <stdio.h> //for the sprintf_s function


ModuleInterface::ModuleInterface()
{
	
}

ModuleInterface::~ModuleInterface()
{}

// Load assets
bool ModuleInterface::Start()
{
	LOG("Loading interface ");
	 roundfinish = false;

	startingtime = SDL_GetTicks();


	font_time = App->fonts->Load("Assets/Fonts/TimeTile.png", "0123456789", 1);
	font_name = App->fonts->Load("Assets/Fonts/NameTile.png", "ABCDEFGHIJKLMNOPQRSTUWYZ0123456789-= ", 1);
	ui = App->textures->Load("Assets/Sprites/UIspritesheet2.png");

	return true;
}

// UnLoad assets
bool ModuleInterface::CleanUp()
{
	LOG("Unloading interface ");
	App->textures->Unload(ui);
	App->fonts->UnLoad(font_time);
	App->fonts->UnLoad(font_name);


	App->audio->CleanUp();


	return true;
}

// Update: draw background
update_status ModuleInterface::Update()
{
	App->render->Blit(ui, (SCREEN_WIDTH / 2) - 14, 10, false, &ko, NULL, true); // KO UI


	actualtime = 99 - ((SDL_GetTicks() - startingtime) / 1000);// gets the time since the start of the module in seconds
	if (actualtime < 0) { actualtime = 0; roundfinish = true; }//condition to end the stage 

		//ends the round if a players healthbar goes to 0
	if (App->player->health >= HEALTH_VALUE || App->player2->health >= HEALTH_VALUE) { roundfinish = true; }

	sprintf_s(time_text, 10, "%7d", actualtime);
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 15, 40, 0, time_text);

	App->fonts->BlitText(10, 30, 1, "HAOHMARU");
	App->fonts->BlitText(10, 5, 1, "P1= 30");

	App->fonts->BlitText(230, 30, 1, "HAOHMARU");
	App->fonts->BlitText(200, 5, 1, "P2= 99");

	App->fonts->BlitText(10, 212, 1, "CREDITS 03");
	App->render->Blit(ui, 34, 202, false, &powbar, NULL, true);
	App->render->Blit(ui, 20, 200, false, &pow, NULL, true);

	App->fonts->BlitText(210, 212, 1, "CREDITS 03");
	App->render->Blit(ui, 210, 202, false, &powbar, NULL, true);
	App->render->Blit(ui, 275, 200, false, &pow, NULL, true);


	return UPDATE_CONTINUE;
}