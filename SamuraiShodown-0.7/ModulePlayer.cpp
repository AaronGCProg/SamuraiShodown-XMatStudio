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
#include <cstdlib>
#include <time.h>


ModulePlayer::ModulePlayer()
{
	//Attack types: 1->low punch/kick, 2->heavy punch/kick, 3->low/mid sword, 4->strong sword, 5->punch that knocks down, 6-> sword that knocks down, 7->special (both specials knock down).
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
	backward.PushBack({ 458,127,98,109 }, 9, { 43,1 }, backCollider, backHitbox, backCollType, backCallBack, 0, 0, 0, 0);
	backward.PushBack({ 277,137,91,99 }, 6, { 44,1 }, backCollider, backHitbox, backCollType, backCallBack, 0, 0, 0, 0);
	backward.PushBack({ 368,140,91,96 }, 9, { 49,1 }, backCollider, backHitbox, backCollType, backCallBack, 0, 0, 0, 0);
	backward.PushBack({ 277,137,91,99 }, 6, { 44,1 }, backCollider, backHitbox, backCollType, backCallBack, 0, 0, 0, 0);


	//backward.speed = 0.1f;


	const int forCollider = 2;//Collider num for the forward animation
	SDL_Rect forHitbox[forCollider] = { { 32, 0, 40, 75 },{ 33, 70, 20, 20 } };
	COLLIDER_TYPE forCollType[forCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* forCallBack[forCollider] = { {this},{this} };

	// walk forward animation 
	forward.PushBack({ 0,133,98,103 }, 8, { 49,1 }, forCollider, forHitbox, forCollType, forCallBack, 0, 0, 0, 0);
	forward.PushBack({ 187,128,88,108 }, 8, { 44,1 }, forCollider, forHitbox, forCollType, forCallBack, 0, 0, 0, 0);
	forward.PushBack({ 98,127,88,109 }, 8, { 44,1 }, forCollider, forHitbox, forCollType, forCallBack, 0, 0, 0, 0);
	forward.PushBack({ 187,128,88,108 }, 8, { 44,1 }, forCollider, forHitbox, forCollType, forCallBack, 0, 0, 0, 0);

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
	punch.PushBack({ 1,721,86,97 }, 3, { 31,2 }, punchCollider2, punchHitbox2, punchCollType2, punchCallBack2, 20, 9, 25, 3);
	punch.PushBack({ 88,729,130,89 }, 4, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack, 20, 9, 25, 3);
	punch.PushBack({ 219,729,150,90 }, 8, { 31,2 }, punchCollider, punchHitbox, punchCollType, punchCallBack, 20, 9, 25, 3);
	punch.PushBack({ 370,729,137,89 }, 6, { 31,2 }, punchCollider2, punchHitbox2, punchCollType2, punchCallBack2, 20, 9, 25, 3);
	punch.PushBack({ 508,729,96,89 }, 5, { 31,2 }, punchCollider2, punchHitbox2, punchCollType2, punchCallBack2, 20, 9, 25, 3);
	//punch.speed = 0.2f;


	const int jumpCollider = 2;//Collider num for the jump animation
	SDL_Rect jumpHitbox[jumpCollider] = { { 10, 10, 40, 65 },{ 20, 65, 20, 20 } };
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


	const int blockingCollider = 2;
	SDL_Rect blockingtHitbox[blockingCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE blockingCollType[blockingCollider] = { {COLLIDER_NONE},{COLLIDER_NONE} };
	Module* blockingCallBack[blockingCollider] = { {this},{this} };

	blockingIdle.PushBack({ 1500,28,74,99 }, 20, { 31,2 }, blockingCollider, blockingtHitbox, blockingCollType, blockingCallBack, 0, 0, 0, 0);



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
	SDL_Rect crouchHitbox2[crouchCollider] = { { 30, 0, 30, 55 },{40, 0, 20, 20 } };
	SDL_Rect crouchHitbox[crouchCollider] = { { 10, 0, 40, 55 },{ 30, 50, 20, 20 } };
	COLLIDER_TYPE crouchCollType[crouchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crouchCallBack[crouchCollider] = { {this},{this} };

	crouch.PushBack({ 949,31,77,86 }, 6, { 40, 4 }, crouchCollider, crouchHitbox2, crouchCollType, crouchCallBack, 0, 0, 0, 0);
	crouch.PushBack({ 1102,37,70,80 }, 2, { 30, 3 }, crouchCollider, crouchHitbox, crouchCollType, crouchCallBack, 0, 0, 0, 0);
	crouch.PushBack({ 1027,40,73,77 }, 2, { 30, 3 }, crouchCollider, crouchHitbox, crouchCollType, crouchCallBack, 0, 0, 0, 0);
	crouch.firstLoopFrame = 2;
	crouch.loop = true;


	crouchBlock.PushBack({ 1101,37,68,80 }, 20, { 40, 6 }, crouchCollider, crouchHitbox2, crouchCollType, crouchCallBack, 0, 0, 0, 0);



	//crouch punch animation 
	const int crouchPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox[crouchPunchCollider] = { { 30, 10, 40, 35 },{ 50, 35, 20, 20 },{ 75, 5, 50, 20 } };
	COLLIDER_TYPE crouchPunchCollType[crouchPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crouchPunchCallBack[crouchPunchCollider] = { {this},{this},{this} };

	const int crouchPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox2[crouchPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchPunchCollType2[crouchPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crouchPunchCallBack2[crouchPunchCollider2] = { {this},{this} };

	crouchPunch.PushBack({ 703,730,74,94 }, 3, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2, 20, 9, 25, 3);
	crouchPunch.PushBack({ 778,722,76,102 }, 3, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2, 20, 9, 25, 3);
	crouchPunch.PushBack({ 855,731,69,93 }, 3, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2, 20, 9, 25, 3);
	crouchPunch.PushBack({ 925,754,100,70 }, 2, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack, 20, 9, 25, 3);
	crouchPunch.PushBack({ 1026,754,110,70 }, 3, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack, 20, 9, 25, 3);
	crouchPunch.PushBack({ 1137,730,111,94 }, 2, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack, 20, 9, 25, 3);
	crouchPunch.PushBack({ 1249,730,70,94 }, 8, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack, 20, 9, 25, 3);
	crouchPunch.PushBack({ 1321,754,100,70 }, 4, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack, 20, 9, 25, 3);
	crouchPunch.PushBack({ 1422,731,69,93 }, 4, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack, 20, 9, 25, 3);


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
	fall.PushBack({ 1604,741,105,81 }, 25, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack, 0, 0, 0, 0);
	fall.PushBack({ 1530,742,71,83 }, 13, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack, 0, 0, 0, 0);
	fall.PushBack({ 1604,741,105,81 }, 13, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack, 0, 0, 0, 0);
	fall.PushBack({ 1712,783,123,42 }, 45, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack, 0, 0, 0, 0);

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

	//NEW ANIMATIONS


	const int midkickCollider = 3;//Collider num for the kick animation
	const int midkickCollider2 = 2;//Collider num for the kick animation
	SDL_Rect midkickHitbox[midkickCollider] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 },{ 60, 10, 35, 20 } };
	SDL_Rect midkickHitbox2[midkickCollider2] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 } };
	COLLIDER_TYPE midkickCollType[midkickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	COLLIDER_TYPE midkickCollType2[midkickCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* midkickCallBack[midkickCollider] = { {this},{this},{this} };
	Module* midkickCallBack2[midkickCollider2] = { {this},{this} };


	// Kick animation 
	midkick.PushBack({ 902,487,77,107 }, 10, { 31,2 }, midkickCollider2, midkickHitbox2, midkickCollType2, midkickCallBack2, 15, 6, 20, 1);
	midkick.PushBack({ 980,483,62,111 }, 8, { 31,2 }, midkickCollider, midkickHitbox, midkickCollType, midkickCallBack, 15, 6, 20, 1);
	midkick.PushBack({ 1155,478,82,116 }, 8, { 31,2 }, midkickCollider2, midkickHitbox2, midkickCollType2, midkickCallBack2, 15, 6, 20, 1);
	midkick.PushBack({ 980,483,62,111 }, 10, { 31,2 }, midkickCollider2, midkickHitbox, midkickCollType, midkickCallBack, 15, 6, 20, 1);
	//kick.speed = 0.12f;

	const int strongkickCollider = 3;//Collider num for the kick animation
	const int strongkickCollider2 = 2;//Collider num for the kick animation
	SDL_Rect strongkickHitbox[strongkickCollider] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 },{ 60, 10, 35, 20 } };
	SDL_Rect strongkickHitbox2[strongkickCollider2] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 } };
	COLLIDER_TYPE strongkickCollType[strongkickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	COLLIDER_TYPE strongkickCollType2[strongkickCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* strongkickCallBack[strongkickCollider] = { {this},{this},{this} };
	Module* strongkickCallBack2[strongkickCollider2] = { {this},{this} };


	// Kick animation 
	strongkick.PushBack({ 801,2157,67,93 }, 6, { 31,2 }, strongkickCollider2, strongkickHitbox2, strongkickCollType2, strongkickCallBack2, 15, 6, 20, 2);
	strongkick.PushBack({ 902,2141,90,109 }, 6, { 31,2 }, strongkickCollider, strongkickHitbox, strongkickCollType, strongkickCallBack, 15, 6, 20, 2);
	strongkick.PushBack({ 1022,2132,81,118 }, 6, { 31,2 }, strongkickCollider2, strongkickHitbox2, strongkickCollType2, strongkickCallBack2, 15, 6, 20, 2);
	strongkick.PushBack({ 1279,1250,116,93 }, 6, { 31,2 }, strongkickCollider, strongkickHitbox, strongkickCollType, strongkickCallBack, 15, 6, 20, 2);
	strongkick.PushBack({ 1571,2159,76,91 }, 6, { 31,2 }, strongkickCollider, strongkickHitbox, strongkickCollType, strongkickCallBack, 15, 6, 20, 2);
	// falta poner si alugna se repite y eso


	//kick.speed = 0.12f;

	const int midpunchCollider = 3;//Collider num for the punch animation
	const int midpunchCollider2 = 2;//Collider num for the punch animation
	SDL_Rect midpunchHitbox[midpunchCollider] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 },{ 40, 30, 80, 30 } };
	COLLIDER_TYPE midpunchCollType[midpunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* midpunchCallBack[midpunchCollider] = { {this},{this},{this} };

	SDL_Rect midpunchHitbox2[midpunchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE midpunchCollType2[midpunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER}, };
	Module* midpunchCallBack2[midpunchCollider2] = { {this},{this} };

	// Punch animation 
	midpunch.PushBack({ 1,930,82,117 }, 5, { 31,2 }, midpunchCollider2, midpunchHitbox2, midpunchCollType2, midpunchCallBack2, 20, 9, 25, 3);
	midpunch.PushBack({ 94,958,130,89 }, 5, { 31,2 }, midpunchCollider, midpunchHitbox, midpunchCollType, midpunchCallBack, 20, 9, 25, 3);
	midpunch.PushBack({ 225,958,161,90 }, 3, { 31,2 }, midpunchCollider, midpunchHitbox, midpunchCollType, midpunchCallBack, 20, 9, 25, 3);
	midpunch.PushBack({ 387,958,162,89 }, 7, { 31,2 }, midpunchCollider, midpunchHitbox, midpunchCollType, midpunchCallBack, 20, 9, 25, 3);
	midpunch.PushBack({ 550,958,163,89 }, 7, { 31,2 }, midpunchCollider, midpunchHitbox, midpunchCollType, midpunchCallBack, 20, 9, 25, 3);
	midpunch.PushBack({ 877,958,157,89 }, 5, { 31,2 }, midpunchCollider, midpunchHitbox, midpunchCollType, midpunchCallBack, 20, 9, 25, 3);


	const int strongpunchCollider = 3;//Collider num for the punch animation
	const int strongpunchCollider2 = 2;//Collider num for the punch animation
	SDL_Rect strongpunchHitbox[strongpunchCollider] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 },{ 40, 30, 80, 30 } };
	COLLIDER_TYPE strongpunchCollType[strongpunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* strongpunchCallBack[strongpunchCollider] = { {this},{this},{this} };

	SDL_Rect strongpunchHitbox2[strongpunchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE strongpunchCollType2[strongpunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER}, };
	Module* strongpunchCallBack2[strongpunchCollider2] = { {this},{this} };

	// Punch animation 
	strongpunch.PushBack({ 5,1674,75,112 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 161,1452,77,121 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 184,1669,92,117 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 676,1256,113,90 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 790,1248,63,98 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 1,1231,113,116 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 225,1236,113,110 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 339,1240,125,106 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 590,1240,85,106 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 1547,1240,78,106 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 676,1256,113,90 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 790,1248,63,98 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 854,1256,132,90 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 987,1245,152,101 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 1140,1245,153,101 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 1294,1245,147,101 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 790,1248,63,98 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);
	strongpunch.PushBack({ 1626,1234,74,112 }, 7, { 31,2 }, strongpunchCollider, strongpunchHitbox, strongpunchCollType, strongpunchCallBack, 20, 9, 25, 4);



	const int jumpmidPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpmidPunchHitbox[jumpmidPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 55, 27, 90, 10 } };
	COLLIDER_TYPE jumpmidPunchCollType[jumpmidPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpmidPunchCallBack[jumpmidPunchCollider] = { {this},{this},{this} };

	const int jumpmidPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpmidPunchHitbox2[jumpmidPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpmidPunchCollType2[jumpmidPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpmidPunchCallBack2[jumpmidPunchCollider2] = { {this},{this} };

	jumpmidPunch.PushBack({ 1,819,83,87 }, 12, { 31, 2 }, jumpmidPunchCollider2, jumpmidPunchHitbox2, jumpmidPunchCollType2, jumpmidPunchCallBack2, 15, 6, 20, 3);
	jumpmidPunch.PushBack({ 85,824,79,82 }, 12, { 31, 2 }, jumpmidPunchCollider, jumpmidPunchHitbox, jumpmidPunchCollType, jumpmidPunchCallBack, 15, 6, 20, 3);
	jumpmidPunch.PushBack({ 165,835,73,71 }, 10, { 31, 2 }, jumpmidPunchCollider, jumpmidPunchHitbox, jumpmidPunchCollType, jumpmidPunchCallBack, 15, 6, 20, 3);
	jumpmidPunch.PushBack({ 1,1160,155,70 }, 12, { 31, 2 }, jumpmidPunchCollider2, jumpmidPunchHitbox2, jumpmidPunchCollType2, jumpmidPunchCallBack2, 15, 6, 20, 3);
	jumpmidPunch.PushBack({ 396,837,157,69 }, 12, { 31, 2 }, jumpmidPunchCollider, jumpmidPunchHitbox, jumpmidPunchCollType, jumpmidPunchCallBack, 15, 6, 20, 3);
	jumpmidPunch.PushBack({ 554,842,147,64 }, 12, { 31, 2 }, jumpmidPunchCollider, jumpmidPunchHitbox, jumpmidPunchCollType, jumpmidPunchCallBack, 15, 6, 20, 3);

	const int jumpstrongPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpstrongPunchHitbox[jumpstrongPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 55, 27, 90, 10 } };
	COLLIDER_TYPE jumpstrongPunchCollType[jumpstrongPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpstrongPunchCallBack[jumpstrongPunchCollider] = { {this},{this},{this} };

	const int jumpstrongPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpstrongPunchHitbox2[jumpstrongPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpstrongPunchCollType2[jumpstrongPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpstrongPunchCallBack2[jumpstrongPunchCollider2] = { {this},{this} };

	jumpstrongPunch.PushBack({ 1,1577, 69,92 }, 12, { 31, 2 }, jumpstrongPunchCollider2, jumpstrongPunchHitbox2, jumpstrongPunchCollType2, jumpstrongPunchCallBack2, 15, 6, 20, 4);
	jumpstrongPunch.PushBack({ 70,1590,108,80 }, 12, { 31, 2 }, jumpstrongPunchCollider, jumpstrongPunchHitbox, jumpstrongPunchCollType, jumpstrongPunchCallBack, 15, 6, 20, 4);
	jumpstrongPunch.PushBack({ 179,1589,117,80 }, 12, { 31, 2 }, jumpstrongPunchCollider, jumpstrongPunchHitbox, jumpstrongPunchCollType, jumpstrongPunchCallBack, 15, 6, 20, 4);
	jumpstrongPunch.PushBack({ 298,1588,116,81 }, 12, { 31, 2 }, jumpstrongPunchCollider, jumpstrongPunchHitbox, jumpstrongPunchCollType, jumpstrongPunchCallBack, 15, 6, 20, 4);
	jumpstrongPunch.PushBack({ 415,1588,76,81 }, 12, { 31, 2 }, jumpstrongPunchCollider2, jumpstrongPunchHitbox2, jumpstrongPunchCollType2, jumpstrongPunchCallBack2, 15, 6, 20, 4);
	jumpstrongPunch.PushBack({ 492,1589,108,80 }, 40, { 31, 2 }, jumpstrongPunchCollider2, jumpstrongPunchHitbox2, jumpstrongPunchCollType2, jumpstrongPunchCallBack2, 15, 6, 20, 4);
	// falta poner si alugna se repite y eso

	const int jumpmidKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpmidKickHitbox[jumpmidKickCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 90, 10, 25, 20 } };
	COLLIDER_TYPE jumpmidKickCollType[jumpmidKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpmidKickCallBack[jumpmidKickCollider] = { {this},{this},{this} };

	const int jumpmidKickCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpmidKickHitbox2[jumpmidKickCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpmidKickCollType2[jumpmidKickCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpmidKickCallBack2[jumpmidKickCollider2] = { {this},{this} };

	jumpmidKick.PushBack({ 1102,21,71,80 }, 12, { 31,2 }, jumpmidKickCollider2, jumpmidKickHitbox2, jumpmidKickCollType2, jumpmidKickCallBack2, 15, 6, 20, 1);
	jumpmidKick.PushBack({ 1160,146,122,96 }, 60, { 31,2 }, jumpmidKickCollider, jumpmidKickHitbox, jumpmidKickCollType, jumpmidKickCallBack, 15, 6, 20, 1);
	jumpmidKick.PushBack({ 1102,21,71,80 }, 18, { 31,2 }, jumpmidKickCollider2, jumpmidKickHitbox2, jumpmidKickCollType2, jumpmidKickCallBack2, 15, 6, 20, 1);


	const int jumpstrongKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpstrongKickHitbox[jumpstrongKickCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 90, 10, 25, 20 } };
	COLLIDER_TYPE jumpstrongKickCollType[jumpstrongKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* jumpstrongKickCallBack[jumpstrongKickCollider] = { {this},{this},{this} };

	const int jumpstrongKickCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpstrongKickHitbox2[jumpstrongKickCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpstrongKickCollType2[jumpstrongKickCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpstrongKickCallBack2[jumpstrongKickCollider2] = { {this},{this} };

	jumpstrongKick.PushBack({ 1283,163, }, 12, { 31,2 }, jumpstrongKickCollider2, jumpstrongKickHitbox2, jumpstrongKickCollType2, jumpstrongKickCallBack2, 15, 6, 20, 2);
	jumpstrongKick.PushBack({ 1696,2288,88,100 }, 49, { 31,2 }, jumpstrongKickCollider, jumpstrongKickHitbox, jumpstrongKickCollType, jumpstrongKickCallBack, 15, 6, 20, 2);
	jumpstrongKick.PushBack({ 1838,2265,81,118 }, 16, { 31,2 }, jumpstrongKickCollider2, jumpstrongKickHitbox2, jumpstrongKickCollType2, jumpstrongKickCallBack2, 15, 6, 20, 2);
	jumpstrongKick.PushBack({ 1939,2305,116,80 }, 16, { 31,2 }, jumpstrongKickCollider2, jumpstrongKickHitbox2, jumpstrongKickCollType2, jumpstrongKickCallBack2, 15, 6, 20, 2);
	jumpstrongKick.PushBack({ 2081,2277,84,108 }, 16, { 31,2 }, jumpstrongKickCollider2, jumpstrongKickHitbox2, jumpstrongKickCollType2, jumpstrongKickCallBack2, 15, 6, 20, 2);
	// falta poner si alugna se repite y eso



	//crouch punch animation 
	const int crouchmidPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchmidPunchHitbox[crouchmidPunchCollider] = { { 30, 10, 40, 35 },{ 50, 35, 20, 20 },{ 75, 5, 50, 20 } };
	COLLIDER_TYPE crouchmidPunchCollType[crouchmidPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crouchmidPunchCallBack[crouchmidPunchCollider] = { {this},{this},{this} };

	const int crouchmidPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect crouchmidPunchHitbox2[crouchmidPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchmidPunchCollType2[crouchmidPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crouchmidPunchCallBack2[crouchmidPunchCollider2] = { {this},{this} };

	crouchmidPunch.PushBack({ 120,1059,95,100 }, 4, { 31, 2 }, crouchmidPunchCollider2, crouchmidPunchHitbox2, crouchmidPunchCollType2, crouchmidPunchCallBack2, 20, 9, 25, 3);
	crouchmidPunch.PushBack({ 250,1084,131,76 }, 4, { 31, 2 }, crouchmidPunchCollider2, crouchmidPunchHitbox2, crouchmidPunchCollType2, crouchmidPunchCallBack2, 20, 9, 25, 3);
	crouchmidPunch.PushBack({ 386,1087,162,73 }, 4, { 31, 2 }, crouchmidPunchCollider2, crouchmidPunchHitbox2, crouchmidPunchCollType2, crouchmidPunchCallBack2, 20, 9, 25, 3);
	crouchmidPunch.PushBack({ 777,1087,163,73 }, 3, { 31, 2 }, crouchmidPunchCollider, crouchmidPunchHitbox, crouchmidPunchCollType, crouchmidPunchCallBack, 20, 9, 25, 3);
	crouchmidPunch.PushBack({ 953,1087,164,73 }, 4, { 31, 2 }, crouchmidPunchCollider, crouchmidPunchHitbox, crouchmidPunchCollType, crouchmidPunchCallBack, 20, 9, 25, 3);
	crouchmidPunch.PushBack({ 250,1084,131,76 }, 3, { 31, 2 }, crouchmidPunchCollider, crouchmidPunchHitbox, crouchmidPunchCollType, crouchmidPunchCallBack, 20, 9, 25, 3);
	// falta poner si alugna se repite y eso


	const int crouchstrongPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchstrongPunchHitbox[crouchstrongPunchCollider] = { { 30, 10, 40, 35 },{ 50, 35, 20, 20 },{ 75, 5, 50, 20 } };
	COLLIDER_TYPE crouchstrongPunchCollType[crouchstrongPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crouchstrongPunchCallBack[crouchstrongPunchCollider] = { {this},{this},{this} };

	const int crouchstrongPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect crouchstrongPunchHitbox2[crouchstrongPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchstrongPunchCollType2[crouchstrongPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crouchstrongPunchCallBack2[crouchstrongPunchCollider2] = { {this},{this} };

	crouchstrongPunch.PushBack({ 703,730,74,94 }, 4, { 31, 2 }, crouchstrongPunchCollider2, crouchstrongPunchHitbox2, crouchstrongPunchCollType2, crouchstrongPunchCallBack2, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 778,722,76,102 }, 4, { 31, 2 }, crouchstrongPunchCollider2, crouchstrongPunchHitbox2, crouchstrongPunchCollType2, crouchstrongPunchCallBack2, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 855,731,69,93 }, 4, { 31, 2 }, crouchstrongPunchCollider2, crouchstrongPunchHitbox2, crouchstrongPunchCollType2, crouchstrongPunchCallBack2, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 925,754,100,70 }, 3, { 31, 2 }, crouchstrongPunchCollider, crouchstrongPunchHitbox, crouchstrongPunchCollType, crouchstrongPunchCallBack, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 1026,754,110,70 }, 4, { 31, 2 }, crouchstrongPunchCollider, crouchstrongPunchHitbox, crouchstrongPunchCollType, crouchstrongPunchCallBack, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 1137,730,111,94 }, 4, { 31, 2 }, crouchstrongPunchCollider, crouchstrongPunchHitbox, crouchstrongPunchCollType, crouchstrongPunchCallBack, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 1249,730,70,94 }, 10, { 31, 2 }, crouchstrongPunchCollider, crouchstrongPunchHitbox, crouchstrongPunchCollType, crouchstrongPunchCallBack, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 1321,754,100,70 }, 5, { 31, 2 }, crouchstrongPunchCollider, crouchstrongPunchHitbox, crouchstrongPunchCollType, crouchstrongPunchCallBack, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 1422,731,69,93 }, 5, { 31, 2 }, crouchstrongPunchCollider, crouchstrongPunchHitbox, crouchstrongPunchCollType, crouchstrongPunchCallBack, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 152,1538,69,93 }, 4, { 31, 2 }, crouchstrongPunchCollider, crouchstrongPunchHitbox, crouchstrongPunchCollType, crouchstrongPunchCallBack, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 854,1256,132,90 }, 4, { 31, 2 }, crouchstrongPunchCollider, crouchstrongPunchHitbox, crouchstrongPunchCollType, crouchstrongPunchCallBack, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 987,1245,152,101 }, 11, { 31, 2 }, crouchstrongPunchCollider, crouchstrongPunchHitbox, crouchstrongPunchCollType, crouchstrongPunchCallBack, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 1140,1245,153,101 }, 5, { 31, 2 }, crouchstrongPunchCollider, crouchstrongPunchHitbox, crouchstrongPunchCollType, crouchstrongPunchCallBack, 20, 9, 25, 4);
	crouchstrongPunch.PushBack({ 1295,1245,147,101 }, 6, { 31, 2 }, crouchstrongPunchCollider, crouchstrongPunchHitbox, crouchstrongPunchCollType, crouchstrongPunchCallBack, 20, 9, 25, 4);
	// falta poner si alugna se repite y eso


	const int crouchmidKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchmidKickHitbox[crouchmidPunchCollider] = { { 5, 10, 40, 35 },{ 20, 35, 20, 20 },{ 78,0,20,20 } };
	COLLIDER_TYPE crouchmidKickCollType[crouchmidKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crouchmidKickCallBack[crouchmidKickCollider] = { {this},{this},{this} };
	crouchmidKick.PushBack({ 1056,267,76,102 }, 4, { 31,2 }, crouchmidPunchCollider, crouchmidKickHitbox, crouchmidKickCollType, crouchmidKickCallBack, 15, 6, 20, 1);
	crouchmidKick.PushBack({ 1133,278,71,91 }, 8, { 31,2 }, crouchmidKickCollider, crouchmidKickHitbox, crouchmidPunchCollType, crouchmidKickCallBack, 15, 6, 20, 1);
	//crouchmidKick.PushBack({1205,278 ,71,91 }, 8, { 31,2 }, crouchmidKickCollider, crouchmidKickHitbox, crouchmidPunchCollType, crouchmidKickCallBack, 15, 6, 20, 1);
	crouchmidKick.PushBack({ 1277,272,97,97 }, 8, { 31,2 }, crouchmidKickCollider, crouchmidKickHitbox, crouchmidPunchCollType, crouchmidKickCallBack, 15, 6, 20, 1);
	crouchmidKick.PushBack({ 1375,284,85,85 }, 8, { 31,2 }, crouchmidKickCollider, crouchmidKickHitbox, crouchmidPunchCollType, crouchmidKickCallBack, 15, 6, 20, 1);
	crouchmidKick.PushBack({ 1461,293,95,76 }, 8, { 31,2 }, crouchmidKickCollider, crouchmidKickHitbox, crouchmidPunchCollType, crouchmidKickCallBack, 15, 6, 20, 1);
	crouchmidKick.PushBack({ 1557,293,62,76 }, 8, { 31,2 }, crouchmidKickCollider, crouchmidKickHitbox, crouchmidPunchCollType, crouchmidKickCallBack, 15, 6, 20, 1);


	const int crouchstrongKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchstrongKickHitbox[crouchstrongPunchCollider] = { { 5, 10, 40, 35 },{ 20, 35, 20, 20 },{ 78,0,20,20 } };
	COLLIDER_TYPE crouchstrongKickCollType[crouchstrongKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crouchstrongKickCallBack[crouchstrongKickCollider] = { {this},{this},{this} };
	crouchstrongKick.PushBack({ 1102,21,71,80 }, 4, { 31,2 }, crouchstrongPunchCollider, crouchstrongKickHitbox, crouchstrongKickCollType, crouchstrongKickCallBack, 15, 6, 20, 2);
	crouchstrongKick.PushBack({ 1262,31,122,86 }, 8, { 31,2 }, crouchstrongKickCollider, crouchstrongKickHitbox, crouchstrongPunchCollType, crouchstrongKickCallBack, 15, 6, 20, 2);
	crouchstrongKick.PushBack({ 1056,267,76,102 }, 4, { 31,2 }, crouchstrongPunchCollider, crouchstrongKickHitbox, crouchstrongKickCollType, crouchstrongKickCallBack, 15, 6, 20, 2);
	crouchstrongKick.PushBack({ 1277,272,97,97 }, 8, { 31,2 }, crouchstrongKickCollider, crouchstrongKickHitbox, crouchstrongPunchCollType, crouchstrongKickCallBack, 15, 6, 20, 2);
	crouchstrongKick.PushBack({ 1056,267,76,102 }, 4, { 31,2 }, crouchstrongPunchCollider, crouchstrongKickHitbox, crouchstrongKickCollType, crouchstrongKickCallBack, 15, 6, 20, 2);
	// falta poner si alugna se repite y eso

	const int shortPunchCollider = 3;//Collider num for the punch animation
	const int shortPunchCollider2 = 2;//Collider num for the punch animation
	SDL_Rect shortPunchHitbox[shortPunchCollider] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 },{ 40, 30, 80, 30 } };
	COLLIDER_TYPE shortPunchCollType[shortPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* shortPunchCallBack[shortPunchCollider] = { {this},{this},{this} };

	SDL_Rect shortPunchHitbox2[shortPunchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE shortPunchCollType2[shortPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER}, };
	Module* shortPunchCallBack2[shortPunchCollider2] = { {this},{this} };

	// Punch animation 
	shortPunch.PushBack({ 1417,4,82,123 }, 25, { 31,2 }, shortPunchCollider, shortPunchHitbox, shortPunchCollType, shortPunchCallBack, 20, 9, 25, 3);

	const int grabCollider = 3;//Collider num for the punch animation
	const int grabCollider2 = 2;//Collider num for the punch animation
	SDL_Rect grabHitbox[grabCollider] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE grabCollType[grabCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* grabCallBack[grabCollider] = { {this},{this} };

	COLLIDER_TYPE grabCollType2[grabCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER}, };
	Module* grabCallBack2[grabCollider2] = { {this},{this} };

	// Punch animation 
	grab.PushBack({ 137,2450,61,87 }, 35, { 31,2 }, grabCollider, grabHitbox, grabCollType, grabCallBack, 0, 9, 25, 3);
	grab.PushBack({ 254,2447,62,90 }, 19, { 31,2 }, grabCollider, grabHitbox, grabCollType, grabCallBack, 0, 9, 25, 3);
	grab.PushBack({ 400,2470,107,67 }, 15, { 31,2 }, grabCollider, grabHitbox, grabCollType, grabCallBack, 0, 9, 25, 3);
	grab.PushBack({ 702,2452,84,86 }, 15, { 31,2 }, grabCollider, grabHitbox, grabCollType, grabCallBack, 0, 9, 25, 3);


	const int getgrabCollider = 2;//Collider num for the hurt animation
	SDL_Rect  getgrabHitbox[getgrabCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE  getgrabCollType[getgrabCollider] = { {COLLIDER_GRAB},{COLLIDER_GRAB} };
	Module*  getgrabCallBack[getgrabCollider] = { {this},{this} };
	// grab animation
	getGrab.PushBack({ 1838,736,98,90 }, 35, { 31,2 }, getgrabCollider, getgrabHitbox, getgrabCollType, getgrabCallBack, 0, 0, 0, 0);
	getGrab.PushBack({ 1530,742,71,83 }, 21, { 31,2 }, getgrabCollider, getgrabHitbox, getgrabCollType, getgrabCallBack, 0, 0, 0, 0);

	// grab animation
	swordFight.PushBack({ 117,2707,82,108 }, 91, { 31,2 }, getgrabCollider, getgrabHitbox, getgrabCollType, getgrabCallBack, 0, 0, 0, 0);
	swordFight.PushBack({ 242,2713,96,104 }, 91, { 31,2 }, getgrabCollider, getgrabHitbox, getgrabCollType, getgrabCallBack, 0, 0, 0, 0);
	swordFight.PushBack({ 366,2705,68,110 }, 91, { 31,2 }, getgrabCollider, getgrabHitbox, getgrabCollType, getgrabCallBack, 0, 0, 0, 0);


	const int NWidleCollider = 2;//Collider num for the idle animation
	SDL_Rect NWidleHitbox[NWidleCollider] = { { 25, 0, 40, 75 },{ 40, 75, 20, 20 } };
	COLLIDER_TYPE NWidleCollType[NWidleCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWidleCallBack[NWidleCollider] = { {this},{this} };

	// idle animation (arcade sprite sheet)
	NWidle.PushBack({ 1,387,72,93 }, 8, { 49,1 }, NWidleCollider, NWidleHitbox, NWidleCollType, NWidleCallBack, 0, 0, 0, 0);
	NWidle.PushBack({ 74,385,69,95 }, 8, { 45,1 }, NWidleCollider, NWidleHitbox, NWidleCollType, NWidleCallBack, 0, 0, 0, 0);
	NWidle.PushBack({ 144,382,68,98 }, 8, { 45,1 }, NWidleCollider, NWidleHitbox, NWidleCollType, NWidleCallBack, 0, 0, 0, 0);
	NWidle.PushBack({ 74,385,69,95 }, 8, { 45,1 }, NWidleCollider, NWidleHitbox, NWidleCollType, NWidleCallBack, 0, 0, 0, 0);


	// idle animation (arcade sprite sheet)
	pickUpSword.PushBack({ 1965,1,67,97 }, 8, { 49,1 }, crouchCollider, crouchHitbox2, crouchCollType, crouchCallBack, 0, 0, 0, 0);
	pickUpSword.PushBack({ 2031,10,84,86 }, 8, { 45,1 }, crouchCollider, crouchHitbox2, crouchCollType, crouchCallBack, 0, 0, 0, 0);


	sideStep.PushBack({ 557,124,75,119 }, 8, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	sideStep.PushBack({ 631,124,75,119 }, 7, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	sideStep.PushBack({ 705,135,73,108 }, 18, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);
	sideStep.PushBack({ 778,169,73,73 }, 7, { 31,2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack, 0, 0, 0, 0);

	const int sprintCollider = 2;//Collider num for the forward animation
	SDL_Rect sprintHitbox[sprintCollider] = { { 32, 0, 40, 75 },{ 33, 70, 20, 20 } };
	COLLIDER_TYPE sprintCollType[sprintCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* sprintCallBack[sprintCollider] = { {this},{this} };

	// walk forward animation 
	sprint.PushBack({ 81,265,89,104 }, 8, { 34,1 }, sprintCollider, sprintHitbox, sprintCollType, sprintCallBack, 0, 0, 0, 0);
	sprint.PushBack({ 171,265,69,104 }, 8, { 34,1 }, sprintCollider, sprintHitbox, sprintCollType, sprintCallBack, 0, 0, 0, 0);
	sprint.PushBack({ 81,265,89,104 }, 8, { 34,1 }, sprintCollider, sprintHitbox, sprintCollType, sprintCallBack, 0, 0, 0, 0);
	sprint.PushBack({ 171,265,69,104 }, 8, { 34,1 }, sprintCollider, sprintHitbox, sprintCollType, sprintCallBack, 0, 0, 0, 0);

	sprintEnd.PushBack({ 241,248,77,121 }, 8, { 34,1 }, sprintCollider, sprintHitbox, sprintCollType, sprintCallBack, 0, 0, 0, 0);

	const int backsprintCollider = 2;//Collider num for the forward animation
	SDL_Rect backsprintHitbox[backsprintCollider] = { { 32, 0, 40, 75 },{ 33, 70, 20, 20 } };
	COLLIDER_TYPE backsprintCollType[backsprintCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* backsprintCallBack[backsprintCollider] = { {this},{this} };

	// walk forward animation 
	backsprint.PushBack({ 319,268,75,101 }, 8, { 29,1 }, backsprintCollider, backsprintHitbox, backsprintCollType, backsprintCallBack, 0, 0, 0, 0);
	backsprint.PushBack({ 395,263,91,106, }, 8, { 34,1 }, backsprintCollider, backsprintHitbox, backsprintCollType, backsprintCallBack, 0, 0, 0, 0);
	backsprint.PushBack({ 487,246,89,123 }, 8, { 34,1 }, backsprintCollider, backsprintHitbox, backsprintCollType, backsprintCallBack, 0, 0, 0, 0);
	backsprint.PushBack({ 577,249,90,120 }, 8, { 34,1 }, backsprintCollider, backsprintHitbox, backsprintCollType, backsprintCallBack, 0, 0, 0, 0);
	backsprint.PushBack({ 668,243,91,126 }, 8, { 34,1 }, backsprintCollider, backsprintHitbox, backsprintCollType, backsprintCallBack, 0, 0, 0, 0);
	backsprint.PushBack({ 760,248,95,121 }, 8, { 34,1 }, backsprintCollider, backsprintHitbox, backsprintCollType, backsprintCallBack, 0, 0, 0, 0);
	backsprint.PushBack({ 856,245,98,124 }, 8, { 34,1 }, backsprintCollider, backsprintHitbox, backsprintCollType, backsprintCallBack, 0, 0, 0, 0);
	backsprint.PushBack({ 955,250,100,119 }, 8, { 34,1 }, backsprintCollider, backsprintHitbox, backsprintCollType, backsprintCallBack, 0, 0, 0, 0);
	backsprint.PushBack({ 1968,3152,86,106 }, 8, { 34,1 }, backsprintCollider, backsprintHitbox, backsprintCollType, backsprintCallBack, 0, 0, 0, 0);



	const int NWcrouchCollider = 2;//Collider num for the jump kick animation
	SDL_Rect NWcrouchHitbox2[NWcrouchCollider] = { { 30, 0, 30, 55 },{40, 50, 20, 20 } };
	SDL_Rect NWcrouchHitbox[NWcrouchCollider] = { { 50, 0, 30, 55 },{ 60, 50, 20, 20 } };
	COLLIDER_TYPE NWcrouchCollType[NWcrouchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWcrouchCallBack[NWcrouchCollider] = { {this},{this} };

	NWcrouch.PushBack({ 1263,3158, 68,83 }, 6, { 40, 6 }, NWcrouchCollider, NWcrouchHitbox2, NWcrouchCollType, NWcrouchCallBack, 0, 0, 0, 0);
	NWcrouch.PushBack({ 1332,3166,66,75 }, 2, { 60, 8 }, NWcrouchCollider, NWcrouchHitbox, NWcrouchCollType, NWcrouchCallBack, 0, 0, 0, 0);
	NWcrouch.PushBack({ 415,3303,66,70 }, 2, { 60, 8 }, NWcrouchCollider, NWcrouchHitbox, NWcrouchCollType, NWcrouchCallBack, 0, 0, 0, 0);
	NWcrouch.firstLoopFrame = 2;
	NWcrouch.loop = true;

	const int NWjumpCollider = 2;//Collider num for the jump animation
	SDL_Rect NWjumpHitbox[NWjumpCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE NWjumpCollType[NWjumpCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWjumpCallBack[NWjumpCollider] = { {this},{this} };

	//jump animation s
	NWjump.PushBack({ 74,495,72,99 }, 5, { 31,2 }, NWjumpCollider, NWjumpHitbox, NWjumpCollType, NWjumpCallBack, 0, 0, 0, 0);
	NWjump.PushBack({ 147,506,70,88 }, 8, { 31,2 }, NWjumpCollider, NWjumpHitbox, NWjumpCollType, NWjumpCallBack, 0, 0, 0, 0);
	NWjump.PushBack({ 218,516,70,78 }, 13, { 31,2 }, NWjumpCollider, NWjumpHitbox, NWjumpCollType, NWjumpCallBack, 0, 0, 0, 0);
	NWjump.PushBack({ 147,506,70,88 }, 4, { 31,2 }, NWjumpCollider, NWjumpHitbox, NWjumpCollType, NWjumpCallBack, 0, 0, 0, 0);
	NWjump.PushBack({ 1399,3141,72,100 }, 17, { 31,2 }, NWjumpCollider, NWjumpHitbox, NWjumpCollType, NWjumpCallBack, 0, 0, 0, 0);
	NWjump.PushBack({ 433,511,68,83 }, 11, { 40, 6 }, NWjumpCollider, NWjumpHitbox, NWjumpCollType, NWjumpCallBack, 0, 0, 0, 0);


	const int NWpunchCollider = 3;//Collider num for the punch animation
	const int NWpunchCollider2 = 2;//Collider num for the punch animation
	SDL_Rect NWpunchHitbox[NWpunchCollider] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 },{ 40, 30, 80, 30 } };
	COLLIDER_TYPE NWpunchCollType[NWpunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* NWpunchCallBack[NWpunchCollider] = { {this},{this},{this} };

	SDL_Rect NWpunchHitbox2[NWpunchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE NWpunchCollType2[NWpunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER}, };
	Module* NWpunchCallBack2[NWpunchCollider2] = { {this},{this} };

	// Punch animation 
	NWpunch.PushBack({ 117,2862,73,97 }, 7, { 31,2 }, NWpunchCollider, NWpunchHitbox, NWpunchCollType, NWpunchCallBack, 20, 9, 25, 3);
	NWpunch.PushBack({ 226,2870,82,89 }, 7, { 31,2 }, NWpunchCollider, NWpunchHitbox, NWpunchCollType, NWpunchCallBack, 20, 9, 25, 3);
	NWpunch.PushBack({ 350,2870,91,89 }, 5, { 31,2 }, NWpunchCollider, NWpunchHitbox, NWpunchCollType, NWpunchCallBack, 20, 9, 25, 3);
	NWpunch.PushBack({ 477,2870,91,89 }, 6, { 31,2 }, NWpunchCollider, NWpunchHitbox, NWpunchCollType, NWpunchCallBack, 20, 9, 25, 3);

	const int NWstrongpunchCollider = 3;//Collider num for the punch animation
	const int NWstrongpunchCollider2 = 2;//Collider num for the punch animation
	SDL_Rect NWstrongpunchHitbox[NWstrongpunchCollider] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 },{ 40, 30, 80, 30 } };
	COLLIDER_TYPE NWstrongtrongpunchCollType[NWstrongpunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* NWstrongtrongpunchCallBack[NWstrongpunchCollider] = { {this},{this},{this} };

	SDL_Rect NWstrongpunchHitbox2[NWstrongpunchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE NWstrongpunchCollType2[NWstrongpunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER}, };
	Module* NWstrongpunchCallBack2[NWstrongpunchCollider2] = { {this},{this} };

	// Punch animation 
	NWstrongpunch.PushBack({ 2114,2854,72,100 }, 7, { 31,2 }, NWstrongpunchCollider, NWstrongpunchHitbox, NWstrongtrongpunchCollType, NWstrongtrongpunchCallBack, 20, 9, 25, 3);
	NWstrongpunch.PushBack({ 645,2867,92,92 }, 7, { 31,2 }, NWstrongpunchCollider, NWstrongpunchHitbox, NWstrongtrongpunchCollType, NWstrongtrongpunchCallBack, 20, 9, 25, 3);
	NWstrongpunch.PushBack({ 782,2862,66,96 }, 5, { 31,2 }, NWstrongpunchCollider, NWstrongpunchHitbox, NWstrongtrongpunchCollType, NWstrongtrongpunchCallBack, 20, 9, 25, 3);
	NWstrongpunch.PushBack({ 884,2870 ,89,89 }, 6, { 31,2 }, NWstrongpunchCollider, NWstrongpunchHitbox, NWstrongtrongpunchCollType, NWstrongtrongpunchCallBack, 20, 9, 25, 3);
	NWstrongpunch.PushBack({ 645,2867,92,92 }, 6, { 31,2 }, NWstrongpunchCollider, NWstrongpunchHitbox, NWstrongtrongpunchCollType, NWstrongtrongpunchCallBack, 20, 9, 25, 3);
	NWstrongpunch.PushBack({ 2114,2854,72,100 }, 6, { 31,2 }, NWstrongpunchCollider, NWstrongpunchHitbox, NWstrongtrongpunchCollType, NWstrongtrongpunchCallBack, 20, 9, 25, 3);


	const int NWkickCollider = 3;//Collider num for the kick animation
	const int NWkickCollider2 = 2;//Collider num for the kick animation
	SDL_Rect NWkickHitbox[NWkickCollider] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 },{ 60, 10, 35, 20 } };
	SDL_Rect NWkickHitbox2[NWkickCollider2] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 } };
	COLLIDER_TYPE NWkickCollType[NWkickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	COLLIDER_TYPE NWkickCollType2[NWkickCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWkickCallBack[NWkickCollider] = { {this},{this},{this} };
	Module* NWkickCallBack2[NWkickCollider2] = { {this},{this} };


	// Kick animation 
	NWkick.PushBack({ 101,3146,68,95 }, 6, { 31,2 }, NWkickCollider2, NWkickHitbox2, NWkickCollType2, NWkickCallBack2, 15, 6, 20, 1);
	NWkick.PushBack({ 214,3147,62,94 }, 6, { 31,2 }, NWkickCollider, NWkickHitbox, NWkickCollType, NWkickCallBack, 15, 6, 20, 1);
	NWkick.PushBack({ 345,3146,82,92 }, 6, { 31,2 }, NWkickCollider2, NWkickHitbox2, NWkickCollType2, NWkickCallBack2, 15, 6, 20, 1);
	NWkick.PushBack({ 214,3147,62,94 }, 6, { 31,2 }, NWkickCollider, NWkickHitbox, NWkickCollType, NWkickCallBack, 15, 6, 20, 1);

	const int NWstrongkickCollider = 3;//Collider num for the kick animation
	const int NWstrongkickCollider2 = 2;//Collider num for the kick animation
	SDL_Rect NWstrongkickHitbox[NWstrongkickCollider] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 },{ 60, 10, 35, 20 } };
	SDL_Rect NWstrongkickHitbox2[NWstrongkickCollider2] = { { 12, 0, 40, 75 },{ 23, 70, 20, 20 } };
	COLLIDER_TYPE NWstrongkickCollType[NWstrongkickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	COLLIDER_TYPE NWstrongkickCollType2[NWstrongkickCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWstrongkickCallBack[NWstrongkickCollider] = { {this},{this},{this} };
	Module* NWstrongkickCallBack2[NWstrongkickCollider2] = { {this},{this} };


	// Kick animation 
	NWstrongkick.PushBack({ 662,3145,67,93 }, 6, { 31,2 }, NWstrongkickCollider2, NWstrongkickHitbox2, NWstrongkickCollType2, NWstrongkickCallBack2, 15, 6, 20, 1);
	NWstrongkick.PushBack({ 741,3138,94,100 }, 6, { 31,2 }, NWstrongkickCollider, NWstrongkickHitbox, NWstrongkickCollType, NWstrongkickCallBack, 15, 6, 20, 1);
	NWstrongkick.PushBack({ 885,3149,79,92 }, 6, { 31,2 }, NWstrongkickCollider2, NWstrongkickHitbox2, NWstrongkickCollType2, NWstrongkickCallBack2, 15, 6, 20, 1);
	NWstrongkick.PushBack({ 1003,3161,102,77 }, 6, { 31,2 }, NWstrongkickCollider, NWstrongkickHitbox, NWstrongkickCollType, NWstrongkickCallBack, 15, 6, 20, 1);
	NWstrongkick.PushBack({ 1133,3153,75,85 }, 6, { 31,2 }, NWstrongkickCollider, NWstrongkickHitbox, NWstrongkickCollType, NWstrongkickCallBack, 15, 6, 20, 1);
	NWstrongkick.PushBack({ 1263,3158,68,83 }, 6, { 31,2 }, NWstrongkickCollider, NWstrongkickHitbox, NWstrongkickCollType, NWstrongkickCallBack, 15, 6, 20, 1);

	const int NWcrouchPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect NWcrouchPunchHitbox[NWcrouchPunchCollider] = { { 30, 10, 40, 35 },{ 50, 35, 20, 20 },{ 75, 5, 50, 20 } };
	COLLIDER_TYPE NWcrouchPunchCollType[NWcrouchPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* NWcrouchPunchCallBack[NWcrouchPunchCollider] = { {this},{this},{this} };

	const int NWcrouchPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect NWcrouchPunchHitbox2[NWcrouchPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE NWcrouchPunchCollType2[NWcrouchPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWcrouchPunchCallBack2[NWcrouchPunchCollider2] = { {this},{this} };

	NWcrouchPunch.PushBack({ 106,3028,63,70 }, 2, { 31, 2 }, NWcrouchPunchCollider2, NWcrouchPunchHitbox2, NWcrouchPunchCollType2, NWcrouchPunchCallBack2, 20, 9, 25, 3);
	NWcrouchPunch.PushBack({ 188,3028,68,70 }, 2, { 31, 2 }, NWcrouchPunchCollider2, NWcrouchPunchHitbox2, NWcrouchPunchCollType2, NWcrouchPunchCallBack2, 20, 9, 25, 3);
	NWcrouchPunch.PushBack({ 283,3026,64,69 }, 2, { 31, 2 }, NWcrouchPunchCollider2, NWcrouchPunchHitbox2, NWcrouchPunchCollType2, NWcrouchPunchCallBack2, 20, 9, 25, 3);
	NWcrouchPunch.PushBack({ 374,3031,101,67 }, 1, { 31, 2 }, NWcrouchPunchCollider, NWcrouchPunchHitbox, NWcrouchPunchCollType, NWcrouchPunchCallBack, 20, 9, 25, 3);
	NWcrouchPunch.PushBack({ 283,3026,64,69 }, 2, { 31, 2 }, NWcrouchPunchCollider, NWcrouchPunchHitbox, NWcrouchPunchCollType, NWcrouchPunchCallBack, 20, 9, 25, 3);


	const int NWstrongcrouchPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect NWstrongcrouchPunchHitbox[NWstrongcrouchPunchCollider] = { { 30, 10, 40, 35 },{ 50, 35, 20, 20 },{ 75, 5, 50, 20 } };
	COLLIDER_TYPE NWstrongcrouchPunchCollType[NWstrongcrouchPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* NWstrongcrouchPunchCallBack[NWstrongcrouchPunchCollider] = { {this},{this},{this} };

	const int NWstrongcrouchPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect NWstrongcrouchPunchHitbox2[NWstrongcrouchPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE NWstrongcrouchPunchCollType2[NWstrongcrouchPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWstrongcrouchPunchCallBack2[NWstrongcrouchPunchCollider2] = { {this},{this} };

	NWstrongcrouchPunch.PushBack({ 568,3024,73,73 }, 2, { 31, 2 }, NWstrongcrouchPunchCollider2, NWstrongcrouchPunchHitbox2, NWstrongcrouchPunchCollType2, NWstrongcrouchPunchCallBack2, 20, 9, 25, 3);
	NWstrongcrouchPunch.PushBack({ 666,3029,94,68 }, 2, { 31, 2 }, NWstrongcrouchPunchCollider2, NWstrongcrouchPunchHitbox2, NWstrongcrouchPunchCollType2, NWstrongcrouchPunchCallBack2, 20, 9, 25, 3);
	NWstrongcrouchPunch.PushBack({ 796,3021,72,73 }, 2, { 31, 2 }, NWstrongcrouchPunchCollider2, NWstrongcrouchPunchHitbox2, NWstrongcrouchPunchCollType2, NWstrongcrouchPunchCallBack2, 20, 9, 25, 3);
	NWstrongcrouchPunch.PushBack({ 916,3029,106,64 }, 1, { 31, 2 }, NWstrongcrouchPunchCollider, NWstrongcrouchPunchHitbox, NWstrongcrouchPunchCollType, NWstrongcrouchPunchCallBack, 20, 9, 25, 3);
	NWstrongcrouchPunch.PushBack({ 666,3029,94,68 }, 2, { 31, 2 }, NWstrongcrouchPunchCollider, NWstrongcrouchPunchHitbox, NWstrongcrouchPunchCollType, NWstrongcrouchPunchCallBack, 20, 9, 25, 3);

	const int NWcrouchKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect NWcrouchKickHitbox[NWcrouchKickCollider] = { { 5, 10, 40, 35 },{ 20, 35, 20, 20 },{ 78,0,20,20 } };
	COLLIDER_TYPE NWcrouchKickCollType[NWcrouchKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* NWcrouchKickCallBack[NWcrouchKickCollider] = { {this},{this},{this} };
	NWcrouchKick.PushBack({ 96,3303,85,70 }, 4, { 31,2 }, NWcrouchKickCollider, NWcrouchKickHitbox, NWcrouchKickCollType, NWcrouchKickCallBack, 15, 6, 20, 1);
	NWcrouchKick.PushBack({ 218,3303,108,70 }, 8, { 31,2 }, NWcrouchKickCollider, NWcrouchKickHitbox, NWcrouchKickCollType, NWcrouchKickCallBack, 15, 6, 20, 1);

	const int NWcrouchmidKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect NWcrouchmidKickHitbox[NWcrouchmidKickCollider] = { { 5, 10, 40, 35 },{ 20, 35, 20, 20 },{ 78,0,20,20 } };
	COLLIDER_TYPE NWcrouchmidKickCollType[NWcrouchmidKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* NWcrouchmidKickCallBack[NWcrouchmidKickCollider] = { {this},{this},{this} };
	NWcrouchmidKick.PushBack({ 531,3296,74,74 }, 4, { 31,2 }, NWcrouchmidKickCollider, NWcrouchmidKickHitbox, NWcrouchmidKickCollType, NWcrouchmidKickCallBack, 15, 6, 20, 1);
	NWcrouchmidKick.PushBack({ 641,3301,71,74 }, 8, { 31,2 }, NWcrouchmidKickCollider, NWcrouchmidKickHitbox, NWcrouchmidKickCollType, NWcrouchmidKickCallBack, 15, 6, 20, 1);
	NWcrouchmidKick.PushBack({ 767,3299,97,74 }, 8, { 31,2 }, NWcrouchmidKickCollider, NWcrouchmidKickHitbox, NWcrouchmidKickCollType, NWcrouchmidKickCallBack, 15, 6, 20, 1);
	NWcrouchmidKick.PushBack({ 910,3298,85,72 }, 8, { 31,2 }, NWcrouchmidKickCollider, NWcrouchmidKickHitbox, NWcrouchmidKickCollType, NWcrouchmidKickCallBack, 15, 6, 20, 1);
	NWcrouchmidKick.PushBack({ 1050,3300,89,72 }, 8, { 31,2 }, NWcrouchmidKickCollider, NWcrouchmidKickHitbox, NWcrouchmidKickCollType, NWcrouchmidKickCallBack, 15, 6, 20, 1);
	NWcrouchmidKick.PushBack({ 1180,3298,56,76 }, 8, { 31,2 }, NWcrouchmidKickCollider, NWcrouchmidKickHitbox, NWcrouchmidKickCollType, NWcrouchmidKickCallBack, 15, 6, 20, 1);

	const int NWcrouchstrongKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect NWcrouchstrongKickHitbox[NWcrouchstrongKickCollider] = { { 5, 10, 40, 35 },{ 20, 35, 20, 20 },{ 78,0,20,20 } };
	COLLIDER_TYPE NWcrouchstrongKickCollType[NWcrouchstrongKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* NWcrouchstrongKickCallBack[NWcrouchstrongKickCollider] = { {this},{this},{this} };
	NWcrouchstrongKick.PushBack({ 96,3303,85,70 }, 4, { 31,2 }, NWcrouchstrongKickCollider, NWcrouchstrongKickHitbox, NWcrouchstrongKickCollType, NWcrouchstrongKickCallBack, 15, 6, 20, 1);
	NWcrouchstrongKick.PushBack({ 218,3303,108,70 }, 8, { 31,2 }, NWcrouchstrongKickCollider, NWcrouchstrongKickHitbox, NWcrouchstrongKickCollType, NWcrouchstrongKickCallBack, 15, 6, 20, 1);
	NWcrouchstrongKick.PushBack({ 531,3296,74,74 }, 4, { 31,2 }, NWcrouchstrongKickCollider, NWcrouchstrongKickHitbox, NWcrouchstrongKickCollType, NWcrouchstrongKickCallBack, 15, 6, 20, 1);
	NWcrouchstrongKick.PushBack({ 641,3301,71,74 }, 8, { 31,2 }, NWcrouchstrongKickCollider, NWcrouchstrongKickHitbox, NWcrouchstrongKickCollType, NWcrouchstrongKickCallBack, 15, 6, 20, 1);
	NWcrouchstrongKick.PushBack({ 767,3299,97,74 }, 4, { 31,2 }, NWcrouchstrongKickCollider, NWcrouchstrongKickHitbox, NWcrouchstrongKickCollType, NWcrouchstrongKickCallBack, 15, 6, 20, 1);
	NWcrouchstrongKick.PushBack({ 910,3298,85,72 }, 8, { 31,2 }, NWcrouchstrongKickCollider, NWcrouchstrongKickHitbox, NWcrouchstrongKickCollType, NWcrouchstrongKickCallBack, 15, 6, 20, 1);
	NWcrouchstrongKick.PushBack({ 1050,3300,89,72 }, 4, { 31,2 }, NWcrouchstrongKickCollider, NWcrouchstrongKickHitbox, NWcrouchstrongKickCollType, NWcrouchstrongKickCallBack, 15, 6, 20, 1);
	NWcrouchstrongKick.PushBack({ 1180,3298,56,76 }, 8, { 31,2 }, NWcrouchstrongKickCollider, NWcrouchstrongKickHitbox, NWcrouchstrongKickCollType, NWcrouchstrongKickCallBack, 15, 6, 20, 1);

	const int NWjumpPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect NWjumpPunchHitbox[NWjumpPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 55, 27, 90, 10 } };
	COLLIDER_TYPE NWjumpPunchCollType[NWjumpPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* NWjumpPunchCallBack[NWjumpPunchCollider] = { {this},{this},{this} };

	const int NWjumpPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect NWjumpPunchHitbox2[jumpPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE NWjumpPunchCollType2[NWjumpPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWjumpPunchCallBack2[NWjumpPunchCollider2] = { {this},{this} };

	NWjumpPunch.PushBack({ 1472,3163,63,78 }, 4, { 31, 2 }, NWjumpPunchCollider2, NWjumpPunchHitbox2, NWjumpPunchCollType2, NWjumpPunchCallBack2, 15, 6, 20, 1);
	NWjumpPunch.PushBack({ 1536,3163,73,78 }, 4, { 31, 2 }, NWjumpPunchCollider, NWjumpPunchHitbox, NWjumpPunchCollType, NWjumpPunchCallBack, 15, 6, 20, 1);
	NWjumpPunch.PushBack({ 1610,3165,67,76 }, 3, { 31, 2 }, NWjumpPunchCollider, NWjumpPunchHitbox, NWjumpPunchCollType, NWjumpPunchCallBack, 15, 6, 20, 1);
	NWjumpPunch.PushBack({ 1678,3168,109,73 }, 3, { 31, 2 }, NWjumpPunchCollider, NWjumpPunchHitbox, NWjumpPunchCollType, NWjumpPunchCallBack, 15, 6, 20, 1);
	NWjumpPunch.PushBack({ 1610,3165,67,76 }, 3, { 31, 2 }, NWjumpPunchCollider2, NWjumpPunchHitbox2, NWjumpPunchCollType2, NWjumpPunchCallBack2, 15, 6, 20, 1);

	const int NWjumpstrongPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect NWjumpstrongPunchHitbox[NWjumpstrongPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 55, 27, 90, 10 } };
	COLLIDER_TYPE NWjumpstrongPunchCollType[NWjumpstrongPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* NWjumpstrongPunchCallBack[NWjumpstrongPunchCollider] = { {this},{this},{this} };

	const int NWjumpstrongPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect NWjumpstrongPunchHitbox2[jumpstrongPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE NWjumpstrongPunchCollType2[NWjumpstrongPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWjumpstrongPunchCallBack2[NWjumpstrongPunchCollider2] = { {this},{this} };

	NWjumpstrongPunch.PushBack({ 1425,2877,73,71 }, 4, { 31, 2 }, NWjumpstrongPunchCollider2, NWjumpstrongPunchHitbox2, NWjumpstrongPunchCollType2, NWjumpstrongPunchCallBack2, 15, 6, 20, 1);
	NWjumpstrongPunch.PushBack({ 1534,2848,94,66 }, 4, { 31, 2 }, NWjumpstrongPunchCollider, NWjumpstrongPunchHitbox, NWjumpstrongPunchCollType, NWjumpstrongPunchCallBack, 15, 6, 20, 1);
	NWjumpstrongPunch.PushBack({ 1676,2815,72,70 }, 3, { 31, 2 }, NWjumpstrongPunchCollider, NWjumpstrongPunchHitbox, NWjumpstrongPunchCollType, NWjumpstrongPunchCallBack, 15, 6, 20, 1);
	NWjumpstrongPunch.PushBack({ 1799,2850,110,73 }, 3, { 31, 2 }, NWjumpstrongPunchCollider, NWjumpstrongPunchHitbox, NWjumpstrongPunchCollType, NWjumpstrongPunchCallBack, 15, 6, 20, 1);
	NWjumpstrongPunch.PushBack({ 1936,2889,70,69 }, 3, { 31, 2 }, NWjumpstrongPunchCollider2, NWjumpstrongPunchHitbox2, NWjumpstrongPunchCollType2, NWjumpstrongPunchCallBack2, 15, 6, 20, 1);
	NWjumpstrongPunch.PushBack({ 1515,3013,70,78 }, 3, { 31, 2 }, NWjumpstrongPunchCollider2, NWjumpstrongPunchHitbox2, NWjumpstrongPunchCollType2, NWjumpstrongPunchCallBack2, 15, 6, 20, 1);


	const int NWjumpKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect NWjumpKickHitbox[NWjumpKickCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 90, 10, 25, 20 } };
	COLLIDER_TYPE NWjumpKickCollType[NWjumpKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* NWjumpKickCallBack[NWjumpKickCollider] = { {this},{this},{this} };

	const int NWjumpKickCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect NWjumpKickHitbox2[NWjumpKickCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE NWjumpKickCollType2[NWjumpKickCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWjumpKickCallBack2[NWjumpKickCollider2] = { {this},{this} };

	NWjumpKick.PushBack({ 1213,3027,85,70 }, 6, { 31,2 }, NWjumpKickCollider2, NWjumpKickHitbox2, NWjumpKickCollType2, NWjumpKickCallBack2, 15, 6, 20, 1);
	NWjumpKick.PushBack({ 218,3303,108,70 }, 32, { 31,2 }, NWjumpKickCollider, NWjumpKickHitbox, NWjumpKickCollType, NWjumpKickCallBack, 15, 6, 20, 1);

	const int NWjumpstrongKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect NWjumpstrongKickHitbox[NWjumpstrongKickCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 90, 10, 25, 20 } };
	COLLIDER_TYPE NWjumpstrongKickCollType[NWjumpstrongKickCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* NWjumpstrongKickCallBack[NWjumpstrongKickCollider] = { {this},{this},{this} };

	const int NWjumpstrongKickCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect NWjumpstrongKickHitbox2[NWjumpstrongKickCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE NWjumpstrongKickCollType2[NWjumpstrongKickCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWjumpstrongKickCallBack2[NWjumpstrongKickCollider2] = { {this},{this} };

	NWjumpstrongKick.PushBack({ 1787,3165,73,75 }, 6, { 31,2 }, NWjumpstrongKickCollider2, NWjumpstrongKickHitbox2, NWjumpstrongKickCollType2, NWjumpstrongKickCallBack2, 15, 6, 20, 1);
	NWjumpstrongKick.PushBack({ 1866,3158,88,91 }, 32, { 31,2 }, NWjumpstrongKickCollider, NWjumpstrongKickHitbox, NWjumpstrongKickCollType, NWjumpstrongKickCallBack, 15, 6, 20, 1);
	NWjumpstrongKick.PushBack({ 885,3149,79,92 }, 6, { 31,2 }, NWjumpstrongKickCollider2, NWjumpstrongKickHitbox2, NWjumpstrongKickCollType2, NWjumpstrongKickCallBack2, 15, 6, 20, 1);
	NWjumpstrongKick.PushBack({ 1003,3161,102,77 }, 32, { 31,2 }, NWjumpstrongKickCollider, NWjumpstrongKickHitbox, NWjumpstrongKickCollType, NWjumpstrongKickCallBack, 15, 6, 20, 1);

	const int NWsprintCollider = 2;//Collider num for the forward animation
	SDL_Rect NWsprintHitbox[NWsprintCollider] = { { 32, 0, 40, 75 },{ 33, 70, 20, 20 } };
	COLLIDER_TYPE NWsprintCollType[NWsprintCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWsprintCallBack[NWsprintCollider] = { {this},{this} };

	// walk forward animation 
	NWsprint.PushBack({ 574,504,89,90 }, 8, { 34,1 }, NWsprintCollider, NWsprintHitbox, NWsprintCollType, NWsprintCallBack, 0, 0, 0, 0);
	NWsprint.PushBack({ 664,505,63,89 }, 8, { 34,1 }, NWsprintCollider, NWsprintHitbox, NWsprintCollType, NWsprintCallBack, 0, 0, 0, 0);
	NWsprint.PushBack({ 574,504,89,90 }, 8, { 34,1 }, NWsprintCollider, NWsprintHitbox, NWsprintCollType, NWsprintCallBack, 0, 0, 0, 0);

	NWsprintEnd.PushBack({ 818,501,77,93 }, 8, { 34,1 }, NWsprintCollider, NWsprintHitbox, NWsprintCollType, NWsprintCallBack, 0, 0, 0, 0);


	const int NWbacksprintCollider = 2;//Collider num for the forward animation
	SDL_Rect NWbacksprintHitbox[NWbacksprintCollider] = { { 32, 0, 40, 75 },{ 33, 70, 20, 20 } };
	COLLIDER_TYPE NWbacksprintCollType[NWbacksprintCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWbacksprintCallBack[NWbacksprintCollider] = { {this},{this} };

	// walk forward animation 
	NWbacksprint.PushBack({ 2057,3157,75,101 }, 8, { 29,1 }, NWbacksprintCollider, NWbacksprintHitbox, NWbacksprintCollType, NWbacksprintCallBack, 0, 0, 0, 0);
	NWbacksprint.PushBack({ 73,601,89,105 }, 8, { 34,1 }, NWbacksprintCollider, NWbacksprintHitbox, NWbacksprintCollType, NWbacksprintCallBack, 0, 0, 0, 0);
	NWbacksprint.PushBack({ 163,603,90,103 }, 8, { 34,1 }, NWbacksprintCollider, NWbacksprintHitbox, NWbacksprintCollType, NWbacksprintCallBack, 0, 0, 0, 0);
	NWbacksprint.PushBack({ 254,604,90,102 }, 8, { 34,1 }, NWbacksprintCollider, NWbacksprintHitbox, NWbacksprintCollType, NWbacksprintCallBack, 0, 0, 0, 0);
	NWbacksprint.PushBack({ 345,605,91,101 }, 8, { 34,1 }, NWbacksprintCollider, NWbacksprintHitbox, NWbacksprintCollType, NWbacksprintCallBack, 0, 0, 0, 0);
	NWbacksprint.PushBack({ 437,603,97,103 }, 8, { 34,1 }, NWbacksprintCollider, NWbacksprintHitbox, NWbacksprintCollType, NWbacksprintCallBack, 0, 0, 0, 0);
	NWbacksprint.PushBack({ 535,598,81,108 }, 8, { 34,1 }, NWbacksprintCollider, NWbacksprintHitbox, NWbacksprintCollType, NWbacksprintCallBack, 0, 0, 0, 0);
	NWbacksprint.PushBack({ 617,604,76,102 }, 8, { 34,1 }, NWbacksprintCollider, NWbacksprintHitbox, NWbacksprintCollType, NWbacksprintCallBack, 0, 0, 0, 0);
	NWbacksprint.PushBack({ 2057,3157,75,101 }, 8, { 34,1 }, NWbacksprintCollider, NWbacksprintHitbox, NWbacksprintCollType, NWbacksprintCallBack, 0, 0, 0, 0);

	const int NWblockingCollider = 2;
	SDL_Rect NWblockingtHitbox[NWblockingCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE NWblockingCollType[NWblockingCollider] = { {COLLIDER_NONE},{COLLIDER_NONE} };
	Module* NWblockingCallBack[NWblockingCollider] = { {this},{this} };

	NWblockingIdle.PushBack({ 503,503,70,91 }, 20, { 31,2 }, NWblockingCollider, NWblockingtHitbox, NWblockingCollType, NWblockingCallBack, 0, 0, 0, 0);
	NwcrouchBlock.PushBack({ 2133,3187,66,71 }, 2, { 60,8 }, NWcrouchCollider, NWcrouchHitbox2, NWcrouchCollType, NWcrouchCallBack, 0, 0, 0, 0);

	const int NWbackCollider = 2;//Collider num for the backward animation
	SDL_Rect NWbackHitbox[NWbackCollider] = { { 25, 0, 40, 75 },{ 40, 75, 20, 20 } };
	COLLIDER_TYPE NWbackCollType[NWbackCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWbackCallBack[NWbackCollider] = { {this},{this} };

	// walk backward animation 
	NWbackward.PushBack({ 705,382, 68,98 }, 9, { 23,1 }, NWbackCollider, NWbackHitbox, NWbackCollType, NWbackCallBack, 0, 0, 0, 0);
	NWbackward.PushBack({ 615,380,64,97 }, 6, { 24,1 }, NWbackCollider, NWbackHitbox, NWbackCollType, NWbackCallBack, 0, 0, 0, 0);
	NWbackward.PushBack({ 955,382,72,95 }, 9, { 29,1 }, NWbackCollider, NWbackHitbox, NWbackCollType, NWbackCallBack, 0, 0, 0, 0);
	NWbackward.PushBack({ 705,382, 68,98 }, 6, { 24,1 }, NWbackCollider, NWbackHitbox, NWbackCollType, NWbackCallBack, 0, 0, 0, 0);

	const int NWforCollider = 2;//Collider num for the forward animation
	SDL_Rect NWforHitbox[NWforCollider] = { { 32, 0, 40, 75 },{ 33, 70, 20, 20 } };
	COLLIDER_TYPE NWforCollType[NWforCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* NWforCallBack[NWforCollider] = { {this},{this} };

	// walk forward animation 
	NWforward.PushBack({ 816,379,68,98 }, 8, { 29,1 }, NWforCollider, NWforHitbox, NWforCollType, NWforCallBack, 0, 0, 0, 0);
	NWforward.PushBack({ 885,380,69,97 }, 8, { 34,1 }, NWforCollider, NWforHitbox, NWforCollType, NWforCallBack, 0, 0, 0, 0);
	NWforward.PushBack({ 955,382,72,95 }, 8, { 34,1 }, NWforCollider, NWforHitbox, NWforCollType, NWforCallBack, 0, 0, 0, 0);
	NWforward.PushBack({ 816,379,68,98 }, 8, { 34,1 }, NWforCollider, NWforHitbox, NWforCollType, NWforCallBack, 0, 0, 0, 0);

	const int NWgrabCollider = 3;//Collider num for the punch animation
	const int NWgrabCollider2 = 2;//Collider num for the punch animation
	SDL_Rect NWgrabHitbox[NWgrabCollider] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 },{ 40, 30, 80, 30 } };
	COLLIDER_TYPE NWgrabCollType[NWgrabCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* NWgrabCallBack[NWgrabCollider] = { {this},{this},{this} };

	COLLIDER_TYPE NWgrabCollType2[NWgrabCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER}, };
	Module* NWgrabCallBack2[NWgrabCollider2] = { {this},{this} };

	// Punch animation 
	NWgrab.PushBack({ 137,2450,61,87 }, 7, { 31,2 }, NWgrabCollider, NWgrabHitbox, NWgrabCollType, NWgrabCallBack, 20, 9, 25, 3);
	NWgrab.PushBack({ 254,2447,62,90 }, 7, { 31,2 }, NWgrabCollider, NWgrabHitbox, NWgrabCollType, NWgrabCallBack, 20, 9, 25, 3);
	NWgrab.PushBack({ 374,3031,101,67 }, 7, { 31,2 }, NWgrabCollider, NWgrabHitbox, NWgrabCollType, NWgrabCallBack, 20, 9, 25, 3);

	const int midgrabCollider = 3;//Collider num for the punch animation
	const int midgrabCollider2 = 2;//Collider num for the punch animation
	SDL_Rect midgrabHitbox[midgrabCollider] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 },{ 40, 30, 80, 30 } };
	COLLIDER_TYPE midgrabCollType[midgrabCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* midgrabCallBack[midgrabCollider] = { {this},{this},{this} };

	COLLIDER_TYPE midgrabCollType2[midgrabCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER}, };
	Module* midgrabCallBack2[midgrabCollider2] = { {this},{this} };

	// Punch animation 
	midgrab.PushBack({ 137,2450,61,87 }, 15, { 31,2 }, midgrabCollider, midgrabHitbox, midgrabCollType, midgrabCallBack, 20, 9, 25, 3);
	midgrab.PushBack({ 2202,3206,78,52 }, 15, { 31,2 }, midgrabCollider, midgrabHitbox, midgrabCollType, midgrabCallBack, 20, 9, 25, 3);
	midgrab.PushBack({ 2284,3180,52,78 }, 15, { 31,2 }, midgrabCollider, midgrabHitbox, midgrabCollType, midgrabCallBack, 20, 9, 25, 3);
	midgrab.PushBack({ 2342,3206,78,52 }, 15, { 31,2 }, midgrabCollider, midgrabHitbox, midgrabCollType, midgrabCallBack, 20, 9, 25, 3);
	midgrab.PushBack({ 2426,3185,122,78 }, 15, { 31,2 }, midgrabCollider, midgrabHitbox, midgrabCollType, midgrabCallBack, 20, 9, 25, 3);

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
	srand(time(NULL));
	healthAnim = 0;
	critical = false;
	health = 0;

	LOG("Listening for Arrow keys + SPACE:\n");
	LOG("Loading player textures");

	graphics = App->textures->Load("Assets/Sprites/jubei.png"); // arcade version
	//ui = App->textures->Load("Assets/Sprites/UIspritesheet2.png"); // health bar 
	shadow = App->textures->Load("Assets/Sprites/sombra.png"); // health bar 


	App->audio->effects[0] = Mix_LoadWAV("Assets/Music/jubei_shigetsutoh.wav");
	App->audio->effects[1] = Mix_LoadWAV("Assets/Music/jubei_wavesound.wav");
	App->audio->effects[2] = Mix_LoadWAV("Assets/Music/jubei_getshitted1.wav");
	App->audio->effects[14] = Mix_LoadWAV("Assets/Music/CharacterLandingGround.wav");
	App->audio->effects[15] = Mix_LoadWAV("Assets/Music/LightJumpAir.wav");
	App->audio->effects[16] = Mix_LoadWAV("Assets/Music/Slash1.wav");
	App->audio->effects[17] = Mix_LoadWAV("Assets/Music/KickConnect.wav");
	App->audio->effects[18] = Mix_LoadWAV("Assets/Music/WeaponAttackNoConnect.wav");
	App->audio->effects[19] = Mix_LoadWAV("Assets/Music/LightKickMiss1.wav");
	App->audio->effects[20] = Mix_LoadWAV("Assets/Music/weaponblock1.wav");
	App->audio->effects[21] = Mix_LoadWAV("Assets/Music/weaponblock2.wav");
	App->audio->effects[22] = Mix_LoadWAV("Assets/Music/weaponblock3.wav");
	App->audio->effects[23] = Mix_LoadWAV("Assets/Music/throw&block.wav");
	App->audio->effects[24] = Mix_LoadWAV("Assets/Music/slash2.wav");
	App->audio->effects[25] = Mix_LoadWAV("Assets/Music/slash3.wav");
	App->audio->effects[26] = Mix_LoadWAV("Assets/Music/kick.wav");
	App->audio->effects[27] = Mix_LoadWAV("Assets/Music/jubei_getshitted2.wav");
	App->audio->effects[28] = Mix_LoadWAV("Assets/Music/jubei_getshitted3.wav");
	App->audio->effects[29] = Mix_LoadWAV("Assets/Music/jubei_getshitted4.wav");
	App->audio->effects[30] = Mix_LoadWAV("Assets/Music/fallGroundHit.wav");
	App->audio->effects[31] = Mix_LoadWAV("Assets/Music/swordDrop.wav");
	App->audio->effects[32] = Mix_LoadWAV("Assets/Music/swordstruggle.wav");
	App->audio->effects[33] = Mix_LoadWAV("Assets/Music/sprintstop.wav");


	return ret;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading Character");
	App->audio->CleanUp();

	App->textures->Unload(shadow);
	//App->textures->Unload(ui);
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

	if (swordDrop || swordOnTheGround)
		current_animation = &NWidle;
	else
		current_animation = &idle;

	int speed;
	if (App->render->escala < 1.25)speed = 1;//speed when zoomout
	else speed = 2;//speed when zoomin

	float jumpingescala;
	if (App->render->escala < 1.25)jumpingescala = 0.75f;
	else jumpingescala = 1;

	if (invencibleframes) {
		if (SDL_GetTicks() - (invencibleaux) >= invencibleTotalTime) {
			invencibleframes = false;
			invencibleTotalTime = 750;
		}
	}

	internal_input(inputs);
	player_states state = process_fsm(inputs);
	current_state = state;

	if (powValue >= 31) {
		powActivated = true;
		powValue = 31;
	}
	else
		powActivated = false;


	if (powOff) {
		if (powValue > 0) {
			powValue--;
		}
		else {
			powValue = 0;
			powOff = false;
		}
	}


	if (!playerFlip) {
		if (App->player2->position.x - position.x < 110)
			close = true;
		else
			close = false;
	}
	else {
		if (position.x - App->player2->position.x < 110)
			close = true;
		else
			close = false;
	}


	if (!doingAction) {
		switch (state)
		{
		case ST_IDLE:
			LOG("IDLE\n");
			if (swordDrop || swordOnTheGround)
				current_animation = &NWidle;
			else
				current_animation = &idle;

			break;
		case ST_WALK_FORWARD:
			LOG("FORWARD >>>\n");
			if (!playerFlip) {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWforward; //FALTA ANIM
				else
					current_animation = &forward;
				position.x += speed + 1 * speed;
			}
			else {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWbackward; //FALTA ANIM
				else
					current_animation = &backward;
				position.x += speed;
			}
			break;
		case ST_WALK_BACKWARD:
			LOG("BACKWARD <<<\n");
			if (!playerFlip) {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWbackward; //FALTA ANIM
				else
					current_animation = &backward;
				position.x += speed;
			}
			else {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWforward; //FALTA ANIM
				else
					current_animation = &forward;
				position.x += speed + 1 * speed;
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
		case ST_PUNCH_MID_CROUCH:
			LOG("PUNCH CROUCHING **++\n");
			crouchpunching = true; doingAction = true;
			break;
		case ST_PUNCH_STRONG_CROUCH:
			LOG("PUNCH CROUCHING **++\n");
			crouchpunching = true; doingAction = true;
			break;
		case ST_KICK_CROUCH:
			LOG("KICK CROUCHING **++\n");
			crouchkicking = true; doingAction = true;
			break;
		case ST_KICK_MID_CROUCH:
			LOG("KICK CROUCHING **++\n");
			crouchkicking = true; doingAction = true;
			break;
		case ST_KICK_STRONG_CROUCH:
			LOG("KICK CROUCHING **++\n");
			crouchkicking = true; doingAction = true;
			break;
		case ST_PUNCH_STANDING:
			LOG("PUNCH STANDING ++++\n");
			punching = true; doingAction = true;
			break;
		case ST_PUNCH_CLOSE_STANDING:
			LOG("PUNCH STANDING ++++\n");
			closeLowpunching = true; doingAction = true;
			break;
		case ST_MID_PUNCH_STANDING:
			LOG("PUNCH STANDING ++++\n");
			midPunching = true; doingAction = true;
			break;
		case ST_STRONG_PUNCH_STANDING:
			LOG("PUNCH STANDING ++++\n");
			strongPunching = true; doingAction = true;
			break;
		case ST_KICK_STANDING:
			LOG("KICK STANDING ----\n");
			kicking = true; doingAction = true;
			break;
		case ST_MID_KICK:
			LOG("KICK STANDING ----\n");
			midKicking = true; doingAction = true;
			break;
		case ST_STRONG_KICK:
			LOG("KICK STANDING ----\n");
			strongKicking = true; doingAction = true;
			break;
		case ST_GRAB:
			LOG("KICK STANDING ----\n");
			grabbing = true; doingAction = true;
			break;
		case ST_GET_GRABBED2:
			doingAction = true;
			break;
		case ST_BLOCKING:
			blockingAction = true; doingAction = true;
			break;
		case ST_CROUCH_BLOCK:
			blockingActionCrouch = true; doingAction = true;
			break;
		case ST_SWORD_FIGHT:
			swordFighting = true; doingAction = true;
			break;
		case ST_SPECIAL:
			LOG("SPECIAL OwwwwO\n");
			tornading = true; doingAction = true;
			break;
		case ST_FALLING://new
			falling = true; doingAction = true;
			break;
		case ST_SWORD_GRABBING:
			grabbingSword = true; doingAction = true;
			break;
		case ST_SIDE_STEPPING:
			sideStepping = true; doingAction = true;
			break;
		case ST_SPRINT:
			sprinting = true; doingAction = true;
			break;
		case ST_SECOND_GRAB:
			grabbing2 = true; doingAction = true;
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

	if (grabbingSword) {
		current_animation = &pickUpSword;

		noSword = false;
		delete App->particles->active[swordTrackGround];
		App->particles->active[swordTrackGround] = nullptr;
		swordTrackGround = 0;
		swordTrack = 0;
		swordDropped = false;
		swordOnTheGround = false;
		closeSword = false;

		if (pickUpSword.GetAnimEnd() == true) {
			grabbingSword = false; pickUpSword.SetAnimEnd(false);
			inputs.Push(IN_SWORD_GRABBED);
			doingAction = false;
		}


	}
	if (sideStepping) {
		if (swordDrop || swordOnTheGround)
			current_animation = &NWbacksprint;
		else
			current_animation = &backsprint;

		position.y = groundlevelaux + (-(JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY*4)*pow(jumpingframe, 2)))*jumpingescala;//MRUA formula

		if (!playerFlip)
			position.x -= 10;
		else
			position.x += 10;

		hasjumped = true;
		jumpingframe++;
		//stop jump anim
		if (position.y > groundlevelaux && hasjumped == true) {
			position.y = groundlevelaux;
			doingAction = false;
			sideStepping = false; doingAction = false; backsprint.SetAnimEnd(false);
			sideStep.Reset();
			inputs.Push(IN_JUMP_FINISH);
			jumpingframe = 0;
			hasjumped = false;
			jumpdiagonal = false;
			jumpleft = false;
			JumpPunching = false;
			JumpKicking = false;
			Mix_PlayChannel(-1, App->audio->effects[14], 0);
		}





	}
	if (sprinting) {
		if (swordDrop || swordOnTheGround)
			current_animation = &NWsprint;
		else
			current_animation = &sprint;
		if (!playerFlip)
			position.x += 6;
		else
			position.x -= 6;
		if (App->input->Controller_player1_LAxisX < DEATHZONE  && playerFlip == false && current_state == ST_SPRINT) { inputs.Push(IN_SPRINT_END); }
		if (App->input->Controller_player1_LAxisX > -DEATHZONE && playerFlip && current_state == ST_SPRINT) { inputs.Push(IN_SPRINT_END); }

		if (current_state == ST_SPRINT_END) {
			sideStepAux++;
			if (swordDrop || swordOnTheGround)
				current_animation = &NWsprintEnd;
			else
				current_animation = &sprintEnd;
			if (sideStepAux > 10) {
				if (App->player2->position.x > position.x)
					App->particles->AddParticle(App->particles->groundHit, position.x - 40, position.y - 20, playerFlip, COLLIDER_NONE); //Particle test
				else
					App->particles->AddParticle(App->particles->groundHit, position.x - 40, position.y - 20, playerFlip, COLLIDER_NONE); //Particle test		
				doingAction = false;
				inputs.Push(IN_SPRINT_END);
				sprinting = false;
				sprint.SetAnimEnd(false);
				sprint.SetAnimEnd(false);
				sprint.Reset();
				NWsprint.SetAnimEnd(false);
				NWsprint.Reset();
				sideStepAux = 0;
				Mix_PlayChannel(-1, App->audio->effects[33], 0);
			}
		}

	}


	if (kicking) {
		//set kick anim
		if (swordDrop || swordOnTheGround)
			current_animation = &NWkick;
		else
			current_animation = &kick;
		//stop kick anim

		if (current_animation->current_frame > 2 && !App->player2->invencibleframes && !audioPlayed) {
			Mix_PlayChannel(-1, App->audio->effects[19], 0);
			audioPlayed = true;
		}
		if (kick.GetAnimEnd() == true || NWkick.GetAnimEnd() == true || grabbingSword) {
			if (!grabbingSword)
				doingAction = false;
			kicking = false;
			kick.SetAnimEnd(false);
			NWkick.SetAnimEnd(false);
			audioPlayed = false;
		}
	}

	if (midKicking) {
		//set kick anim
		if (swordDrop || swordOnTheGround)
			current_animation = &NWkick;
		else
			current_animation = &midkick;

		if (current_animation->current_frame > 3 && !App->player2->invencibleframes && !audioPlayed) {
			Mix_PlayChannel(-1, App->audio->effects[19], 0);
			audioPlayed = true;
		}
		if (midkick.GetAnimEnd() == true || NWkick.GetAnimEnd() == true || grabbingSword) {
			if (!grabbingSword)
				doingAction = false;
			midKicking = false; midkick.SetAnimEnd(false);
			NWkick.SetAnimEnd(false);
			audioPlayed = false;
			inputs.Push(IN_PUNCH_FINISH);
		}
	}
	if (strongKicking) {
		//set kick anim
		if (swordDrop || swordOnTheGround)
			current_animation = &NWstrongkick;
		else
			current_animation = &strongkick;

		if (current_animation->current_frame > 2 && !App->player2->invencibleframes && !audioPlayed) {
			Mix_PlayChannel(-1, App->audio->effects[19], 0);
			audioPlayed = true;
		}
		if (strongkick.GetAnimEnd() == true || NWstrongkick.GetAnimEnd() == true) {
			strongKicking = false; doingAction = false; strongkick.SetAnimEnd(false); NWstrongkick.SetAnimEnd(false);
			audioPlayed = false;
			inputs.Push(IN_PUNCH_FINISH);
		}
	}

	if (grabbing) {
		if ((close && !App->player2->invencibleframes && App->player2->position.y == position.y) || current_state == ST_GRABBING) {
			App->player2->p2inputs.Push(IN_GET_GRABBED2);
			if (App->player2->current_state == ST_GET_GRABBED2 || grabStates >= 0) {
				inputs.Push(IN_GRABBED);

				if (App->player2->playerFlip && grabStates == 0) { flipAux = true; grabStates++; }
				else if (!App->player2->playerFlip && grabStates == 0) { flipAux = false; grabStates++; }
				if (swordDrop || swordOnTheGround)
					current_animation = &NWgrab; // FALTA ANIM
				else
					current_animation = &grab;
				if (grabStates < 3) {

					if (swordDrop || swordOnTheGround)
						current_animation = &getGrab; // FALTA ANIM + FALTA ANIM FALLING
					else
						App->player2->current_animation = &App->player2->getGrab;
				}
				if (current_animation->current_frame > 0 && grabStates == 1) {
					Mix_PlayChannel(-1, App->audio->effects[23], 0);
					if (flipAux)
						App->player2->position.x = position.x - 60;
					else
						App->player2->position.x = position.x + 60;

					grabStates++;
				}
				if (current_animation->current_frame > 1 && grabStates == 2) {
					if (flipAux)
						App->player2->position.x += 40;
					else
						App->player2->position.x -= 40;

					App->player2->position.y -= 40;
					grabStates++;
				}
				if (current_animation->current_frame > 2 && grabStates == 3) {
					if (flipAux)
						App->player2->position.x += 40;
					else
						App->player2->position.x -= 40;
					App->player2->doingAction = false;
					App->player2->p2inputs.Push(IN_GRABBED_FINISH2);
					grabStates++;
				}
				if (grab.GetAnimEnd() == true) {
					grabStates = 0;
					grab.SetAnimEnd(false);
					App->player2->health += 20;
					inputs.Push(IN_GRAB_FINISH);
					grabbing = false; doingAction = false;
					App->player2->getGrab.SetAnimEnd(false);

				}
			}
			else {
				inputs.Push(IN_NOT_GRAB);
				grabbing = false; doingAction = false;

			}
		}
		else {
			inputs.Push(IN_NOT_GRAB);
			grabbing = false; doingAction = false;
		}
	}

	if (grabbing2) {
		if ((close && !App->player2->invencibleframes && App->player2->position.y == position.y) || current_state == ST_SECOND_GRAB) {
			App->player2->p2inputs.Push(IN_GET_GRABBED2);
			if (App->player2->current_state == ST_GET_GRABBED2 || grabStates >= 0) {
				inputs.Push(IN_GRABBED);
				if (App->player2->playerFlip && grabStates == 0) { flipAux = true; grabStates++; }
				else if (!App->player2->playerFlip && grabStates == 0) { flipAux = false; grabStates++; }
				current_animation = &midgrab;
				if (grabStates < 3) {
					if (swordDrop || swordOnTheGround)
						App->player2->current_animation = &App->player2->getGrab2;
					else
						App->player2->current_animation = &App->player2->getGrab2;
				}
				if (current_animation->current_frame > 0 && grabStates == 1) {
					Mix_PlayChannel(-1, App->audio->effects[23], 0);
					if (flipAux)
						App->player2->position.x = position.x - 60;
					else
						App->player2->position.x = position.x + 60;

					grabStates++;
				}
				if (current_animation->current_frame > 1 && grabStates == 2) {
					if (flipAux)
						App->player2->position.x += 40;
					else
						App->player2->position.x -= 40;

					App->player2->position.y -= 40;
					App->player2->doingAction = false;
					App->player2->p2inputs.Push(IN_GRABBED_FINISH2);
					grabStates++;
				}

				if (midgrab.GetAnimEnd() == true) {
					grabStates = 0;
					grab.SetAnimEnd(false);
					App->player2->health += 20;
					inputs.Push(IN_GRAB_FINISH);
					grabbing2 = false; doingAction = false;
					App->player2->getGrab.SetAnimEnd(false);

				}
			}
			else {
				inputs.Push(IN_NOT_GRAB);
				grabbing2 = false; doingAction = false;

			}
		}
		else {
			inputs.Push(IN_NOT_GRAB);
			grabbing2 = false; doingAction = false;
		}
	}

	if (swordFighting) {
		if (grabStates >= 0 && !swordDropped) {
			App->player2->p2inputs.Push(IN_SWORD_FIGHT2);
			App->interface->printSwordFight = true;
			alredycollided2 = false;

			if (App->player2->playerFlip && grabStates == 0) {
				flipAux = true; grabStates++; App->player2->position.x = position.x + 50;
				Mix_PlayChannel(-1, App->audio->effects[21], 0);
				swordFightCount = 0;
				App->particles->AddParticle(App->particles->swordFightEnd, position.x, position.y - 65, COLLIDER_GRAB);
				App->particles->AddParticle(App->particles->spark, position.x, position.y - 65, COLLIDER_GRAB);

			}
			else if (!App->player2->playerFlip && grabStates == 0) {
				flipAux = false; grabStates++;  position.x = App->player2->position.x + 50;
				Mix_PlayChannel(-1, App->audio->effects[21], 0);
				App->particles->AddParticle(App->particles->swordFightEnd, (App->player2->position.x + 20), position.y - 65, COLLIDER_GRAB);
				App->particles->AddParticle(App->particles->spark, (App->player2->position.x + 20), position.y - 65, COLLIDER_GRAB);


			}
			current_animation = &swordFight;
			App->player2->current_animation = &swordFight;

			if (SDL_GetTicks() % 2 == 0) {
				position.x += 1;
				App->player2->position.x += 1;

			}
			else {
				position.x -= 1;
				App->player2->position.x -= 1;
			}

			if (grabStates >= 1 && grabStates <= 60) {
				if (grabStates == 2) {
					Mix_PlayChannel(-1, App->audio->effects[32], 0);
					if (flipAux) {
						App->particles->AddParticle(App->particles->spark, position.x + 20, position.y - 80, COLLIDER_GRAB);
						App->particles->AddParticle(App->particles->swordFight, position.x + 20, position.y - 90, COLLIDER_GRAB);
					}
					else {
						App->particles->AddParticle(App->particles->spark, position.x + 20, position.y - 80, COLLIDER_GRAB);
						App->particles->AddParticle(App->particles->swordFight, position.x + 20, position.y - 90, COLLIDER_GRAB);

					}

				}
				grabStates++;

			}
			else if (grabStates > 60 && grabStates <= 120) {
				if (grabStates == 61) {
					aux = 10;
					Mix_PlayChannel(-1, App->audio->effects[32], 0);
				}

				if (flipAux && aux == 1) {
					App->particles->AddParticle(App->particles->spark, position.x + 20, position.y - 80, COLLIDER_GRAB);
					App->particles->AddParticle(App->particles->swordFight, position.x + 50, position.y - 90, COLLIDER_GRAB);
					aux--;
				}
				else if (aux == 1) {
					App->particles->AddParticle(App->particles->spark, position.x + 20, position.y - 80, COLLIDER_GRAB);
					App->particles->AddParticle(App->particles->swordFight, position.x + 50, position.y - 90, COLLIDER_GRAB);
					aux--;

				}
				if (aux > 0 && aux < 11 && flipAux) {
					App->player2->position.x += (int)(aux*player1scale);
					position.x += (int)(aux*player1scale);
					aux--;
				}
				else if (aux > 0 && aux < 11 && !flipAux) {
					App->player2->position.x -= (int)(aux*player1scale);
					position.x -= (int)(aux*player1scale);
					aux--;
				}

				grabStates++;
			}
			else if (grabStates > 120 && grabStates <= 181) {
				if (grabStates == 121) {
					aux = 10;
					Mix_PlayChannel(-1, App->audio->effects[32], 0);
				}
				if (flipAux && aux == 1) {
					App->particles->AddParticle(App->particles->spark, position.x + 20, position.y - 80, COLLIDER_GRAB);
					App->particles->AddParticle(App->particles->swordFight, position.x + 50, position.y - 90, COLLIDER_GRAB);
					aux--;
				}
				else if (aux == 1) {
					App->particles->AddParticle(App->particles->spark, position.x + 20, position.y - 80, COLLIDER_GRAB);
					App->particles->AddParticle(App->particles->swordFight, position.x + 50, position.y - 90, COLLIDER_GRAB);
					aux--;
				}

				if (aux > 0 && aux < 11 && flipAux) {
					App->player2->position.x -= (int)(aux*player1scale);
					position.x -= (int)(aux*player1scale);
					aux--;
				}
				else if ((aux > 0 && aux < 11 && !flipAux)) {
					App->player2->position.x += (int)(aux*player1scale);
					position.x += (int)(aux*player1scale);
					aux--;
				}

				grabStates++;
			}
			else if (grabStates == 182) grabStates = 1;


			if (swordFightCount > 20 || App->player2->swordFightCount > 20) {
				App->interface->printSwordFight = false;
				App->interface->countAux = 0;
				Mix_PlayChannel(-1, App->audio->effects[21], 0);
				if (flipAux) {
					App->particles->AddParticle(App->particles->swordFightEnd, position.x, position.y - 65, COLLIDER_GRAB);
					App->particles->AddParticle(App->particles->spark, position.x, position.y - 65, COLLIDER_GRAB);
				}
				else {
					App->particles->AddParticle(App->particles->swordFightEnd, (App->player2->position.x + 20), position.y - 65, COLLIDER_GRAB);
					App->particles->AddParticle(App->particles->spark, (App->player2->position.x + 20), position.y - 65, COLLIDER_GRAB);

				}
				grabStates = 0;
				swordFight.SetAnimEnd(false);
				swordFighting = false; doingAction = false;
				App->player2->doingAction = false;
				App->player2->swordFighting = false;
				if (swordFightCount - App->player2->swordFightCount > 5) {
					inputs.Push(IN_SWORD_FIGHT_WIN);
					App->player2->p2inputs.Push(IN_SWORD_FIGHT_LOSE2);
					App->player2->swordDrop = true;
				}
				else if (swordFightCount - App->player2->swordFightCount < 5 && swordFightCount - App->player2->swordFightCount > -5) {
					inputs.Push(IN_SWORD_FIGHT_DRAW);
					App->player2->p2inputs.Push(IN_SWORD_FIGHT_DRAW2);
					App->particles->AddParticle(App->particles->spark, (App->player2->position.x + 20), position.y - 65, COLLIDER_GRAB);
				}
				else {
					App->player2->p2inputs.Push(IN_SWORD_FIGHT_WIN2);
					inputs.Push(IN_SWORD_FIGHT_LOSE);
					swordDrop = true;
				}
				aux = 5;
				swordFightCount = 1;
				App->player2->swordFightCount = 1;
			}

		}
		else {
			inputs.Push(IN_NOT_SWORD_FIGHT);
		}

	}
	if (swordDrop) {
		if (!swordDropped)
			App->particles->AddParticle(App->particles->swordDrop, (int)(position.x - (140 * player1scale)), (int)(position.y - (44 * player1scale)), playerFlip, COLLIDER_GRAB);
		swordDropped = true;

		App->particles->active[swordTrack]->position.y = groundlevelaux - (JUMP_INIT_VY*jumpingSwordFrame) + (0.5*(JUMP_INIT_AY)*pow(jumpingSwordFrame, 2));//MRUA formula

		App->particles->active[swordTrack]->position.x += 2;
		jumpingSwordFrame++;

		if (App->particles->active[swordTrack]->position.y > groundlevelaux && jumpingSwordFrame > 1) {

			swordDrop = false;
			swordOnTheGround = true;
			jumpingSwordFrame = 0;
			swordDropped = false;
			Mix_PlayChannel(-1, App->audio->effects[31], 0);

		}


	}
	if (swordOnTheGround) {
		if (!swordDropped) {
			noSword = true;
			App->particles->AddParticle(App->particles->swordGround, (int)App->particles->active[swordTrack]->position.x, (int)App->particles->active[swordTrack]->position.y - (60 * player1scale), playerFlip, COLLIDER_GRAB);
			delete App->particles->active[swordTrack];
			App->particles->active[swordTrack] = nullptr;
			swordTrack = 0;
			swordDropped = true;
		}

		if (swordTrackGround != NULL && ((App->particles->active[swordTrackGround]->position.x - position.x < 110 && playerFlip) || (playerFlip && position.x - App->particles->active[swordTrackGround]->position.x < 110)))
			closeSword = true;
	}

	if (tornading) {
		current_animation = &tornado;
		if (current_animation->current_frame == 4.5) {
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
		}
		if (tornado.GetAnimEnd() == true) {
			tornading = false; doingAction = false; tornado.SetAnimEnd(false);
			inputs.Push(IN_PUNCH_FINISH);

		}
	}

	if (closeLowpunching) {
		if (swordDrop || swordOnTheGround)
			current_animation = &NWpunch;
		else
			current_animation = &shortPunch;


		if (shortPunch.GetAnimEnd() == true || NWpunch.GetAnimEnd() == true) {
			if (!App->player2->invencibleframes)	Mix_PlayChannel(-1, App->audio->effects[18], 0);
			closeLowpunching = false; doingAction = false; shortPunch.SetAnimEnd(false); NWpunch.SetAnimEnd(false);
			audioPlayed = false;
			inputs.Push(IN_PUNCH_FINISH);
		}
	}

	if (punching) {
		if (swordDrop || swordOnTheGround)
			current_animation = &NWpunch;
		else
			current_animation = &punch;


		if (current_animation->current_frame > 3 && !App->player2->invencibleframes && !audioPlayed) {
			Mix_PlayChannel(-1, App->audio->effects[18], 0);
			audioPlayed = true;
		}
		if (punch.GetAnimEnd() == true || NWpunch.GetAnimEnd() == true) {
			punching = false; doingAction = false;
			punch.SetAnimEnd(false);
			NWpunch.SetAnimEnd(false);
			audioPlayed = false;
			inputs.Push(IN_PUNCH_FINISH);
			alredycollided2 = false;
		}
	}

	if (midPunching) {
		if (swordDrop || swordOnTheGround)
			current_animation = &NWpunch;
		else
			current_animation = &midpunch;



		if (midpunch.GetAnimEnd() == true || NWpunch.GetAnimEnd() == true) {
			if (!App->player2->invencibleframes)	Mix_PlayChannel(-1, App->audio->effects[18], 0);
			midPunching = false; doingAction = false; midpunch.SetAnimEnd(false);
			NWpunch.SetAnimEnd(false);
			audioPlayed = false;
			inputs.Push(IN_PUNCH_FINISH);
			alredycollided2 = false;

		}
	}
	if (strongPunching) {
		if (swordDrop || swordOnTheGround)
			current_animation = &NWstrongpunch;
		else
			current_animation = &strongpunch;



		if (current_animation->current_frame > 6 && current_animation->current_frame < 8 && !App->player2->invencibleframes && !audioPlayed) {
			Mix_PlayChannel(-1, App->audio->effects[18], 0);
			audioPlayed = true;
		}
		if (strongpunch.GetAnimEnd() == true || NWstrongpunch.GetAnimEnd() == true) {
			strongPunching = false; doingAction = false; strongpunch.SetAnimEnd(false);
			NWstrongpunch.SetAnimEnd(false);
			audioPlayed = false;
			inputs.Push(IN_PUNCH_FINISH);
			alredycollided2 = false;

		}
	}

	if (crouching) {
		//set punch anim
		if (swordDrop || swordOnTheGround)
			current_animation = &NWcrouch;
		else
			current_animation = &crouch;
		if (!playerFlip) {
			if (App->input->Controller_player1_LAxisX < -DEATHZONE)
				blocking = true;
			else
				blocking = false;
		}

		else {
			if (App->input->Controller_player1_LAxisX > DEATHZONE)
				blocking = true;
			else
				blocking = false;
		}

		//stop punch anim
		if (crouch.GetAnimEnd() == true || NWcrouch.GetAnimEnd() == true) {
			crouching = false; doingAction = false; crouch.SetAnimEnd(false); NWcrouch.SetAnimEnd(false);
		}
	}

	if (crouchpunching)
	{

		if (current_state == ST_PUNCH_CROUCH) {
			if (swordDrop || swordOnTheGround)
				current_animation = &NWcrouchPunch;
			else
				current_animation = &crouchPunch;

		}
		else	if (current_state == ST_PUNCH_MID_CROUCH) {
			if (swordDrop || swordOnTheGround)
				current_animation = &NWcrouchPunch;
			else
				current_animation = &crouchmidPunch;
		}
		else {
			if (swordDrop || swordOnTheGround)
				current_animation = &NWstrongcrouchPunch;
			else
				current_animation = &crouchstrongPunch;
		}

		//stop crouch punch anim
		if (crouchPunch.GetAnimEnd() == true || crouchmidPunch.GetAnimEnd() == true || crouchstrongPunch.GetAnimEnd() == true || NWcrouchPunch.GetAnimEnd() == true || NWstrongcrouchPunch.GetAnimEnd() == true) {
			crouchpunching = false; doingAction = false; crouchPunch.SetAnimEnd(false); crouchmidPunch.SetAnimEnd(false); crouchstrongPunch.SetAnimEnd(false);
			NWcrouchPunch.SetAnimEnd(false); crouchstrongPunch.SetAnimEnd(false);
			inputs.Push(IN_PUNCH_FINISH);
			if (!App->player2->invencibleframes)	Mix_PlayChannel(-1, App->audio->effects[18], 0);
		}
	}

	if (crouchkicking)
	{
		//set crouch punch anim.
		if (current_state == ST_KICK_CROUCH) {
			if (swordDrop || swordOnTheGround)
				current_animation = &NWcrouchKick;
			else
				current_animation = &crouchKick;

		}
		else if (current_state == ST_KICK_MID_CROUCH) {
			if (swordDrop || swordOnTheGround)
				current_animation = &NWcrouchKick;
			else
				current_animation = &crouchmidKick;
		}
		else {
			if (swordDrop || swordOnTheGround)
				current_animation = &crouchstrongKick;
			else
				current_animation = &crouchstrongKick;
		}
		//stop crouch punch anim
		if (crouchKick.GetAnimEnd() == true || crouchmidKick.GetAnimEnd() == true || crouchstrongKick.GetAnimEnd() == true || NWcrouchKick.GetAnimEnd() == true || NWcrouchstrongKick.GetAnimEnd() == true)
		{
			crouchkicking = false; doingAction = false; crouchKick.SetAnimEnd(false); crouchmidKick.SetAnimEnd(false); crouchstrongKick.SetAnimEnd(false); inputs.Push(IN_PUNCH_FINISH);
			NWcrouchKick.SetAnimEnd(false); NWcrouchstrongKick.SetAnimEnd(false);

		}
	}

	if (getsHit) {
		//set punch anim
		if (swordDrop || swordOnTheGround)
			current_animation = &hurtLow; //FALTA ANIM
		else
			current_animation = &hurtLow;

		internalAux = aux + 1;
		App->render->DrawQuad({ 0,588,391,148 }, 0, 255, 0, 80);


		if (position.x < 50 || position.x > 310) {
			if (App->player2->playerFlip) {
				if (aux > 0 && aux < internalAux) {
					App->player2->position.x += (int)(aux*player1scale);
					aux--;
				}
			}
			else if (!App->player2->playerFlip) {
				if (aux > 0 && aux < internalAux)
					App->player2->position.x -= (int)(aux*player1scale);
				aux--;
			}
		}
		else {
			if (playerFlip) {
				if (aux > 0 && aux < internalAux) {
					position.x += (int)(aux*player1scale);
					aux--;
				}
			}
			else if (!playerFlip) {
				if (aux > 0 && aux < internalAux)
					position.x -= (int)(aux*player1scale);
				aux--;

			}
		}

		if (hurtLow.GetAnimEnd() == true) {
			getsHit = false; doingAction = false; hurtLow.SetAnimEnd(false);
			invencibleframes = true;
			invencibleaux = SDL_GetTicks() + 200;

		}
	}
	if (blockingAction) {
		//set punch anim

		if (swordDrop || swordOnTheGround)
			current_animation = &NWblockingIdle;
		else
			current_animation = &blockingIdle;

		blocking = true;

		int internalAux = aux + 1;
		if (position.x < 50 || position.x > 310) {
			if (App->player2->playerFlip) {
				if (aux > 0 && aux < internalAux) {
					App->player2->position.x += (int)(aux*player1scale);
					aux--;
				}
			}
			else if (!App->player2->playerFlip) {
				if (aux > 0 && aux < internalAux)
					App->player2->position.x -= (int)(aux*player1scale);
				aux--;
			}
		}
		else {
			if (playerFlip) {
				if (aux > 0 && aux < internalAux) {
					position.x += (int)(aux*player1scale);
					aux--;
				}
			}
			else if (!playerFlip) {
				if (aux > 0 && aux < internalAux)
					position.x -= (int)(aux*player1scale);
				aux--;

			}
		}

		if (blockingIdle.GetAnimEnd() == true) {
			inputs.Push(IN_BLOCK_FINISH);
			blocking = false; doingAction = false; blockingIdle.SetAnimEnd(false); crouchBlock.SetAnimEnd(false);
			blockingAction = false;
			invencibleframes = true;
			invencibleaux = SDL_GetTicks();
			invencibleTotalTime = 550;
		}

	}
	if (blockingActionCrouch) {
		//set punch anim
		if (swordDrop || swordOnTheGround)
			current_animation = &NwcrouchBlock; //FALTA ANIM
		else
			current_animation = &crouchBlock;

		blocking = true;

		int internalAux = aux + 1;
		if (position.x < 50 || position.x > 310) {
			if (App->player2->playerFlip) {
				if (aux > 0 && aux < internalAux) {
					App->player2->position.x += (int)(aux*player1scale);
					aux--;
				}
			}
			else if (!App->player2->playerFlip) {
				if (aux > 0 && aux < internalAux)
					App->player2->position.x -= (int)(aux*player1scale);
				aux--;
			}
		}
		else {
			if (playerFlip) {
				if (aux > 0 && aux < internalAux) {
					position.x += (int)(aux*player1scale);
					aux--;
				}
			}
			else if (!playerFlip) {
				if (aux > 0 && aux < internalAux)
					position.x -= (int)(aux*player1scale);
				aux--;

			}
		}

		if (crouchBlock.GetAnimEnd() == true) {
			inputs.Push(IN_BLOCK_FINISH);
			blocking = false; doingAction = false; crouchBlock.SetAnimEnd(false);
			blockingActionCrouch = false;
			invencibleframes = true;
			invencibleaux = SDL_GetTicks();
			invencibleTotalTime = 550;

		}

	}
	if (jumping)
	{
		//set jump anim

		if (current_state == ST_PUNCH_NEUTRAL_JUMP || current_state == ST_MID_PUNCH_NEUTRAL_JUMP || current_state == ST_STRONG_PUNCH_NEUTRAL_JUMP) {
			JumpPunching = true;
		}


		if (current_state == ST_KICK_NEUTRAL_JUMP || current_state == ST_KICK_MID_NEUTRAL_JUMP || current_state == ST_KICK_STRONG_NEUTRAL_JUMP) {
			JumpKicking = true;
		}

		if (JumpPunching) {
			if (current_state == ST_MID_PUNCH_NEUTRAL_JUMP) {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWjumpPunch;
				else
					current_animation = &jumpmidPunch;
			}
			else if (current_state == ST_STRONG_PUNCH_NEUTRAL_JUMP) {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWjumpstrongPunch;
				else
					current_animation = &jumpstrongPunch;

			}
			else {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWjumpPunch;
				else
					current_animation = &jumpPunch;

			}
		}
		else if (JumpKicking) {
			if (current_state == ST_KICK_MID_NEUTRAL_JUMP) {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWjumpKick;
				else
					current_animation = &jumpmidKick;
			}
			else if (current_state == ST_KICK_STRONG_NEUTRAL_JUMP) {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWjumpstrongKick;
				else
					current_animation = &jumpstrongKick;
			}
			else {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWjumpKick;
				else
					current_animation = &jumpKick;
			}
		}
		else {
			if (swordDrop || swordOnTheGround)
				current_animation = &NWjump;
			else
				current_animation = &jump;

		}


		position.y = groundlevelaux + (-(JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY)*pow(jumpingframe, 2)))*jumpingescala;//MRUA formula
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
			App->particles->AddParticle(App->particles->groundHit, position.x, position.y - 30, playerFlip, COLLIDER_NONE); //Particle test
			if (App->player2->position.x > position.x)
				App->particles->AddParticle(App->particles->groundHit, position.x - 40, position.y - 30, playerFlip, COLLIDER_NONE); //Particle test
			else
				App->particles->AddParticle(App->particles->groundHit, position.x - 40, position.y - 30, playerFlip, COLLIDER_NONE); //Particle test
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
			jumpmidKick.Reset();
			jumpstrongKick.Reset();
			jumpPunch.Reset();
			jumpmidPunch.Reset();
			jumpstrongPunch.Reset();
			jump.Reset();
			NWjump.Reset();
			NWjumpKick.Reset();
			NWjumpstrongKick.Reset();
			NWjumpPunch.Reset();
			NWjumpstrongPunch.Reset();
		}
		jumpingframe++;
	}
	if (jumpdiagonal)
	{
		if (current_state == ST_PUNCH_NEUTRAL_JUMP || current_state == ST_MID_PUNCH_NEUTRAL_JUMP || current_state == ST_STRONG_PUNCH_NEUTRAL_JUMP) {
			JumpPunching = true;
		}
		if (current_state == ST_KICK_NEUTRAL_JUMP || current_state == ST_KICK_MID_NEUTRAL_JUMP || current_state == ST_KICK_STRONG_NEUTRAL_JUMP) {
			JumpKicking = true;
		}

		if (JumpPunching) {
			if (current_state == ST_MID_PUNCH_NEUTRAL_JUMP) {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWjumpPunch;
				else
					current_animation = &jumpmidPunch;
			}
			else if (current_state == ST_STRONG_PUNCH_NEUTRAL_JUMP) {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWjumpstrongPunch;
				else
					current_animation = &jumpstrongPunch;

			}
			else {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWjumpPunch;
				else
					current_animation = &jumpPunch;

			}
		}
		else if (JumpKicking) {
			if (current_state == ST_KICK_MID_NEUTRAL_JUMP) {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWjumpKick;
				else
					current_animation = &jumpmidKick;
			}
			else if (current_state == ST_KICK_STRONG_NEUTRAL_JUMP) {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWjumpstrongKick;
				else
					current_animation = &jumpstrongKick;
			}
			else {
				if (swordDrop || swordOnTheGround)
					current_animation = &NWjumpKick;
				else
					current_animation = &jumpKick;
			}
		}
		else {
			if (swordDrop || swordOnTheGround)
				current_animation = &NWjump;
			else
				current_animation = &jump;

		}




		position.y = groundlevelaux + (-(JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY)*pow(jumpingframe, 2)))*jumpingescala;//MRUA formula
		if (jumpleft)
			position.x -= 4 * jumpingescala;
		else
			position.x += 4 * jumpingescala;
		hasjumped = true;
		//stop jump anim
		if (position.y > groundlevelaux && hasjumped == true)	//end of the jump
		{
			App->particles->AddParticle(App->particles->groundHit, position.x, position.y - 30, playerFlip, COLLIDER_NONE); //Particle test
			if (App->player2->position.x > position.x)
				App->particles->AddParticle(App->particles->groundHit, position.x - 40, position.y - 30, playerFlip, COLLIDER_NONE); //Particle test
			else
				App->particles->AddParticle(App->particles->groundHit, position.x - 40, position.y - 30, playerFlip, COLLIDER_NONE); //Particle test

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
			jumpmidKick.Reset();
			jumpstrongKick.Reset();
			jumpmidPunch.Reset();
			jumpstrongPunch.Reset();
			swordFightCount = 0;
			App->player2->swordFightCount = 0;
			NWjump.Reset();
			NWjumpKick.Reset();
			NWjumpstrongKick.Reset();
			NWjumpPunch.Reset();
			NWjumpstrongPunch.Reset();
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
			invencibleframes = true;
			swordFightCount = 0;
			App->player2->swordFightCount = 0;
			NWjump.Reset();
			NWjumpKick.Reset();
			NWjumpstrongKick.Reset();
			NWjumpPunch.Reset();
			NWjumpstrongPunch.Reset();
		}
		jumpingframe++;
	}

	if (falling)//new
	{
		if (swordDrop || swordOnTheGround)
			current_animation = &fall;
		else
			current_animation = &fall;
		if (fall_bounces > FALLBOUNCES) { position.y = groundlevelaux; delay++; }
		else
		{

			position.y = groundlevelaux + (-(10 * jumpingframe) + (0.5*(0.5*JUMP_INIT_AY + (0.2f*(fall_bounces + 1)))*pow(jumpingframe, 2)))*jumpingescala;//MRUA formula
			if (playerFlip)position.x += (2 - (fall_bounces))*jumpingescala;
			else position.x -= (2 - (fall_bounces))*jumpingescala;
			hasjumped = true;
			jumpingframe++;
			if (position.y > groundlevelaux)
			{
				App->particles->AddParticle(App->particles->groundHit, position.x, position.y - 30, playerFlip, COLLIDER_NONE); //Particle test
				App->particles->AddParticle(App->particles->groundHit, position.x - 20, position.y - 30, playerFlip, COLLIDER_NONE); //Particle test
				App->particles->AddParticle(App->particles->groundHit, position.x - 40, position.y - 30, playerFlip, COLLIDER_NONE); //Particle test

				App->render->StartCameraShake(60, 1);
				Mix_PlayChannel(-1, App->audio->effects[30], 0);
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
			Mix_PlayChannel(-1, App->audio->effects[29], 0);
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
			invencibleframes = true;
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



	if (!powActivated)
		SDL_SetTextureColorMod(graphics, 255, 255 - (powValue * 6), 255 - (powValue * 6));
	else
		SDL_SetTextureColorMod(graphics, 255, 30, 30);


	if (health > healthAnim)
		healthAnim++;

	if (health > healthAnim)
		healthAnim++;

	SDL_Rect healthBar = { 90, 81, 134, 15 };

	if ((App->fight->showHealthBar) == true) {
		App->render->Blit(App->interface->ui, 5, 15, false, &healthBar, NULL, true);
		SDL_Rect healthBar = { 90, 81, 134, 15 };
		App->render->Blit(App->interface->ui, 167, 15, false, &healthBar, NULL, true);
		if (HEALTH_VALUE > health + 50) {
			SDL_Rect healthValue = { 90, 97, HEALTH_VALUE - healthAnim, 9 };
			App->render->Blit(App->interface->ui, 7, 17, false, &healthValue, NULL, true);
		}
		else {

			if (healthBlinking < 4) {
				critical = true;
				SDL_Rect healthValue = { 90, 107, HEALTH_VALUE - healthAnim, 9 };
				App->render->Blit(App->interface->ui, 168, 17, false, &healthValue, NULL, true);
				healthBlinking++;
			}
			else {
				SDL_Rect healthValue = { 90, 117, HEALTH_VALUE - healthAnim, 9 };
				App->render->Blit(App->interface->ui, 168, 17, false, &healthValue, NULL, true);
				healthBlinking++;

				if (healthBlinking > 8)
					healthBlinking = 0;

			}
		}
	}
	return UPDATE_CONTINUE;
}




// TODO 4: Detect collision with a wall. If so, do something.
void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (!godMode) {
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
			if (blocking && (current_state == ST_WALK_BACKWARD || current_state == ST_CROUCH)) {
				Mix_PlayChannel(-1, App->audio->effects[20], 0);
				if (crouching)
					inputs.Push(IN_BLOCKING_CROUCH);
				else
					inputs.Push(IN_BLOCKING);
			}
			else {
				if (App->player2->powActivated) {
					health += 25 * 3 / 2;
					App->player2->powActivated = false;
					App->player2->powOff = true;
				}
				else {
					health += 25;

				}
				inputs.Push(IN_FALL);
				if (App->player2->position.y < groundlevelaux) {
					inputs.Push(IN_FALL);
					airhit = true;

				}
			}
			if (c1->type == COLLIDER_PLAYER_ATTACK && c2->type == COLLIDER_ENEMY_ATTACK && (c1->attackType != 1 || c1->attackType != 2 || c2->attackType != 1 || c2->attackType != 2)) {
				if (!alredycollided2) {
					Mix_PlayChannel(-1, App->audio->effects[20], 0);
					App->particles->AddParticle(App->particles->spark, (c1->rect.x + c1->rect.w) - (c1->rect.x + c1->rect.w - c1->rect.x), c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test
					alredycollided2 = true;
					if (SDL_GetTicks() % 4 == 0 && !swordDropped)
						inputs.Push(IN_SWORD_FIGHT);
				}
			}

			if (c2->type == COLLIDER_ENEMY_ATTACK && (c1->type != COLLIDER_PLAYER_ATTACK || c1->attackType == 1 || c1->attackType == 2)) {
				int random = rand();
				aux = c2->delayEnemy;
				if (blocking && (current_state == ST_WALK_BACKWARD || current_state == ST_CROUCH || current_state == ST_WALK_FORWARD || crouching)) {
					if (c2->attackType == 3 || c2->attackType == 4) {
						if (random % 3 == 0) {
							Mix_PlayChannel(-1, App->audio->effects[20], 0);
						}

						else if (random % 3 == 1) {
							Mix_PlayChannel(-1, App->audio->effects[21], 0);

						}

						else {
							Mix_PlayChannel(-1, App->audio->effects[22], 0);
						}

						if (!playerFlip) {
							App->particles->AddParticle(App->particles->blocking, (c1->rect.x + c1->rect.w) - (c1->rect.x + c1->rect.w - c1->rect.x), c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test
							App->particles->AddParticle(App->particles->spark, (c1->rect.x + c1->rect.w) - (c1->rect.x + c1->rect.w - c1->rect.x), c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test
						}
						else {
							App->particles->AddParticle(App->particles->blocking, c2->rect.x + c2->rect.w, c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test
							App->particles->AddParticle(App->particles->spark, (c1->rect.x + c1->rect.w) - (c1->rect.x + c1->rect.w - c1->rect.x), c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test
						}
					}
					if (c2->attackType == 1 || c2->attackType == 2) {
						Mix_PlayChannel(-1, App->audio->effects[23], 0);

						if (!playerFlip) {
							App->particles->AddParticle(App->particles->blocking, (c1->rect.x + c1->rect.w) - (c1->rect.x + c1->rect.w - c1->rect.x), c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test

						}
						else {
							App->particles->AddParticle(App->particles->blocking, c2->rect.x + c2->rect.w, c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test

						}
					}
					if (crouching) {
						inputs.Push(IN_BLOCKING_CROUCH);

					}
					else
						inputs.Push(IN_BLOCKING);
				}
				else if (current_state != ST_CROUCH_BLOCK && current_state != ST_BLOCKING) {
					if (c2->attackType == 3 || c2->attackType == 4) {
						if (random % 3 == 0) {
							Mix_PlayChannel(-1, App->audio->effects[16], 0);
							App->particles->AddParticle(App->particles->bloodLow, (c1->rect.x + c1->rect.w) - (c1->rect.x + c1->rect.w - c1->rect.x), c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test
							Mix_PlayChannel(-1, App->audio->effects[2], 0);

						}

						else if (random % 3 == 1) {
							Mix_PlayChannel(-1, App->audio->effects[25], 0);
							App->particles->AddParticle(App->particles->bloodMid, (c1->rect.x + c1->rect.w) - (c1->rect.x + c1->rect.w - c1->rect.x), c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test
							Mix_PlayChannel(-1, App->audio->effects[27], 0);

						}

						else {
							Mix_PlayChannel(-1, App->audio->effects[26], 0);
							App->particles->AddParticle(App->particles->bloodHard, (c1->rect.x + c1->rect.w / 2), c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test
							Mix_PlayChannel(-1, App->audio->effects[28], 0);

						}

						if (!playerFlip) {
							App->particles->AddParticle(App->particles->slash, (c1->rect.x + c1->rect.w) - (c1->rect.x + c1->rect.w - c1->rect.x), c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test

						}
						else {
							App->particles->AddParticle(App->particles->slash, c2->rect.x + c2->rect.w, c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test
						}
					}
					else if (c2->attackType == 1 || c2->attackType == 2) {
						if (random % 2 == 0) {
							Mix_PlayChannel(-1, App->audio->effects[17], 0);
							Mix_PlayChannel(-1, App->audio->effects[28], 0);
						}

						else {
							Mix_PlayChannel(-1, App->audio->effects[27], 0);
							Mix_PlayChannel(-1, App->audio->effects[2], 0);

						}


						if (!playerFlip) {
							App->particles->AddParticle(App->particles->kick, (c1->rect.x + c1->rect.w) - (c1->rect.x + c1->rect.w - c1->rect.x), c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test
						}
						else {
							App->particles->AddParticle(App->particles->kick, c2->rect.x + c2->rect.w, c2->rect.y, playerFlip, COLLIDER_NONE); //Particle test
						}
					}
					if (App->player2->position.y < groundlevelaux) {
						inputs.Push(IN_FALL);
						airhit = true;
					}

					if (powActivated || App->player2->powActivated) {
						health += c2->damage * 3 / 2;
						if (App->player2->powActivated) {
							App->player2->powActivated = false;
							App->player2->powOff = true;
						}
						else if (powActivated) {
							powActivated = false;
							powOff = true;
						}
						else {
							powActivated = false;
							powOff = true;
							App->player2->powActivated = false;
							App->player2->powOff = true;
						}
					}
					else {
						health += c2->damage;
					}

			if (powActivated || App->player2->powActivated) {
				health += c2->damage * 3 / 2;
				if (App->player2->powActivated) {
					App->player2->powActivated = false;
					App->player2->powOff = true;
				}
				else if (powActivated) {
					powActivated = false;
					powOff = true;
				}
				else {
					powActivated = false;
					powOff = true;
					App->player2->powActivated = false;
					App->player2->powOff = true;
				}
			}
			else {
				health += c2->damage;
				
			}	
			score += c2->damage*2;
			powValue += 4;
			getsHit = true; doingAction = true;


				}
			}
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
			case ST_IDLE:
			{
				switch (last_input)
				{
				case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
				case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
				case IN_JUMP: state = ST_JUMP_NEUTRAL;  break;
				case IN_CROUCH_DOWN: state = ST_CROUCH; break;
				case IN_X:
					if (App->player->close)
						state = ST_PUNCH_CLOSE_STANDING;
					else
						state = ST_PUNCH_STANDING;
					punch_timer = SDL_GetTicks();
					blocking = false; break;
				case IN_KICK: state = ST_KICK_STANDING; punch_timer = SDL_GetTicks();  break;
				case IN_SPECIAL: state = ST_SPECIAL; punch_timer = SDL_GetTicks();  break;
				case IN_FALL:state = ST_FALLING; break;//new
				case IN_DEATH: state = ST_FALLING; break;
				case IN_GET_GRABBED:state = ST_GET_GRABBED; break;

				case IN_X_MID: state = ST_MID_PUNCH_STANDING; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_X_STRONG: state = ST_STRONG_PUNCH_STANDING; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_MID_KICK: state = ST_MID_KICK; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_STRONG_KICK: state = ST_STRONG_KICK; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_SWORD_GRAB: state = ST_SWORD_GRABBING; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_SIDE_STEP: state = ST_SIDE_STEPPING; break;
				case IN_SPRINT: state = ST_SPRINT; break;
				case IN_SWORD_FIGHT: state = ST_SWORD_FIGHT; break;

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
				case IN_X:
					if (close)
						state = ST_PUNCH_CLOSE_STANDING;
					else
						state = ST_PUNCH_STANDING;
					punch_timer = SDL_GetTicks();
					blocking = false; break;
				case IN_SPECIAL: state = ST_SPECIAL; punch_timer = SDL_GetTicks();  break;

				case IN_X_MID: state = ST_MID_PUNCH_STANDING; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_X_STRONG: state = ST_STRONG_PUNCH_STANDING; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_MID_KICK: state = ST_MID_KICK; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_STRONG_KICK: state = ST_STRONG_KICK; punch_timer = SDL_GetTicks(); blocking = false; break;


				case IN_KICK: state = ST_KICK_STANDING; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_CROUCH_DOWN: state = ST_CROUCH; blocking = false; break;
				case IN_FALL:state = ST_FALLING;  blocking = false;  break;
				case IN_GRAB:state = ST_GRAB; break;
				case IN_SECOND_GRAB:state = ST_SECOND_GRAB; break;
				case IN_GET_GRABBED:state = ST_GET_GRABBED; break;
				case IN_BLOCKING:state = ST_BLOCKING;
				case IN_SWORD_GRAB: state = ST_SWORD_GRABBING; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_SIDE_STEP: state = ST_SIDE_STEPPING; break;
				case IN_SPRINT: state = ST_SPRINT; break;

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

				case IN_CROUCH_DOWN: state = ST_CROUCH; blocking = false; break;
				case IN_FALL:state = ST_FALLING; blocking = false;  break;
				case IN_GRAB:state = ST_GRAB; break;
				case IN_SECOND_GRAB:state = ST_SECOND_GRAB; break;
				case IN_GET_GRABBED:state = ST_GET_GRABBED; break;
				case IN_BLOCKING:state = ST_BLOCKING; break;
				case IN_SPECIAL: state = ST_SPECIAL; punch_timer = SDL_GetTicks();  break;

				case IN_X:
					if (close)
						state = ST_PUNCH_CLOSE_STANDING;
					else
						state = ST_PUNCH_STANDING;
					punch_timer = SDL_GetTicks();
					blocking = false; break;
				case IN_KICK: state = ST_KICK_STANDING; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_X_MID: state = ST_MID_PUNCH_STANDING; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_X_STRONG: state = ST_STRONG_PUNCH_STANDING; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_MID_KICK: state = ST_MID_KICK; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_STRONG_KICK: state = ST_STRONG_KICK; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_SWORD_GRAB: state = ST_SWORD_GRABBING; punch_timer = SDL_GetTicks(); blocking = false; break;
				case IN_SIDE_STEP: state = ST_SIDE_STEPPING; break;
				case IN_SPRINT: state = ST_SPRINT; break;
				}
			}
			break;

			case ST_JUMP_NEUTRAL:
			{
				switch (last_input)
				{
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_X: state = ST_PUNCH_NEUTRAL_JUMP; punch_timer = SDL_GetTicks(); break;
				case IN_X_MID: state = ST_MID_PUNCH_NEUTRAL_JUMP; ; break;
				case IN_X_STRONG: state = ST_STRONG_PUNCH_NEUTRAL_JUMP;  break;
				case IN_KICK: state = ST_KICK_NEUTRAL_JUMP; punch_timer = SDL_GetTicks();  break;
				case IN_MID_KICK: state = ST_KICK_MID_NEUTRAL_JUMP; ; blocking = false; break;
				case IN_STRONG_KICK: state = ST_KICK_STRONG_NEUTRAL_JUMP; blocking = false; break;
				case IN_FALL:state = ST_FALLING; break;

				}
			}
			break;

			case ST_JUMP_FORWARD:
			{
				switch (last_input)
				{
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_FALL:state = ST_FALLING; break;
				case IN_X: state = ST_PUNCH_FORWARD_JUMP; break;
				case IN_X_MID: state = ST_MID_PUNCH_NEUTRAL_JUMP; break;
				case IN_X_STRONG: state = ST_STRONG_PUNCH_NEUTRAL_JUMP; break;
				case IN_KICK: state = ST_KICK_NEUTRAL_JUMP; punch_timer = SDL_GetTicks();  break;
				case IN_MID_KICK: state = ST_KICK_MID_NEUTRAL_JUMP; blocking = false; break;
				case IN_STRONG_KICK: state = ST_KICK_STRONG_NEUTRAL_JUMP; blocking = false; break;

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
				case IN_X_MID: state = ST_MID_PUNCH_NEUTRAL_JUMP; break;
				case IN_X_STRONG: state = ST_STRONG_PUNCH_NEUTRAL_JUMP;  break;
				case IN_MID_KICK: state = ST_KICK_MID_NEUTRAL_JUMP;  blocking = false; break;
				case IN_STRONG_KICK: state = ST_KICK_STRONG_NEUTRAL_JUMP; blocking = false; break;
				case IN_FALL:state = ST_FALLING; break;

				}
			}
			break;

			case ST_PUNCH_NEUTRAL_JUMP:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_FALL:state = ST_FALLING; break;

				}
			}
			break;
			case ST_MID_PUNCH_NEUTRAL_JUMP:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_FALL:state = ST_FALLING; break;
				}
			}
			break;
			case ST_STRONG_PUNCH_NEUTRAL_JUMP:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_FALL:state = ST_FALLING; break;

				}
			}
			break;

			case ST_KICK_NEUTRAL_JUMP:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_FALL:state = ST_FALLING; break;

				}
			}
			break;
			case ST_KICK_MID_NEUTRAL_JUMP:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; break;
				case IN_JUMP_FINISH: state = ST_IDLE; break;
				case IN_FALL:state = ST_FALLING; break;

				}
			}
			break;
			case ST_KICK_STRONG_NEUTRAL_JUMP:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_JUMP_NEUTRAL; break;
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
				case IN_SWORD_FIGHT: state = ST_SWORD_FIGHT; break;
				}
			}
			break;
			case ST_PUNCH_CLOSE_STANDING:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_IDLE; break;
				case IN_FALL:state = ST_FALLING; break;
				case IN_SWORD_FIGHT: state = ST_SWORD_FIGHT; break;

				}
			}
			break;
			case ST_MID_PUNCH_STANDING:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_IDLE; break;
				case IN_FALL:state = ST_FALLING; break;
				case IN_SWORD_FIGHT: state = ST_SWORD_FIGHT; break;

				}
			}
			break;
			case ST_STRONG_PUNCH_STANDING:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_IDLE; break;
				case IN_FALL:state = ST_FALLING; break;
				case IN_SWORD_FIGHT: state = ST_SWORD_FIGHT; break;

				}
			}
			break;

			case ST_CROUCH:
			{
				switch (last_input)
				{
				case IN_CROUCH_UP: state = ST_IDLE; break;
				case IN_X: state = ST_PUNCH_CROUCH; break;
				case IN_X_MID: state = ST_PUNCH_MID_CROUCH; break;
				case IN_X_STRONG: state = ST_PUNCH_STRONG_CROUCH; break;
				case IN_MID_KICK: state = ST_KICK_MID_CROUCH; break;
				case IN_STRONG_KICK: state = ST_KICK_STRONG_CROUCH; break;
				case IN_KICK: state = ST_KICK_CROUCH; break;
				case IN_FALL:state = ST_FALLING; break;
				case IN_BLOCKING_CROUCH:state = ST_CROUCH_BLOCK; break;
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

			case ST_KICK_MID_CROUCH:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_CROUCH; break;
				case IN_FALL:state = ST_FALLING; break;

				}
				break;
			}
			case ST_KICK_STRONG_CROUCH:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_CROUCH; break;
				case IN_FALL:state = ST_FALLING; break;

				}
				break;
			}
			case ST_PUNCH_CROUCH:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_CROUCH; break;
				case IN_FALL:state = ST_FALLING; break;
				case IN_SWORD_FIGHT: state = ST_SWORD_FIGHT; break;

				}
				break;
			}
			case ST_PUNCH_MID_CROUCH:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_CROUCH; break;
				case IN_FALL:state = ST_FALLING; break;
				case IN_SWORD_FIGHT: state = ST_SWORD_FIGHT; break;

				}
				break;
			}
			case ST_PUNCH_STRONG_CROUCH:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_CROUCH; break;
				case IN_FALL:state = ST_FALLING; break;
				case IN_SWORD_FIGHT: state = ST_SWORD_FIGHT; break;

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
				break;
			}
			case ST_MID_KICK:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_IDLE; break;
				case IN_FALL:state = ST_FALLING; break;

				}
				break;
			}
			case ST_STRONG_KICK:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_IDLE; break;
				case IN_FALL:state = ST_FALLING; break;

				}
				break;
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

			case ST_KICK_BACKWARD_JUMP:
			{
				switch (last_input)
				{
				case IN_PUNCH_FINISH: state = ST_IDLE; break;
				case IN_JUMP_FINISH:state = ST_IDLE; break;

				}
			}
			break;

			case ST_GRAB:
			{
				switch (last_input)
				{
				case IN_NOT_GRAB: state = ST_IDLE; break;
				case IN_GRABBED:state = ST_GRABBING; break;
				case IN_GRAB_FINISH: state = ST_IDLE; break;

				}
			}
			break;
			case ST_SECOND_GRAB:
			{
				switch (last_input)
				{
				case IN_NOT_GRAB: state = ST_IDLE; break;
				case IN_GRABBED:state = ST_SECOND_GRABBING; break;
				case IN_GRAB_FINISH: state = ST_IDLE; break;

				}
			}
			break;

			case ST_GRABBING:
			{
				switch (last_input)
				{
				case IN_GRAB_FINISH: state = ST_IDLE; break;

				}
			}
			break;
			case ST_SECOND_GRABBING:
			{
				switch (last_input)
				{
				case IN_GRAB_FINISH: state = ST_IDLE; break;

				}
			}
			break;

			case ST_GET_GRABBED:
			{
				switch (last_input)
				{
				case IN_GRABBED_FINISH: state = ST_FALLING; break;

				}
			}
			break;
			case ST_BLOCKING:
			{
				switch (last_input) {

				case IN_BLOCK_FINISH: state = ST_IDLE; break;
				}
			}
			break;

			case ST_CROUCH_BLOCK:
			{
				switch (last_input)
				{
				case IN_BLOCK_FINISH: state = ST_CROUCH; break;
				}
			}
			break;
			case ST_SWORD_FIGHT:
			{
				switch (last_input)
				{
				case IN_SWORD_FIGHT_LOSE: state = ST_FALLING; break;
				case IN_SWORD_FIGHT_WIN: state = ST_JUMP_BACKWARD; break;
				case IN_SWORD_FIGHT_DRAW: state = ST_JUMP_BACKWARD; break;
				case IN_NOT_SWORD_FIGHT: state = ST_IDLE;

				}
			}
			break;

			case ST_SWORD_GRABBING:
			{
				switch (last_input)
				{

				case IN_SWORD_GRABBED: state = ST_IDLE; break;

				}
			}
			break;

			case ST_SIDE_STEPPING:
			{
				switch (last_input)
				{

				case IN_JUMP_FINISH: state = ST_IDLE; break;

				}
			}
			break;

			case ST_SPRINT:
			{
				switch (last_input)
				{

				case IN_SPRINT_END: state = ST_SPRINT_END; break;
				case IN_SWORD_FIGHT: state = ST_SWORD_FIGHT; break;


				}
			}
			break;

			case ST_SPRINT_END:
			{
				switch (last_input)
				{

				case IN_SPRINT_END: state = ST_IDLE; break;

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
