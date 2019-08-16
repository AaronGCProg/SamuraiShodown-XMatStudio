#include "ModulePlayerSelection.h"
#include "Application.h"
#include "Globals.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModuleSceneHanzo.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include"ModuleFadeToBlack.h"



ModulePlayerSelection::ModulePlayerSelection()
{
	background.w = 304;
	background.h = 224;
	background.x = 0;
	background.y = 0;

	p1p2selector.x = 260;
	p1p2selector.y = 168;
	p1p2selector.w = 40;
	p1p2selector.h = 48;

	p1p2selectorwhite.x = 219;
	p1p2selectorwhite.y = 168;
	p1p2selectorwhite.w = 40;
	p1p2selectorwhite.h = 48;

	jubeiword.x = 0;
	jubeiword.y = 0;
	jubeiword.w = 76;
	jubeiword.h = 33;

	jubeiwordwhite.x = 0;
	jubeiwordwhite.y = 33;
	jubeiwordwhite.w = 76;
	jubeiwordwhite.h = 33;

	japanword.x = 79;
	japanword.y = 0;
	japanword.w = 41;
	japanword.h = 15;

	japanwordwhite.x = 79;
	japanwordwhite.y = 16;
	japanwordwhite.w = 41;
	japanwordwhite.h = 15;



}
ModulePlayerSelection::~ModulePlayerSelection() {}

bool ModulePlayerSelection::Delay::CountDelayInFrames(int delayframes)//returns false if the time set hasn't passed but true if it has
{
	if (!countingdelay) { countingdelay = true; delayleft = delayframes; }
	delayleft--;
	if (delayleft == 0)
	{
		countingdelay = false;
		return true;
	}
	else return false;
};


bool ModulePlayerSelection::Start()
{
	graphics = App->textures->Load("Assets/Sprites/PlayerSelectionBackground.png");
	ui = App->textures->Load("Assets/Sprites/UIspritesheet2.png");
	ui2 = App->textures->Load("Assets/Sprites/Jubeiselection.png");

	App->audio->soundtracks[2] = Mix_LoadMUS("Assets/Music/Player_Select.ogg");
	Mix_PlayMusic(App->audio->soundtracks[2], 2);

	App->audio->effects[39] = Mix_LoadWAV("Assets/Music/SelectCharacter.wav");


	App->player->Enable();
	App->player2->Enable();
	App->player->position.x = 135;
	App->player2->position.x = 290;

	return true;
}

bool ModulePlayerSelection::CleanUp()
{
	App->audio->CleanUp();
	App->player->Disable();
	App->player2->Disable();
	App->textures->Unload(ui2);
	App->textures->Unload(ui);
	App->textures->Unload(graphics);


	return true;
}
update_status ModulePlayerSelection::PreUpdate()
{
	App->render->Blit(graphics, 0, 0, false, &background, NULL, true);//backgroundBlit

	if (Timerwiggle.CountDelayInFrames(4))//6 frames to change between white/normal
	{
		if (showingp1p2)showingp1p2 = false;
		else showingp1p2 = true;
	}
	if (showingp1p2)App->render->Blit(ui, 152, 65, false, &p1p2selector, NULL, true);//p1p2selectorBlit
	else App->render->Blit(ui, 152, 65, false, &p1p2selectorwhite, NULL, true);//p1p2selectorwhiteBlit

	return UPDATE_CONTINUE;
}
update_status ModulePlayerSelection::Update()
{
	//App->render->Blit(graphics, 0, 0, false, &background, NULL, true);


	if (Timerselect.CountDelayInFrames(60 * 30) || App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || App->input->keyboard[SDL_SCANCODE_P] == 1 || App->input->controller_player1_Start_pressed == true || App->input->controller_player2_Start_pressed == true)
	{
		if (!selected1 && (App->input->controller_player1_Start_pressed == true || App->input->keyboard[SDL_SCANCODE_SPACE] == 1))
		{
			Mix_PlayChannel(-1, App->audio->effects[39], 0);

			selected1 = true;
			textwhite1 = true;

		}
		if (!selected2 && (App->input->controller_player2_Start_pressed == true || App->input->keyboard[SDL_SCANCODE_P] == 1))
		{
			Mix_PlayChannel(-1, App->audio->effects[39], 0);


			selected2 = true;
			textwhite2 = true;
		}
	}

	if (!selected1 || !selected2)
	{
		if (Timerend.CountDelayInFrames(60 * 33))
		{
			Mix_FadeOutMusic(2000);
			App->fade->FadeToBlack(App->scene_selection, App->scene_hanzo, 2.0f);
		}
	}//end

	if (selected1&&selected2)
	{
		if (Timerendquick.CountDelayInFrames(60 * 3))
		{
			Mix_FadeOutMusic(2000);
			App->fade->FadeToBlack(App->scene_selection, App->scene_hanzo, 2.0f);
		}
	}//endquick}


		App->render->Blit(ui2, 53, 194, false, &japanword, NULL, true);//japanleft
		App->render->Blit(ui2, 32, 160, false, &jubeiword, NULL, true);//jubeileft

		App->render->Blit(ui2, 213, 194, false, &japanword, NULL, true);//japanleft
		App->render->Blit(ui2, 192, 160, false, &jubeiword, NULL, true);//jubeileft

	if (textwhite1)
	{
		if (!Timerwhite1.CountDelayInFrames(8))
		{
			App->render->Blit(ui2, 53, 194, false, &japanwordwhite, NULL, true);//japanleft
			App->render->Blit(ui2, 32, 160, false, &jubeiwordwhite, NULL, true);//jubeileft

		}
		else textwhite1 = false;
	}
	

	if (textwhite2)
	{
		if (!Timerwhite1.CountDelayInFrames(8))
		{
			App->render->Blit(ui2, 213, 194, false, &japanwordwhite, NULL, true);//japanleft
			App->render->Blit(ui2, 192, 160, false, &jubeiwordwhite, NULL, true);//jubeileft

		}
		else textwhite2 = false;
	}
	



	return UPDATE_CONTINUE;
}
