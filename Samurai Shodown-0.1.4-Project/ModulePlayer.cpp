#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"


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

	// hurt animation
	hurtLow.PushBack({ 1421,24,79,97 });
	hurtLow.speed = 0.05f;

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
	App->audio->effects[2] = Mix_LoadWAV("Assets/Music/haohmaru_getshitted1.wav");


	body = App->collision->AddCollider({ position.x, position.y - 113, 73, 113 }, COLLIDER_PLAYER, this);


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
	
	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN)
	{
		if (godMode)
			godMode = false;
		else
			godMode = true;

	}
	else if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_UP) {
		if (godMode) {
			body->to_delete = true;
		}

		if (!godMode) {
			body = App->collision->AddCollider({ position.x, position.y, 73, 113 }, COLLIDER_PLAYER, this);
		}
	}

	//move
	if (App->input->keys[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && !doingAction)
	{
		current_animation = &forward;
		position.x += speed;
	}
	if (App->input->keys[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && !doingAction)
	{
		current_animation = &backward;
		position.x -= speed;
	}
	//Jump
	if (App->input->keys[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && !doingAction)
	{
		jumping = true; doingAction = true;
	}
	//Punch
	if (App->input->keys[SDL_SCANCODE_X] == KEY_STATE::KEY_REPEAT && !doingAction)
	{
		punching = true; doingAction = true;
	}
	//Kick
	if (App->input->keys[SDL_SCANCODE_C] == KEY_STATE::KEY_REPEAT && !doingAction)
	{
		kicking = true; doingAction = true;
	}
	// Tornado
	if (App->input->keys[SDL_SCANCODE_V] == KEY_STATE::KEY_REPEAT && !doingAction)
	{		
		tornading = true; doingAction = true;
		Mix_PlayChannel(-1, App->audio->effects[0], 0);
		Mix_PlayChannel(-1, App->audio->effects[1], 0);	
		App->particles->tornadoHao.speed.x = +3;
		App->particles->AddParticle(App->particles->tornadoHao, position.x + 20, position.y - 70, COLLIDER_PLAYER_SHOT);

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

	// TODO 3: Update collider position to player position
	body->SetPos(position.x, position.y - 113);
	

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, playerFlip, &r); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)
	
	return UPDATE_CONTINUE;
}

// TODO 4: Detect collision with a wall. If so, do something.
void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
		if(this->body == c1){
			if(c1->rect.x < c2->rect.x)
			position.x = c2->rect.x - c1->rect.w;
			if(c1->rect.x > c2->rect.x)
				position.x = c2->rect.x + c2->rect.w;
			
		}

		if (c2->type == COLLIDER_ENEMY_SHOT) {
			Mix_PlayChannel(-1, App->audio->effects[2], 0);
			getsHit = true; doingAction = true;
		}
}
