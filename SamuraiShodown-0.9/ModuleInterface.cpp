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
#include <cstdlib>
#include <time.h>

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
	srand(time(NULL));

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
	showscore = false;


	//debug puntuations


	P1punt.Resetactual();
	//pow-----------------------------------
	powword[0] = { 33, 53, 16, 11 };
	powword[1] = { 50, 49, 22, 15 };
	powword[2] = { 73, 44, 24,20 };
	powword[3] = { 98 ,40 ,28 ,24 };
	powword[4] = { 127 ,28 ,48 ,35 };
	powword[5] = { 175,25 ,51 ,39 };
	powword[6] = { 228, 24,51 ,40 };

	powpivot1[0] = { 0,63 };
	powpivot1[1] = { 0,63 };
	powpivot1[2] = { 0,63 };
	powpivot1[3] = { 0,63 };
	powpivot1[4] = { -13,63 };
	powpivot1[5] = { -12,63 };
	powpivot1[6] = { -13,63 };

	powpivot2[0] = { 0,63 };
	powpivot2[1] = { 0,63 };
	powpivot2[2] = { 0,63 };
	powpivot2[3] = { 0,63 };
	powpivot2[4] = { 13,63 };
	powpivot2[5] = { 14,63 };
	powpivot2[6] = { 13,63 };

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
	if (!countingscore)
	{
		timecounterfloat += 0.1;
		P1punt.life = (50+ rand()%100);
		P1punt.time = (abs(500-timecounterfloat+ rand()%100))*5;
		P1punt.hitting_perc = (100 +rand()%100)*3;
		P2punt.life = (50 + rand() % 100);
		P2punt.time = (abs(500 - timecounterfloat + rand() % 100)) * 5;
		P2punt.hitting_perc = (100 + rand() % 100) * 3;
		P1punt.Resetactual();
		P2punt.Resetactual();
	}
	else timecounterfloat = 0;

	if (App->fight->showHealthBar) {
		if (App->fight->rounds == 1)


			if (App->player->critical || App->player2->critical) {

				if (koBlinking < 4) {
					SDL_Rect ko = { 33, 66, 28, 22 };
					App->render->Blit(ui, (SCREEN_WIDTH / 2) - 14, 10, false, &ko, NULL, true); // KO UI
					koBlinking++;
				}
				else {
					SDL_Rect ko = { 60, 65, 30, 23 };
					App->render->Blit(ui, (SCREEN_WIDTH / 2) - 14, 10, false, &ko, NULL, true); // KO UI
					koBlinking++;

					if (koBlinking > 8)
						koBlinking = 0;
				}
			}
			else
				App->render->Blit(ui, (SCREEN_WIDTH / 2) - 14, 10, false, &ko, NULL, true); // KO UI


		else {

			if (App->player->critical || App->player2->critical) {

				if (koBlinking < 4) {
					SDL_Rect end = { 33, 89, 28, 22 };
					App->render->Blit(ui, (SCREEN_WIDTH / 2) - 14, 10, false, &end, NULL, true); // KO UI
					koBlinking++;
				}
				else {
					SDL_Rect end = { 60, 89, 29, 23 };
					App->render->Blit(ui, (SCREEN_WIDTH / 2) - 14, 10, false, &end, NULL, true); // KO UI
					koBlinking++;

					if (koBlinking > 8)
						koBlinking = 0;
				}
			}
			else
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

		sprintf_s(p1scorechar, 10, "P1: %d", P1punt.score);
		App->fonts->BlitText(10, 30, 1, "JUBEI");
		App->fonts->BlitText(10, 5, 1, p1scorechar);

		sprintf_s(p2scorechar, 10, "P2: %d", P2punt.score);
		App->fonts->BlitText(230, 30, 1, "JUBEI");
		App->fonts->BlitText(200, 5, 1, p2scorechar);

		//pows


		pow1damage = App->player->powValue;
		pow2damage = App->player2->powValue;
		pow1interiorbar.y = 24 - 8 + (8 * pow1damage);
		pow1interiorbar.w = (2 * pow1damage);
		pow2interiorbar.y = 24 - 8 + (8 * pow2damage);
		pow2interiorbar.w = (2 * pow2damage);

		if (pow1damage >= 31)
		{
			if (critpowdelay1 < 4)
			{
				critpowdelay1++;
			}
			else { critpowdelay1 = 0; critpowbarbucle1++; };

			if (critpowbarbucle1 == 0)pow1interiorbar = { 223,96,62,8 };
			if (critpowbarbucle1 == 1)pow1interiorbar = { 223,104,62,8 };
			if (critpowbarbucle1 == 2)pow1interiorbar = { 223,112,62,8 };
			if (critpowbarbucle1 >= 3)critpowbarbucle1 = 0;

		}
		else pow1interiorbar.x = 0;

		if (pow2damage >= 31)
		{
			if (critpowdelay2 < 4)
			{
				critpowdelay2++;
			}
			else { critpowdelay2 = 0; critpowbarbucle2++; };

			if (critpowbarbucle2 == 0)pow2interiorbar = { 223,96,62,8 };
			if (critpowbarbucle2 == 1)pow2interiorbar = { 223,104,62,8 };
			if (critpowbarbucle2 == 2)pow2interiorbar = { 223,112,62,8 };
			if (critpowbarbucle2 >= 3)critpowbarbucle2 = 0;

		}
		else pow2interiorbar.x = 0;


		if (pow1damage != 0)App->render->Blit(ui, 104 - (2 * pow1damage), 207, false, &pow1interiorbar, NULL, true);//pow p1

		if (pow2damage != 0)App->render->Blit(ui, 201, 207, false, &pow2interiorbar, NULL, true);//powp2

		//powword logic
		if (pow2damage < 8)actualpowwordframe2 = 0;
		else if (pow2damage < 16)actualpowwordframe2 = 1;
		else if (pow2damage < 24)actualpowwordframe2 = 2;
		else if (pow2damage < 30)actualpowwordframe2 = 3;
		else
		{
			if (powdelay2 < 4)
			{
				powdelay2++;
			}
			else {
				powdelay2 = 0;

				if (criticalpowbucle2 == 0)actualpowwordframe2 = 4;
				if (criticalpowbucle2 == 1)actualpowwordframe2 = 5;
				if (criticalpowbucle2 == 2)actualpowwordframe2 = 6;
				if (criticalpowbucle2 >= 3)criticalpowbucle2 = 0;
				criticalpowbucle2++;
			}
		}

		if (pow1damage < 8)actualpowwordframe = 0;
		else if (pow1damage < 16)actualpowwordframe = 1;
		else if (pow1damage < 24)actualpowwordframe = 2;
		else if (pow1damage < 30)actualpowwordframe = 3;
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
				if (criticalpowbucle == 2)actualpowwordframe = 6;
				if (criticalpowbucle >= 3)criticalpowbucle = 0;
				criticalpowbucle++;
			}
		}


		SDL_Rect credits = { 230,264,64,8 };
		App->render->Blit(ui, 16, 216, false, &credits, NULL, true);//credits 03 blit left
		App->render->Blit(ui, 39, 207, false, &powbar, NULL, true);

		App->render->Blit(ui, 40 - powpivot1[actualpowwordframe].x - powword[actualpowwordframe].w, 216 - powword[actualpowwordframe].h, false, &powword[actualpowwordframe], NULL, true);//word pow left

		App->render->Blit(ui, 224, 216, false, &credits, NULL, true);//credits 03 blit right
		App->render->Blit(ui, 200, 207, true, &powbar, NULL, true);

		App->render->Blit(ui, SCREEN_WIDTH - 40 - powpivot2[actualpowwordframe2].x, 216 - powword[actualpowwordframe2].h, false, &powword[actualpowwordframe2], NULL, true);//word pow right


		if (App->player2->debugmode)//debug information
		{
			App->fonts->BlitText(0, 0, 1, "DEBUG");//title

			sprintf_s(debug_buttons_text, 50, "P1 BUTTONS PRESSED  A %d  B %d", App->input->controller_player1_A_pressed, App->input->controller_player1_B_pressed);
			App->fonts->BlitText(0, 10, 1, debug_buttons_text);
			sprintf_s(debug_joystick_text, 50, "P1 JOYSTICK H %d  V %d", App->input->Controller_player1_LAxisX, App->input->Controller_player1_LAxisY);
			App->fonts->BlitText(0, 20, 1, debug_joystick_text);

		}

	}

	if (printSwordFight) {
		SDL_Rect pushButton = { 2117, 41, 41, 56 };
		SDL_Rect pushButton2 = { 2159, 40, 49, 57 };
		if (countAux < 4)
			App->render->Blit(App->player->graphics, (SCREEN_WIDTH / 2) - 20, 40, false, &pushButton, NULL, true);
		else
			App->render->Blit(App->player->graphics, (SCREEN_WIDTH / 2) - 20, 40, false, &pushButton2, NULL, true);

		countAux++;
		if (countAux > 8) countAux = 0;

	}



	//need to do it for both players
	if (showscore)
	{	
		countingscore = true;
		scoreended = false;
		if (playerwins == 1||App->fight->finalwin2 == 1)
		{

			switch (scoretable)
			{
			case DEFAULT:
				if (P1punt.CountDelayInFrames(180)) { scoretable = IN_LIFE; }
				break;
			case IN_LIFE:
				if (P1punt.LifeSubstraction(PUNTUATION_TIME)) { scoretable = IN_TIME; }
				break;
			case IN_TIME:
				if (P1punt.TimeSubstraction(PUNTUATION_TIME)) { scoretable = IN_WAITINGFORPERCENTATGE; }
				break;
			case IN_WAITINGFORPERCENTATGE:
				if (P1punt.TimeSubstraction(60*2)) { hitisinpercentatge = false; scoretable = IN_HITTINGPERCENTATGE; }
				break;
			case IN_HITTINGPERCENTATGE:
			
				if (P1punt.HittingPercSubtraction(PUNTUATION_TIME)) { scoretable = IN_TOTAL; }
				break;
			case IN_TOTAL:
				if (P1punt.CountDelayInFrames(PUNTUATION_TIME))
				{
					scoreended = true;
					showscore = false;
					countingscore = false;
					hitisinpercentatge = true;
				}
				break;

			}
			lifescore = P1punt.actuallife;
			timescore = P1punt.actualtime;
			hittingpercentatgescore = P1punt.actualhitting_perc;
			totalScore = P1punt.actualtotal;
		}
		if (playerwins == 2||App->fight->finalwin2==2)
		{
			switch (scoretable)
			{
			case DEFAULT:
				if (P2punt.CountDelayInFrames(180)) { scoretable = IN_LIFE; }
				break;
			case IN_LIFE:
				if (P2punt.LifeSubstraction(PUNTUATION_TIME)) { scoretable = IN_TIME; }
				break;
			case IN_TIME:
				if (P2punt.TimeSubstraction(PUNTUATION_TIME)) { scoretable = IN_WAITINGFORPERCENTATGE; }
				break;
			case IN_WAITINGFORPERCENTATGE:
				if (P2punt.TimeSubstraction(60*2)) { hitisinpercentatge = false; scoretable = IN_HITTINGPERCENTATGE; }
				break;
			case IN_HITTINGPERCENTATGE:

				if (P2punt.HittingPercSubtraction(PUNTUATION_TIME)) { scoretable = IN_TOTAL; }
				break;
			case IN_TOTAL:
				if (P2punt.CountDelayInFrames(PUNTUATION_TIME))
				{
					scoreended = true;
					showscore = false;
					countingscore = false;
					hitisinpercentatge = true;
				}
				break;

			}
			lifescore = P2punt.actuallife;
			timescore = P2punt.actualtime;
			hittingpercentatgescore = P2punt.actualhitting_perc;
			totalScore = P2punt.actualtotal;

		}


		


		//blit of the score words______________________________________________________________________________________

		App->render->Blit(ui, 65, 70, false, &life_time, NULL, false);//life/time words
		App->render->Blit(ui, 63, 133, false, &hittingperc_total, NULL, false);//life/time words


		//blit of the puntuation______________________________________________________________________________________
		sprintf_s(life_text_char, 20, "%d", lifescore);
		App->fonts->BlitText(160, 75, 3, life_text_char);//life score

		sprintf_s(time_text_char, 20, "%d", timescore);
		App->fonts->BlitText(160, 107, 3, time_text_char);//time score

		if (hitisinpercentatge)
		{
			decimal = (hittingpercentatgescore % 10);
			sencer = ((hittingpercentatgescore - decimal) / 10) % 100;
			sprintf_s(hittingpercent_text_char, 20, "%d,%d %s", sencer, decimal, "%");
			App->fonts->BlitText(160, 139, 3, hittingpercent_text_char);
		}
		else
		{
			sprintf_s(hittingpercent_text_char, 20, "%d", hittingpercentatgescore);
			App->fonts->BlitText(160, 139, 3, hittingpercent_text_char);//hitting percentatge score
		}
		
		

		//!!!!!!!!!!!!!!!!!!!!!!!!! Atencion esta linea de codigo falla
		sprintf_s(total_score_text_char, 10, "%d", totalScore);
		App->fonts->BlitText(160, 171, 3, total_score_text_char);//total score

	}
	return UPDATE_CONTINUE;
}

