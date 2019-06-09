#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleNeoGeo.h"
#include "ModuleSceneWelcome.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"




ModuleNEO::ModuleNEO()
{
	background.w = SCREEN_WIDTH* SCREEN_SIZE;
	background.h = SCREEN_HEIGHT* SCREEN_SIZE;
	background.x = 0;
	background.y = 0;

	

	
	NEO.PushBack({ 145,52,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 442,52,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 739,52,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1036,52,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1332,52,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1629,52,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1926,52,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 2223,52,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 88,276,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 385,276,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 681,276,227,40 },5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 978,276,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1274,276,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1576,276,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1868,276,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 2165,276,227,40 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);

	NEO.PushBack({ 37,501,227,38 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 341,503,227,35 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 645,504,227,30 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 949,505,227,28 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1253,506,227,28 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1557,508,227,25 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1861,509,227,22 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 2165,510,227,20 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 37,735,227,18 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 341,737,227,15 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 645,738,227,12 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 949,739,227,10}, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1253,740,227,8 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1557,742,227,5 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1862,743,227,2 }, 5, { 0,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	
	NEO.PushBack({ 45,967,227,2 }, 5, { 105,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 347,966,227,5 }, 5, { 98,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 651,965,227,8 }, 5, { 91,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 955,964,227,10 }, 5, { 84,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 973,963,227,12 }, 5, { 77,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1560,962,227,15 }, 5, { 70,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1864,960,227,18 }, 5, { 63,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 2168,959,227,20 }, 5, { 56,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 40,1182,227,22 }, 5, { 49,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 344,1181,227,25 }, 5, { 42,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 648,1179,227,28 }, 5, { 35,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 952,1178,227,28 }, 5, { 28,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1256,1177,227,30 }, 5, { 22,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	NEO.PushBack({ 1560,1176,227,35 }, 5, { 14,0 }, 0, {}, {}, {}, 0, 0, 0, 0);
	//NEO.PushBack({1864,1174 ,227,38 }, 5, { 7,0 }, 0, {}, {}, {}, 0, 0, 0, 0);

	Xmat.PushBack({ 3,1277,32,33 },235, { 7,0 }, 0, {}, {}, {}, 0, 0, 0, 0);


	






}

ModuleNEO::~ModuleNEO()
{}

// Load assets
bool ModuleNEO::Start()
{


	LOG("Loading SNK scene");

	graphics = App->textures->Load("Assets/Sprites/NeoGeo.png");

	App->audio->soundtracks[2] = Mix_LoadMUS("Assets/Music/_neoOP.ogg");

	if (!App->audio->soundtracks[2]) {
		LOG("Mix_LoadMUS(\"WelcomeMusic.ogg\"): %s\n", Mix_GetError());
	}
	else {
		Mix_PlayMusic(App->audio->soundtracks[2], 2);
	}
	neo = { 2165, 276, 227, 40 };
	neoAux = { ((SCREEN_WIDTH/2)-(227/2))*SCREEN_SIZE,((SCREEN_HEIGHT/2) - (35/2))*SCREEN_SIZE,0,40};
	neoAux.h *= SCREEN_SIZE;
	neoAux.w *= SCREEN_SIZE;


	return true;
}

// UnLoad assets
bool ModuleNEO::CleanUp()
{
	LOG("Unloading Welcome scene");

	App->audio->CleanUp();

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleNEO::Update()  //85*30
{
	
	
	SDL_SetRenderDrawColor(App->render->renderer, r, g, b, 255);
	SDL_RenderFillRect(App->render->renderer, &background); neoAux.x = ((SCREEN_WIDTH / 2))*SCREEN_SIZE;
	
	if (neoAux.h > SCREEN_SIZE && count>=75)
	{
		neoAux.h-=SCREEN_SIZE;
	}

	if (neoAux.h/2 <40*SCREEN_SIZE && count >= 150)
	{
		neo.x = 2168;
		neo.y = 959;

		neoAux.h += (40 / (SCREEN_SIZE*2));
		
	}
	if (neoAux.h > 40 * SCREEN_SIZE*2 && count >= 150)
	{
		neoAux.h = 40*SCREEN_SIZE*2;

	}
	

	if (neoAux.w < 227 * SCREEN_SIZE)
	{
		neoAux.w += SCREEN_SIZE*3;
	}

	if (count>=300)
	{		
		neoEnd = true;
	}

	if (!neoEnd)
	{
		if (countX==5 && count<=75)
		{			
			countX = 0;
			r-= 5;
			g-= 5;
			b-= 5;

			countY = 0;
		}
		if (countY == 5 && count >= 75 && count <= 150)
		{	
			r -= 5;
			g -= 5;
			b -= 5;

			
			countY = 0;
		}
		if (countY==5 && count>=150)
		{

			r -= 5;
			g -= 5;
			b -= 5;

			if (r < 0 || g < 0 || b < 0)
			{
				r = 0;
				g = 0;
				b = 0;
			}
		
			countY = 0;
			
		}
		neoAux.x -= neoAux.w / 2;
		SDL_RenderCopy(App->render->renderer, graphics , &neo, &neoAux);
		countX++;
		countY++;
		count++;
	}

	if (Xmat.GetAnimEnd())xmatEnd = true;
	if (!xmatEnd)
	{		
		App->render->Blit(graphics,10, SCREEN_HEIGHT-60, false, &(Xmat.GetCurrentFrame()), 1.0, false, false, false);
	}

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1 || App->input->controller_player1_Start_pressed == true || neoEnd) {

		Mix_FadeOutMusic(2000);
		App->fade->FadeToBlack(App->scene_neo, App->scene_welcome, 3.0f);
	}

	return UPDATE_CONTINUE;
}