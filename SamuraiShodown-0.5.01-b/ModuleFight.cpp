#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneHao.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"
#include "ModuleFight.h"

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

	App->audio->CleanUp();


	return true;
}

// Update: draw background
update_status ModuleFight::Update()
{

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
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 3*16, 70, 2, "DUEL 1");
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
				App->fonts->BlitText((SCREEN_WIDTH / 2)  -3 * 16, 70, 2, "DUEL 2");
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
			App->fonts->BlitText((SCREEN_WIDTH / 2) -2*16, 70, 2, "BEGIN");
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
		if (App->player->health >= HEALTH_VALUE || App->interface->actualtime <= 0 && App->player->health > App->player2->health ) {
			if(!winplayer2){
			winplayer2 = true;
			}
			else if (!finalwin2 && winplayer2 && ((rounds == 2 && !winplayer1) || (rounds == 3 && winplayer1))) {
				finalwin2 = true;

			}

		if (App->player->health == HEALTH_VALUE){
			perfect = true;
		}
		WinRound1(2, finalwin2, perfect);

		}
		if (App->player2->health >= HEALTH_VALUE || App->interface->actualtime <= 0 && App->player->health < App->player2->health) {
			if(!winplayer1){
			winplayer1 = true;
			}
			else if (!finalwin1 && winplayer1 && ((rounds == 2 && !winplayer2) || (rounds == 3 && winplayer2))) {
				finalwin1 = true;

			}
			WinRound1(1, finalwin1, perfect);

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

	if(!final)
	{

	
	if (!firstWin) {
		firstWin = true;
		}
	if (player == 1 && SDL_GetTicks() - startingtime > 500) {
		//Player1 1st victory animation
		//Player2 1st death animation
	 if (SDL_GetTicks() - startingtime < 1200) {

		App->fonts->BlitText((SCREEN_WIDTH / 2) - 30, 70, 2, "IRRON");
		if(played ==3){
		Mix_PlayChannel(-1, App->audio->effects[9], 0);
		played++;
		timerRound = true;
		}
	 }
		else if (SDL_GetTicks() - startingtime < 2000) {
			App->fonts->BlitText((SCREEN_WIDTH / 2)-4*16, 70, 2, "HAOHMARU 1");
			if(played ==4)
			{
			Mix_PlayChannel(-1, App->audio->effects[10], 0);
			played++;
			timerRound = true;
			}
		}
	}
	if (player == 2 && SDL_GetTicks() - startingtime > 500) {
		//Player1 1st death animation
		//Player2 1st victory animation
		if (SDL_GetTicks() - startingtime < 1200) {
			App->fonts->BlitText((SCREEN_WIDTH / 2) - 30, 70, 2, "IRRON");
			if (played == 3) {
				Mix_PlayChannel(-1, App->audio->effects[9], 0);
				played++;
				timerRound = true;
			}
		}
		else if (SDL_GetTicks() - startingtime < 2000) {
			App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "HAOHMARU 2");
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


	if(SDL_GetTicks() - startingtime > 3500){ //Substituir  por getanimationend
	played = 1;
	App->scene_hao->roundFinish();
	}
	}

	else {
		if (player == 1 && SDL_GetTicks() - startingtime > 500) {
			if (SDL_GetTicks() - startingtime < 1430) {

				App->fonts->BlitText((SCREEN_WIDTH / 2) - 30, 70, 2, "VICTORY");
				if (played == 3) {
					Mix_PlayChannel(-1, App->audio->effects[11], 0);
					played++;
					timerRound = true;
				}
			}
			//Player1 2nd victory animation
			//Player2 2nd death animation
			else if (SDL_GetTicks() - startingtime < 2000) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "WELL DONE");
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 102, 2, "HAOHMARU 1");
				if (played == 4) {
					Mix_PlayChannel(-1, App->audio->effects[10], 0);
					played++;
				}
			}
			else if (SDL_GetTicks() - startingtime < 2800) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "WELL DONE");
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 102, 2, "HAOHMARU 1");
				if (played == 5 && SDL_GetTicks() - startingtime < 2100) {
					Mix_PlayChannel(-1, App->audio->effects[12], 0);
					played++;
				}
			}
		}
		if (player == 2 && SDL_GetTicks() - startingtime > 500) {
			if (SDL_GetTicks() - startingtime < 1200) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 30, 70, 2, "VICTORY");
				if (played == 3) {
					Mix_PlayChannel(-1, App->audio->effects[11], 0);
					played++;
				}
			}
			//Player1 2nd death animation
			//Player2 2nd victory animation
			else if (SDL_GetTicks() - startingtime < 2000) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "WELL DONE");
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 102, 2, "HAOHMARU 2");
				if (played == 4) {
					Mix_PlayChannel(-1, App->audio->effects[10], 0);
					played++;
				}
			}
			else if (SDL_GetTicks() - startingtime < 2800) {
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 70, 2, "WELL DONE");
				App->fonts->BlitText((SCREEN_WIDTH / 2) - 4 * 16, 102, 2, "HAOHMARU 2");
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
		if (SDL_GetTicks() - startingtime > 3000 && player > 0) { //Substituir  por getanimationend
			App->scene_hao->BattleEnd();
		}
		else if  (SDL_GetTicks() - startingtime > 3500) { 
			played = 1;
				App->scene_hao->roundFinish();
		}


	}
}

