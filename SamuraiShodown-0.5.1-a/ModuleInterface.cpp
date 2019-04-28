#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneHao.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"
#include "ModuleFight.h"
#include "ModuleFadeToBlack.h"

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

	startingtime = SDL_GetTicks();
	int actualtime = 99;
	timerStop = false;

	font_time = App->fonts->Load("Assets/Fonts/TimeTile.png", "0123456789", 1);
	font_name = App->fonts->Load("Assets/Fonts/NameTile.png", "ABCDEFGHIJKLMNOPQRSTUWYZ0123456789-= ", 1);
	font_menu = App->fonts->Load("Assets/Fonts/TextTile.png", "ABCDEFGHIJKLMNOPQRSTUVWYZ-123! ", 1);
	ui = App->textures->Load("Assets/Sprites/UIspritesheet2.png");

	App->audio->effects[3] = Mix_LoadWAV("Assets/Music/Kuroko_BattleStart.wav");
	App->audio->effects[4] = Mix_LoadWAV("Assets/Music/Kuroko_EnGarde.wav");
	App->audio->effects[5] = Mix_LoadWAV("Assets/Music/kuroko_firstround.wav");
	App->audio->effects[6] = Mix_LoadWAV("Assets/Music/Kuroko_BattleStart.wav");
	App->audio->effects[7] = Mix_LoadWAV("Assets/Music/kuroko_secondround.wav");
	App->audio->effects[8] = Mix_LoadWAV("Assets/Music/kuroko_thirdround.wav");
	App->audio->effects[9] = Mix_LoadWAV("Assets/Music/kuroko_ippon.wav");
	App->audio->effects[10] = Mix_LoadWAV("Assets/Music/kuroko_haohmaru.wav");
	App->audio->effects[11] = Mix_LoadWAV("Assets/Music/kuroko_battleEnd.wav");
	App->audio->effects[12] = Mix_LoadWAV("Assets/Music/kuroko_congratulations.wav");
	App->audio->effects[13] = Mix_LoadWAV("Assets/Music/draw_audio.wav");

	App->fight->interfaceStart = true;
	return true;
}

// UnLoad assets
bool ModuleInterface::CleanUp()
{
	LOG("Unloading interface ");
	App->audio->CleanUp();
	App->fight->interfaceStart = false;

	App->textures->Unload(ui);
	App->fonts->UnLoad(font_menu);
	App->fonts->UnLoad(font_name);
	App->fonts->UnLoad(font_time);

	return true;
}

// Update: draw background
update_status ModuleInterface::Update()
{
	if (App->fight->showHealthBar) {
		if (App->fight->rounds == 1)
			App->render->Blit(ui, (SCREEN_WIDTH / 2) - 14, 10, false, &ko, NULL, true); // KO UI
		else {
			App->render->Blit(ui, (SCREEN_WIDTH / 2) - 14, 10, false, &end, NULL, true); // KO UI
		}

		if (App->fight->winplayer1)
			App->render->Blit(ui, 5, 40, false, &victory, NULL, true); // VICTORY UI

		if (App->fight->winplayer2)
			App->render->Blit(ui, SCREEN_WIDTH - 28, 40, false, &victory, NULL, true); // VICTORY UI

		if (App->fight->finalwin1 && App->fight->winplayer1 && App->fight->winplayer1)
			App->render->Blit(ui, 40, 40, false, &victory, NULL, true); // VICTORY UI


		if (App->fight->finalwin2 && App->fight->winplayer2)
			App->render->Blit(ui, SCREEN_WIDTH - 63, 40, false, &victory, NULL, true); // VICTORY UI

		if (App->input->keys[SDL_SCANCODE_F11] == KEY_STATE::KEY_DOWN)
		{
			actualtime = 99;
			timerStop = true;			
		}

		if (App->input->keys[SDL_SCANCODE_F10] == KEY_STATE::KEY_DOWN)
		{
			App->player->health = 129;
		}

		if (App->input->keys[SDL_SCANCODE_F9] == KEY_STATE::KEY_DOWN)
		{
			App->player2->health = 129;
		}

		if (!timerStop && App->fight->playerControl && !App->fight->timer)
			actualtime = 99 - ((SDL_GetTicks() - (startingtime + App->fight->playerControlTime)) / 1000);// gets the time since the start of the module in seconds
		else if (!timerStop && !App->fight->playerControl && App->fight->timer)  actualtime = 0;



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

	}
	return UPDATE_CONTINUE;
}