#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include "ModuleAttack.h"
#include "ModulePlayer.h"



Uint32 jump_timer = 0;
Uint32 punch_timer = 0;
Uint32 kick_timer = 0;


ModulePlayer::ModulePlayer()
{


	// idle animation (arcade sprite sheet)
	idle.PushBack({ 1, 8, 73, 113 }, 8);
	idle.PushBack({ 75, 10, 72, 111 }, 7);
	idle.PushBack({ 148, 12, 71, 109 }, 8);
	idle.PushBack({ 220, 14, 71, 107 }, 9);
	idle.PushBack({ 148, 12, 71, 109 }, 9);
	idle.PushBack({ 75, 10, 72, 111 }, 9);
	//idle.speed = 0.125f;

	// walk backward animation 
	backward.PushBack({ 767, 10, 82, 111 }, 5);
	backward.PushBack({ 849, 7, 74, 114 }, 11);
	backward.PushBack({ 924, 3, 68, 118 }, 11);
	backward.PushBack({ 993, 1, 65, 120 }, 9);
	backward.PushBack({ 924, 3, 68, 118 }, 11);
	backward.PushBack({ 849, 7, 74, 114 }, 11);
	//backward.speed = 0.1f;

	// walk forward animation 
	forward.PushBack({ 1089,12,75,109 }, 5);
	forward.PushBack({ 1165,9,68,112 }, 11);
	forward.PushBack({ 1234,5,61,116 }, 9);
	forward.PushBack({ 1296,3,56,118 }, 11);
	forward.PushBack({ 1352,9,69,112 }, 9);
	//forward.speed = 0.1f;

	// Kick animation 
	kick.PushBack({ 292,26,66,95 }, 5);
	kick.PushBack({ 359,23,86,98 }, 6);
	kick.PushBack({ 292,26,66,95 }, 5);
	kick.PushBack({ 1, 8, 73, 113 }, 1);
	//kick.speed = 0.12f;

	// Punch animation 
	punch.PushBack({ 1,122,68,127 }, 2);
	punch.PushBack({ 70,153,78,96 }, 4);
	punch.PushBack({ 149,156,130,93 }, 1);
	punch.PushBack({ 280,156,130,93 }, 2);
	punch.PushBack({ 411,167,129,93 }, 3);
	punch.PushBack({ 541,167,127,93 }, 4);
	punch.PushBack({ 669,167,119,93 }, 6);
	punch.PushBack({ 789,164,130,85 }, 6);
	//punch.speed = 0.2f;

	//jump animation 
	jump.PushBack({ 484,9,60,112 }, 10);
	jump.PushBack({ 545,30,74,91 }, 5);
	jump.PushBack({ 620,38,76,83 }, 10);
	jump.PushBack({ 545,30,74,91 }, 5);
	jump.PushBack({ 484,9,60,112 }, 19);
	jump.PushBack({ 697,11,68,110 }, 11);

	//jump.speed = 0.05f;

	// hurt animation
	hurtLow.PushBack({ 1421,24,79,97 }, 20);
	//hurtLow.speed = 0.05f;

	// Tornado animation
	tornado.PushBack({ 1, 271, 100, 102 }, 8);
	tornado.PushBack({ 102,271,81,103 }, 2);
	tornado.PushBack({ 185,277,82, 95 }, 2);
	tornado.PushBack({ 268,268,67,107 }, 4);
	tornado.PushBack({ 443,262,72,174 }, 2);
	tornado.PushBack({ 516,261,112,113 }, 4);
	tornado.PushBack({ 628,263,113,105 }, 10);
	tornado.PushBack({ 741,263,119,105 }, 18);
	tornado.PushBack({ 860,263,98,105 }, 13);
	//tornado.speed = 0.2f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	position.x = 100;
	position.y = 200; //369 about the same position on the ground as its on the real game.

	jump_timer = 0;
	punch_timer = 0;
	kick_timer = 0;
	bool ret = true;
	playerFlip = false;

	health = 0;

	LOG("Listening for Arrow keys + SPACE:\n");
	LOG("Loading player textures");

	graphics = App->textures->Load("Assets/Sprites/haohmaru.png"); // arcade version
	ui = App->textures->Load("Assets/Sprites/UIspritesheet.png"); // health bar 
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
	App->textures->Unload(ui);
	App->audio->CleanUp();

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	Animation* current_animation = &idle;

	int speed = 1;
	if (external_input(inputs))
	{
		internal_input(inputs);
		player_states state = process_fsm(inputs);

		if (!doingAction) {
			switch (state)
			{
			case ST_IDLE:
				LOG("IDLE\n");
				break;
			case ST_WALK_FORWARD:
				LOG("FORWARD >>>\n");
				current_animation = &forward;
				position.x += speed;
				break;
			case ST_WALK_BACKWARD:
				LOG("BACKWARD <<<\n");
				current_animation = &backward;
				position.x -= speed;
				break;
			case ST_JUMP_NEUTRAL:
				LOG("JUMPING NEUTRAL ^^^^\n");
				jumping = true; doingAction = true;
				break;
			case ST_JUMP_FORWARD:
				LOG("JUMPING FORWARD ^^>>\n");
				jumping = true; doingAction = true;
				break;
			case ST_JUMP_BACKWARD:
				LOG("JUMPING BACKWARD ^^<<\n");
				jumping = true; doingAction = true;
				break;
			case ST_CROUCH:
				LOG("CROUCHING ****\n");
				break;
			case ST_PUNCH_CROUCH:
				LOG("PUNCH CROUCHING **++\n");
				break;
			case ST_PUNCH_STANDING:
				LOG("PUNCH STANDING ++++\n");
				punching = true; doingAction = true;
				App->attack->addAttack({ position.x + 73, position.y - 56, 40, 40 }, COLLIDER_PLAYER_ATTACK, 20,7);
				break;
			case ST_KICK_STANDING:
				LOG("KICK STANDING ----\n");
				kicking = true; doingAction = true;
				App->attack->addAttack({ position.x + 73, position.y - 56/2, 40, 20 }, COLLIDER_PLAYER_ATTACK, 10, 3);
				break;
			case ST_PUNCH_NEUTRAL_JUMP:
				LOG("PUNCH JUMP NEUTRAL ^^++\n");
				break;
			case ST_PUNCH_FORWARD_JUMP:
				LOG("PUNCH JUMP FORWARD ^>>+\n");
				break;
			case ST_PUNCH_BACKWARD_JUMP:
				LOG("PUNCH JUMP BACKWARD ^<<+\n");
				break;
			case ST_SPECIAL:
				LOG("SPECIAL OwwwwO\n");
				tornading = true; doingAction = true;
				Mix_PlayChannel(-1, App->audio->effects[0], 0);
				Mix_PlayChannel(-1, App->audio->effects[1], 0);
				App->particles->tornadoHao.speed.x = +3;
				App->particles->AddParticle(App->particles->tornadoHao, position.x + 20, position.y - 70, COLLIDER_PLAYER_SHOT);
				break;

			}
		}
		current_state = state;
	}
	//_________________


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
			//stop jump anim
			if (position.y > groundlevelaux && hasjumped == true)	//end of the jump
			{
				jumpingframe = 0;
				hasjumped = false;
				jumping = false;
				position.y = groundlevelaux;
				doingAction = false;
				inputs.Push(IN_JUMP_FINISH);
				jump.Reset();
				
				
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



	SDL_Rect healthBar = { 0, 905, 269, 32 };
	App->render->Blit(ui, 0, 32, false, &healthBar, NULL, true);

	if (health > 200) {
		SDL_Rect healthValue = { 0, 937, HEALTH_VALUE - health, 18 };
		App->render->Blit(ui, 5, 37, false, &healthValue, NULL, true);
	}
	else {
		SDL_Rect healthValue = { 0, 956, HEALTH_VALUE - health, 18 };
		App->render->Blit(ui, 5, 37, false, &healthValue, NULL, true);
	}
	
	



	return UPDATE_CONTINUE;
}

// TODO 4: Detect collision with a wall. If so, do something.
void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (this->body == c1) {
		if (c1->rect.x < c2->rect.x)
			position.x = c2->rect.x - c1->rect.w;
		if (c1->rect.x > c2->rect.x)
			position.x = c2->rect.x + c2->rect.w;
	}

	if (c2->type == COLLIDER_ENEMY_SHOT) {
		Mix_PlayChannel(-1, App->audio->effects[2], 0);
		health += 30;
		getsHit = true; doingAction = true;
	}
}

