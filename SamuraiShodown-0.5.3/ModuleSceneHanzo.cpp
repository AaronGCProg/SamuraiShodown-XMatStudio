#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneHanzo.h"
#include "ModuleSceneCongrats.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"
#include "ModuleFight.h"
#include "ModuleReferee.h"
#include "ModuleFadeToBlack.h"



#include <stdio.h> //for the sprintf_s function



ModuleSceneHanzo::ModuleSceneHanzo()
{
	//for (int i = 0; i < 3; i++)//haohmarubackground anim
	//{
	//	if (i == 3) 
	//	{
	//		for (int j = 0; j < 1; j++) 
	//		{
	//			backgroundanim.PushBack({ (640 * j),416 * i,640,416 }, 10, { 0,0 }, 0, {}, {}, {});
	//		}
	//	}
	//	else
	//	{
	//		for (int j = 0; j < 2; j++) 
	//		{
	//			backgroundanim.PushBack({ (640 * j),416 * i,640,416 }, 10, { 0,0 }, 0, {}, {}, {});
	//		}
	//	}
	//}

	//backgroundanim.speed = (0.1f);
	Bird.PushBack({146,865,23,10 },15, { 0,0 }, 0, {}, {}, {});
	Bird.PushBack({146,875,23,10 }, 15, { 0,0 }, 0, {}, {}, {});
	Bird.PushBack({ 146,885,23,10 }, 15, { 0,0 }, 0, {}, {}, {});

	BirdShadow.PushBack({ 169,865,14,14 }, 15, { 0,0 }, 0, {}, {}, {});
	BirdShadow.PushBack({ 169,879,14,14 }, 15, { 0,0 }, 0, {}, {}, {});
	BirdShadow.PushBack({ 169,893,14,14 }, 15, { 0,0 }, 0, {}, {}, {});

	LowSky.PushBack({0,736,146,39}, 5, { 0,0 }, 0, {}, {}, {});
	LowSky.PushBack({ 0,775,146,39 }, 5, { 0,0 }, 0, {}, {}, {});
	LowSky.PushBack({ 0,814,146,39 }, 5, { 0,0 }, 0, {}, {}, {});
	LowSky.PushBack({ 0,853,146,39 }, 5, { 0,0 }, 0, {}, {}, {}); 

	HighSky.PushBack({ 0,0,392,98 }, 10, { 0,0 }, 0, {}, {}, {});
	HighSky.PushBack({ 0,98,392,98 }, 10, { 0,0 }, 0, {}, {}, {});
	HighSky.PushBack({ 0,196,392,98}, 10, { 0,0 }, 0, {}, {}, {});
	HighSky.PushBack({ 0,294,392,98 }, 10, { 0,0 }, 0, {}, {}, {});
	HighSky.PushBack({ 0,392,392,98 }, 10, { 0,0 }, 0, {}, {}, {});
	HighSky.PushBack({ 0,490,392,98 }, 10, { 0,0 }, 0, {}, {}, {});


}

ModuleSceneHanzo::~ModuleSceneHanzo()
{}

// Load assets
bool ModuleSceneHanzo::Start()
{

	graphics = App->textures->Load("Assets/Sprites/GameStages.png");

	App->referee->Enable();
	App->player->Enable();
	App->player2->Enable();
	App->collision->Enable();
	App->interface->Enable();
	App->fight->Enable();

	App->audio->soundtracks[0] = Mix_LoadMUS("Assets/Music/HaohmaruMusic.ogg");

	if (!App->audio->soundtracks[0]) {
		LOG("Mix_LoadMUS(\"HaohmaruMusic.ogg\"): %s\n", Mix_GetError());
	}
	else {

		Mix_PlayMusic(App->audio->soundtracks[0], 2);
	}


	App->fight->startingtime = SDL_GetTicks();

	return true;
}

// UnLoad assets
bool ModuleSceneHanzo::CleanUp()
{
	LOG("Unloading HAO scene");

	App->audio->CleanUp();

	if (App->fight->finalwin1 || App->fight->finalwin2) {
		App->fight->Disable();
	}

	App->interface->Disable();
	App->collision->Disable();
	App->player2->Disable();
	App->player->Disable();
	App->referee->Disable();

	App->textures->Unload(graphics);
	

	return true;
}

// Update: draw background
update_status ModuleSceneHanzo::Update()
{
	if (App->player->position.x <= 5) { App->player->position.x = 5; }
    if (App->player->position.x >= 392) { App->player->position.x = 392; }
    if (App->player2->position.x <= 5) { App->player2->position.x = 5; }
    if (App->player2->position.x >= 392) { App->player2->position.x = 392; }
	// Draw everything --------------------------------------	
	//App->render->Blit(graphics, 0, -168, false, &(backgroundanim.GetCurrentFrame()), 1.0f); //ukyo background animation
	
	SDL_Rect backgroundstatic = { 0,588,391,148 };
	App->render->Blit(graphics, 0, 75, false, &backgroundstatic);//static part of the Hanzo stage
	App->render->Blit(graphics, 292, 98, false, &(Bird.GetCurrentFrame()));//Bird of the Hanzo stage
	App->render->Blit(graphics, 340, 157, false, &(BirdShadow.GetCurrentFrame()));//Birdshadow part of the Hanzo stage
	App->render->Blit(graphics, 0, 97, false, &(LowSky.GetCurrentFrame()));//LowSky part of the Hanzo stage
	App->render->Blit(graphics, 0, 0, false, &(HighSky.GetCurrentFrame()));//HighSky part of the Hanzo stage
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || App->input->controller_player1_Start_pressed == true) {
		BattleEnd();
	}

	return UPDATE_CONTINUE;
}


void ModuleSceneHanzo::roundFinish() {
	Mix_FadeOutMusic(2000);
	App->fade->FadeToBlack(App->scene_hanzo, App->scene_hanzo, 2.0f); //BUG
	App->fight->played = 1;
	App->fight->firstWin = true;

}

void ModuleSceneHanzo::BattleEnd() {
	Mix_FadeOutMusic(2000);
	App->fight->played = 1;
	App->fade->FadeToBlack(App->scene_hanzo, App->scene_congrats, 2.0f); //BUG

}