#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 200; //369 about the same position on the ground as its on the real game.

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 1, 8, 73, 113 });
	idle.PushBack({ 75, 10, 72, 111 });
	idle.PushBack({ 148, 12, 71, 109 });
	idle.PushBack({ 220, 14, 71, 107 });
	idle.PushBack({ 148, 12, 71, 109 });
	idle.PushBack({ 75, 10, 72, 111 });
	idle.speed = 0.125f;

	// walk backward animation 
	backward.PushBack({ 767, 10, 82, 111 });
	backward.PushBack({ 849, 7, 74, 114 });
	backward.PushBack({ 924, 3, 68, 118 });
	backward.PushBack({ 993, 1, 65, 120 });
	backward.PushBack({ 924, 3, 68, 118 });
	backward.PushBack({ 849, 7, 74, 114 });
	backward.PushBack({ 767, 10, 82, 111 });
	backward.speed = 0.1f;

	// walk forward animation 
	forward.PushBack({ 1089,12,75,109 });
	forward.PushBack({ 1165,9,68,112 });
	forward.PushBack({ 1234,5,61,116 });
	forward.PushBack({ 1296,3,56,118 });
	forward.PushBack({ 1352,9,69,112 });
	forward.speed = 0.1f;

	// Kick animation 
	kick.PushBack({ 292,26,66,95 });
	kick.PushBack({ 359,23,86,98 });
	kick.PushBack({ 292,26,66,95 });
	kick.PushBack({ 1, 8, 73, 113 });
	kick.speed = 0.12f;

	// Punch animation 
	punch.PushBack({ 1,122,68,127 });
	punch.PushBack({ 70,153,78,96 });
	punch.PushBack({ 149,156,130,93 });
	punch.PushBack({ 280,156,130,93 });
	punch.PushBack({ 411,167,129,93 });
	punch.PushBack({ 541,167,127,93 });
	punch.PushBack({ 669,167,119,93 });
	punch.PushBack({ 789,164,130,85 });
	punch.speed = 0.2f;

	//jump animation 
	jump.PushBack({ 484,9,60,112 });
	jump.PushBack({ 545,30,74,91 });
	jump.PushBack({ 620,38,76,83 });
	jump.PushBack({ 697,11,68,110 });
	jump.speed = 0.05f;

	// Tornado animation
	tornado.PushBack({ 1, 271, 100, 102 });
	tornado.PushBack({ 102,271,81,103 });
	tornado.PushBack({ 185,277,82, 95 });
	tornado.PushBack({ 268,268,67,107 });
	tornado.PushBack({ 443,262,72,174 });
	tornado.PushBack({ 516,261,112,113 });
	tornado.PushBack({ 628,263,113,105 });
	tornado.PushBack({ 741,263,119,105 });
	tornado.PushBack({ 860,263,98,105 });
	tornado.speed = 0.2f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	playerFlip = false;

	graphics = App->textures->Load("Assets/Sprites/haohmaru.png"); // arcade version
	groundlevelaux = position.y;

	App->audio->effects[0] = Mix_LoadWAV("Assets/Music/haohmaru_senpuuretsuzan.wav");
	App->audio->effects[1] = Mix_LoadWAV("Assets/Music/HaohmaruTornado.wav");
	
	return ret;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading Character");
	App->textures->Unload(graphics);

	App->audio->CleanUp();

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	//move
	if (App->input->keyboard[SDL_SCANCODE_D] == 1 && !doingAction)
	{
		current_animation = &forward;
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_A] == 1 && !doingAction)
	{
		current_animation = &backward;
		position.x -= speed;
	}
	//Jump
	if (App->input->keyboard[SDL_SCANCODE_W] == 1 && !doingAction)
	{
		jumping = true; doingAction = true;
	}
	//Punch
	if (App->input->keyboard[SDL_SCANCODE_X] == 1 && !doingAction)
	{
		punching = true; doingAction = true;
	}
	//Kick
	if (App->input->keyboard[SDL_SCANCODE_C] == 1 && !doingAction)
	{
		kicking = true; doingAction = true;
	}
	// Tornado
	if (App->input->keyboard[SDL_SCANCODE_V] == 1 && !doingAction)
	{		
		tornading = true; doingAction = true;
		Mix_PlayChannel(-1, App->audio->effects[0], 0);
		Mix_PlayChannel(-1, App->audio->effects[1], 0);	
		App->particles->AddParticle(App->particles->tornadoHao, position.x + 20, position.y - 70);
	}

	if (doingAction)
	{
		if (kicking) {
			//set kick anim
			current_animation = &kick;
			//stop kick anim
			if (kick.GetAnimEnd() == true) { kicking = false; doingAction = false; kick.SetAnimEnd(false); }
		}

		if (punching) {
			//set punch anim
			current_animation = &punch;
			//stop punch anim
			if (punch.GetAnimEnd() == true) { punching = false; doingAction = false; punch.SetAnimEnd(false); }
		}

		if (tornading) {
			//set punch anim
			current_animation = &tornado;
			//stop punch anim
			if (tornado.GetAnimEnd() == true) { tornading = false; doingAction = false; tornado.SetAnimEnd(false); }
		}

		if (jumping)
		{
			//set jump anim
			current_animation = &jump;
			position.y = groundlevelaux - (JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY)*pow(jumpingframe, 2));//MRUA formula
			hasjumped = true;
			//stop punch anim
			if (position.y > groundlevelaux && hasjumped == true)	//end of the jump
			{
				jumpingframe = 0;
				hasjumped = false;
				jumping = false;
				position.y = groundlevelaux;
				doingAction = false;
			}
			jumpingframe++;
		}
	}

	//Jump Logic------------------------------------------

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, playerFlip, &r); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)
	
	return UPDATE_CONTINUE;
}