bool ModulePlayer::external_input(p2Qeue<player_inputs>& inputs)
{
	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;

	SDL_Event event;

	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_KEYUP && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				return false;
				break;
			case SDLK_s:
				inputs.Push(IN_CROUCH_UP);
				down = false;
				break;
			case SDLK_w:
				up = false;
				break;
			case SDLK_a:
				inputs.Push(IN_LEFT_UP);
				left = false;
				break;
			case SDLK_d:
				inputs.Push(IN_RIGHT_UP);
				right = false;
				break;
			}
		}
		if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_x:
				inputs.Push(IN_X);
				break;
			case SDLK_c:
				inputs.Push(IN_KICK);
				break;
			case SDLK_v:
				inputs.Push(IN_SPECIAL);
				break;
			case SDLK_w:
				up = true;
				break;
			case SDLK_s:
				down = true;
				break;
			case SDLK_a:
				left = true;
				break;
			case SDLK_d:
				right = true;
				break;
			}
		}
	}

	if (left && right)
		inputs.Push(IN_LEFT_AND_RIGHT);
	{
		if (left)
			inputs.Push(IN_LEFT_DOWN);
		if (right)
			inputs.Push(IN_RIGHT_DOWN);
	}

	if (up && down)
		inputs.Push(IN_JUMP_AND_CROUCH);
	else
	{
		if (down)
			inputs.Push(IN_CROUCH_DOWN);
		else
			inputs.Push(IN_CROUCH_UP);
		if (up)
			inputs.Push(IN_JUMP);
	}

	return true;
}
void ModulePlayer::internal_input(p2Qeue<player_inputs>& inputs)
{

	if (jump_timer > 0)
	{
		if (SDL_GetTicks() - jump_timer > JUMP_TIME)
		{
			inputs.Push(IN_JUMP_FINISH);
			jump_timer = 0;
		}
	}
	
	
	if (punch_timer > 0)
	{
		if (SDL_GetTicks()/1000/60 - punch_timer > PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}

	if (kick_timer > 0)
	{
		if (SDL_GetTicks() / 1000 / 60 - kick_timer > PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}
	
}
player_states ModulePlayer::process_fsm(p2Qeue<player_inputs>& inputs)
{
	static player_states state = ST_IDLE;
	player_inputs last_input;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{
		case ST_IDLE:
		{
			switch (last_input)
			{
			case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
			case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
			case IN_JUMP: state = ST_JUMP_NEUTRAL;  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_X: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
			case IN_KICK: state = ST_KICK_STANDING; punch_timer = SDL_GetTicks();  break;
			case IN_SPECIAL: state = ST_SPECIAL; punch_timer = SDL_GetTicks();  break;

			}
		}
		break;

		case ST_WALK_FORWARD:
		{
			switch (last_input)
			{
			case IN_RIGHT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_FORWARD; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			}
		}
		break;

		case ST_WALK_BACKWARD:
		{
			switch (last_input)
			{
			case IN_LEFT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			case IN_JUMP: state = ST_JUMP_BACKWARD; jump_timer = SDL_GetTicks(); break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_NEUTRAL_JUMP; punch_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_FORWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_FORWARD_JUMP; break;
			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_BACKWARD_JUMP; break;
			}
		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			}
		}
		break;

		case ST_PUNCH_FORWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			}
		}
		break;

		case ST_PUNCH_BACKWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			}
		}
		break;

		case ST_CROUCH:
		{
			switch (last_input)
			{
			case IN_CROUCH_UP: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_CROUCH; punch_timer = SDL_GetTicks();  break;
			}
		}
		break;
		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{
			case IN_CROUCH_UP && IN_PUNCH_FINISH: state = ST_IDLE; break;
			case IN_PUNCH_FINISH: state = ST_CROUCH; break;
			}
		}
		case ST_KICK_STANDING:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			}
		}
		case ST_SPECIAL:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			}
		}
		break;
		}
	}
	return state;
}
