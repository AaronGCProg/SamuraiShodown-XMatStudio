#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInterface.h"
#include "ModuleFight.h"
#include "ModuleSlowdown.h"


#include<math.h>


ModulePlayer2::ModulePlayer2()
{
	// JUBEI ANIM
	const int idleCollider = 2;//Collider num for the idle animation
	SDL_Rect idleHitbox[idleCollider] = { { 25, 0, 40, 75 },{ 40, 75, 20, 20 } };
	COLLIDER_TYPE idleCollType[idleCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* idleCallBack[idleCollider] = { {this},{this} };

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 1, 11, 96, 106 }, 8, { 49,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 98,10,87,107 }, 8, { 45,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 186,11,88,106 }, 8, { 45,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 275,12,89,105 }, 8, { 45,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 365,13,92,104 }, 8, { 47,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 458,13,97,104 }, 8, { 49,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 556,13,104,104 }, 8, { 53,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 661,12,102,105 }, 8, { 52,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 764,11,96,106 }, 8, { 49,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	//idle.speed = 0.125f;


	const int backCollider = 2;//Collider num for the backward animation
	SDL_Rect backHitbox[backCollider] = { { 25, 0, 40, 75 },{ 40, 75, 20, 20 } };
	COLLIDER_TYPE backCollType[backCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* backCallBack[backCollider] = { {this},{this} };

	// walk backward animation 
	backward.PushBack({ 458,127,98,109 }, 9, { 23,1 }, backCollider, backHitbox, backCollType, backCallBack);
	backward.PushBack({ 277,137,91,99 }, 6, { 24,1 }, backCollider, backHitbox, backCollType, backCallBack);
	backward.PushBack({ 368,140,91,96 }, 9, { 29,1 }, backCollider, backHitbox, backCollType, backCallBack);
	backward.PushBack({ 277,137,91,99 }, 6, { 24,1 }, backCollider, backHitbox, backCollType, backCallBack);


	//backward.speed = 0.1f;


	const int forCollider = 2;//Collider num for the forward animation
	SDL_Rect forHitbox[forCollider] = { { 32, 0, 40, 75 },{ 33, 70, 20, 20 } };
	COLLIDER_TYPE forCollType[forCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* forCallBack[forCollider] = { {this},{this} };

	// walk forward animation 
	forward.PushBack({ 0,133,98,103 }, 8, { 29,1 }, forCollider, forHitbox, forCollType, forCallBack);
	forward.PushBack({ 184,128,91,108 }, 8, { 21,1 }, forCollider, forHitbox, forCollType, forCallBack);
	forward.PushBack({ 98,127,88,109 }, 8, { 21,1 }, forCollider, forHitbox, forCollType, forCallBack);
	forward.PushBack({ 184,128,91,108 }, 8, { 21,1 }, forCollider, forHitbox, forCollType, forCallBack);

	//forward.speed = 0.1f;


	const int kickCollider = 3;//Collider num for the kick animation
	const int kickCollider2 = 2;//Collider num for the kick animation
	SDL_Rect kickHitbox[kickCollider] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 },{ 60, 10, 35, 20 } };
	SDL_Rect kickHitbox2[kickCollider2] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 } };
	COLLIDER_TYPE kickCollType[kickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	COLLIDER_TYPE kickCollType2[kickCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* kickCallBack[kickCollider] = { {this},{this},{this} };
	Module* kickCallBack2[kickCollider2] = { {this},{this} };


	// Kick animation 
	kick.PushBack({ 902,487,77,107 }, 6, { 31,2 }, kickCollider2, kickHitbox2, kickCollType2, kickCallBack2);
	kick.PushBack({ 980,483,62,111 }, 6, { 31,2 }, kickCollider, kickHitbox, kickCollType, kickCallBack);
	kick.PushBack({ 1155,478,82,116 }, 6, { 31,2 }, kickCollider2, kickHitbox2, kickCollType2, kickCallBack2);
	kick.PushBack({ 980,483,62,111 }, 6, { 31,2 }, kickCollider, kickHitbox, kickCollType, kickCallBack);
	//kick.speed = 0.12f;


	const int punchCollider = 3;//Collider num for the punch animation
	const int punchCollider2 = 2;//Collider num for the punch animation
	SDL_Rect punchHitbox[punchCollider] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 },{ 40, 30, 80, 30 } };
	COLLIDER_TYPE punchCollType[punchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* punchCallBack[punchCollider] = { {this},{this},{this} };

	SDL_Rect punchHitbox2[punchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE punchCollType2[punchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY}, };
	Module* punchCallBack2[punchCollider2] = { {this},{this} };

	// Punch animation 
	punch.PushBack({ 1,721,86,97 }, 7, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack);
	punch.PushBack({ 88,729,130,89 }, 7, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack);
	punch.PushBack({ 219,729,150,90 }, 5, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack);
	punch.PushBack({ 370,729,137,89 }, 6, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack);
	punch.PushBack({ 508,729,96,89 }, 5, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack);
	//punch.speed = 0.2f;


	const int jumpCollider = 2;//Collider num for the jump animation
	SDL_Rect jumpHitbox[jumpCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpCollType[jumpCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* jumpCallBack[jumpCollider] = { {this},{this} };

	//jump animation 
	jump.PushBack({ 557,124,75,119 }, 5, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jump.PushBack({ 631,124,75,119 }, 8, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jump.PushBack({ 705,135,73,108 }, 13, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jump.PushBack({ 778,169,73,73 }, 4, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jump.PushBack({ 852,152,73,90 }, 17, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jump.PushBack({ 949,31,77,86 }, 11, { 40, 6 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);

	//jump.speed = 0.05f;

	const int hurtCollider = 2;//Collider num for the hurt animation
	SDL_Rect hurtHitbox[hurtCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE hurtCollType[hurtCollider] = { {COLLIDER_NONE},{COLLIDER_NONE} };
	Module* hurtCallBack[hurtCollider] = { {this},{this} };
	// hurt animation
	hurtLow.PushBack({ 1838,736,98,90 }, 20, { 31,2 }, hurtCollider, hurtHitbox, hurtCollType, hurtCallBack);
	//hurtLow.speed = 0.05f;


	//jump kick animation 
	const int jumpKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpKickHitbox[jumpKickCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 60, 10, 35, 20 } };
	COLLIDER_TYPE jumpKickCollType[jumpKickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpKickCallBack[jumpKickCollider] = { {this},{this},{this} };

	const int jumpKickCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpKickHitbox2[jumpKickCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpKickCollType2[jumpKickCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* jumpKickCallBack2[jumpKickCollider2] = { {this},{this} };

	jumpKick.PushBack({ 1102,21,71,80 }, 6, { 31,2 }, jumpKickCollider2, jumpKickHitbox2, jumpKickCollType2, jumpKickCallBack2);
	jumpKick.PushBack({ 1160,146,122,96 }, 32, { 31,2 }, jumpKickCollider, jumpKickHitbox, jumpKickCollType, jumpKickCallBack);
	jumpKick.PushBack({ 1102,21,71,80 }, 6, { 31,2 }, jumpKickCollider2, jumpKickHitbox2, jumpKickCollType2, jumpKickCallBack2);


	//jump backwards animation 

	jumpBackward.PushBack({ 557,124,75,119 }, 10, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jumpBackward.PushBack({ 631,124,75,119 }, 8, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jumpBackward.PushBack({ 705,135,73,108 }, 15, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jumpBackward.PushBack({ 778,169,73,73 }, 4, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jumpBackward.PushBack({ 852,152,73,90 }, 32, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jumpBackward.PushBack({ 949,31,77,86 }, 6, { 40, 6 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);


	//jump punch animation 
	const int jumpPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpPunchHitbox[jumpPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 55, 27, 90, 10 } };
	COLLIDER_TYPE jumpPunchCollType[jumpPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpPunchCallBack[jumpPunchCollider] = { {this},{this},{this} };

	const int jumpPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpPunchHitbox2[jumpPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpPunchCollType2[jumpPunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* jumpPunchCallBack2[jumpPunchCollider2] = { {this},{this} };

	jumpPunch.PushBack({ 1,819,83,87 }, 4, { 31, 2 }, jumpPunchCollider2, jumpPunchHitbox2, jumpPunchCollType2, jumpPunchCallBack2);
	jumpPunch.PushBack({ 85,824,79,82 }, 4, { 31, 2 }, jumpPunchCollider, jumpPunchHitbox, jumpPunchCollType, jumpPunchCallBack);
	jumpPunch.PushBack({ 165,835,73,71 }, 3, { 31, 2 }, jumpPunchCollider, jumpPunchHitbox, jumpPunchCollType, jumpPunchCallBack);
	jumpPunch.PushBack({ 239,836,156,70 }, 3, { 31, 2 }, jumpPunchCollider, jumpPunchHitbox, jumpPunchCollType, jumpPunchCallBack);
	jumpPunch.PushBack({ 396,837,157,69 }, 3, { 31, 2 }, jumpPunchCollider2, jumpPunchHitbox2, jumpPunchCollType2, jumpPunchCallBack2);
	jumpPunch.PushBack({ 554,842,147,64 }, 20, { 31, 2 }, jumpPunchCollider2, jumpPunchHitbox2, jumpPunchCollType2, jumpPunchCallBack2);


	//jump foward animation 

	jumpFw.PushBack({ 557,124,75,119 }, 10, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jumpFw.PushBack({ 631,124,75,119 }, 8, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jumpFw.PushBack({ 705,135,73,108 }, 20, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jumpFw.PushBack({ 778,169,73,73 }, 8, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jumpFw.PushBack({ 852,152,73,90 }, 19, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jumpFw.PushBack({ 554,842,147,64 }, 20, { 31, 2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);


	//jump foward punch animation 
	const int jumpForwardPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpForwardPunchHitbox[jumpForwardPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 40, 75, 20, 20 } };
	COLLIDER_TYPE jumpForwardPunchCollType[jumpForwardPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpForwardPunchCallBack[jumpForwardPunchCollider] = { {this},{this},{this} };




	const int crouchCollider = 2;//Collider num for the jump kick animation
	SDL_Rect crouchHitbox2[crouchCollider] = { { 30, 0, 30, 55 },{40, 50, 20, 20 } };
	SDL_Rect crouchHitbox[crouchCollider] = { { 50, 0, 30, 55 },{ 60, 50, 20, 20 } };
	COLLIDER_TYPE crouchCollType[crouchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* crouchCallBack[crouchCollider] = { {this},{this} };

	crouch.PushBack({ 949,31,77,86 }, 6, { 40, 6 }, crouchCollider, crouchHitbox2, crouchCollType, crouchCallBack);
	crouch.PushBack({ 1102,37,70,80 }, 2, { 60, 8 }, crouchCollider, crouchHitbox, crouchCollType, crouchCallBack);
	crouch.PushBack({ 1027,40,73,77 }, 2, { 60, 8 }, crouchCollider, crouchHitbox, crouchCollType, crouchCallBack);
	crouch.firstLoopFrame = 2;
	crouch.loop = true;


	//crouch punch animation 
	const int crouchPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox[crouchPunchCollider] = { { 30, 10, 40, 35 },{ 50, 35, 20, 20 },{ 75, 5, 50, 20 } };
	COLLIDER_TYPE crouchPunchCollType[crouchPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* crouchPunchCallBack[crouchPunchCollider] = { {this},{this},{this} };

	const int crouchPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox2[crouchPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchPunchCollType2[crouchPunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* crouchPunchCallBack2[crouchPunchCollider2] = { {this},{this} };

	crouchPunch.PushBack({ 703,730,74,94 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);
	crouchPunch.PushBack({ 778,722,76,102 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);
	crouchPunch.PushBack({ 855,731,69,93 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);
	crouchPunch.PushBack({ 925,754,100,70 }, 1, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 1026,754,110,70 }, 2, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 1137,730,111,94 }, 1, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 1249,730,70,94 }, 7, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 1321,754,100,70 }, 3, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 1422,731,69,93 }, 3, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);


	const int crouchKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchKickHitbox[crouchPunchCollider] = { { 5, 10, 40, 35 },{ 20, 35, 20, 20 },{ 78,0,20,20 } };
	COLLIDER_TYPE crouchKickCollType[crouchKickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* crouchKickCallBack[crouchKickCollider] = { {this},{this},{this} };
	crouchKick.PushBack({ 1102,21,71,80 }, 4, { 31,2 }, crouchPunchCollider, crouchKickHitbox, crouchKickCollType, crouchKickCallBack);
	crouchKick.PushBack({ 1262,31,122,86 }, 8, { 31,2 }, crouchKickCollider, crouchKickHitbox, crouchPunchCollType, crouchKickCallBack);

	//fall animation
	const int fallCollider = 2;//Collider num for the jump kick animation
	SDL_Rect fallHitbox[fallCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } }; //RESOLVE
	COLLIDER_TYPE fallCollType[fallCollider] = { {COLLIDER_NONE},{COLLIDER_NONE} };
	Module* fallCallBack[fallCollider] = { {this},{this} };

	fall.PushBack({ 1530,742,71,83 }, 23, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack);
	fall.PushBack({ 1604,741,105,81 }, 52, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack);
	fall.PushBack({ 1530,742,71,83 }, 13, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack);
	fall.PushBack({ 1604,741,105,81 }, 13, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack);
	fall.PushBack({ 1712,783,123,42 }, 75, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack);

	//getUp animation
	const int getUpCollider = 2;//Collider num for the jump kick animation
	SDL_Rect getUpHitbox[getUpCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } }; //RESOLVE
	COLLIDER_TYPE getUpCollType[getUpCollider] = { {COLLIDER_NONE},{COLLIDER_NONE} };
	Module* getUpCallBack[getUpCollider] = { {this},{this} };
	getUp.PushBack({ 108,470,108,54 }, 5, { 31,2 }, getUpCollider, getUpHitbox, getUpCollType, getUpCallBack);
	getUp.PushBack({ 1306,789,75,94 }, 8, { 31,2 }, getUpCollider, getUpHitbox, getUpCollType, getUpCallBack);
	getUp.PushBack({ 1,455,106,69 }, 4, { 31,2 }, getUpCollider, getUpHitbox, getUpCollType, getUpCallBack);
	getUp.PushBack({ 334,435,98,89 }, 4, { 31,2, }, getUpCollider, getUpHitbox, getUpCollType, getUpCallBack);


	const int tornadoCollider = 2;//Collider num for the tornado animation
	SDL_Rect tornadoHitbox[tornadoCollider] = { { 40, 10, 40, 65 },{ 55, 75, 20, 20 } };
	COLLIDER_TYPE tornadoCollType[tornadoCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* tornadoCallBack[tornadoCollider] = { {this},{this} };

	// Tornado animation
	tornado.PushBack({ 80, 1670, 105, 116 }, 8, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 184,1669,118,103 }, 2, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 276,1692,71, 94 }, 2, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 346,1715,100,71 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 445,1717,112,70 }, 2, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 556,1694,111,94 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 666,1701,103,87 }, 22, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 769,1691,73,96 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 842,1715,102,71 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 942,1693,71,94 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);


}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	position.x = 200;
	position.y = 198; //200 about the same position on the ground as its on the real game.

	LOG("Loading player textures");
	bool ret = true;
	playerFlip = true;

	p2jump_timer = 0;

	current_animation = &idle;

	health = 0;

	graphics = App->textures->Load("Assets/Sprites/Jubei2.png"); // arcade version
	ui = App->textures->Load("Assets/Sprites/UIspritesheet2.png"); // health bar 
	shadow = App->textures->Load("Assets/Sprites/sombra.png"); // health bar 
	groundlevelaux = position.y;



	//body = App->collision->AddCollider({ position.x, position.y - 113, 73, 113 }, COLLIDER_ENEMY, this);

	return ret;
}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	// TODO 5: Remove all memory leaks
	LOG("Unloading Character");
	App->textures->Unload(graphics);
	App->textures->Unload(ui);


	for (int i = 0; i < MAXNUMOFCOLLIDERS; i++)//deletes all the hitboxes at the start of the frame
	{
		if (colisionadores[i] != nullptr) {
			colisionadores[i]->to_delete = true;
			colisionadores[i] = nullptr;
		}
	}

	return true;
}

update_status ModulePlayer2::PreUpdate()
{

	for (int i = 0; i < MAXNUMOFCOLLIDERS; i++)//deletes all the hitboxes at the start of the frame
	{
		if (colisionadores[i] != nullptr) {
			colisionadores[i]->to_delete = true;
			colisionadores[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	current_animation = &idle;
	int speed = 2;

	if (invencibleframes) {
		if (SDL_GetTicks() - (invencibleaux) >= 350) {
			invencibleframes = false;
		}
	}

	if (external_input(p2inputs, App->player->inputs))
	{
		internal_input(p2inputs);
		player2_states state = process_fsm(p2inputs);

		if (!App->player->doingAction) {

			if (App->player->position.x < App->player2->position.x) {
				App->player->playerFlip = false;
			}
			else {
				App->player->playerFlip = true;
			}
		}
		if (!App->player->doingAction) {

			if (App->player->position.x < App->player2->position.x) {
				App->player->playerFlip = false;
			}
			else {
				App->player->playerFlip = true;
			}
		}


		if (!playerFlip) {


			if (!doingAction) {
				audioPlayed = false;


				if (App->player->position.x < App->player2->position.x) {
					playerFlip = true;
				}
				else {
					playerFlip = false;
				}
				switch (state)
				{
				case ST_IDLE2:
					LOG("IDLE\n");
					current_animation = &idle;
					break;
				case ST_WALK_FORWARD2:
					LOG("FORWARD >>>\n");
					current_animation = &forward;
					position.x += speed + 1;
					break;
				case ST_WALK_BACKWARD2:
					LOG("BACKWARD <<<\n");
					current_animation = &backward;
					position.x -= speed;
					break;
				case ST_JUMP_NEUTRAL2:
					LOG("JUMPING NEUTRAL ^^^^\n");
					jumping = true; doingAction = true;
					Mix_PlayChannel(-1, App->audio->effects[15], 0);
					break;
				case ST_JUMP_FORWARD2:
					LOG("JUMPING FORWARD ^^>>\n");
					jumpright = true;
					Mix_PlayChannel(-1, App->audio->effects[15], 0);
					doingAction = true;
					break;
				case ST_JUMP_BACKWARD2:
					LOG("JUMPING BACKWARD ^^<<\n");
					jumpleft = true;
					Mix_PlayChannel(-1, App->audio->effects[15], 0);
					doingAction = true;
					break;
				case ST_CROUCH2:
					LOG("CROUCHING ****\n");
					crouching = true;
					doingAction = true;
					break;
				case ST_PUNCH_STANDING2:
					LOG("PUNCH STANDING ++++\n");
					punching = true; doingAction = true;
					break;
				case ST_KICK_STANDING2:
					LOG("KICK STANDING ----\n");
					kicking = true; doingAction = true;
					break;
				case ST_PUNCH_NEUTRAL_JUMP2:
					LOG("PUNCH JUMP NEUTRAL ^^++\n");
					break;
				case ST_PUNCH_FORWARD_JUMP2:
					LOG("PUNCH JUMP FORWARD ^>>+\n");
					break;
				case ST_PUNCH_BACKWARD_JUMP2:
					LOG("PUNCH JUMP BACKWARD ^<<+\n");
					break;
				case ST_PUNCH_CROUCH2:
					LOG("PUNCH CROUCHING **++\n");
					crouchpunching = true; doingAction = true;
					break;
				case ST_KICK_CROUCH2:
					LOG("KICK CROUCHING **++\n");
					crouchkicking = true; doingAction = true;
					break;
				case ST_SPECIAL2:
					LOG("SPECIAL OwwwwO\n");
					tornading = true; doingAction = true;
					Mix_PlayChannel(-1, App->audio->effects[0], 0);
					Mix_PlayChannel(-1, App->audio->effects[1], 0);
					App->particles->tornadoHao.speed.x = +3;
					App->particles->tornadoHao.speed.x = +3;
					App->particles->AddParticle(App->particles->tornadoHao, position.x + 18, position.y - 44, playerFlip, COLLIDER_ENEMY_SHOT);



					break;
				case ST_FALLING2://new
					falling = true; doingAction = true;
					break;
				}
			}
		}
		else {


			if (!doingAction) {

				audioPlayed = false;


				if (App->player->position.x < App->player2->position.x) {
					playerFlip = true;
				}
				else {
					playerFlip = false;
				}
				switch (state)
				{
				case ST_IDLE2:
					LOG("IDLE\n");
					current_animation = &idle;
					break;
				case ST_WALK_FORWARD2:
					LOG("FORWARD >>>\n");
					current_animation = &backward;
					position.x += speed;
					break;
				case ST_WALK_BACKWARD2:
					LOG("BACKWARD <<<\n");
					current_animation = &forward;
					position.x -= speed + 1;
					break;
				case ST_JUMP_NEUTRAL2:
					LOG("JUMPING NEUTRAL ^^^^\n");
					jumping = true; doingAction = true;
					Mix_PlayChannel(-1, App->audio->effects[15], 0);
					break;
				case ST_JUMP_FORWARD2:
					LOG("JUMPING FORWARD ^^>>\n");
					jumpright = true;

					Mix_PlayChannel(-1, App->audio->effects[15], 0);

					doingAction = true;
					break;
				case ST_JUMP_BACKWARD2:
					LOG("JUMPING BACKWARD ^^<<\n");

					jumpleft = true;

					Mix_PlayChannel(-1, App->audio->effects[15], 0);

					doingAction = true;
					break;
				case ST_CROUCH2:
					LOG("CROUCHING ****\n");
					crouching = true;
					doingAction = true;
					break;

				case ST_PUNCH_STANDING2:
					LOG("PUNCH STANDING ++++\n");
					punching = true; doingAction = true;
					break;
				case ST_KICK_STANDING2:
					LOG("KICK STANDING ----\n");
					kicking = true; doingAction = true;
					break;
				case ST_PUNCH_NEUTRAL_JUMP2:
					LOG("PUNCH JUMP NEUTRAL ^^++\n");
					break;
				case ST_PUNCH_FORWARD_JUMP2:
					LOG("PUNCH JUMP FORWARD ^>>+\n");
					break;
				case ST_PUNCH_BACKWARD_JUMP2:
					LOG("PUNCH JUMP BACKWARD ^<<+\n");
					break;
				case ST_PUNCH_CROUCH2:
					LOG("PUNCH CROUCHING **++\n");
					crouchpunching = true; doingAction = true;
					break;
				case ST_KICK_CROUCH2:
					LOG("KICK CROUCHING **++\n");
					crouchkicking = true; doingAction = true;
					break;
				case ST_SPECIAL2:
					LOG("SPECIAL OwwwwO\n");
					tornading = true; doingAction = true;
					Mix_PlayChannel(-1, App->audio->effects[0], 0);
					Mix_PlayChannel(-1, App->audio->effects[1], 0);
					App->particles->tornadoHao.speed.x = +3;
					App->particles->tornadoHao.speed.x = -3;
					App->particles->AddParticle(App->particles->tornadoHao, position.x - 140, position.y - 44, playerFlip, COLLIDER_ENEMY_SHOT);

					break;

				case ST_FALLING2://new
					falling = true; doingAction = true;
					break;


				}
			}
		}
		current_state = state;
	}


	if (App->input->keys[SDL_SCANCODE_F6] == KEY_STATE::KEY_DOWN)
	{
		if (godMode2)
			godMode2 = false;
		else
			godMode2 = true;

	}

	if (App->input->keys[SDL_SCANCODE_F3] == KEY_STATE::KEY_DOWN)
	{
		health = 0;
		App->player->health = 0;
	}

	if (App->input->keys[SDL_SCANCODE_F8] == KEY_STATE::KEY_DOWN)
	{
		if (debugmode)
			debugmode = false;
		else
			debugmode = true;

	}

	if (doingAction)
	{
		if (kicking) {
			//set kick anim
			current_animation = &kick;
			//stop kick anim

			if (current_animation->current_frame > 2 && !App->player2->getsHit && !audioPlayed) {
				Mix_PlayChannel(-1, App->audio->effects[19], 0);
				audioPlayed = true;
			}
			if (kick.GetAnimEnd() == true) {
				kicking = false; doingAction = false; kick.SetAnimEnd(false);
				audioPlayed = false;
			}
		}

		if (tornading) {
			//set punch anim
			current_animation = &tornado;

			//stop punch anim
			if (tornado.GetAnimEnd() == true) { tornading = false; doingAction = false; tornado.SetAnimEnd(false); }
		}

		if (punching) {
			//set kick anim
			current_animation = &punch;
			//stop kick anim

			if (current_animation->current_frame > 6 && current_animation->current_frame < 8 && !App->player2->getsHit && !audioPlayed) {
				Mix_PlayChannel(-1, App->audio->effects[18], 0);
				audioPlayed = true;
			}
			if (punch.GetAnimEnd() == true) {
				punching = false; doingAction = false; punch.SetAnimEnd(false);
				audioPlayed = false;


			}
		}

		if (crouching) {
			//set punch anim
			current_animation = &crouch;
			//stop punch anim
			if (crouch.GetAnimEnd() == true) { crouching = false; doingAction = false; crouch.SetAnimEnd(false); }
		}

		if (crouchpunching)
		{
			//set crouch punch anim.
			current_animation = &crouchPunch;
			//stop crouch punch anim
			if (crouchPunch.GetAnimEnd() == true) {
				crouchpunching = false; doingAction = false; crouchPunch.SetAnimEnd(false); p2inputs.Push(IN_PUNCH_FINISH2);
			}
		}

		if (crouchkicking)
		{
			//set crouch punch anim.
			current_animation = &crouchKick;
			//stop crouch punch anim
			if (crouchKick.GetAnimEnd() == true) { crouchkicking = false; doingAction = false; crouchKick.SetAnimEnd(false); p2inputs.Push(IN_PUNCH_FINISH2); }
		}

		if (getsHit) {
			//set punch anim
			current_animation = &hurtLow;

			//App->slowdown->StartSlowdown(100, 6);
			App->render->StartCameraShake(30, 1);
			//body->to_delete = true;

			if (playerFlip) {
				if (aux > 0 && aux < 11) {
					position.x += aux;
					aux--;
				}
			}
			else if (!playerFlip) {
				if (aux > 0 && aux < 11)
					position.x -= aux;
				aux--;

			}

			if (hurtLow.GetAnimEnd() == true) {
				getsHit = false; doingAction = false; hurtLow.SetAnimEnd(false);
				aux = 10;
				invencibleframes = true;
				invencibleaux = SDL_GetTicks();

			}
			//stop punch anim

			/*if (hurtLow.GetAnimEnd() == true) {
				getsHit = false; doingAction = false; hurtLow.SetAnimEnd(false);
				body->to_delete = true;
				body = App->collision->AddCollider({ position.x, position.y, 73, 113 }, COLLIDER_ENEMY, this);
			}*/
		}

		if (jumping)
		{
			//set jump anim
			if (App->player2->current_state == ST_PUNCH_NEUTRAL_JUMP2) {
				JumpPunching = true;
			}
			if (App->player2->current_state == ST_KICK_NEUTRAL_JUMP2) {
				JumpKicking = true;
			}

			if (JumpPunching)
				current_animation = &jumpPunch;
			else if (JumpKicking)
				current_animation = &jumpKick;
			else
				current_animation = &jump;

			position.y = groundlevelaux - (JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY)*pow(jumpingframe, 2));//MRUA formula
			hasjumped = true;
			if (JumpPunching &&current_animation->current_frame >= 3 && !App->player2->getsHit && !audioPlayed) {
				Mix_PlayChannel(-1, App->audio->effects[18], 0);
				audioPlayed = true;
			}
			if (JumpKicking && current_animation->current_frame >= 2 && !App->player2->getsHit && !audioPlayed) {
				Mix_PlayChannel(-1, App->audio->effects[19], 0);
				audioPlayed = true;
			}
			jumpingframe++;

			//stop punch anim
			if (position.y > groundlevelaux && hasjumped == true)	//end of the jump
			{
				jumpingframe = 0;
				hasjumped = false;
				jumping = false;
				JumpPunching = false;
				JumpKicking = false;
				audioPlayed = false;
				position.y = groundlevelaux;
				Mix_PlayChannel(-1, App->audio->effects[14], 0);
				doingAction = false;
				p2inputs.Push(IN_JUMP_FINISH2);
				jumpKick.Reset();
				jumpPunch.Reset();
				jump.Reset();
			}

			if (airhit)	//end of the jump
			{
				jumpingframe = 0;
				hasjumped = false;
				jumpleft = false;
				JumpPunching = false;
				JumpKicking = false;
				jumping = false;
				doingAction = false;
				audioPlayed = false;
				p2inputs.Push(IN_JUMP_FINISH2);
				jumpFw.Reset();
				jumpKick.Reset();
				jumpBackward.Reset();
				jump.Reset();
				airhit = false;
			}
		}
		if (jumpright)
		{
			if (!playerFlip) {
				if (App->player2->current_state == ST_PUNCH_NEUTRAL_JUMP2) {
					JumpPunching = true;
				}
				if (App->player2->current_state == ST_KICK_NEUTRAL_JUMP2) {
					JumpKicking = true;
				}

				if (JumpPunching)
					current_animation = &jumpPunch;
				else if (JumpKicking)
					current_animation = &jumpKick;
				else
					current_animation = &jumpFw; //Jumpforward animation
			}
			else {
				if (App->player2->current_state == ST_PUNCH_NEUTRAL_JUMP2) {
					JumpPunching = true;
				}
				if (App->player2->current_state == ST_KICK_NEUTRAL_JUMP2) {
					JumpKicking = true;
				}

				if (JumpPunching)
					current_animation = &jumpPunch;
				else if (JumpKicking)
					current_animation = &jumpKick;
				else
					current_animation = &jumpBackward; //Jumpforward animation



				if (JumpPunching)
					current_animation = &jumpPunch;
				else if (JumpKicking)
					current_animation = &jumpKick;
				else
					current_animation = &jumpFw; //Jumpforward animation
			}
			if (JumpPunching &&current_animation->current_frame >= 3 && !App->player2->getsHit && !audioPlayed) {
				Mix_PlayChannel(-1, App->audio->effects[18], 0);
				audioPlayed = true;
			}
			if (JumpKicking && current_animation->current_frame >= 2 && !App->player2->getsHit && !audioPlayed) {
				Mix_PlayChannel(-1, App->audio->effects[19], 0);
				audioPlayed = true;
			}

			position.y = groundlevelaux - (JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY)*pow(jumpingframe, 2));//MRUA formula
			position.x += 4;
			hasjumped = true;

			jumpingframe++;

			//stop jump anim
			if (position.y > groundlevelaux && hasjumped == true)	//end of the jump
			{
				jumpingframe = 0;
				hasjumped = false;
				jumpright = false;
				JumpPunching = false;
				JumpKicking = false;
				audioPlayed = false;
				Mix_PlayChannel(-1, App->audio->effects[14], 0);
				position.y = groundlevelaux;
				doingAction = false;
				p2inputs.Push(IN_JUMP_FINISH2);
				jumpFw.Reset();
				jumpBackward.Reset();
				jumpFw.Reset();
				jumpKick.Reset();
				jumpBackward.Reset();

			}

			if (airhit)	//end of the jump
			{
				jumpingframe = 0;
				hasjumped = false;
				jumpleft = false;
				JumpPunching = false;
				JumpKicking = false;
				jumping = false;
				doingAction = false;
				audioPlayed = false;
				p2inputs.Push(IN_JUMP_FINISH2);
				jumpFw.Reset();
				jumpKick.Reset();
				jumpBackward.Reset();
				jump.Reset();
				airhit = false;
			}
		}
		if (jumpleft)
		{
			//set jump anim
			if (playerFlip) {
				if (App->player2->current_state == ST_PUNCH_NEUTRAL_JUMP2) {
					JumpPunching = true;
				}
				if (App->player2->current_state == ST_KICK_NEUTRAL_JUMP2) {
					JumpKicking = true;
				}

				if (JumpPunching)
					current_animation = &jumpPunch;
				else if (JumpKicking)
					current_animation = &jumpKick;
				else
					current_animation = &jumpFw; //Jumpforward animation
			}
			else {
				if (App->player2->current_state == ST_PUNCH_NEUTRAL_JUMP2) {
					JumpPunching = true;
				}
				if (App->player2->current_state == ST_KICK_NEUTRAL_JUMP2) {
					JumpKicking = true;
				}

				if (JumpPunching)
					current_animation = &jumpPunch;
				else if (JumpKicking)
					current_animation = &jumpKick;
				else
					current_animation = &jumpBackward; //Jumpforward animation



				if (JumpPunching)
					current_animation = &jumpPunch;
				else if (JumpKicking)
					current_animation = &jumpKick;
				else
					current_animation = &jumpFw; //Jumpforward animation
			}
			if (JumpPunching &&current_animation->current_frame >= 3 && !App->player2->getsHit && !audioPlayed) {
				Mix_PlayChannel(-1, App->audio->effects[18], 0);
				audioPlayed = true;
			}
			if (JumpKicking && current_animation->current_frame >= 2 && !App->player2->getsHit && !audioPlayed) {
				Mix_PlayChannel(-1, App->audio->effects[19], 0);
				audioPlayed = true;
			}
			position.y = groundlevelaux - (JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY)*pow(jumpingframe, 2));//MRUA formula
			position.x -= 4;
			hasjumped = true;
			//stop jump anim
			jumpingframe++;
			if (position.y > groundlevelaux && hasjumped == true)	//end of the jump
			{
				jumpingframe = 0;
				hasjumped = false;
				jumpleft = false;
				JumpPunching = false;
				JumpKicking = false;
				Mix_PlayChannel(-1, App->audio->effects[14], 0);
				position.y = groundlevelaux;
				doingAction = false;
				p2inputs.Push(IN_JUMP_FINISH2);
				jumpFw.Reset();
				jumpKick.Reset();
				jumpBackward.Reset();

			}

			if (airhit)	//end of the jump
			{
				jumpingframe = 0;
				hasjumped = false;
				jumpleft = false;
				JumpPunching = false;
				JumpKicking = false;
				jumping = false;
				doingAction = false;
				audioPlayed = false;
				p2inputs.Push(IN_JUMP_FINISH2);
				jumpFw.Reset();
				jumpKick.Reset();
				jumpBackward.Reset();
				jump.Reset();
				airhit = false;

			}
		}
		if (falling)//new
		{
			current_animation = &fall;
			if (fall_bounces > FALLBOUNCES) { position.y = groundlevelaux; delay++; }
			else
			{

				if (fall_bounces == 0) position.y = posyaux - (10 * jumpingframe) + (0.5*(JUMP_INIT_AY + (0.2f*(fall_bounces + 1)))*pow(jumpingframe, 2));//MRUA formula
				else position.y = groundlevelaux - (10 * jumpingframe) + (0.5*(0.5*JUMP_INIT_AY + (0.2f*(fall_bounces + 1)))*pow(jumpingframe, 2));//MRUA formula
				if (playerFlip)position.x += 2 - (fall_bounces);
				else position.x -= 2 - (fall_bounces);

				hasjumped = true;
				jumpingframe++;
				if (position.y > groundlevelaux)
				{
					App->render->StartCameraShake(30, 1);
					App->slowdown->StartSlowdown(40, 1);

					jumpingframe = 0;
					position.y = groundlevelaux;
					fall_bounces++;
				}
			}
			if (fall_bounces > FALLBOUNCES &&hasjumped == true && delay > 45 || App->fight->played == 1)
			{
				hasjumped = false;
				jumpingframe = 0;
				p2inputs.Push(IN_FALL_FINISH2);
				fall_bounces = 0;
				doingAction = false;
				falling = false;
				position.y = groundlevelaux;
				fall.Reset();
				delay = 0;
				Mix_PlayChannel(-1, App->audio->effects[20], 0);
			}

		}
	}
	for (int i = 0; i < MAXNUMOFCOLLIDERS; i++)//deletes all the hitboxes at the start of the frame
	{
		if (colisionadores[i] != nullptr)
			colisionadores[i]->to_delete = true;
	}
	//Jump Logic------------------------------------------

	//body->SetPos(position.x, position.y - 113);

	// Draw everything --------------------------------------
	playerPivotX = current_animation->pivotpos[(int)current_animation->current_frame].x;
	playerPivotY = current_animation->pivotpos[(int)current_animation->current_frame].y;

	SDL_Rect r;
	int hitboxmax = current_animation->collidersmax[(int)current_animation->current_frame]; //number of collision boxes in each frame
	for (int i = 0; i < hitboxmax; i++)
	{
		r = current_animation->hitbox[i];
		if ((!godMode2 || current_animation->tipo[i] != COLLIDER_PLAYER) && invencibleframes && current_animation->tipo[i] == COLLIDER_ENEMY)
			if (playerFlip)
				colisionadores[i] = App->collision->AddCollider({ position.x - (r.w - playerPivotX) - r.x , position.y - r.h + playerPivotY - r.y,r.w,r.h }, COLLIDER_NONE, current_animation->callback[i]);
			else
				colisionadores[i] = App->collision->AddCollider({ position.x - playerPivotX + r.x , position.y + playerPivotY - r.h - r.y,r.w,r.h }, COLLIDER_NONE, current_animation->callback[i]);

		else if (!godMode2 || current_animation->tipo[i] != COLLIDER_PLAYER)
			if (playerFlip)
				colisionadores[i] = App->collision->AddCollider({ position.x - (r.w - playerPivotX) - r.x , position.y - r.h + playerPivotY - r.y,r.w,r.h }, current_animation->tipo[i], current_animation->callback[i]);
			else
				colisionadores[i] = App->collision->AddCollider({ position.x - playerPivotX + r.x , position.y + playerPivotY - r.h - r.y,r.w,r.h }, current_animation->tipo[i], current_animation->callback[i]);
	}
	r = current_animation->GetCurrentFrame();//returns the rectangle displaying the current animation

	SDL_Rect shadowrect = { 0,0,70,14 };
	//Blits player + collisions + shadow_____________
	if (playerFlip)
	{		//blit if player is flipped(compensates for pivot)
		if (showingshadow) { App->render->Blit(shadow, position.x - 39, 190, playerFlip, &shadowrect); showingshadow = false; }//shadow semitransparent
		else showingshadow = true;

		App->render->Blit(graphics, position.x - (r.w - playerPivotX), position.y + playerPivotY - r.h, playerFlip, &r); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)
	}
	else
	{    //blit if player is NOT flipped
		if (showingshadow) { App->render->Blit(shadow, position.x - 31, 190, playerFlip, &shadowrect); showingshadow = false; }//shadow semitransparent
		else showingshadow = true;
		
		App->render->Blit(graphics, position.x - playerPivotX, position.y + playerPivotY - r.h, playerFlip, &r); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)
	}




	if ((App->fight->showHealthBar) == true) {
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
	}


	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {
	if (!godMode2) {
		bool alredycollided = false;
		for (int i = 0; i < MAXNUMOFCOLLIDERS; i++)
		{
			if (c2->type == COLLIDER_PLAYER && !alredycollided) {
				alredycollided = true;
				if (this->playerFlip) {//normal pos (right)
					position.x += 1;

				}
				else {//flipped position (left)
					position.x -= 1;

				}
			}
		}
		if (c2->type == COLLIDER_PLAYER_SHOT) {
			Mix_PlayChannel(-1, App->audio->effects[2], 0);
			health += 30;
			p2inputs.Push(IN_FALL2);
			if (App->player2->position.y < groundlevelaux) {
				p2inputs.Push(IN_FALL2);
				airhit = true;
				posyaux = position.y;
			}
			invencibleframes = true;
			invencibleaux = SDL_GetTicks();
		}
		if (c2->type == COLLIDER_PLAYER_ATTACK) {
			if (App->player2->position.y < groundlevelaux){
				p2inputs.Push(IN_FALL2);
				airhit = true;
				posyaux = position.y;
			}
			else { getsHit = true; doingAction = true; }
			Mix_PlayChannel(-1, App->audio->effects[2], 0);
			invencibleframes = true;
			invencibleaux = SDL_GetTicks();
			health += 20;
			
			if (App->player->kicking || App->player->JumpKicking)
				Mix_PlayChannel(-1, App->audio->effects[17], 0);

			else
				Mix_PlayChannel(-1, App->audio->effects[16], 0);



		}


	}
}

bool ModulePlayer2::external_input(p2Qeue<player2_inputs>& p2inputs, p2Qeue<player_inputs>& inputs)
{
	static bool left2 = false;
	static bool right2 = false;
	static bool down2 = false;
	static bool up2 = false;

	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;

	if (App->fight->playerControl) {

		while (SDL_PollEvent(&event2) != 0)
		{
			if (event2.type == SDL_KEYUP && event2.key.repeat == 0)
			{
				switch (event2.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					return false;
					break;
				case SDLK_DOWN:
					p2inputs.Push(IN_CROUCH_UP2);
					down2 = false;
					break;
				case SDLK_UP:
					up2 = false;
					break;
				case SDLK_LEFT:
					p2inputs.Push(IN_LEFT_UP2);
					left2 = false;
					break;
				case SDLK_RIGHT:
					p2inputs.Push(IN_RIGHT_UP2);
					right2 = false;
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
			if (event2.type == SDL_KEYDOWN && event2.key.repeat == 0)
			{
				switch (event2.key.keysym.sym)
				{
				case SDLK_KP_1:
					p2inputs.Push(IN_X2);
					break;
				case SDLK_KP_2:
					p2inputs.Push(IN_KICK2);
					break;
				case SDLK_KP_3:
					p2inputs.Push(IN_SPECIAL2);
					break;
				case SDLK_UP:
					up2 = true;
					break;
				case SDLK_DOWN:
					down2 = true;
					break;
				case SDLK_LEFT:
					left2 = true;
					break;
				case SDLK_RIGHT:
					right2 = true;
					break;

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
			if(App->input->Controller_player1_Connected){
				if (App->input->Controller_player1_LAxisX > DEATHZONE) {

					right = true;
					if(left){
					left = false;
					inputs.Push(IN_RIGHT_UP);
					}
				}
				else if (App->input->Controller_player1_LAxisX < -DEATHZONE) {

					left = true;
					if (right) {
						right = false;
						inputs.Push(IN_LEFT_UP);
					}
				}
				else if (App->input->Controller_player1_LAxisY > -DEATHZONE && App->input->Controller_player1_LAxisX < DEATHZONE) {
					left = false;
					inputs.Push(IN_RIGHT_UP);
					right = false;
					inputs.Push(IN_LEFT_UP);
				}

				if (App->input->Controller_player1_LAxisY > DEATHZONE) {

					down = true;
					if (down) {
						up = false;
					}
				}
				else if (App->input->Controller_player1_LAxisY < -DEATHZONE) {

					up = true;
					if (down) {
						up = false;
						inputs.Push(IN_CROUCH_UP);

					}
				}
				else if (App->input->Controller_player1_LAxisY > -DEATHZONE && App->input->Controller_player1_LAxisY < DEATHZONE) {
					up = false;
					down = false;
					inputs.Push(IN_CROUCH_UP);
				}

				if (App->input->controller_player1_B_pressed == true) {

					if (App->input->CheckTornado(90,0,App->player->playerFlip) == true)
						inputs.Push(IN_SPECIAL);



					else if (App->input->CheckPunch(1,0, App->player->playerFlip) == true)
						inputs.Push(IN_X);;

				}


				if (App->input->controller_player1_A_pressed == true) {

					if (App->input->CheckTornado(90,0, App->player->playerFlip) == true)
						inputs.Push(IN_SPECIAL);



					else if (App->input->CheckPunch(1,0, App->player->playerFlip) == true)
						inputs.Push(IN_KICK);

				}

				if (App->input->controller_player1_RightShoulder_pressed  > DEATHZONE) {

					inputs.Push(IN_SPECIAL);

				}


			}

			if (App->input->Controller_player2_Connected) {
				if (App->input->Controller_player2_LAxisX > DEATHZONE) {

					right2 = true;
					if (left2) {
						left2 = false;
						p2inputs.Push(IN_RIGHT_UP2);
					}
				}
				else if (App->input->Controller_player2_LAxisX < -DEATHZONE) {

					left2 = true;
					if (right2) {
						right = false;
						p2inputs.Push(IN_LEFT_UP2);
					}
				}
				else if (App->input->Controller_player2_LAxisY > -DEATHZONE && App->input->Controller_player2_LAxisX < DEATHZONE) {
					left2 = false;
					p2inputs.Push(IN_RIGHT_UP2);
					right2 = false;
					p2inputs.Push(IN_LEFT_UP2);
				}

				if (App->input->Controller_player2_LAxisY > DEATHZONE) {

					down2 = true;
					if (down2) {
						up2 = false;
					}
				}
				else if (App->input->Controller_player2_LAxisY < -DEATHZONE) {

					up2 = true;
					if (down2) {
						up2 = false;
						p2inputs.Push(IN_CROUCH_UP2);

					}
				}
				else if (App->input->Controller_player2_LAxisY > -DEATHZONE && App->input->Controller_player2_LAxisY < DEATHZONE) {
					up2 = false;
					down2 = false;
					p2inputs.Push(IN_CROUCH_UP2);
				}

				if (App->input->controller_player2_B_pressed == true) {

					if (App->input->CheckTornado(200,1, playerFlip) == true)
						p2inputs.Push(IN_SPECIAL2);



					else if (App->input->CheckPunch(1,1, playerFlip) == true)
						p2inputs.Push(IN_X2);;

				}


				if (App->input->controller_player2_A_pressed == true) {

					if (App->input->CheckTornado(200,1, playerFlip) == true)
						p2inputs.Push(IN_SPECIAL2);



					else if (App->input->CheckPunch(1,1, playerFlip) == true)
						p2inputs.Push(IN_KICK2);

				}

				if (App->input->controller_player2_RightShoulder_pressed > DEATHZONE) {

					p2inputs.Push(IN_SPECIAL2);

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


		if (left2 && right2)
			p2inputs.Push(IN_LEFT_AND_RIGHT2);
		{
			if (left2)
				p2inputs.Push(IN_LEFT_DOWN2);
			if (right2)
				p2inputs.Push(IN_RIGHT_DOWN2);
		}

		if (up2 && down2)
			p2inputs.Push(IN_JUMP_AND_CROUCH2);
		else
		{
			if (down2)
				p2inputs.Push(IN_CROUCH_DOWN2);
			else
				p2inputs.Push(IN_CROUCH_UP2);
			if (up2)
				p2inputs.Push(IN_JUMP2);
		}
	}
	else if (!App->fight->playerControl) {
		p2inputs.Push(IN_CROUCH_UP2);
		down2 = false;

		up2 = false;

		p2inputs.Push(IN_LEFT_UP2);
		left2 = false;

		p2inputs.Push(IN_RIGHT_UP2);
		right2 = false;
		p2inputs.Push(IN_CROUCH_UP2);
		down2 = false;

		up = false;

		p2inputs.Push(IN_LEFT_UP2);
		left2 = false;

		p2inputs.Push(IN_RIGHT_UP2);





		inputs.Push(IN_CROUCH_UP);
		down = false;

		up = false;

		inputs.Push(IN_LEFT_UP);
		left = false;

		inputs.Push(IN_RIGHT_UP);
		right = false;
		inputs.Push(IN_CROUCH_UP);
		down = false;

		up = false;

		inputs.Push(IN_LEFT_UP);
		left = false;

		inputs.Push(IN_RIGHT_UP);

		while (SDL_PollEvent(&event2) != 0){}

	}

	return true;
}
void ModulePlayer2::internal_input(p2Qeue<player2_inputs>& inputs)
{

	if (p2jump_timer > 0)
	{
		if (SDL_GetTicks() / 1000 / 60 - p2jump_timer > JUMP_TIME)
		{
			inputs.Push(IN_JUMP_FINISH2);
			p2jump_timer = 0;
		}
	}


	if (p2punch_timer > 0)
	{
		if (SDL_GetTicks() / 1000 / 60 - p2punch_timer > PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH2);
			p2punch_timer = 0;
		}
	}

	if (p2punch_timer > 0)
	{
		if (SDL_GetTicks() / 1000 / 60 - p2punch_timer > PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH2);
			p2punch_timer = 0;
		}
	}

	if (p2kick_timer > 0)
	{
		if (SDL_GetTicks() / 1000 / 60 - p2kick_timer > PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH2);
			p2punch_timer = 0;
		}
	}

}
player2_states ModulePlayer2::process_fsm(p2Qeue<player2_inputs>& inputs)
{
	static player2_states state = ST_IDLE2;
	player2_inputs last_input;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{
		case ST_IDLE2:
		{
			switch (last_input)
			{
			case IN_RIGHT_DOWN2: state = ST_WALK_FORWARD2; break;
			case IN_LEFT_DOWN2: state = ST_WALK_BACKWARD2; break;
			case IN_JUMP2: state = ST_JUMP_NEUTRAL2;  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH2; break;
			case IN_X2: state = ST_PUNCH_STANDING2; p2punch_timer = SDL_GetTicks();  break;
			case IN_KICK2: state = ST_KICK_STANDING2; p2punch_timer = SDL_GetTicks();  break;
			case IN_SPECIAL2: state = ST_SPECIAL2; p2punch_timer = SDL_GetTicks();  break;
			case IN_DEATH2: state = ST_FALLING2; break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;

		case ST_WALK_FORWARD2:
		{
			switch (last_input)
			{
			case IN_RIGHT_UP2: state = ST_IDLE2; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE2; break;
			case IN_JUMP2: state = ST_JUMP_FORWARD2; p2jump_timer = SDL_GetTicks();  break;
			case IN_X2: state = ST_PUNCH_STANDING2; p2punch_timer = SDL_GetTicks();  break;
			case IN_KICK2: state = ST_KICK_STANDING2; p2punch_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH2; break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;

		case ST_WALK_BACKWARD2:
		{
			switch (last_input)
			{
			case IN_LEFT_UP2: state = ST_IDLE2; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE2; break;
			case IN_JUMP2: state = ST_JUMP_BACKWARD2; p2jump_timer = SDL_GetTicks();  break;
			case IN_X2: state = ST_PUNCH_STANDING2; p2punch_timer = SDL_GetTicks();  break;
			case IN_KICK2: state = ST_KICK_STANDING2; p2punch_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH2; break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;

		case ST_JUMP_NEUTRAL2:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_X2: state = ST_PUNCH_NEUTRAL_JUMP2; p2punch_timer = SDL_GetTicks(); break;
			case IN_KICK2: state = ST_KICK_NEUTRAL_JUMP2; p2punch_timer = SDL_GetTicks();  break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;

		case ST_JUMP_FORWARD2:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_X2: state = ST_PUNCH_FORWARD_JUMP2; break;
			case IN_KICK2: state = ST_KICK_FORWARD_JUMP2; p2punch_timer = SDL_GetTicks();  break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;

		case ST_JUMP_BACKWARD2:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_X2: state = ST_PUNCH_BACKWARD_JUMP2;  p2punch_timer = SDL_GetTicks(); break;
			case IN_KICK2: state = ST_KICK_BACKWARD_JUMP2; p2punch_timer = SDL_GetTicks();  break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_IDLE2; break;
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;

		case ST_KICK_NEUTRAL_JUMP2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_IDLE2; break;
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;

		case ST_PUNCH_FORWARD_JUMP2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_IDLE2; break;
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;

		case ST_KICK_FORWARD_JUMP2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_IDLE2; break;
			case IN_JUMP_FINISH2: state = ST_IDLE2; break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;

		break;

		case ST_PUNCH_STANDING2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_IDLE2; break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;

		case ST_CROUCH2:
		{
			switch (last_input)
			{
			case IN_CROUCH_UP2: state = ST_IDLE2; break;
			case IN_X2: state = ST_PUNCH_CROUCH2; break;
			case IN_KICK2: state = ST_KICK_CROUCH2; break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;
		case ST_KICK_CROUCH2:
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_CROUCH2; break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
			break;


		case ST_PUNCH_CROUCH2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_CROUCH2; break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
			break;
		}
	
		case ST_KICK_STANDING2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_IDLE2; break;
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		case ST_SPECIAL2:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH2: state = ST_IDLE2; break;
			case IN_FALL2:state = ST_FALLING2;break;
			}
		}
		break;

		case ST_FALLING2:
		{//new
			switch (last_input)
			{
			case IN_FALL_FINISH2: state = ST_IDLE2; break;
			}

		}
		break;
		}
	}
	return state;
}
