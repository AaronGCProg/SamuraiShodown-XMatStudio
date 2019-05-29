#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include "ModuleInterface.h"
#include "ModuleFight.h"
#include "ModulePlayer2.h"

ModulePlayer::ModulePlayer()
{

	//Attack types: 1->low punch/kick, 2->heavy punch/kick, 3->low sword, 4->mid sword, 5->punch that knocks down, 6-> sword that knocks down, 7->special (both specials knock down).
	//The four numers at the end of the attacks are: damage, playerDelay (both knockdown & delay frames), enemyDelay & attackType.

	// JUBEI ANIM
	const int idleCollider = 2;//Collider num for the idle animation
	SDL_Rect idleHitbox[idleCollider] = { { 25, 0, 40, 75 },{ 40, 75, 20, 20 } };
	COLLIDER_TYPE idleCollType[idleCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* idleCallBack[idleCollider] = { {this},{this} };

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 1, 11, 96, 106 }, 8, { 49,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack, 0, 0, 0, 0);
	idle.PushBack({ 98,10,87,107 }, 8, { 45,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack, 0, 0, 0, 0);
	idle.PushBack({ 186,11,88,106 }, 8, { 45,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack, 0, 0, 0, 0);
	idle.PushBack({ 275,12,89,105 }, 8, { 45,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack, 0, 0, 0, 0);
	idle.PushBack({ 365,13,92,104 }, 8, { 47,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack, 0, 0, 0, 0);
	idle.PushBack({ 458,13,97,104 }, 8, { 49,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack, 0, 0, 0, 0);
	idle.PushBack({ 556,13,104,104 }, 8, { 53,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack, 0, 0, 0, 0);
	idle.PushBack({ 661,12,102,105 }, 8, { 52,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack, 0, 0, 0, 0);
	idle.PushBack({ 764,11,96,106 }, 8, { 49,1 }, idleCollider, idleHitbox, idleCollType, idleCallBack, 0, 0, 0, 0);
	//idle.speed = 0.125f;


	const int backCollider = 2;//Collider num for the backward animation
	SDL_Rect backHitbox[backCollider] = { { 25, 0, 40, 75 },{ 40, 75, 20, 20 } };
	COLLIDER_TYPE backCollType[backCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* backCallBack[backCollider] = { {this},{this} };

	// walk backward animation 
	backward.PushBack({ 458,127,98,109 }, 9, { 23,1 }, backCollider, backHitbox, backCollType, backCallBack, 0, 0, 0, 0);
	backward.PushBack({ 277,137,91,99 }, 6, { 24,1 }, backCollider, backHitbox, backCollType, backCallBack, 0, 0, 0, 0);
	backward.PushBack({ 368,140,91,96 }, 9, { 29,1 }, backCollider, backHitbox, backCollType, backCallBack, 0, 0, 0, 0);
	backward.PushBack({ 277,137,91,99 }, 6, { 24,1 }, backCollider, backHitbox, backCollType, backCallBack, 0, 0, 0, 0);


	//backward.speed = 0.1f;


	const int forCollider = 2;//Collider num for the forward animation
	SDL_Rect forHitbox[forCollider] = { { 32, 0, 40, 75 },{ 33, 70, 20, 20 } };
	COLLIDER_TYPE forCollType[forCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* forCallBack[forCollider] = { {this},{this} };

	// walk forward animation 
	forward.PushBack({ 0,133,98,103 }, 8, { 29,1 }, forCollider, forHitbox, forCollType, forCallBack, 0, 0, 0, 0);
	forward.PushBack({ 184,128,91,108 }, 8, { 21,1 }, forCollider, forHitbox, forCollType, forCallBack, 0, 0, 0, 0);
	forward.PushBack({ 98,127,88,109 }, 8, { 21,1 }, forCollider, forHitbox, forCollType, forCallBack, 0, 0, 0, 0);
	forward.PushBack({ 184,128,91,108 }, 8, { 21,1 }, forCollider, forHitbox, forCollType, forCallBack, 0, 0, 0, 0);

	//forward.speed = 0.1f;


	const int kickCollider = 3;//Collider num for the kick animation
	const int kickCollider2 = 2;//Collider num for the kick animation
	SDL_Rect kickHitbox[kickCollider] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 },{ 60, 10, 35, 20 } };
	SDL_Rect kickHitbox2[kickCollider2] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 } };
	COLLIDER_TYPE kickCollType[kickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	COLLIDER_TYPE kickCollType2[kickCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* kickCallBack[kickCollider] = { {this},{this},{this} };
	Module* kickCallBack2[kickCollider2] = { {this},{this} };


	// Kick animation 
	kick.PushBack({ 902,487,77,107 }, 6, { 31,2 }, kickCollider2, kickHitbox2, kickCollType2, kickCallBack2, 15, 6, 20, 1);
	kick.PushBack({ 980,483,62,111 }, 6, { 31,2 }, kickCollider, kickHitbox, kickCollType, kickCallBack, 15, 6, 20, 1);
	kick.PushBack({ 1155,478,82,116 }, 6, { 31,2 }, kickCollider2, kickHitbox2, kickCollType2, kickCallBack2, 15, 6, 20, 1);
	kick.PushBack({ 980,483,62,111 }, 6, { 31,2 }, kickCollider, kickHitbox, kickCollType, kickCallBack, 15, 6, 20, 1);
	//kick.speed = 0.12f;


	const int punchCollider = 3;//Collider num for the punch animation
	const int punchCollider2 = 2;//Collider num for the punch animation
	SDL_Rect punchHitbox[punchCollider] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 },{ 40, 30, 80, 30 } };
	COLLIDER_TYPE punchCollType[punchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* punchCallBack[punchCollider] = { {this},{this},{this} };

	SDL_Rect punchHitbox2[punchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE punchCollType2[punchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER}, };
	Module* punchCallBack2[punchCollider2] = { {this},{this} };

	// Punch animation 
	punch.PushBack({ 1,721,86,97 }, 7, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack, 20, 9, 25, 3);
	punch.PushBack({ 88,729,130,89 }, 7, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack, 20, 9, 25, 3);
	punch.PushBack({ 219,729,150,90 }, 5, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack, 20, 9, 25, 3);
	punch.PushBack({ 370,729,137,89 }, 6, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack, 20, 9, 25, 3);
	punch.PushBack({ 508,729,96,89 }, 5, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack, 20, 9, 25, 3);
	//punch.speed = 0.2f;


	const int jumpCollider = 2;//Collider num for the jump animation
	SDL_Rect jumpHitbox[jumpCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpCollType[jumpCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpCallBack[jumpCollider] = { {this},{this} };

	//jump animation 
	jump.PushBack({ 557,124,75,119 }, 5, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jump.PushBack({ 631,124,75,119 }, 8, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jump.PushBack({ 705,135,73,108 }, 13, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jump.PushBack({ 778,169,73,73 }, 4, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jump.PushBack({ 852,152,73,90 }, 17, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jump.PushBack({ 949,31,77,86 }, 11, { 40, 6 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);

	//jump.speed = 0.05f;

	const int hurtCollider = 2;//Collider num for the hurt animation
	SDL_Rect hurtHitbox[hurtCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE hurtCollType[hurtCollider] = { {COLLIDER_NONE},{COLLIDER_NONE} };
	Module* hurtCallBack[hurtCollider] = { {this},{this} };
	// hurt animation
	hurtLow.PushBack({ 1838,736,98,90 }, 20, { 31,2 }, hurtCollider, hurtHitbox, hurtCollType, hurtCallBack, 0, 0, 0, 0);
	//hurtLow.speed = 0.05f;


	//jump kick animation 
	const int jumpKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpKickHitbox[jumpKickCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 90, 10, 25, 20 } };
	COLLIDER_TYPE jumpKickCollType[jumpKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpKickCallBack[jumpKickCollider] = { {this},{this},{this} };

	const int jumpKickCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpKickHitbox2[jumpKickCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpKickCollType2[jumpKickCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpKickCallBack2[jumpKickCollider2] = { {this},{this} };

	jumpKick.PushBack({ 1102,21,71,80 }, 6, { 31,2 }, jumpKickCollider2, jumpKickHitbox2, jumpKickCollType2, jumpKickCallBack2, 15, 6, 20, 1);
	jumpKick.PushBack({ 1160,146,122,96 }, 32, { 31,2 }, jumpKickCollider, jumpKickHitbox, jumpKickCollType, jumpKickCallBack, 15, 6, 20, 1);
	jumpKick.PushBack({ 1102,21,71,80 }, 6, { 31,2 }, jumpKickCollider2, jumpKickHitbox2, jumpKickCollType2, jumpKickCallBack2, 15, 6, 20, 1);


	//jump backwards animation 

	jumpBackward.PushBack({ 557,124,75,119 }, 10, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jumpBackward.PushBack({ 631,124,75,119 }, 8, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jumpBackward.PushBack({ 705,135,73,108 }, 15, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jumpBackward.PushBack({ 778,169,73,73 }, 4, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jumpBackward.PushBack({ 852,152,73,90 }, 32, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jumpBackward.PushBack({ 949,31,77,86 }, 6, { 40, 6 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);


	//jump punch animation 
	const int jumpPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpPunchHitbox[jumpPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 55, 27, 90, 10 } };
	COLLIDER_TYPE jumpPunchCollType[jumpPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpPunchCallBack[jumpPunchCollider] = { {this},{this},{this} };

	const int jumpPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpPunchHitbox2[jumpPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpPunchCollType2[jumpPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpPunchCallBack2[jumpPunchCollider2] = { {this},{this} };

	jumpPunch.PushBack({ 1,819,83,87 }, 4, { 31, 2 }, jumpPunchCollider2, jumpPunchHitbox2, jumpPunchCollType2, jumpPunchCallBack2, 15, 6, 20, 1);
	jumpPunch.PushBack({ 85,824,79,82 }, 4, { 31, 2 }, jumpPunchCollider, jumpPunchHitbox, jumpPunchCollType, jumpPunchCallBack, 15, 6, 20, 1);
	jumpPunch.PushBack({ 165,835,73,71 }, 3, { 31, 2 }, jumpPunchCollider, jumpPunchHitbox, jumpPunchCollType, jumpPunchCallBack, 15, 6, 20, 1);
	jumpPunch.PushBack({ 239,836,156,70 }, 3, { 31, 2 }, jumpPunchCollider, jumpPunchHitbox, jumpPunchCollType, jumpPunchCallBack, 15, 6, 20, 1);
	jumpPunch.PushBack({ 396,837,157,69 }, 3, { 31, 2 }, jumpPunchCollider2, jumpPunchHitbox2, jumpPunchCollType2, jumpPunchCallBack2, 15, 6, 20, 1);
	jumpPunch.PushBack({ 554,842,147,64 }, 20, { 31, 2 }, jumpPunchCollider2, jumpPunchHitbox2, jumpPunchCollType2, jumpPunchCallBack2, 15, 6, 20, 1);


	//jump foward animation 

	jumpFw.PushBack({ 557,124,75,119 }, 10, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jumpFw.PushBack({ 631,124,75,119 }, 8, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jumpFw.PushBack({ 705,135,73,108 }, 20, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jumpFw.PushBack({ 778,169,73,73 }, 8, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jumpFw.PushBack({ 852,152,73,90 }, 19, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jumpFw.PushBack({ 554,842,147,64 }, 20, { 31, 2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	jumpBackward.PushBack({ 949,31,77,86 }, 6, { 40, 6 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);


	//jump foward punch animation 
	const int jumpForwardPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpForwardPunchHitbox[jumpForwardPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 40, 75, 20, 20 } };
	COLLIDER_TYPE jumpForwardPunchCollType[jumpForwardPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpForwardPunchCallBack[jumpForwardPunchCollider] = { {this},{this},{this} };




	const int crouchCollider = 2;//Collider num for the jump kick animation
	SDL_Rect crouchHitbox2[crouchCollider] = { { 30, 0, 30, 55 },{40, 50, 20, 20 } };
	SDL_Rect crouchHitbox[crouchCollider] = { { 50, 0, 30, 55 },{ 60, 50, 20, 20 } };
	COLLIDER_TYPE crouchCollType[crouchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crouchCallBack[crouchCollider] = { {this},{this} };

	crouch.PushBack({ 949,31,77,86 }, 6, { 40, 6 }, crouchCollider, crouchHitbox2, crouchCollType, crouchCallBack, 0, 0, 0, 0);
	crouch.PushBack({ 1102,37,70,80 }, 2, { 60, 8 }, crouchCollider, crouchHitbox, crouchCollType, crouchCallBack, 0, 0, 0, 0);
	crouch.PushBack({ 1027,40,73,77 }, 2, { 60, 8 }, crouchCollider, crouchHitbox, crouchCollType, crouchCallBack, 0, 0, 0, 0);
	crouch.firstLoopFrame = 2;
	crouch.loop = true;


	//crouch punch animation 
	const int crouchPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox[crouchPunchCollider] = { { 30, 10, 40, 35 },{ 50, 35, 20, 20 },{ 75, 5, 50, 20 } };
	COLLIDER_TYPE crouchPunchCollType[crouchPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crouchPunchCallBack[crouchPunchCollider] = { {this},{this},{this} };

	const int crouchPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox2[crouchPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchPunchCollType2[crouchPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crouchPunchCallBack2[crouchPunchCollider2] = { {this},{this} };

	crouchPunch.PushBack({ 703,730,74,94 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2, 20, 9, 25, 3);
	crouchPunch.PushBack({ 778,722,76,102 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2, 20, 9, 25, 3);
	crouchPunch.PushBack({ 855,731,69,93 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2, 20, 9, 25, 3);
	crouchPunch.PushBack({ 925,754,100,70 }, 1, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack, 20, 9, 25, 3);
	crouchPunch.PushBack({ 1026,754,110,70 }, 2, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack, 20, 9, 25, 3);
	crouchPunch.PushBack({ 1137,730,111,94 }, 1, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack, 20, 9, 25, 3);
	crouchPunch.PushBack({ 1249,730,70,94 }, 7, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack, 20, 9, 25, 3);
	crouchPunch.PushBack({ 1321,754,100,70 }, 3, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack, 20, 9, 25, 3);
	crouchPunch.PushBack({ 1422,731,69,93 }, 3, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack, 20, 9, 25, 3);


	const int crouchKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchKickHitbox[crouchPunchCollider] = { { 5, 10, 40, 35 },{ 20, 35, 20, 20 },{ 78,0,20,20 } };
	COLLIDER_TYPE crouchKickCollType[crouchKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crouchKickCallBack[crouchKickCollider] = { {this},{this},{this} };
	crouchKick.PushBack({ 1102,21,71,80 }, 4, { 31,2 }, crouchPunchCollider, crouchKickHitbox, crouchKickCollType, crouchKickCallBack, 15, 6, 20, 1);
	crouchKick.PushBack({ 1262,31,122,86 }, 8, { 31,2 }, crouchKickCollider, crouchKickHitbox, crouchPunchCollType, crouchKickCallBack, 15, 6, 20, 1);

	//fall animation
	const int fallCollider = 2;//Collider num for the jump kick animation
	SDL_Rect fallHitbox[fallCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } }; //RESOLVE
	COLLIDER_TYPE fallCollType[fallCollider] = { {COLLIDER_NONE},{COLLIDER_NONE} };
	Module* fallCallBack[fallCollider] = { {this},{this} };

	fall.PushBack({ 1530,742,71,83 }, 23, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack, 0, 0, 0, 0);
	fall.PushBack({ 1604,741,105,81 }, 52, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack, 0, 0, 0, 0);
	fall.PushBack({ 1530,742,71,83 }, 13, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack, 0, 0, 0, 0);
	fall.PushBack({ 1604,741,105,81 }, 13, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack, 0, 0, 0, 0);
	fall.PushBack({ 1712,783,123,42 }, 75, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack, 0, 0, 0, 0);

	//getUp animation
	const int getUpCollider = 2;//Collider num for the jump kick animation
	SDL_Rect getUpHitbox[getUpCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } }; //RESOLVE
	COLLIDER_TYPE getUpCollType[getUpCollider] = { {COLLIDER_NONE},{COLLIDER_NONE} };
	Module* getUpCallBack[getUpCollider] = { {this},{this} };
	getUp.PushBack({ 108,470,108,54 }, 5, { 31,2 }, getUpCollider, getUpHitbox, getUpCollType, getUpCallBack, 0, 0, 0, 0);
	getUp.PushBack({ 1306,789,75,94 }, 8, { 31,2 }, getUpCollider, getUpHitbox, getUpCollType, getUpCallBack, 0, 0, 0, 0);
	getUp.PushBack({ 1,455,106,69 }, 4, { 31,2 }, getUpCollider, getUpHitbox, getUpCollType, getUpCallBack, 0, 0, 0, 0);
	getUp.PushBack({ 334,435,98,89 }, 4, { 31,2, }, getUpCollider, getUpHitbox, getUpCollType, getUpCallBack, 0, 0, 0, 0);


	const int tornadoCollider = 2;//Collider num for the tornado animation
	SDL_Rect tornadoHitbox[tornadoCollider] = { { 40, 10, 40, 65 },{ 55, 75, 20, 20 } };
	COLLIDER_TYPE tornadoCollType[tornadoCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* tornadoCallBack[tornadoCollider] = { {this},{this} };

	// Tornado animation
	tornado.PushBack({ 80, 1670, 105, 116 }, 8, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack, 0, 0, 0, 0);
	tornado.PushBack({ 184,1669,118,103 }, 2, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack, 0, 0, 0, 0);
	tornado.PushBack({ 276,1692,71, 94 }, 2, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack, 0, 0, 0, 0);
	tornado.PushBack({ 346,1715,100,71 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack, 0, 0, 0, 0);
	tornado.PushBack({ 445,1717,112,70 }, 2, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack, 0, 0, 0, 0);
	tornado.PushBack({ 556,1694,111,94 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack, 0, 0, 0, 0);
	tornado.PushBack({ 666,1701,103,87 }, 22, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack, 0, 0, 0, 0);
	tornado.PushBack({ 769,1691,73,96 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack, 0, 0, 0, 0);
	tornado.PushBack({ 842,1715,102,71 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack, 0, 0, 0, 0);
	tornado.PushBack({ 942,1693,71,94 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack, 0, 0, 0, 0);


	/*HAOMARU
	const int idleCollider = 2;//Collider num for the idle animation
	SDL_Rect idleHitbox[idleCollider] = { { 10, 0, 40, 75 },{ 25, 75, 20, 20 } };
	COLLIDER_TYPE idleCollType[idleCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* idleCallBack[idleCollider] = { {this},{this} };

	// idle animation (arcade sprite sheet)
	idle.PushBack({ 1, 8, 73, 113 }, 8, { 31,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 75, 10, 72, 111 }, 7, { 31,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 148, 12, 71, 109 }, 8, { 31,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 220, 14, 71, 107 }, 9, { 31,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 148, 12, 71, 109 }, 9, { 31,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	idle.PushBack({ 75, 10, 72, 111 }, 9, { 31,2 }, idleCollider, idleHitbox, idleCollType, idleCallBack);
	//idle.speed = 0.125f;


	const int backCollider = 2;//Collider num for the backward animation
	SDL_Rect backHitbox[backCollider] = { { 20, 0, 40, 75 },{ 35, 75, 20, 20 } };
	COLLIDER_TYPE backCollType[backCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* backCallBack[backCollider] = { {this},{this} };

	// walk backward animation
	backward.PushBack({ 767, 10, 82, 111 }, 5, { 31,2 }, backCollider, backHitbox, backCollType, backCallBack);
	backward.PushBack({ 849, 7, 74, 114 }, 11, { 31,2 }, backCollider, backHitbox, backCollType, backCallBack);
	backward.PushBack({ 924, 3, 68, 118 }, 11, { 31,2 }, backCollider, backHitbox, backCollType, backCallBack);
	backward.PushBack({ 993, 1, 65, 120 }, 9, { 31,2 }, backCollider, backHitbox, backCollType, backCallBack);
	backward.PushBack({ 924, 3, 68, 118 }, 11, { 31,2 }, backCollider, backHitbox, backCollType, backCallBack);
	backward.PushBack({ 849, 7, 74, 114 }, 11, { 31,2 }, backCollider, backHitbox, backCollType, backCallBack);
	//backward.speed = 0.1f;


	const int forCollider = 2;//Collider num for the forward animation
	SDL_Rect forHitbox[forCollider] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 } };
	COLLIDER_TYPE forCollType[forCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* forCallBack[forCollider] = { {this},{this} };

	// walk forward animation
	forward.PushBack({ 1089,12,75,109 }, 5, { 31,2 }, forCollider, forHitbox, forCollType, forCallBack);
	forward.PushBack({ 1165,9,68,112 }, 11, { 31,2 }, forCollider, forHitbox, forCollType, forCallBack);
	forward.PushBack({ 1234,5,61,116 }, 9, { 31,2 }, forCollider, forHitbox, forCollType, forCallBack);
	forward.PushBack({ 1296,3,56,118 }, 11, { 31,2 }, forCollider, forHitbox, forCollType, forCallBack);
	forward.PushBack({ 1352,9,69,112 }, 9, { 31,2 }, forCollider, forHitbox, forCollType, forCallBack);
	//forward.speed = 0.1f;


	const int kickCollider = 3;//Collider num for the kick animation
	const int kickCollider2 = 2;//Collider num for the kick animation
	SDL_Rect kickHitbox[kickCollider] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 },{ 60, 10, 35, 20 } };
	SDL_Rect kickHitbox2[kickCollider2] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 } };
	COLLIDER_TYPE kickCollType[kickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	COLLIDER_TYPE kickCollType2[kickCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* kickCallBack[kickCollider] = { {this},{this},{this} };
	Module* kickCallBack2[kickCollider2] = { {this},{this} };


	// Kick animation
	kick.PushBack({ 292,26,66,95 }, 5, { 31,2 }, kickCollider2, kickHitbox2, kickCollType2, kickCallBack2);
	kick.PushBack({ 359,23,86,98 }, 6, { 31,2 }, kickCollider, kickHitbox, kickCollType, kickCallBack);
	kick.PushBack({ 292,26,66,95 }, 5, { 31,2 }, kickCollider2, kickHitbox2, kickCollType2, kickCallBack2);
	//kick.speed = 0.12f;


	const int punchCollider = 3;//Collider num for the punch animation
	const int punchCollider2 = 2;//Collider num for the punch animation
	SDL_Rect punchHitbox[punchCollider] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 },{ 40, 30, 80, 30 } };
	COLLIDER_TYPE punchCollType[punchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* punchCallBack[punchCollider] = { {this},{this},{this} };

	SDL_Rect punchHitbox2[punchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE punchCollType2[punchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER}, };
	Module* punchCallBack2[punchCollider2] = { {this},{this} };

	// Punch animation
	punch.PushBack({ 1,122,68,127 }, 2, { 31,2 }, 2, punchHitbox2, punchCollType2, punchCallBack2);
	punch.PushBack({ 70,153,78,96 }, 4, { 31,2 }, 2, punchHitbox2, punchCollType2, punchCallBack2);
	punch.PushBack({ 149,156,130,93 }, 1, { 31,2 }, 2, punchHitbox2, punchCollType2, punchCallBack2);
	punch.PushBack({ 280,156,130,93 }, 2, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack);
	punch.PushBack({ 411,167,129,93 }, 3, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack);
	punch.PushBack({ 541,167,127,93 }, 4, { 31,5 }, punchCollider, punchHitbox, punchCollType, punchCallBack);
	punch.PushBack({ 669,167,119,93 }, 6, { 31,10 }, 2, punchHitbox, punchCollType, punchCallBack);
	punch.PushBack({ 789,164,130,85 }, 6, { 31,5 }, 2, punchHitbox2, punchCollType2, punchCallBack2);
	//punch.speed = 0.2f;


	const int jumpCollider = 2;//Collider num for the jump animation
	SDL_Rect jumpHitbox[jumpCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpCollType[jumpCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpCallBack[jumpCollider] = { {this},{this} };

	//jump animation
	jump.PushBack({ 484,9,60,112 }, 10, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jump.PushBack({ 545,30,74,91 }, 5, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jump.PushBack({ 620,38,76,83 }, 10, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jump.PushBack({ 545,30,74,91 }, 5, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jump.PushBack({ 484,9,60,112 }, 19, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	jump.PushBack({ 697,11,68,110 }, 11, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);

	//jump.speed = 0.05f;

	const int hurtCollider = 2;//Collider num for the hurt animation
	SDL_Rect hurtHitbox[hurtCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE hurtCollType[hurtCollider] = { {COLLIDER_NONE},{COLLIDER_NONE} };
	Module* hurtCallBack[hurtCollider] = { {this},{this} };
	// hurt animation
	hurtLow.PushBack({ 1421,24,79,97 }, 20, { 31,2 }, hurtCollider, hurtHitbox, hurtCollType, hurtCallBack);
	//hurtLow.speed = 0.05f;


	//jump kick animation
	const int jumpKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpKickHitbox[jumpKickCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 60, 10, 35, 20 } };
	COLLIDER_TYPE jumpKickCollType[jumpKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpKickCallBack[jumpKickCollider] = { {this},{this},{this} };

	const int jumpKickCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpKickHitbox2[jumpKickCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpKickCollType2[jumpKickCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpKickCallBack2[jumpKickCollider2] = { {this},{this} };

	jumpKick.PushBack({ 1278,564,79,91 }, 2, { 31,2 }, jumpKickCollider2, jumpKickHitbox2, jumpKickCollType2, jumpKickCallBack2);
	jumpKick.PushBack({ 1357,574,99,81 }, 19, { 31,2 }, jumpKickCollider, jumpKickHitbox, jumpKickCollType, jumpKickCallBack);
	jumpKick.PushBack({ 620,38,76,83 }, 10000, { 31,2 }, jumpKickCollider2, jumpKickHitbox2, jumpKickCollType2, jumpKickCallBack2);


	//jump backwards animation
	const int jumpBackCollider = 2;//Collider num for the jump kick animation
	SDL_Rect jumpBackHitbox[jumpBackCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpBackCollType[jumpBackCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpBackCallBack[jumpBackCollider] = { {this},{this} };

	jumpBackward.PushBack({ 558,541,64,130 }, 17, { 31,2 }, jumpBackCollider, jumpBackHitbox, jumpBackCollType, jumpBackCallBack);
	jumpBackward.PushBack({ 619,584,46,70 }, 3, { 31,2 }, jumpBackCollider, jumpBackHitbox, jumpBackCollType, jumpBackCallBack);
	jumpBackward.PushBack({ 664,600,44,53 }, 5, { 31,2 }, jumpBackCollider, jumpBackHitbox, jumpBackCollType, jumpBackCallBack);
	jumpBackward.PushBack({ 707,612,83,42 }, 4, { 31,2 }, jumpBackCollider, jumpBackHitbox, jumpBackCollType, jumpBackCallBack);
	jumpBackward.PushBack({ 790,572,63,79 }, 4, { 31,2 }, jumpBackCollider, jumpBackHitbox, jumpBackCollType, jumpBackCallBack);
	jumpBackward.PushBack({ 852,591,83,63 }, 4, { 31,2 }, jumpBackCollider, jumpBackHitbox, jumpBackCollType, jumpBackCallBack);
	jumpBackward.PushBack({ 935,572,63,84 }, 4, { 31,2 }, jumpBackCollider, jumpBackHitbox, jumpBackCollType, jumpBackCallBack);
	jumpBackward.PushBack({ 1027,565,64,84 }, 4, { 31,2 }, jumpBackCollider, jumpBackHitbox, jumpBackCollType, jumpBackCallBack);
	jumpBackward.PushBack({ 1087,563,93,91 }, 4, { 31,2 }, jumpBackCollider, jumpBackHitbox, jumpBackCollType, jumpBackCallBack);


	//jump backward animation
	const int jumpBackwardCollider = 2;//Collider num for the jump kick animation
	SDL_Rect jumpBackwardHitbox[jumpBackwardCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpBackwardCollType[jumpBackwardCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpBackwardCallBack[jumpBackwardCollider] = { {this},{this} };

	jumpBackward.PushBack({ 558,541,64,130 }, 17, { 31,2 }, jumpBackwardCollider, jumpBackwardHitbox, jumpBackwardCollType, jumpBackwardCallBack);
	jumpBackward.PushBack({ 619,584,46,70 }, 3, { 31,2 }, jumpBackwardCollider, jumpBackwardHitbox, jumpBackwardCollType, jumpBackwardCallBack);
	jumpBackward.PushBack({ 664,600,44,53 }, 5, { 31,2 }, jumpBackwardCollider, jumpBackwardHitbox, jumpBackwardCollType, jumpBackwardCallBack);
	jumpBackward.PushBack({ 707,612,83,42 }, 4, { 31,2 }, jumpBackwardCollider, jumpBackwardHitbox, jumpBackwardCollType, jumpBackwardCallBack);
	jumpBackward.PushBack({ 790,572,63,79 }, 4, { 31,2 }, jumpBackwardCollider, jumpBackwardHitbox, jumpBackwardCollType, jumpBackwardCallBack);
	jumpBackward.PushBack({ 852,591,83,63 }, 4, { 31,2 }, jumpBackwardCollider, jumpBackwardHitbox, jumpBackwardCollType, jumpBackwardCallBack);
	jumpBackward.PushBack({ 935,572,63,84 }, 4, { 31,2 }, jumpBackwardCollider, jumpBackwardHitbox, jumpBackwardCollType, jumpBackwardCallBack);
	jumpBackward.PushBack({ 1027,565,64,84 }, 4, { 31,2 }, jumpBackwardCollider, jumpBackwardHitbox, jumpBackwardCollType, jumpBackwardCallBack);
	jumpBackward.PushBack({ 1087,563,93,91 }, 4, { 31,2 }, jumpBackwardCollider, jumpBackwardHitbox, jumpBackwardCollType, jumpBackwardCallBack);


	//jump punch animation
	const int jumpPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpPunchHitbox[jumpPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 55, 27, 40, 10 } };
	COLLIDER_TYPE jumpPunchCollType[jumpPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpPunchCallBack[jumpPunchCollider] = { {this},{this},{this} };

	const int jumpPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpPunchHitbox2[jumpPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpPunchCollType2[jumpPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpPunchCallBack2[jumpPunchCollider2] = { {this},{this} };

	jumpPunch.PushBack({ 1028,566,60,87 }, 2, { 31, 2 }, jumpPunchCollider2, jumpPunchHitbox2, jumpPunchCollType2, jumpPunchCallBack2);
	jumpPunch.PushBack({ 1089,564,90,90 }, 3, { 31, 2 }, jumpPunchCollider, jumpPunchHitbox, jumpPunchCollType, jumpPunchCallBack);
	jumpPunch.PushBack({ 1180,560,98,92 }, 13, { 31, 2 }, jumpPunchCollider, jumpPunchHitbox, jumpPunchCollType, jumpPunchCallBack);
	jumpPunch.PushBack({ 1089,564,90,90 }, 2, { 31, 2 }, jumpPunchCollider, jumpPunchHitbox, jumpPunchCollType, jumpPunchCallBack);
	jumpPunch.PushBack({ 1028,566,60,87 }, 5, { 31, 2 }, jumpPunchCollider2, jumpPunchHitbox2, jumpPunchCollType2, jumpPunchCallBack2);


	//jump foward animation
	const int jumpForwardCollider = 2;//Collider num for the jump kick animation
	SDL_Rect jumpForwardHitbox[jumpForwardCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpForwardCollType[jumpForwardCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpForwardCallBack[jumpForwardCollider] = { {this},{this} };

	jumpFw.PushBack({ 1,525,53,128 }, 22, { 31, 2 }, jumpForwardCollider, jumpForwardHitbox, jumpForwardCollType, jumpForwardCallBack);
	jumpFw.PushBack({ 64,595,51,58 }, 2, { 31, 2 }, jumpForwardCollider, jumpForwardHitbox, jumpForwardCollType, jumpForwardCallBack);
	jumpFw.PushBack({ 116,592,82,61 }, 4, { 31, 2 }, jumpForwardCollider, jumpForwardHitbox, jumpForwardCollType, jumpForwardCallBack);
	jumpFw.PushBack({ 199,592, 82,61 }, 4, { 31, 2 }, jumpForwardCollider, jumpForwardHitbox, jumpForwardCollType, jumpForwardCallBack);
	jumpFw.PushBack({ 64,595,51,58 }, 2, { 31, 2 }, jumpForwardCollider, jumpForwardHitbox, jumpForwardCollType, jumpForwardCallBack);
	jumpFw.PushBack({ 116,592,82,61 }, 4, { 31, 2 }, jumpForwardCollider, jumpForwardHitbox, jumpForwardCollType, jumpForwardCallBack);
	jumpFw.PushBack({ 199,592, 82,61 }, 4, { 31, 2 }, jumpForwardCollider, jumpForwardHitbox, jumpForwardCollType, jumpForwardCallBack);
	jumpFw.PushBack({ 282,570,76,83 }, 22, { 31, 2 }, jumpForwardCollider, jumpForwardHitbox, jumpForwardCollType, jumpForwardCallBack);
	jumpFw.PushBack({ 359,562,74,91 }, 22, { 31, 2 }, jumpForwardCollider, jumpForwardHitbox, jumpForwardCollType, jumpForwardCallBack);


	//jump foward punch animation
	const int jumpForwardPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpForwardPunchHitbox[jumpForwardPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 40, 75, 20, 20 } };
	COLLIDER_TYPE jumpForwardPunchCollType[jumpForwardPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpForwardPunchCallBack[jumpForwardPunchCollider] = { {this},{this},{this} };


	const int jumpForwardPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpForwardPunchHitbox2[jumpForwardPunchCollider2] = { { 0, 10, 40, 65 },{ 60, 30, 30, 20 } };
	COLLIDER_TYPE jumpForwardPunchCollType2[jumpForwardPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpForwardPunchCallBack2[jumpForwardPunchCollider2] = { {this},{this} };

	jumpFwPunch.PushBack({ 1028,566,60,87 }, 2, { 31, 2 }, jumpForwardPunchCollider2, jumpForwardPunchHitbox2, jumpForwardPunchCollType2, jumpForwardPunchCallBack2);
	jumpFwPunch.PushBack({ 101,699,60,87 }, 2, { 31, 2 }, jumpForwardPunchCollider2, jumpForwardPunchHitbox2, jumpForwardPunchCollType2, jumpForwardPunchCallBack2);
	jumpFwPunch.PushBack({ 1,694,98,92 }, 2, { 31, 2 }, jumpForwardPunchCollider2, jumpForwardPunchHitbox2, jumpForwardPunchCollType2, jumpForwardPunchCallBack2);
	jumpFwPunch.PushBack({ 162,693,99,93 }, 2, { 31, 2 }, jumpForwardPunchCollider, jumpForwardPunchHitbox, jumpForwardPunchCollType, jumpForwardPunchCallBack);
	jumpFwPunch.PushBack({ 262,693,99,93 }, 2, { 31, 2 }, jumpForwardPunchCollider, jumpForwardPunchHitbox, jumpForwardPunchCollType, jumpForwardPunchCallBack);
	jumpFwPunch.PushBack({ 362,686,121,100 }, 2, { 31, 2 }, jumpForwardPunchCollider, jumpForwardPunchHitbox, jumpForwardPunchCollType, jumpForwardPunchCallBack);
	jumpFwPunch.PushBack({ 492,690,119,96 }, 3, { 31, 2 }, jumpForwardPunchCollider, jumpForwardPunchHitbox, jumpForwardPunchCollType, jumpForwardPunchCallBack);
	jumpFwPunch.PushBack({ 101,699,60,87 }, 5, { 31, 2 }, jumpForwardPunchCollider2, jumpForwardPunchHitbox2, jumpForwardPunchCollType2, jumpForwardPunchCallBack2);
	jumpFwPunch.PushBack({ 1028,566,60,87 }, 15, { 31, 2 }, jumpForwardPunchCollider2, jumpForwardPunchHitbox2, jumpForwardPunchCollType2, jumpForwardPunchCallBack2);

	const int crouchCollider = 2;//Collider num for the jump kick animation
	SDL_Rect crouchHitbox2[crouchCollider] = { { 30, 0, 30, 55 },{40, 50, 20, 20 } };
	SDL_Rect crouchHitbox[crouchCollider] = { { 50, 0, 30, 55 },{ 60, 50, 20, 20 } };
	COLLIDER_TYPE crouchCollType[crouchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crouchCallBack[crouchCollider] = { {this},{this} };

	crouch.PushBack({ 1499,11,70,113 }, 6, { 40, 6 }, crouchCollider, crouchHitbox2, crouchCollType, crouchCallBack);
	crouch.PushBack({ 1568,46,88,80 }, 2, { 60, 8 }, crouchCollider, crouchHitbox, crouchCollType, crouchCallBack);
	crouch.firstLoopFrame = 1;
	crouch.loop = true;

	//crouch punch animation
	const int crouchPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox[crouchPunchCollider] = { { 30, 10, 40, 35 },{ 50, 35, 20, 20 },{ 75, 5, 50, 20 } };
	COLLIDER_TYPE crouchPunchCollType[crouchPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crouchPunchCallBack[crouchPunchCollider] = { {this},{this},{this} };

	const int crouchPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox2[crouchPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchPunchCollType2[crouchPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crouchPunchCallBack2[crouchPunchCollider2] = { {this},{this} };

	crouchPunch.PushBack({ 178,814,83,69 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);
	crouchPunch.PushBack({ 262,815,126,68 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);
	crouchPunch.PushBack({ 389,815,126,68 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);
	crouchPunch.PushBack({ 516,813,130,71 }, 2, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 640,814,127,69 }, 6, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 767,814,87,72 }, 8, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 852,814,82,68 }, 3, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 934,813,85,71 }, 3, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);


	const int crouchKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchKickHitbox[crouchPunchCollider] = { { 5, 10, 40, 35 },{ 20, 35, 20, 20 },{ 78,0,20,20 } };
	COLLIDER_TYPE crouchKickCollType[crouchKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crouchKickCallBack[crouchKickCollider] = { {this},{this},{this} };
	crouchKick.PushBack({ 1019,803,78,80 }, 2, { 31,2 }, crouchPunchCollider, crouchKickHitbox, crouchKickCollType, crouchKickCallBack);
	crouchKick.PushBack({ 1098,810,98,73 }, 8, { 31,2 }, crouchKickCollider, crouchKickHitbox, crouchPunchCollType, crouchKickCallBack);

	//fall animation
	const int fallCollider = 2;//Collider num for the jump kick animation
	SDL_Rect fallHitbox[fallCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } }; //RESOLVE
	COLLIDER_TYPE fallCollType[fallCollider] = { {COLLIDER_NONE},{COLLIDER_NONE} };
	Module* fallCallBack[fallCollider] = { {this},{this} };

	fall.PushBack({ 334,435,98,89 }, 23, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack);
	fall.PushBack({ 1,455,106,69 }, 45, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack);
	fall.PushBack({ 108,470,108,54 }, 6, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack);
	fall.PushBack({ 1,455,106,69 }, 27, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack);
	fall.PushBack({ 108,470,108,54 }, 5, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack);
	fall.PushBack({ 217,482,116,42 }, 50, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack);

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
	COLLIDER_TYPE tornadoCollType[tornadoCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* tornadoCallBack[tornadoCollider] = { {this},{this} };

	// Tornado animation
	tornado.PushBack({ 1, 271, 100, 102 }, 8, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 102,271,81,103 }, 2, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 185,277,82, 95 }, 2, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 268,268,67,107 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 443,262,72,174 }, 2, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 516,261,112,113 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 628,263,113,105 }, 22, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 741,263,119,105 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	tornado.PushBack({ 860,263,98,105 }, 4, { 31,2 }, tornadoCollider, tornadoHitbox, tornadoCollType, tornadoCallBack);
	//tornado.speed = 0.2f;
	*/

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	position.x = 100;
	position.y = 198; // 198about the same position on the ground as its on the real game.

	jump_timer = 0;
	punch_timer = 0;
	kick_timer = 0;
	bool ret = true;
	groundlevelaux = position.y;

	health = 0;

	LOG("Listening for Arrow keys + SPACE:\n");
	LOG("Loading player textures");

	graphics = App->textures->Load("Assets/Sprites/jubei.png"); // arcade version
	ui = App->textures->Load("Assets/Sprites/UIspritesheet2.png"); // health bar 
	shadow = App->textures->Load("Assets/Sprites/sombra.png"); // health bar 

	/* Haoh Sounds
	App->audio->effects[0] = Mix_LoadWAV("Assets/Music/haohmaru_senpuuretsuzan.wav");
	App->audio->effects[1] = Mix_LoadWAV("Assets/Music/HaohmaruTornado.wav");
	App->audio->effects[2] = Mix_LoadWAV("Assets/Music/haohmaru_getshitted1.wav");
	App->audio->effects[14] = Mix_LoadWAV("Assets/Music/CharacterLandingGround.wav");
	App->audio->effects[15] = Mix_LoadWAV("Assets/Music/LightJumpAir.wav");
	App->audio->effects[16] = Mix_LoadWAV("Assets/Music/Slash1.wav");
	App->audio->effects[17] = Mix_LoadWAV("Assets/Music/KickConnect.wav");
	App->audio->effects[18] = Mix_LoadWAV("Assets/Music/WeaponAttackNoConnect.wav");
	App->audio->effects[19] = Mix_LoadWAV("Assets/Music/LightKickMiss1.wav");
	*/


	App->audio->effects[0] = Mix_LoadWAV("Assets/Music/jubei_shigetsutoh.wav");
	App->audio->effects[1] = Mix_LoadWAV("Assets/Music/jubei_wavesound.wav");
	App->audio->effects[2] = Mix_LoadWAV("Assets/Music/jubei_getshitted1.wav");
	App->audio->effects[20] = Mix_LoadWAV("Assets/Music/jubei_getshitted4.wav");
	App->audio->effects[14] = Mix_LoadWAV("Assets/Music/CharacterLandingGround.wav");
	App->audio->effects[15] = Mix_LoadWAV("Assets/Music/LightJumpAir.wav");
	App->audio->effects[16] = Mix_LoadWAV("Assets/Music/Slash1.wav");
	App->audio->effects[17] = Mix_LoadWAV("Assets/Music/KickConnect.wav");
	App->audio->effects[18] = Mix_LoadWAV("Assets/Music/WeaponAttackNoConnect.wav");
	App->audio->effects[19] = Mix_LoadWAV("Assets/Music/LightKickMiss1.wav");



	return ret;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading Character");
	App->audio->CleanUp();

	App->textures->Unload(shadow);
	App->textures->Unload(ui);
	App->textures->Unload(graphics);


	for (int i = 0; i < MAXNUMOFCOLLIDERS; i++)//deletes all the hitboxes at the start of the frame
	{
		if (colisionadores[i] != nullptr) {
			colisionadores[i]->to_delete = true;
			colisionadores[i] = nullptr;
		}
	}

	return true;
}


update_status ModulePlayer::PreUpdate()
{

	if (godMode)//deletes all the collision boxes if in god mode
	{
		for (int i = 0; i < MAXNUMOFCOLLIDERS; i++)
		{
			if (colisionadores[i] != nullptr)
				colisionadores[i]->to_delete = true;
		}
	}
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
update_status ModulePlayer::Update()
{
	float player1scale = App->render->escala - (PLAYER_ESCALE*(App->render->escala - 0.5)); //sets the player scale to 1.25 when he's in zoomin and to 0.75 when zoomout
	//the PLAYER ESCALE is to adjust the real scale of the player

	current_animation = &idle;

	int speed = 2 * player1scale;

	if (invencibleframes) {
		if (SDL_GetTicks() - (invencibleaux) >= 750) {
			invencibleframes = false;
		}
	}

	internal_input(inputs);
	player_states state = process_fsm(inputs);
	current_state = state;

	if (!doingAction) {
		switch (state)
		{
		case ST_IDLE:
			LOG("IDLE\n");
			current_animation = &idle;
			break;
		case ST_WALK_FORWARD:
			LOG("FORWARD >>>\n");
			if (!playerFlip) {
				current_animation = &forward;
				position.x += (int)((speed + 1)*player1scale);
			}
			else {
				current_animation = &backward;
				position.x += (int)((speed)*player1scale);
				blocking = true;
			}
			break;
		case ST_WALK_BACKWARD:
			LOG("BACKWARD <<<\n");
			if (!playerFlip) {
				current_animation = &backward;
				position.x -= (int)((speed)*player1scale);
				blocking = true;
			}
			else {
				current_animation = &forward;
				position.x -= (int)((speed + 1)*player1scale);
			}
			break;
		case ST_JUMP_NEUTRAL:
			LOG("JUMPING NEUTRAL ^^^^\n");
			jumping = true; doingAction = true;
			Mix_PlayChannel(-1, App->audio->effects[15], 0);
			break;
		case ST_JUMP_FORWARD:
			LOG("JUMPING FORWARD ^^>>\n");
			jumpdiagonal = true;
			Mix_PlayChannel(-1, App->audio->effects[15], 0);
			doingAction = true;
			break;
		case ST_JUMP_BACKWARD:
			LOG("JUMPING BACKWARD ^^<<\n");
			jumpleft = true;
			jumpdiagonal = true;
			Mix_PlayChannel(-1, App->audio->effects[15], 0);
			doingAction = true;
			break;
		case ST_CROUCH:
			LOG("CROUCHING ****\n");
			crouching = true;
			doingAction = true;
			break;
		case ST_PUNCH_CROUCH:
			LOG("PUNCH CROUCHING **++\n");
			crouchpunching = true; doingAction = true;
			break;
		case ST_KICK_CROUCH:
			LOG("KICK CROUCHING **++\n");
			crouchkicking = true; doingAction = true;
			break;
		case ST_PUNCH_STANDING:
			LOG("PUNCH STANDING ++++\n");
			punching = true; doingAction = true;
			break;
		case ST_KICK_STANDING:
			LOG("KICK STANDING ----\n");
			kicking = true; doingAction = true;
			break;
		case ST_SPECIAL:
			LOG("SPECIAL OwwwwO\n");
			tornading = true; doingAction = true;
			Mix_PlayChannel(-1, App->audio->effects[0], 0);
			Mix_PlayChannel(-1, App->audio->effects[1], 0);
			if (playerFlip) {
				App->particles->tornadoHao.speed.x = -3;
				App->particles->AddParticle(App->particles->tornadoHao, (int)(position.x - (140 * player1scale)), (int)(position.y - (44 * player1scale)), playerFlip, COLLIDER_PLAYER_SHOT);

			}
			else {
				App->particles->tornadoHao.speed.x = +3;
				App->particles->AddParticle(App->particles->tornadoHao, (int)(position.x + (18 * player1scale)), (int)(position.y - (44 * player1scale)), playerFlip, COLLIDER_PLAYER_SHOT);
			}
			break;
		case ST_FALLING://new
			falling = true; doingAction = true;
			break;
		}
	}
	//_________________
	if (App->input->keys[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN)
	{
		if (godMode)
			godMode = false;
		else
			godMode = true;

	}

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
		current_animation = &tornado;
		if (tornado.GetAnimEnd() == true) { tornading = false; doingAction = false; tornado.SetAnimEnd(false); }
	}

	if (punching) {
		//set kick anim
		current_animation = &punch;
		//stop kick anim

		if (current_animation->current_frame > 6 && current_animation->current_frame < 8 && !App->player->getsHit && !audioPlayed) {
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
			crouchpunching = false; doingAction = false; crouchPunch.SetAnimEnd(false); inputs.Push(IN_PUNCH_FINISH);
		}
	}

	if (crouchkicking)
	{
		//set crouch punch anim.
		current_animation = &crouchKick;
		//stop crouch punch anim
		if (crouchKick.GetAnimEnd() == true) { crouchkicking = false; doingAction = false; crouchKick.SetAnimEnd(false); inputs.Push(IN_PUNCH_FINISH); }
	}

	if (getsHit) {
		//set punch anim
		current_animation = &hurtLow;
		//body->to_delete = true;

		if (playerFlip) {
			if (aux > 0 && aux < 11) {
				position.x += (int)(aux*player1scale);
				aux--;
			}
		}
		else if (!playerFlip) {
			if (aux > 0 && aux < 11)
				position.x -= (int)(aux*player1scale);
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
		if (App->player->current_state == ST_PUNCH_NEUTRAL_JUMP2) {
			JumpPunching = true;
		}
		if (App->player->current_state == ST_KICK_NEUTRAL_JUMP2) {
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
		if (JumpPunching &&current_animation->current_frame >= 3 && !App->player->getsHit && !audioPlayed) {
			Mix_PlayChannel(-1, App->audio->effects[18], 0);
			audioPlayed = true;
		}
		if (JumpKicking && current_animation->current_frame >= 2 && !App->player->getsHit && !audioPlayed) {
			Mix_PlayChannel(-1, App->audio->effects[19], 0);
			audioPlayed = true;
		}
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
			inputs.Push(IN_JUMP_FINISH);
			jumpKick.Reset();
			jumpPunch.Reset();
			jump.Reset();
		}
		jumpingframe++;
	}
	if (jumpdiagonal)
	{
		if (App->player->current_state == ST_PUNCH_NEUTRAL_JUMP) {
			JumpPunching = true;
		}
		if (App->player->current_state == ST_KICK_NEUTRAL_JUMP) {
			JumpKicking = true;
		}

		if (JumpPunching)
			current_animation = &jumpPunch;
		else if (JumpKicking)
			current_animation = &jumpKick;
		else
			current_animation = &jumpFw; //Jumpforward animation

		if (JumpPunching)
			current_animation = &jumpPunch;
		else if (JumpKicking)
			current_animation = &jumpKick;
		else
			current_animation = &jumpFw; //Jumpforward animation


		position.y = groundlevelaux - (JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY)*pow(jumpingframe, 2));//MRUA formula
		if (jumpleft)
			position.x -= 4;
		else
			position.x += 4;
		hasjumped = true;
		//stop jump anim
		if (position.y > groundlevelaux && hasjumped == true)	//end of the jump
		{
			jumpingframe = 0;
			hasjumped = false;
			jumpdiagonal = false;
			jumpleft = false;
			JumpPunching = false;
			JumpKicking = false;
			audioPlayed = false;
			Mix_PlayChannel(-1, App->audio->effects[14], 0);
			position.y = groundlevelaux;
			doingAction = false;
			inputs.Push(IN_JUMP_FINISH);
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
			inputs.Push(IN_JUMP_FINISH);
			jumpFw.Reset();
			jumpKick.Reset();
			jumpBackward.Reset();
			jump.Reset();
			airhit = false;

		}
		jumpingframe++;
	}

	if (falling)//new
	{
		current_animation = &fall;
		if (fall_bounces > FALLBOUNCES) { position.y = groundlevelaux; delay++; }
		else
		{

			position.y = groundlevelaux - (10 * jumpingframe) + (0.5*(0.5*JUMP_INIT_AY + (0.2f*(fall_bounces + 1)))*pow(jumpingframe, 2));//MRUA formula
			if (playerFlip)position.x += 2 - (fall_bounces);
			else position.x -= 2 - (fall_bounces);

			hasjumped = true;
			jumpingframe++;
			if (position.y > groundlevelaux)
			{
				App->render->StartCameraShake(60, 1);
				jumpingframe = 0;
				position.y = groundlevelaux;
				fall_bounces++;
			}
		}
		if (fall_bounces > FALLBOUNCES &&hasjumped == true && delay > 45 || App->fight->played == 1)
		{
			hasjumped = false;
			jumpingframe = 0;
			inputs.Push(IN_FALL_FINISH);
			fall_bounces = 0;
			doingAction = false;
			falling = false;
			position.y = groundlevelaux;
			fall.Reset();
			delay = 0;
			Mix_PlayChannel(-1, App->audio->effects[20], 0);
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
			inputs.Push(IN_JUMP_FINISH);
			jumpFw.Reset();
			jumpKick.Reset();
			jumpBackward.Reset();
			jump.Reset();
			airhit = false;

		}

	}

	for (int i = 0; i < MAXNUMOFCOLLIDERS; i++)//deletes all the hitboxes at the start of the frame
	{
		if (colisionadores[i] != nullptr)
			colisionadores[i]->to_delete = true;
	}

	// Draw everything --------------------------------------
	playerPivotX = current_animation->pivotpos[(int)current_animation->current_frame].x;
	playerPivotY = current_animation->pivotpos[(int)current_animation->current_frame].y;


	SDL_Rect r;
	int hitboxmax = current_animation->collidersmax[(int)current_animation->current_frame]; //number of collision boxes in each frame
	for (int i = 0; i < hitboxmax; i++)
	{
		r = current_animation->hitbox[i];
		if ((!godMode || current_animation->tipo[i] != COLLIDER_ENEMY) && invencibleframes && current_animation->tipo[i] == COLLIDER_PLAYER)
			if (playerFlip)
				colisionadores[i] = App->collision->AddCollider({ (int)(position.x + (playerPivotX - r.w - r.x)*player1scale) , (int)(position.y + (playerPivotY - r.h - r.y)*player1scale),(int)(r.w*player1scale),(int)(r.h*player1scale) }, COLLIDER_NONE, current_animation->damage, current_animation->playerDelay, current_animation->enemyDelay, current_animation->attackType, current_animation->callback[i]);
			else
				colisionadores[i] = App->collision->AddCollider({ (int)(position.x + (r.x - playerPivotX)*player1scale) , (int)(position.y + (playerPivotY - r.h - r.y)*player1scale),(int)(r.w*player1scale),(int)(r.h*player1scale) }, COLLIDER_NONE, current_animation->damage, current_animation->playerDelay, current_animation->enemyDelay, current_animation->attackType, current_animation->callback[i]);

		else if (!godMode || current_animation->tipo[i] != COLLIDER_ENEMY)
			if (playerFlip)
				colisionadores[i] = App->collision->AddCollider({ (int)(position.x + (playerPivotX - r.w - r.x)*player1scale) , (int)(position.y + (playerPivotY - r.h - r.y)*player1scale),(int)(r.w*player1scale),(int)(r.h*player1scale) }, current_animation->tipo[i], current_animation->damage, current_animation->playerDelay, current_animation->enemyDelay, current_animation->attackType, current_animation->callback[i]);
			else
				colisionadores[i] = App->collision->AddCollider({ (int)(position.x + (r.x - playerPivotX)*player1scale) , (int)(position.y + (playerPivotY - r.h - r.y)*player1scale),(int)(r.w*player1scale),(int)(r.h*player1scale) }, current_animation->tipo[i], current_animation->damage, current_animation->playerDelay, current_animation->enemyDelay, current_animation->attackType, current_animation->callback[i]);
	}
	r = current_animation->GetCurrentFrame();//returns the rectangle displaying the current animation

	SDL_Rect shadowrect = { 0,0,70,14 };
	//Blits player + collisions_____________
	if (playerFlip)
	{		//blit if player is flipped(compensates for pivot)
		if (showingshadow) { App->render->Blit(shadow, position.x - (39 * player1scale), 190, playerFlip, &shadowrect, 1.0, true, true, true); showingshadow = false; }//shadow semitransparent
		else showingshadow = true;
		App->render->Blit(graphics, position.x - (r.w - playerPivotX)*player1scale, position.y + (playerPivotY - r.h)*player1scale, playerFlip, &r, 1.0, true, true, true); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)
	}
	else
	{   //blit if player is NOT flipped
		if (showingshadow) { App->render->Blit(shadow, position.x - (31 * player1scale), 190, playerFlip, &shadowrect, 1.0, true, true, true); showingshadow = false; }//shadow semitransparent
		else showingshadow = true;
		App->render->Blit(graphics, position.x - (playerPivotX*player1scale), position.y + ((playerPivotY - r.h)*player1scale), playerFlip, &r, 1.0, true, true, true); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)
	}



	SDL_Rect healthBar = { 90, 81, 134, 15 };

	if ((App->fight->showHealthBar) == true) {
		App->render->Blit(ui, 5, 15, false, &healthBar, NULL, true);
		SDL_Rect healthBar = { 90, 81, 134, 15 };
		App->render->Blit(ui, 167, 15, false, &healthBar, NULL, true);
		if (HEALTH_VALUE > health + 50) {
			SDL_Rect healthValue = { 90, 97, HEALTH_VALUE - health, 9 };
			App->render->Blit(ui, 7, 17, false, &healthValue, NULL, true);
		}
		else {
			SDL_Rect healthValue = { 90, 107, HEALTH_VALUE - health, 9 };
			App->render->Blit(ui, 7, 17, false, &healthValue, NULL, true);
		}
	}
	return UPDATE_CONTINUE;
}




// TODO 4: Detect collision with a wall. If so, do something.
void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (!godMode && !blocking) {
		bool alredycollided = false;
		for (int i = 0; i < MAXNUMOFCOLLIDERS; i++)
		{
			if ((c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_NONE) && !alredycollided) {
				alredycollided = true;
				if (!this->playerFlip) {//normal pos (left)
					position.x -= 1;

				}
				else {//flipped position (right)
					position.x += 1;

				}
			}
		}
		if (c2->type == COLLIDER_ENEMY_SHOT) {
			Mix_PlayChannel(-1, App->audio->effects[2], 0);
			health += 30;
			inputs.Push(IN_FALL);
			if (App->player2->position.y < groundlevelaux) {
				inputs.Push(IN_FALL);
				airhit = true;

			}
		}
		if (c2->type == COLLIDER_ENEMY_ATTACK) {
			if (App->player2->position.y < groundlevelaux) {
				inputs.Push(IN_FALL);
				airhit = true;
			}
			Mix_PlayChannel(-1, App->audio->effects[2], 0);
			health += c2->damage;
			getsHit = true; doingAction = true;
			if (App->player2->kicking || App->player2->JumpKicking)
				Mix_PlayChannel(-1, App->audio->effects[17], 0);

			else
				Mix_PlayChannel(-1, App->audio->effects[16], 0);
		}
	}
}

void ModulePlayer::internal_input(p2Qeue<player_inputs>& inputs)
{

	if (jump_timer > 0)
	{
		if (SDL_GetTicks() / 1000 / 60 - jump_timer > JUMP_TIME)
		{
			inputs.Push(IN_JUMP_FINISH);
			jump_timer = 0;
		}
	}


	if (punch_timer > 0)
	{
		if (SDL_GetTicks() / 1000 / 60 - punch_timer > PUNCH_TIME)
		{
			inputs.Push(IN_PUNCH_FINISH);
			punch_timer = 0;
		}
	}

	if (punch_timer > 0)
	{
		if (SDL_GetTicks() / 1000 / 60 - punch_timer > PUNCH_TIME)
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
		case ST_IDLE2:
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
			case IN_FALL:state = ST_FALLING; break;//new
			case IN_DEATH: state = ST_FALLING; break;

			}
		}
		break;

		case ST_WALK_FORWARD2:
		{
			switch (last_input)
			{
			case IN_RIGHT_UP: state = ST_IDLE; blocking = false; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; blocking = false; break;
			case IN_JUMP: state = ST_JUMP_FORWARD; jump_timer = SDL_GetTicks(); blocking = false; break;
			case IN_X: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_KICK: state = ST_KICK_STANDING; punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; blocking = false; break;
			case IN_FALL:state = ST_FALLING;  blocking = false;  break;
			}
		}
		break;

		case ST_WALK_BACKWARD:
		{
			switch (last_input)
			{
			case IN_LEFT_UP: state = ST_IDLE; blocking = false;  break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; blocking = false;  break;
			case IN_JUMP: state = ST_JUMP_BACKWARD; jump_timer = SDL_GetTicks(); blocking = false; break;
			case IN_X: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_KICK: state = ST_KICK_STANDING; punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; blocking = false; break;
			case IN_FALL:state = ST_FALLING; blocking = false;  break;

			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_NEUTRAL_JUMP; punch_timer = SDL_GetTicks(); break;
			case IN_KICK: state = ST_KICK_NEUTRAL_JUMP; punch_timer = SDL_GetTicks();  break;
			case IN_FALL:state = ST_FALLING; break;

			}
		}
		break;

		case ST_JUMP_FORWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_FORWARD_JUMP; break;
			case IN_KICK: state = ST_KICK_FORWARD_JUMP; punch_timer = SDL_GetTicks();  break;
			case IN_FALL:state = ST_FALLING; break;

			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_BACKWARD_JUMP;  punch_timer = SDL_GetTicks(); break;
			case IN_KICK: state = ST_KICK_BACKWARD_JUMP; punch_timer = SDL_GetTicks();  break;
			case IN_FALL:state = ST_FALLING; break;

			}
		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_FALL:state = ST_FALLING; break;

			}
		}
		break;

		case ST_KICK_NEUTRAL_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_FALL:state = ST_FALLING; break;

			}
		}
		break;

		case ST_PUNCH_FORWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_FALL:state = ST_FALLING; break;

			}
		}
		break;

		case ST_KICK_FORWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			case IN_FALL:state = ST_FALLING; break;

			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			case IN_FALL:state = ST_FALLING; break;

			}
		}
		break;

		case ST_CROUCH:
		{
			switch (last_input)
			{
			case IN_CROUCH_UP: state = ST_IDLE; break;
			case IN_X: state = ST_PUNCH_CROUCH; break;
			case IN_KICK: state = ST_KICK_CROUCH; break;
			case IN_FALL:state = ST_FALLING; break;

			}
		}
		break;
		case ST_KICK_CROUCH:
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_CROUCH; break;
			case IN_FALL:state = ST_FALLING; break;

			}
			break;


		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_CROUCH; break;
			case IN_FALL:state = ST_FALLING; break;

			}
			break;
		}

		case ST_KICK_STANDING:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			case IN_FALL:state = ST_FALLING; break;

			}
		}
		case ST_SPECIAL:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
			case IN_FALL:state = ST_FALLING; break;

			}
		}
		break;

		case ST_FALLING:
		{//new
			switch (last_input)
			{
			case IN_FALL_FINISH: state = ST_IDLE; break;
			}

		}
		break;
		}
	}

	return state;
}
