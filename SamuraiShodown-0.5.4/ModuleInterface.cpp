#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneHanzo.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"
#include "ModuleFight.h"
#include "ModuleFadeToBlack.h"

#include <stdio.h>//for the sprintf_s function


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
	font_finalscore = App->fonts->Load("Assets/Fonts/FinalScore.png", "0123456789%,", 1);
	font_debug = font_name;
	ui = App->textures->Load("Assets/Sprites/UIspritesheet2.png");

	App->audio->effects[3] = Mix_LoadWAV("Assets/Music/Kuroko_BattleStart.wav");
	App->audio->effects[4] = Mix_LoadWAV("Assets/Music/Kuroko_EnGarde.wav");
	App->audio->effects[5] = Mix_LoadWAV("Assets/Music/kuroko_firstround.wav");
	App->audio->effects[6] = Mix_LoadWAV("Assets/Music/Kuroko_BattleStart.wav");
	App->audio->effects[7] = Mix_LoadWAV("Assets/Music/kuroko_secondround.wav");
	App->audio->effects[8] = Mix_LoadWAV("Assets/Music/kuroko_thirdround.wav");
	App->audio->effects[9] = Mix_LoadWAV("Assets/Music/kuroko_ippon.wav");
	App->audio->effects[10] = Mix_LoadWAV("Assets/Music/kuroko_jubei.wav");
	App->audio->effects[11] = Mix_LoadWAV("Assets/Music/kuroko_battleEnd.wav");
	App->audio->effects[12] = Mix_LoadWAV("Assets/Music/kuroko_congratulations.wav");
	App->audio->effects[13] = Mix_LoadWAV("Assets/Music/draw_audio.wav");

	App->fight->interfaceStart = true;

	//debug puntuations
	P1punt.life = 8114;
	P1punt.time = 505;
	P1punt.hitting_perc = 85;

	P1punt.Resetactual();
	//pow-----------------------------------
	powword[0] = { 33, 53, 16, 11 };
	powword[1] = { 50, 49, 22, 15 };
	powword[2] = { 73, 44, 24,20 };
	powword[3] = { 98 ,40 ,28 ,24 };
	powword[4] = { 127 ,29 ,48 ,35 };
	powword[5] = { 175,26 ,51 ,39 };
	powword[6] = { 228, 25,51 ,39 };

	powpivot[0] = { 0,0 };
	powpivot[1] = { 0,0 };
	powpivot[2] = { 0,0 };
	powpivot[3] = { 0,0 };
	powpivot[4] = { 0,0 };
	powpivot[5] = { 0,0 };
	powpivot[6] = { 0,0 };

	return true;
}

