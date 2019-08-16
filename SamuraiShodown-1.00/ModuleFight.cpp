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


#include <stdio.h> //for the sprintf_s function


ModuleFight::ModuleFight()
{

}

ModuleFight::~ModuleFight()
{}

// Load assets
bool ModuleFight::Start()
{
	LOG("Loading fight module ");



	startingtime = SDL_GetTicks();
	letterTime = 1775;
	playerControlTime = 3363;
	playerControl = false;
	showHealthBar = false;
	played = 0;
	startingtime = 0;
	roundfinish = false;
	rounds = 1;
	winplayer1 = false;
	winplayer2 = false;
	firstWin = false;
	start = true;
	finalwin1 = false;
	finalwin2 = false;
	perfect = false;
	timer = false;


	return true;
}

// UnLoad assets
bool ModuleFight::CleanUp()
{
	LOG("Unloading fight module");

	return true;
}

// Update: draw background
update_status ModuleFight::Update()
{
	if (interfaceStart) {

		if (SDL_GetTicks() - startingtime < letterTime && !firstWin) {
			App->fonts->BlitText((SCREEN_WIDTH / 2) - 115, 70, 2, "E N  G A R D E ");
			if (played == 0) {
				Mix_PlayChannel(-1, App->audio->effects[4], 0);
				played++;
				App->interface->actualtime = 99;
			}
		}
		else {
			showHealthBar = true;

			if (SDL_GetTicks() - App->interface->startingtime < letterTime + 888) {
				App->interface->actualtime = 99;

				if (!winplayer1 && !winplayer2) {
					if (played == 1) {
						Mix_PlayChannel(-1, App->audio->effects[5], 0);
						played++;
						timer = false;
					}
					App->fonts->BlitText((SCREEN_WIDTH / 2) - 3 * 16, 70, 2, "DUEL 1");
				}
				if ((winplayer1 || winplayer2) && (!winplayer1 || !winplayer2)) {
					if (played == 1) {
						Mix_PlayChannel(-1, App->audio->effects[7], 0);
						played++;
						letterTime -= 888;
						playerControlTime -= 300;
						rounds++;
						timer = false;

					}
					App->fonts->BlitText((SCREEN_WIDTH / 2) - 3 * 16, 70, 2, "DUEL 2");
				}
				if (winplayer1 && winplayer2) {
					if (played == 1) {
						Mix_PlayChannel(-1, App->audio->effects[8], 0);
						played++;
						rounds++;
						timer = false;
					}
					App->fonts->BlitText((SCREEN_WIDTH / 2) - 3 * 16, 70, 2, "DUEL 3");
				}
			}
			else if (SDL_GetTicks() - App->interface->startingtime < playerControlTime) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 2 * 16, 70, 2, "BEGIN");
				if (played == 2) {
					Mix_PlayChannel(-1, App->audio->effects[6], 0);
					played++;
					timer = false;
				}
			}
			else playerControl = true;

			if (App->interface->actualtime <= 0 && App->player->health == App->player2->health) {

				WinRound1(0, false, false);
			}

			//ends the round if a players healthbar goes to 0
			if (App->player->health >= HEALTH_VALUE || App->interface->actualtime <= 0 && App->player->health > App->player2->health) {//p2 wins
				if (!winplayer2) {//first round

					winplayer2 = true;
				}
				else if (!finalwin2 && winplayer2 && ((rounds == 2 && !winplayer1) || (rounds == 3 && winplayer1))) {//second round

					finalwin2 = true;

				}

				if (App->player->health == HEALTH_VALUE) {
					perfect = true;
				}
				WinRound1(2, finalwin2, perfect);

			}
			if (App->player2->health >= HEALTH_VALUE || App->interface->actualtime <= 0 && App->player->health < App->player2->health) {//p1 wins
				if (!winplayer1) {//first round
					winplayer1 = true;
				}
				else if (!finalwin1 && winplayer1 && ((rounds == 2 && !winplayer2) || (rounds == 3 && winplayer2))) {//second round
					finalwin1 = true;

				}
				WinRound1(1, finalwin1, perfect);

			}
		}
	}
	return UPDATE_CONTINUE;
}

