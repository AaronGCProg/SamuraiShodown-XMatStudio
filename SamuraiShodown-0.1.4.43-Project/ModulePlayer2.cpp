#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2()
{

					  // idle animation (arcade sprite sheet)
	idle.PushBack({ 1, 8, 73, 113 }, FRAMEDEPRUEBA);
	idle.PushBack({ 75, 10, 72, 111 }, FRAMEDEPRUEBA);
	idle.PushBack({ 148, 12, 71, 109 }, FRAMEDEPRUEBA);
	idle.PushBack({ 220, 14, 71, 107 }, FRAMEDEPRUEBA);
	idle.PushBack({ 148, 12, 71, 109 }, FRAMEDEPRUEBA);
	idle.PushBack({ 75, 10, 72, 111 }, FRAMEDEPRUEBA);
	//idle.speed = 0.125f;

	// walk backward animation 
	backward.PushBack({ 767, 10, 82, 111 }, FRAMEDEPRUEBA);
	backward.PushBack({ 849, 7, 74, 114 }, FRAMEDEPRUEBA);
	backward.PushBack({ 924, 3, 68, 118 }, FRAMEDEPRUEBA);
	backward.PushBack({ 993, 1, 65, 120 }, FRAMEDEPRUEBA);
	backward.PushBack({ 924, 3, 68, 118 }, FRAMEDEPRUEBA);
	backward.PushBack({ 849, 7, 74, 114 }, FRAMEDEPRUEBA);
	backward.PushBack({ 767, 10, 82, 111 }, FRAMEDEPRUEBA);
	//backward.speed = 0.1f;

	// walk forward animation 
	forward.PushBack({ 1089,12,75,109 }, FRAMEDEPRUEBA);
	forward.PushBack({ 1165,9,68,112 }, FRAMEDEPRUEBA);
	forward.PushBack({ 1234,5,61,116 }, FRAMEDEPRUEBA);
	forward.PushBack({ 1296,3,56,118 }, FRAMEDEPRUEBA);
	forward.PushBack({ 1352,9,69,112 }, FRAMEDEPRUEBA);
	//forward.speed = 0.1f;

	// Kick animation 
	kick.PushBack({ 292,26,66,95 }, FRAMEDEPRUEBA);
	kick.PushBack({ 359,23,86,98 }, FRAMEDEPRUEBA);
	kick.PushBack({ 292,26,66,95 }, FRAMEDEPRUEBA);
	kick.PushBack({ 1, 8, 73, 113 }, FRAMEDEPRUEBA);
	//kick.speed = 0.12f;

	// Punch animation 
	punch.PushBack({ 1,122,68,127 }, FRAMEDEPRUEBA);
	punch.PushBack({ 70,153,78,96 }, FRAMEDEPRUEBA);
	punch.PushBack({ 149,156,130,93 }, FRAMEDEPRUEBA);
	punch.PushBack({ 280,156,130,93 }, FRAMEDEPRUEBA);
	punch.PushBack({ 411,167,129,93 }, FRAMEDEPRUEBA);
	punch.PushBack({ 541,167,127,93 }, FRAMEDEPRUEBA);
	punch.PushBack({ 669,167,119,93 }, FRAMEDEPRUEBA);
	punch.PushBack({ 789,164,130,85 }, FRAMEDEPRUEBA);
	//punch.speed = 0.2f;

	//jump animation 
	jump.PushBack({ 484,9,60,112 }, FRAMEDEPRUEBA);
	jump.PushBack({ 545,30,74,91 }, FRAMEDEPRUEBA);
	jump.PushBack({ 620,38,76,83 }, FRAMEDEPRUEBA);
	jump.PushBack({ 697,11,68,110 }, FRAMEDEPRUEBA);
	jump.loop = false;
	//jump.speed = 0.05f;

	// hurt animation
	hurtLow.PushBack({ 1421,24,79,97 }, FRAMEDEPRUEBA);
	//hurtLow.speed = 0.05f;

	// Tornado animation
	tornado.PushBack({ 1, 271, 100, 102 }, FRAMEDEPRUEBA);
	tornado.PushBack({ 102,271,81,103 }, FRAMEDEPRUEBA);
	tornado.PushBack({ 185,277,82, 95 }, FRAMEDEPRUEBA);
	tornado.PushBack({ 268,268,67,107 }, FRAMEDEPRUEBA);
	tornado.PushBack({ 443,262,72,174 }, FRAMEDEPRUEBA);
	tornado.PushBack({ 516,261,112,113 }, FRAMEDEPRUEBA);
	tornado.PushBack({ 628,263,113,105 }, FRAMEDEPRUEBA);
	tornado.PushBack({ 741,263,119,105 }, FRAMEDEPRUEBA);
	tornado.PushBack({ 860,263,98,105 }, FRAMEDEPRUEBA);
	//tornado.speed = 0.2f;
}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	position.x = 200;
	position.y = 200; //369 about the same position on the ground as its on the real game.

	LOG("Loading player textures");
	bool ret = true;
	playerFlip = true;

	health = 0; 

	graphics = App->textures->Load("Assets/Sprites/haohmaru.png"); // arcade version
	ui = App->textures->Load("Assets/Sprites/UIspritesheet2.png"); // health bar 
	groundlevelaux = position.y;



	body = App->collision->AddCollider({ position.x, position.y - 113, 73, 113 }, COLLIDER_ENEMY, this);

	return ret;
}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading Character");
	App->textures->Unload(graphics);
	App->textures->Unload(ui);


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

	if (App->input->keys[SDL_SCANCODE_KP_3] == KEY_STATE::KEY_REPEAT && !doingAction)
	{
		tornading = true; doingAction = true;
		Mix_PlayChannel(-1, App->audio->effects[0], 0);
		Mix_PlayChannel(-1, App->audio->effects[1], 0);
		App->particles->tornadoHao.speed.x = -3;
		App->particles->AddParticle(App->particles->tornadoHao, position.x - 20, position.y - 70, COLLIDER_ENEMY_SHOT);

	}

	if (doingAction)
	{
		if (kicking) {
			//set kick anim
			current_animation = &kick;
			//stop kick anim
			if (kick.GetAnimEnd() == true) { kicking = false; doingAction = false; kick.SetAnimEnd(false); }
		}

		if (tornading) {
			//set punch anim
			current_animation = &tornado;

			//stop punch anim
			if (tornado.GetAnimEnd() == true) { tornading = false; doingAction = false; tornado.SetAnimEnd(false); }
		}

		if (punching) {
			//set punch anim
			current_animation = &punch;
			//stop punch anim
			if (punch.GetAnimEnd() == true) { punching = false; doingAction = false; punch.SetAnimEnd(false); }
		}

		if (getsHit) {
			//set punch anim
			current_animation = &hurtLow;
			//stop punch anim
			if (hurtLow.GetAnimEnd() == true) { getsHit = false; doingAction = false; hurtLow.SetAnimEnd(false); }
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

	body->SetPos(position.x, position.y - 113);

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, position.x, position.y - r.h, playerFlip, &r); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)

	


	SDL_Rect healthBar = { 90, 81, 134, 15 };
	App->render->Blit(ui, 167, 15, false, &healthBar, NULL, true);

	if (HEALTH_VALUE > health + 50) {
		SDL_Rect healthValue = { 90, 97, HEALTH_VALUE - health, 9 };
		App->render->Blit(ui, 168, 17, false, &healthValue, NULL, true);
	}
	else {
		SDL_Rect healthValue = { 90, 107, HEALTH_VALUE - health, 9 };
		App->render->Blit(ui, 168, 17, false, &healthValue, NULL, true);
	}

	

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {
	if (this->body == c1) {
		if (c1->rect.x < c2->rect.x)
			position.x = c2->rect.x - c1->rect.w;
		if (c1->rect.x > c2->rect.x)
			position.x = c2->rect.x + c2->rect.w;
	}
	if (c2->type == COLLIDER_PLAYER_SHOT) {
		Mix_PlayChannel(-1, App->audio->effects[2], 0);
		health += 30;
		getsHit = true; doingAction = true;
	}
	if (c2->type == COLLIDER_PLAYER_ATTACK) {
		Mix_PlayChannel(-1, App->audio->effects[2], 0);
		health += 20;
		getsHit = true; doingAction = true;

		position.x = c2->rect.x + c1->rect.w;

	}
}