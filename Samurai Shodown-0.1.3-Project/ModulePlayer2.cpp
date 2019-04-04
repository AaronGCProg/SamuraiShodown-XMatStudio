#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{
	position.x = 200;
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
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	playerFlip = true;

	graphics = App->textures->Load("Assets/Sprites/haohmaru.png"); // arcade version
	groundlevelaux = position.y;
	return ret;
}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading Character");
	App->textures->Unload(graphics);


	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	//move
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == 1 && !doingAction)
	{
		current_animation = &forward;
		position.x += speed;
	}
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == 1 && !doingAction)
	{
		current_animation = &backward;
		position.x -= speed;
	}
	//Jump
	if (App->input->keyboard[SDL_SCANCODE_UP] == 1 && !doingAction)
	{
		jumping = true; doingAction = true;
	}
	//Punch
	if (App->input->keyboard[SDL_SCANCODE_KP_1] == 1 && !doingAction)
	{
		punching = true; doingAction = true;
	}
	//Kick
	if (App->input->keyboard[SDL_SCANCODE_KP_2] == 1 && !doingAction)
	{
		kicking = true; doingAction = true;
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