void  ModuleFight::WinRound1(int player, bool final, bool perfect) {
	playerControl = false;
	if (!timer) {
		timer = true;
		startingtime = SDL_GetTicks();
	}

	if (!final)
	{
		if (!firstWin) {
			firstWin = true;


		}
		if (player == 1 && SDL_GetTicks() - startingtime > 500) {
			//Player1 1st victory animation
			App->player->doingAction = true;
			if (!App->player->noSword)
				App->player->winning1 = true;
			else
				App->player->winnw = true;


			//Player2 1st death animation
			App->player2->doingAction = true;
			if (!App->player2->noSword)
				App->player2->lost1 = true;
			else
				App->player2->losenw = true;


			if (SDL_GetTicks() - startingtime < 1200) {

				App->fonts->BlitText((SCREEN_WIDTH / 2) - 30, 70, 2, "IPPON");
				if (played == 3) {
					Mix_PlayChannel(-1, App->audio->effects[9], 0);
					played++;
					timerRound = true;

				}
			}
			else if (SDL_GetTicks() - startingtime < 2000) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "JUBEI 1");
				if (played == 4)
				{
					Mix_PlayChannel(-1, App->audio->effects[10], 0);
					played++;
					timerRound = true;
				}
			}
		}
		if (player == 2 && SDL_GetTicks() - startingtime > 500) {
			//Player1 1st death animation
						//Player1 1st victory animation
			App->player2->doingAction = true;
			if (!App->player2->noSword)
				App->player2->winning1 = true;
			else
				App->player2->winnw = true;


			//Player2 1st death animation
			App->player->doingAction = true;
			if (!App->player->noSword)
				App->player->lost1 = true;
			else
				App->player->losenw = true;
			//Player2 1st victory animation
			if (SDL_GetTicks() - startingtime < 1200) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 30, 70, 2, "IPPON");
				if (played == 3) {
					Mix_PlayChannel(-1, App->audio->effects[9], 0);
					played++;
					timerRound = true;
					App->player->inputs.Push(IN_DEATH);

				}
			}
			else if (SDL_GetTicks() - startingtime < 2000) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "JUBEI 2");
				if (played == 4) {
					Mix_PlayChannel(-1, App->audio->effects[10], 0);
					played++;
					timerRound = true;
				}
			}


		}
		else if (player == 0 && SDL_GetTicks() - startingtime > 500) {
			if (SDL_GetTicks() - startingtime < 1200) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 30, 70, 2, "TIME UP");
				if (played == 3) {
					Mix_PlayChannel(-1, App->audio->effects[13], 0);
					played++;
				}
			}
			else if (SDL_GetTicks() - startingtime < 2000) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "DRAW");

			}
		}


		if (SDL_GetTicks() - startingtime > 2500) { //Substituir  por getanimationend
			App->interface->showscore = true;

			if (player == 1)App->interface->playerwins = 1;
			if (player == 2)App->interface->playerwins = 2;
			if (player == 0)App->interface->playerwins = 0;

			if (App->interface->scoreended)
			{
				App->interface->showscore = false;

				played = 1;
				App->scene_hanzo->roundFinish();

			}

		}
	}

	else {
		if (player == 1 && SDL_GetTicks() - startingtime > 500) {
			App->player->doingAction = true;
			if (!App->player->noSword)
				App->player->winning2 = true;
			else
				App->player->winnw = true;


			//Player2 1st death animation
			App->player2->doingAction = true;
			if (!App->player2->noSword)
				App->player2->lost2 = true;
			else
				App->player2->losenw = true;
			if (SDL_GetTicks() - startingtime < 1430) {

				App->fonts->BlitText((SCREEN_WIDTH / 2) - 30, 70, 2, "VICTORY");
				if (played == 3) {
					Mix_PlayChannel(-1, App->audio->effects[11], 0);
					played++;
					timerRound = true;
					App->player2->p2inputs.Push(IN_DEATH2);

				}
			}
			//Player1 2nd victory animation

			//Player2 2nd death animation
			else if (SDL_GetTicks() - startingtime < 2000) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "WELL DONE");
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 102, 2, "JUBEI 1");
				if (played == 4) {
					Mix_PlayChannel(-1, App->audio->effects[10], 0);
					played++;
				}
			}
			else if (SDL_GetTicks() - startingtime < 2800) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "WELL DONE");
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 102, 2, "JUBEI 1");
				if (played == 5 && SDL_GetTicks() - startingtime < 2100) {
					Mix_PlayChannel(-1, App->audio->effects[12], 0);
					played++;
				}
			}
		}
		if (player == 2 && SDL_GetTicks() - startingtime > 500) {
			App->player2->doingAction = true;
			if (!App->player2->noSword)
				App->player2->winning2 = true;
			else
				App->player2->winnw = true;


			//Player2 1st death animation
			App->player->doingAction = true;
			if (!App->player->noSword)
				App->player->lost2 = true;
			else
				App->player->losenw = true;
			if (SDL_GetTicks() - startingtime < 1200) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 30, 70, 2, "VICTORY");
				if (played == 3) {
					Mix_PlayChannel(-1, App->audio->effects[11], 0);
					played++;
					App->player->inputs.Push(IN_DEATH);

				}
			}
			//Player1 2nd death animation
			//Player2 2nd victory animation
			else if (SDL_GetTicks() - startingtime < 2000) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "WELL DONE");
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 102, 2, "JUBEI 2");
				if (played == 4) {
					Mix_PlayChannel(-1, App->audio->effects[10], 0);
					played++;
				}
			}
			else if (SDL_GetTicks() - startingtime < 2800) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "WELL DONE");
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 102, 2, "JUBEI 2");
				if (played == 5 && SDL_GetTicks() - startingtime < 2100) {
					Mix_PlayChannel(-1, App->audio->effects[12], 0);
					played++;
				}
			}
		}
		else if (player == 0 && SDL_GetTicks() - startingtime > 500) {
			if (SDL_GetTicks() - startingtime < 1200) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 30, 70, 2, "TIME UP");
				if (played == 3) {
					Mix_PlayChannel(-1, App->audio->effects[13], 0);
					played++;
				}
			}
			else if (SDL_GetTicks() - startingtime < 2000) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "DRAW");

			}
		}
		if (SDL_GetTicks() - startingtime > 2500 && player > 0) { //Substituir  por getanimationend
			App->interface->showscore = true;
			if (player == 1)App->interface->playerwins = 1;
			if (player == 2)App->interface->playerwins = 2;
			if (player == 0)App->interface->playerwins = 0;

			if (App->interface->scoreended)
			{
				App->interface->showscore = false;
				App->scene_hanzo->BattleEnd();
				App->player->powValue = 0;
				App->player2->powValue = 0;
			}
		}
		else if (SDL_GetTicks() - startingtime > 3500)
		{

			played = 1;

			App->scene_hanzo->roundFinish();
		}
	}
}