// UnLoad assets
bool ModuleInterface::CleanUp()
{
	LOG("Unloading interface ");
	App->audio->CleanUp();
	App->fight->interfaceStart = false;

	App->textures->Unload(ui);
	App->fonts->UnLoad(font_finalscore);
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

		if (App->input->keys[SDL_SCANCODE_F12] == KEY_STATE::KEY_DOWN)
		{
			P1punt.Resetactual();
			if (!showscore)showscore = true;
			else showscore = false;

		}

		if (!timerStop && App->fight->playerControl && !App->fight->timer)
			actualtime = 99 - ((SDL_GetTicks() - (startingtime + App->fight->playerControlTime)) / 1000);// gets the time since the start of the module in seconds
		else if (!timerStop && !App->fight->playerControl && App->fight->timer)  actualtime = 0;


		sprintf_s(time_text, 10, "%7d", actualtime);
		App->fonts->BlitText((SCREEN_WIDTH / 2) - 15, 40, 0, time_text);

		App->fonts->BlitText(10, 30, 1, "JUBEI");
		App->fonts->BlitText(10, 5, 1, "P1= 3230");

		App->fonts->BlitText(230, 30, 1, "JUBEI");
		App->fonts->BlitText(200, 5, 1, "P2= 9249");

		//pows


		pow1damage = App->player->powValue;
		pow2damage = App->player2->powValue;
		pow1interiorbar.y = 24 - 8 + (8 * pow1damage);
		pow1interiorbar.w = (2 * pow1damage);
		pow2interiorbar.y = 24 - 8 + (8 * pow2damage);
		pow2interiorbar.w = (2 * pow2damage);

		if (pow1damage != 0)App->render->Blit(ui, 37, 202, false, &pow1interiorbar, NULL, true);//pow p1

		if (pow2damage != 0)App->render->Blit(ui, 273 - (2 * pow2damage), 202, true, &pow2interiorbar, NULL, true);//powp2

		//powword logic
		if (pow2damage < 6)actualpowwordframe = 0;
		else if (pow2damage < 12)actualpowwordframe = 1;
		else if (pow2damage < 18)actualpowwordframe = 2;
		else if (pow2damage < 24)actualpowwordframe = 3;
		else
		{
			if (powdelay < 4)
			{
				powdelay++;
			}
			else {
				powdelay = 0;

				if (criticalpowbucle == 0)actualpowwordframe = 4;
				if (criticalpowbucle == 1)actualpowwordframe = 5;
				if (criticalpowbucle == 3)actualpowwordframe = 6;
				if (criticalpowbucle > 3)criticalpowbucle = 0;
				criticalpowbucle++;
			}
		}



		App->fonts->BlitText(10, 212, 1, "CREDITS 03");
		App->render->Blit(ui, 34, 202, false, &powbar, NULL, true);

		App->render->Blit(ui, 21, 200, false, &powword[actualpowwordframe], NULL, true);//word pow

		App->fonts->BlitText(210, 212, 1, "CREDITS 03");
		App->render->Blit(ui, 211, 202, true, &powbar, NULL, true);

		App->render->Blit(ui, 274, 200, false, &powword[actualpowwordframe], NULL, true);//word pow


		if (App->player2->debugmode)//debug information
		{
			App->fonts->BlitText(0, 0, 1, "DEBUG");//title

			sprintf_s(debug_buttons_text, 50, "P1 BUTTONS PRESSED  A %d  B %d", App->input->controller_player1_A_pressed, App->input->controller_player1_B_pressed);
			App->fonts->BlitText(0, 10, 1, debug_buttons_text);
			sprintf_s(debug_joystick_text, 50, "P1 JOYSTICK H %d  V %d", App->input->Controller_player1_LAxisX, App->input->Controller_player1_LAxisY);
			App->fonts->BlitText(0, 20, 1, debug_joystick_text);

		}

	}

	//need to do it for both players
	if (showscore)
	{
		switch (scoretable)
		{
		case DEFAULT:
			if (P1punt.CountDelayInFrames(500)) { scoretable = IN_LIFE; }
			break;
		case IN_LIFE:
			if (P1punt.LifeSubstraction(PUNTUATION_TIME)) { scoretable = IN_TIME; }
			break;
		case IN_TIME:
			if (P1punt.TimeSubstraction(PUNTUATION_TIME)) { scoretable = IN_HITTINGPERCENTATGE; }
			break;
		case IN_HITTINGPERCENTATGE:
			if (P1punt.HittingPercSubtraction(PUNTUATION_TIME)) { scoretable = IN_TOTAL; }
			break;
		case IN_TOTAL:
			if (P1punt.CountDelayInFrames(PUNTUATION_TIME))
			{
				//when it ends the puntuation table
			}
			break;

		}

		lifescore = P1punt.actuallife;
		timescore = P1punt.actualtime;
		hittingpercentatgescore = P1punt.actualhitting_perc;
		totalScore = P1punt.actualtotal;

		//blit of the score words______________________________________________________________________________________

		App->render->Blit(ui, 65, 70, false, &life_time, NULL, false);//life/time words
		App->render->Blit(ui, 63, 133, false, &hittingperc_total, NULL, false);//life/time words


		//blit of the puntuation______________________________________________________________________________________
		sprintf_s(life_text_char, 20, "%d", lifescore);
		App->fonts->BlitText(160, 75, 3, life_text_char);//life score

		sprintf_s(time_text_char, 20, "%d", timescore);
		App->fonts->BlitText(160, 107, 3, time_text_char);//time score

		sprintf_s(hittingpercent_text_char, 20, "%d,%d %s", hittingpercentatgescore, hittingpercentatgescore, "%");
		App->fonts->BlitText(160, 139, 3, hittingpercent_text_char);//hitting percentatge score

		//!!!!!!!!!!!!!!!!!!!!!!!!! Atencion esta linea de codigo falla
		sprintf_s(total_score_text_char, 10, "%d", totalScore);
		App->fonts->BlitText(160, 171, 3, total_score_text_char);//total score

	}
	return UPDATE_CONTINUE;
}

