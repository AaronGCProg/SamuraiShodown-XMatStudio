#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleReferee.h"



ModuleReferee::ModuleReferee()
{


	// idle animation (arcade sprite sheet)
	idle.PushBack({ 1, 1, 58, 70 }, 4, { NULL,NULL }, NULL, NULL, NULL, NULL);
	
	
	// walk backward animation 
	backward.PushBack({ 60, 2, 58 , 69 }, 5, { NULL,NULL }, NULL, NULL, NULL, NULL);
	backward.PushBack({ 372,1,58,70 }, 5, { NULL,NULL }, NULL, NULL, NULL, NULL);
	backward.PushBack({ 431, 2, 58 , 69 }, 5, { NULL,NULL }, NULL, NULL, NULL, NULL);
	backward.PushBack({ 490, 5,58,70 }, 5, { NULL,NULL }, NULL, NULL, NULL, NULL);
	backward.PushBack({ 557, 4, 58 , 69 }, 5, { NULL,NULL }, NULL, NULL, NULL, NULL);
	
	
	// walk forward animation 
	forward.PushBack({ 60, 2, 58 , 69 }, 5, { NULL,NULL }, NULL, NULL, NULL, NULL);
	forward.PushBack({ 119, 1,58,70 }, 5, { NULL,NULL }, NULL, NULL, NULL, NULL);
	forward.PushBack({ 178, 2,58,69 }, 5, { NULL,NULL }, NULL, NULL, NULL, NULL);
	forward.PushBack({ 237, 5,66,66 }, 5, { NULL,NULL }, NULL, NULL, NULL, NULL);
	forward.PushBack({ 311, 4,60,67 }, 5, { NULL,NULL }, NULL, NULL, NULL, NULL);


	//red flag
	redFlag.PushBack({ 1,94,51,70 },   8, { NULL,NULL }, NULL, NULL, NULL, NULL);
	redFlag.PushBack({ 53,94,51,70 },  8, { NULL,NULL }, NULL, NULL, NULL, NULL);
	redFlag.PushBack({ 105,72,81,92 }, 12, { NULL,NULL }, NULL, NULL, NULL, NULL);
	redFlag.PushBack({ 187,73,77,91 }, 12, { NULL,NULL }, NULL, NULL, NULL, NULL);
	redFlag.PushBack({ 265,73,73,91 }, 10, { NULL,NULL }, NULL, NULL, NULL, NULL);
	redFlag.PushBack({ 349,85,69,79 }, 8, { NULL,NULL }, NULL, NULL, NULL, NULL);


	//white flag
	whiteFlag.PushBack({ 1,187,51,70 },   8, { NULL,NULL }, NULL, NULL, NULL, NULL);
	whiteFlag.PushBack({ 53,187,51,70 },  8, { NULL,NULL }, NULL, NULL, NULL, NULL);
	whiteFlag.PushBack({ 105,165,81,92 }, 12, { NULL,NULL }, NULL, NULL, NULL, NULL);
	whiteFlag.PushBack({ 187,166,77,91 }, 12, { NULL,NULL }, NULL, NULL, NULL, NULL);
	whiteFlag.PushBack({ 265,166,73,91 }, 10, { NULL,NULL }, NULL, NULL, NULL, NULL);
	whiteFlag.PushBack({ 349,178,69,79 }, 8, { NULL,NULL }, NULL, NULL, NULL, NULL);




}

ModuleReferee::~ModuleReferee()
{}

// Load assets
bool ModuleReferee::Start()
{

	position.x = 121;
	position.y = 170; //369 about the same position on the ground as its on the real game.

	playerFlip = false;
	bool ret = true;

	LOG("Listening for Arrow keys + SPACE:\n");
	LOG("Loading player textures");

	graphics = App->textures->Load("Assets/Sprites/referee.png"); // arcade version
	
	

	current_animation = &idle;

	return ret;
}

// Unload assets
bool ModuleReferee::CleanUp()
{


	LOG("Unloading Referee");

	App->textures->Unload(graphics);
	

	return true;
}

// Update: draw background
update_status ModuleReferee::Update()
{
	//referee flip
	if (App->player->position.x+35 > App->player2->position.x) { playerFlip = true; }
	else  playerFlip = false;

	// referee flags when someone gets hit
	if (App->player->getsHit) { current_animation = &whiteFlag; }
	if (whiteFlag.GetAnimEnd() == true) { current_animation = &idle; whiteFlag.SetAnimEnd(false); }


	if (App->player2->getsHit) { current_animation = &redFlag;}
	if (redFlag.GetAnimEnd() == true) { current_animation = &idle; redFlag.SetAnimEnd(false); }


	//referee movement logic
	int dist= abs(App->player->position.x - App->player2->position.x); //distance betwen players


	
	if (App->player->position.x > App->player2->position.x)
	{
		position.x = App->player2->position.x + (dist / 2) - 28;
	}
	else
	{
		position.x = App->player->position.x + (dist / 2) - 28;
	}
	

	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, position.x, position.y - r.h, playerFlip, &r);

	return UPDATE_CONTINUE;
}





