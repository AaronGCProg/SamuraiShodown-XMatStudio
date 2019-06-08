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
#include <cstdlib>
#include <time.h>


#include<math.h>


ModulePlayer2::ModulePlayer2()
{
	//Attack types: 1->low punch/kick, 2->heavy punch/kick, 3->low sword, 4->mid sword, 5->punch that knocks down, 6-> sword that knocks down, 7->special (both specials knock down).
	//The four numers at the end of the attacks are: damage, playerDelay (both knockdown & delay frames), enemyDelay & attackType.


	// JUBEI ANIM
	const int idleCollider = 2;//Collider num for the idle animation
	SDL_Rect idleHitbox[idleCollider] = { { 25, 0, 40, 75 },{ 40, 75, 20, 20 } };
	COLLIDER_TYPE idleCollType[idleCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE backCollType[backCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* backCallBack[backCollider] = { {this},{this} };

	// walk backward animation 
	backward.PushBack({ 458,127,98,109 }, 9, { 43,1 }, backCollider, backHitbox, backCollType, backCallBack, 0, 0, 0, 0);
	backward.PushBack({ 277,137,91,99 }, 6, { 44,1 }, backCollider, backHitbox, backCollType, backCallBack, 0, 0, 0, 0);
	backward.PushBack({ 368,140,91,96 }, 9, { 49,1 }, backCollider, backHitbox, backCollType, backCallBack, 0, 0, 0, 0);
	backward.PushBack({ 277,137,91,99 }, 6, { 44,1 }, backCollider, backHitbox, backCollType, backCallBack, 0, 0, 0, 0);


	//backward.speed = 0.1f;


	const int forCollider = 2;//Collider num for the forward animation
	SDL_Rect forHitbox[forCollider] = { { 32, 0, 40, 75 },{ 33, 70, 20, 20 } };
	COLLIDER_TYPE forCollType[forCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE kickCollType[kickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	COLLIDER_TYPE kickCollType2[kickCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE punchCollType[punchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* punchCallBack[punchCollider] = { {this},{this},{this} };

	SDL_Rect punchHitbox2[punchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE punchCollType2[punchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY}, };
	Module* punchCallBack2[punchCollider2] = { {this},{this} };

	// Punch animation 
	punch.PushBack({ 1,721,86,97 }, 3, { 28,3 }, punchCollider2, punchHitbox2, punchCollType2, punchCallBack2, 20, 9, 25, 3);
	punch.PushBack({ 88,729,130,89 }, 4, { 28,3 }, punchCollider, punchHitbox, punchCollType, punchCallBack, 20, 9, 25, 3);
	punch.PushBack({ 219,729,150,90 }, 8, { 28,3 }, punchCollider, punchHitbox, punchCollType, punchCallBack, 20, 9, 25, 3);
	punch.PushBack({ 370,729,137,89 }, 6, { 28,3 }, punchCollider2, punchHitbox2, punchCollType2, punchCallBack2, 20, 9, 25, 3);
	punch.PushBack({ 508,729,96,89 }, 5, { 28,3 }, punchCollider2, punchHitbox2, punchCollType2, punchCallBack2, 20, 9, 25, 3);
	//punch.speed = 0.2f;


	const int jumpCollider = 2;//Collider num for the jump animation
	SDL_Rect jumpHitbox[jumpCollider] = { { 10, 10, 40, 65 },{ 20, 65, 20, 20 } };
	COLLIDER_TYPE jumpCollType[jumpCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE jumpKickCollType[jumpKickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpKickCallBack[jumpKickCollider] = { {this},{this},{this} };

	const int jumpKickCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpKickHitbox2[jumpKickCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpKickCollType2[jumpKickCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE jumpPunchCollType[jumpPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpPunchCallBack[jumpPunchCollider] = { {this},{this},{this} };

	const int jumpPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpPunchHitbox2[jumpPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpPunchCollType2[jumpPunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE jumpForwardPunchCollType[jumpForwardPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpForwardPunchCallBack[jumpForwardPunchCollider] = { {this},{this},{this} };




	const int crouchCollider = 2;//Collider num for the jump kick animation
	SDL_Rect crouchHitbox2[crouchCollider] = { { 30, 0, 30, 55 },{40, 0, 20, 20 } };
	SDL_Rect crouchHitbox[crouchCollider] = { { 10, 0, 40, 55 },{ 30, 50, 20, 20 } };
	COLLIDER_TYPE crouchCollType[crouchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE crouchPunchCollType[crouchPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* crouchPunchCallBack[crouchPunchCollider] = { {this},{this},{this} };

	const int crouchPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox2[crouchPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchPunchCollType2[crouchPunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE crouchKickCollType[crouchKickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
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
	COLLIDER_TYPE tornadoCollType[tornadoCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE midkickCollType[midkickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	COLLIDER_TYPE midkickCollType2[midkickCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE strongkickCollType[strongkickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	COLLIDER_TYPE strongkickCollType2[strongkickCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE midpunchCollType[midpunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* midpunchCallBack[midpunchCollider] = { {this},{this},{this} };

	SDL_Rect midpunchHitbox2[midpunchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE midpunchCollType2[midpunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY}, };
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
	COLLIDER_TYPE strongpunchCollType[strongpunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* strongpunchCallBack[strongpunchCollider] = { {this},{this},{this} };

	SDL_Rect strongpunchHitbox2[strongpunchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE strongpunchCollType2[strongpunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY}, };
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
	COLLIDER_TYPE jumpmidPunchCollType[jumpmidPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpmidPunchCallBack[jumpmidPunchCollider] = { {this},{this},{this} };

	const int jumpmidPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpmidPunchHitbox2[jumpmidPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpmidPunchCollType2[jumpmidPunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* jumpmidPunchCallBack2[jumpmidPunchCollider2] = { {this},{this} };

	jumpmidPunch.PushBack({ 1,819,83,87 }, 12, { 31, 2 }, jumpmidPunchCollider2, jumpmidPunchHitbox2, jumpmidPunchCollType2, jumpmidPunchCallBack2, 15, 6, 20, 3);
	jumpmidPunch.PushBack({ 85,824,79,82 }, 12, { 31, 2 }, jumpmidPunchCollider, jumpmidPunchHitbox, jumpmidPunchCollType, jumpmidPunchCallBack, 15, 6, 20, 3);
	jumpmidPunch.PushBack({ 165,835,73,71 }, 10, { 31, 2 }, jumpmidPunchCollider, jumpmidPunchHitbox, jumpmidPunchCollType, jumpmidPunchCallBack, 15, 6, 20, 3);
	jumpmidPunch.PushBack({ 1,1160,155,70 }, 12, { 31, 2 }, jumpmidPunchCollider2, jumpmidPunchHitbox2, jumpmidPunchCollType2, jumpmidPunchCallBack2, 15, 6, 20, 3);
	jumpmidPunch.PushBack({ 396,837,157,69 }, 12, { 31, 2 }, jumpmidPunchCollider, jumpmidPunchHitbox, jumpmidPunchCollType, jumpmidPunchCallBack, 15, 6, 20, 3);
	jumpmidPunch.PushBack({ 554,842,147,64 }, 12, { 31, 2 }, jumpmidPunchCollider, jumpmidPunchHitbox, jumpmidPunchCollType, jumpmidPunchCallBack, 15, 6, 20, 3);

	const int jumpstrongPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpstrongPunchHitbox[jumpstrongPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 55, 27, 90, 10 } };
	COLLIDER_TYPE jumpstrongPunchCollType[jumpstrongPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpstrongPunchCallBack[jumpstrongPunchCollider] = { {this},{this},{this} };

	const int jumpstrongPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpstrongPunchHitbox2[jumpstrongPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpstrongPunchCollType2[jumpstrongPunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE jumpmidKickCollType[jumpmidKickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpmidKickCallBack[jumpmidKickCollider] = { {this},{this},{this} };

	const int jumpmidKickCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpmidKickHitbox2[jumpmidKickCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpmidKickCollType2[jumpmidKickCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* jumpmidKickCallBack2[jumpmidKickCollider2] = { {this},{this} };

	jumpmidKick.PushBack({ 1102,21,71,80 }, 12, { 31,2 }, jumpmidKickCollider2, jumpmidKickHitbox2, jumpmidKickCollType2, jumpmidKickCallBack2, 15, 6, 20, 1);
	jumpmidKick.PushBack({ 1160,146,122,96 }, 60, { 31,2 }, jumpmidKickCollider, jumpmidKickHitbox, jumpmidKickCollType, jumpmidKickCallBack, 15, 6, 20, 1);
	jumpmidKick.PushBack({ 1102,21,71,80 }, 18, { 31,2 }, jumpmidKickCollider2, jumpmidKickHitbox2, jumpmidKickCollType2, jumpmidKickCallBack2, 15, 6, 20, 1);


	const int jumpstrongKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect jumpstrongKickHitbox[jumpstrongKickCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 90, 10, 25, 20 } };
	COLLIDER_TYPE jumpstrongKickCollType[jumpstrongKickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpstrongKickCallBack[jumpstrongKickCollider] = { {this},{this},{this} };

	const int jumpstrongKickCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpstrongKickHitbox2[jumpstrongKickCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpstrongKickCollType2[jumpstrongKickCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE crouchmidPunchCollType[crouchmidPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* crouchmidPunchCallBack[crouchmidPunchCollider] = { {this},{this},{this} };

	const int crouchmidPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect crouchmidPunchHitbox2[crouchmidPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchmidPunchCollType2[crouchmidPunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE crouchstrongPunchCollType[crouchstrongPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* crouchstrongPunchCallBack[crouchstrongPunchCollider] = { {this},{this},{this} };

	const int crouchstrongPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect crouchstrongPunchHitbox2[crouchstrongPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchstrongPunchCollType2[crouchstrongPunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE crouchmidKickCollType[crouchmidKickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
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
	COLLIDER_TYPE crouchstrongKickCollType[crouchstrongKickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
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
	COLLIDER_TYPE shortPunchCollType[shortPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* shortPunchCallBack[shortPunchCollider] = { {this},{this},{this} };

	SDL_Rect shortPunchHitbox2[shortPunchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE shortPunchCollType2[shortPunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY}, };
	Module* shortPunchCallBack2[shortPunchCollider2] = { {this},{this} };

	// Punch animation 
	shortPunch.PushBack({ 1417,4,82,123 }, 25, { 31,2 }, shortPunchCollider, shortPunchHitbox, shortPunchCollType, shortPunchCallBack, 20, 9, 25, 3);

	const int grabCollider = 3;//Collider num for the punch animation
	const int grabCollider2 = 2;//Collider num for the punch animation
	SDL_Rect grabHitbox[grabCollider] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE grabCollType[grabCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* grabCallBack[grabCollider] = { {this},{this} };

	COLLIDER_TYPE grabCollType2[grabCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY}, };
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
	healthAnim = 0;
	critical = false;

	graphics = App->textures->Load("Assets/Sprites/Jubei2.png"); // arcade version
	//ui = App->textures->Load("Assets/Sprites/UIspritesheet2.png"); // health bar 
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
	//App->textures->Unload(ui);


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
	float player2scale = App->render->escala - (PLAYER_ESCALE*(App->render->escala - 0.5)); //sets the player scale to 1 when he's in zoomin and to 0.75 when zoomout
	//the PLAYER ESCALE is to adjust the real scale of the player
	current_animation = &idle;
	int speed;
	if (App->render->escala < 1.25)speed = 1;
	else speed = 2;

	float jumpingescala;
	if (App->render->escala < 1.25)jumpingescala = 0.75f;
	else jumpingescala = 1;

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



	if (invencibleframes) {
		if (SDL_GetTicks() - (invencibleaux) >= 350) {
			invencibleframes = false;
		}
	}

	if (!playerFlip) {
		if (App->player->position.x - position.x < 110)
			close = true;
		else
			close = false;
	}
	else {
		if (position.x - App->player->position.x < 110)
			close = true;
		else
			close = false;
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
		if (!App->player2->doingAction) {

			if (App->player2->position.x < App->player->position.x) {
				App->player2->playerFlip = false;
			}
			else {
				App->player2->playerFlip = true;
			}
		}


		if (!doingAction) {
			switch (state)
			{
			case ST_IDLE2:
				LOG("IDLE\n");
				current_animation = &idle;
				break;
			case ST_WALK_FORWARD:
				LOG("FORWARD >>>\n");
				if (!playerFlip) {
					current_animation = &forward;
					position.x += speed + 1*speed;
				}
				else {
					current_animation = &backward;
					position.x += speed;
					
				}
				break;
			case ST_WALK_BACKWARD:
				LOG("BACKWARD <<<\n");
				if (!playerFlip) {
					current_animation = &backward;
					position.x -= speed;
					
				}
				else {
					current_animation = &forward;
					position.x -= speed + 1*speed;
				}
				break;
			case ST_JUMP_NEUTRAL2:
				LOG("JUMPING NEUTRAL ^^^^\n");
				jumping = true; doingAction = true;
				Mix_PlayChannel(-1, App->audio->effects[15], 0);
				break;
			case ST_JUMP_FORWARD2:
				LOG("JUMPING FORWARD ^^>>\n");
				jumpdiagonal = true;
				Mix_PlayChannel(-1, App->audio->effects[15], 0);
				doingAction = true;
				break;
			case ST_JUMP_BACKWARD2:
				LOG("JUMPING BACKWARD ^^<<\n");
				jumpleft = true;
				jumpdiagonal = true;
				Mix_PlayChannel(-1, App->audio->effects[15], 0);
				doingAction = true;
				break;
			case ST_CROUCH2:
				LOG("CROUCHING ****\n");
				crouching = true;
				doingAction = true;
				break;
			case ST_PUNCH_CROUCH2:
				LOG("PUNCH CROUCHING **++\n");
				crouchpunching = true; doingAction = true;
				break;
			case ST_KICK_CROUCH2:
				LOG("KICK CROUCHING **++\n");
				crouchkicking = true; doingAction = true;
				break;
			case ST_PUNCH_STANDING2:
				LOG("PUNCH STANDING ++++\n");
				punching = true; doingAction = true;
				break;
			case ST_KICK_STANDING2:
				LOG("KICK STANDING ----\n");
				kicking = true; doingAction = true;
				break;

			case ST_GET_GRABBED2:
				gettingGrabbed = true; doingAction = true;
				break;
			case ST_GRAB:
				LOG("KICK STANDING ----\n");
				grabbing = true; doingAction = true;
				break;
			case ST_BLOCKING2:
				blockingAction = true; doingAction = true;
				break;
			case ST_CROUCH_BLOCK2:
				blockingActionCrouch = true; doingAction = true;
				break;
			case ST_SPECIAL2:
				LOG("SPECIAL OwwwwO\n");
				tornading = true; doingAction = true;
				Mix_PlayChannel(-1, App->audio->effects[0], 0);
				Mix_PlayChannel(-1, App->audio->effects[1], 0);
				if (playerFlip) {
					App->particles->tornadoHao.speed.x = -3;
					App->particles->AddParticle(App->particles->tornadoHao, (int)(position.x - (140 * player2scale)), (int)(position.y - (44 * player2scale)), playerFlip, COLLIDER_ENEMY_SHOT);

				}
				else {
					App->particles->tornadoHao.speed.x = +3;
					App->particles->AddParticle(App->particles->tornadoHao, (int)(position.x + (18 * player2scale)), (int)(position.y - (44 * player2scale)), playerFlip, COLLIDER_ENEMY_SHOT);
				}
				break;
			case ST_FALLING2://new
				falling = true; doingAction = true;
				break;
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

	if (grabbing) {
		if (App->player->close || current_state == ST_GRABBING) {
			App->player->inputs.Push(IN_GET_GRABBED);
			if (App->player->current_state == ST_GET_GRABBED) {
				App->player->doingAction = true;
				p2inputs.Push(IN_GRABBED2);
				//AQUI PASA LA ANIMACION Y LOGICA

				//if(grab.GetAnimEnd() == true){
				App->player->health += 20;
				p2inputs.Push(IN_GRAB_FINISH2);
				grabbing = false; doingAction = false;
				App->player->getGrabbed = false; App->player->doingAction = false;
				App->player->inputs.Push(IN_GRABBED_FINISH);
				//}
			}
			else {
				p2inputs.Push(IN_NOT_GRAB2);
				grabbing = false; doingAction = false;

			}
		}
		else {
			p2inputs.Push(IN_NOT_GRAB2);
			grabbing = false; doingAction = false;
		}
	}
	if (gettingGrabbed) {
		current_animation = &getGrab;

		if (getGrab.GetAnimEnd() == true || falling) {
			getGrab.SetAnimEnd(false);
			gettingGrabbed = false;
			getGrab.Reset();

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

		if (current_animation->current_frame > 6 && current_animation->current_frame < 8 && !App->player->getsHit && !audioPlayed) {
			Mix_PlayChannel(-1, App->audio->effects[18], 0);
			audioPlayed = true;
		}
		if (punch.GetAnimEnd() == true) {
			punching = false; doingAction = false; punch.SetAnimEnd(false);
			audioPlayed = false;
			p2inputs.Push(IN_PUNCH_FINISH2);

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

	if (blockingAction) {
		//set punch anim

		current_animation = &blockingIdle;

		blocking = true;

		int internalAux = aux + 1;
		if (position.x < 50 || position.x > 310) {
			if (App->player2->playerFlip) {
				if (aux > 0 && aux < internalAux) {
					App->player2->position.x += (int)(aux*player2scale);
					aux--;
				}
			}
			else if (!App->player2->playerFlip) {
				if (aux > 0 && aux < internalAux)
					App->player2->position.x -= (int)(aux*player2scale);
				aux--;
			}
		}
		else {
			if (playerFlip) {
				if (aux > 0 && aux < internalAux) {
					position.x += (int)(aux*player2scale);
					aux--;
				}
			}
			else if (!playerFlip) {
				if (aux > 0 && aux < internalAux)
					position.x -= (int)(aux*player2scale);
				aux--;

			}
		}

		if (blockingIdle.GetAnimEnd() == true) {
			p2inputs.Push(IN_BLOCK_FINISH2);
			blocking = false; doingAction = false; blockingIdle.SetAnimEnd(false); crouchBlock.SetAnimEnd(false);
			blockingAction = false;
			invencibleframes = true;
			invencibleaux = SDL_GetTicks();
			invencibleTotalTime = 550;
		}

	}
	if (blockingActionCrouch) {
		//set punch anim
		current_animation = &crouchBlock;

		blocking = true;

		int internalAux = aux + 1;
		if (position.x < 50 || position.x > 310) {
			if (App->player2->playerFlip) {
				if (aux > 0 && aux < internalAux) {
					App->player2->position.x += (int)(aux*player2scale);
					aux--;
				}
			}
			else if (!App->player2->playerFlip) {
				if (aux > 0 && aux < internalAux)
					App->player2->position.x -= (int)(aux*player2scale);
				aux--;
			}
		}
		else {
			if (playerFlip) {
				if (aux > 0 && aux < internalAux) {
					position.x += (int)(aux*player2scale);
					aux--;
				}
			}
			else if (!playerFlip) {
				if (aux > 0 && aux < internalAux)
					position.x -= (int)(aux*player2scale);
				aux--;

			}
		}

		if (crouchBlock.GetAnimEnd() == true) {
			p2inputs.Push(IN_BLOCK_FINISH2);
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

		position.y = groundlevelaux+( - (JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY)*pow(jumpingframe, 2)))*jumpingescala;//MRUA formula
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
			p2inputs.Push(IN_JUMP_FINISH2);
			jumpKick.Reset();
			jumpPunch.Reset();
			jump.Reset();
		}
		jumpingframe++;
	}
	if (jumpdiagonal)
	{
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

		if (JumpPunching)
			current_animation = &jumpPunch;
		else if (JumpKicking)
			current_animation = &jumpKick;
		else
			current_animation = &jumpFw; //Jumpforward animation


		position.y = groundlevelaux+( - (JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY)*pow(jumpingframe, 2)))*jumpingescala;//MRUA formula
		if (jumpleft)
			position.x -= 4*jumpingescala;
		else
			position.x += 4*jumpingescala;
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
		jumpingframe++;
	}

	if (falling)//new
	{
		current_animation = &fall;
		if (fall_bounces > FALLBOUNCES) { position.y = groundlevelaux; delay++; }
		else
		{

			position.y = groundlevelaux+( - (10 * jumpingframe) + (0.5*(0.5*JUMP_INIT_AY + (0.2f*(fall_bounces + 1)))*pow(jumpingframe, 2)))*jumpingescala;//MRUA formula
			if (playerFlip)position.x += 2 - (fall_bounces);
			else position.x -= (2 - (fall_bounces))*jumpingframe;

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
			p2inputs.Push(IN_FALL_FINISH2);
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
			p2inputs.Push(IN_JUMP_FINISH2);
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
				colisionadores[i] = App->collision->AddCollider({ (int)(position.x + (playerPivotX - r.w - r.x)*player2scale) , (int)(position.y + (playerPivotY - r.h - r.y)*player2scale),(int)(r.w*player2scale),(int)(r.h*player2scale) }, COLLIDER_NONE, current_animation->damage, current_animation->playerDelay, current_animation->enemyDelay, current_animation->attackType, current_animation->callback[i]);
			else
				colisionadores[i] = App->collision->AddCollider({ (int)(position.x + (r.x - playerPivotX)*player2scale) , (int)(position.y + (playerPivotY - r.h - r.y)*player2scale),(int)(r.w*player2scale),(int)(r.h*player2scale) }, COLLIDER_NONE, current_animation->damage, current_animation->playerDelay, current_animation->enemyDelay, current_animation->attackType, current_animation->callback[i]);

		else if (!godMode2 || current_animation->tipo[i] != COLLIDER_PLAYER)
			if (playerFlip)
				colisionadores[i] = App->collision->AddCollider({ (int)(position.x + (playerPivotX - r.w - r.x)*player2scale) , (int)(position.y + (playerPivotY - r.h - r.y)*player2scale),(int)(r.w*player2scale),(int)(r.h*player2scale) }, current_animation->tipo[i], current_animation->damage, current_animation->playerDelay, current_animation->enemyDelay, current_animation->attackType, current_animation->callback[i]);
			else
				colisionadores[i] = App->collision->AddCollider({ (int)(position.x + (r.x - playerPivotX)*player2scale) , (int)(position.y + (playerPivotY - r.h - r.y)*player2scale),(int)(r.w*player2scale),(int)(r.h*player2scale) }, current_animation->tipo[i], current_animation->damage, current_animation->playerDelay, current_animation->enemyDelay, current_animation->attackType, current_animation->callback[i]);
	}
	r = current_animation->GetCurrentFrame();//returns the rectangle displaying the current animation

	SDL_Rect shadowrect = { 0,0,70,14 };
	//Blits player + collisions + shadow_____________
	if (playerFlip)
	{		//blit if player is flipped(compensates for pivot)
		if (showingshadow) { App->render->Blit(shadow, position.x - (39 * player2scale), 190, playerFlip, &shadowrect, 1.0, true, true, true); showingshadow = false; }//shadow semitransparent
		else showingshadow = true;
		App->render->Blit(graphics, position.x - (r.w - playerPivotX)*player2scale, position.y + (playerPivotY - r.h) * player2scale, playerFlip, &r, 1.0, true, true, true); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)
	}
	else
	{   //blit if player is NOT flipped
		if (showingshadow) { App->render->Blit(shadow, position.x - (31 * player2scale), 190, playerFlip, &shadowrect, 1.0, true, true, true); showingshadow = false; }//shadow semitransparent
		else showingshadow = true;
		App->render->Blit(graphics, position.x - (playerPivotX*player2scale), position.y + ((playerPivotY - r.h)*player2scale), playerFlip, &r, 1.0, true, true, true); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)
	}

	if(!powActivated)
		SDL_SetTextureColorMod(graphics, 255, 255 - (powValue * 6), 255 - (powValue * 6));
	else
		SDL_SetTextureColorMod(graphics, 255, 30, 30);

	if (health > healthAnim)
		healthAnim++;

	if ((App->fight->showHealthBar) == true) {
		SDL_Rect healthBar = { 90, 81, 134, 15 };
		App->render->Blit(App->interface->ui, 167, 15, false, &healthBar, NULL, true);
		if (HEALTH_VALUE > health + 50) {
			SDL_Rect healthValue = { 90, 97, HEALTH_VALUE - healthAnim, 9 };
			App->render->Blit(App->interface->ui, 168, 17, false, &healthValue, NULL, true);
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

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2) {
	if (!godMode2 && !blocking) {
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
			if (blocking && (current_state == ST_WALK_BACKWARD2 || current_state == ST_CROUCH2)) {
				if (crouching)
					p2inputs.Push(IN_BLOCKING_CROUCH2);
				else
					p2inputs.Push(IN_BLOCKING2);
			}
			else {
				health += 25;
				powValue += 2;
				p2inputs.Push(IN_FALL2);
				if (App->player2->position.y < groundlevelaux) {
					p2inputs.Push(IN_FALL2);
					airhit = true;

				}
			}
		}
		if (c2->type == COLLIDER_PLAYER_ATTACK) {
			int random = rand();
			aux = c2->delayEnemy;
			if (blocking && (current_state == ST_WALK_BACKWARD2 || current_state == ST_CROUCH2 || current_state == ST_WALK_FORWARD2 || crouching)) {
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
					p2inputs.Push(IN_BLOCKING_CROUCH2);

				}
				else
					p2inputs.Push(IN_BLOCKING2);
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
					p2inputs.Push(IN_FALL2);
					airhit = true;
				}
				
				if (powActivated || App->player->powActivated) {
					health += c2->damage * 3 / 2;
					App->player2->powActivated = false;
					App->player2->powOff = true;
				}
				else {
					health += c2->damage;
				}

				powValue += 4;
				getsHit = true; doingAction = true;

			}
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
			if (App->input->Controller_player1_Connected) {
				if (App->input->Controller_player1_LAxisX > DEATHZONE) {
					if (App->player->playerFlip)
						App->player->blocking = true;
					else
						App->player->blocking = false;
					right = true;
					if (left) {
						left = false;
						inputs.Push(IN_RIGHT_UP);
					}
				}
				else if (App->input->Controller_player1_LAxisX < -DEATHZONE) {

					if(!App->player->playerFlip)
						App->player->blocking = true;
					else
						App->player->blocking = false;
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
					if (App->input->Controller_player1_LAxisY > -DEATHZONE && App->input->Controller_player1_LAxisX < DEATHZONE)
						App->player->blocking = true;
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
					bool attacked = false;

					 if (App->input->CheckKick(25, 0, App->player->playerFlip) == true || App->input->controller_player1_A_pressed == true) {
						 inputs.Push(IN_STRONG_KICK);
						 attacked = true;
					 }

					 if (App->input->CheckThrow1(40, 0, App->player->playerFlip) == true && App->player->close == true) {
						 inputs.Push(IN_GRAB);
						 attacked = true;
					 }
					if(!attacked)
						inputs.Push(IN_MID_KICK);


				}


				if (App->input->controller_player1_A_pressed == true) {
					bool attacked = false;
					 if (App->input->CheckKick(25, 0, App->player->playerFlip) == true || App->input->controller_player1_B_pressed == true) {
						 inputs.Push(IN_STRONG_KICK);
						 attacked = true;
					 }
					if (!attacked)
						inputs.Push(IN_KICK);


				}
				if (App->input->controller_player1_X_pressed == true ) {
					bool attacked = false;
					if (App->input->CheckTornado(50, 0, App->player->playerFlip) == true) {
						inputs.Push(IN_SPECIAL);
						attacked = true;
					}

					 if (App->input->CheckPunch(25, 0, App->player->playerFlip) == true || App->input->controller_player1_Y_pressed == true) {
						 inputs.Push(IN_X_STRONG);
						 attacked = true;
					 }
					 if (!attacked) {
						 inputs.Push(IN_X);
					 }


				}
				if (App->input->controller_player1_Y_pressed == true ) {
					bool attacked = false;
					if (App->input->CheckTornado(50, 0, App->player->playerFlip) == true) {
						inputs.Push(IN_SPECIAL);
						attacked = true;

					}

					 if (App->input->CheckPunch(25, 0, App->player->playerFlip) == true || App->input->controller_player1_X_pressed == true) {
						inputs.Push(IN_X_STRONG);
						attacked = true;
					}
					 if (!attacked) {
						 inputs.Push(IN_X_MID);
					 }


				}

				if (App->input->controller_player1_RightShoulder_pressed > DEATHZONE) {

					inputs.Push(IN_GRAB);

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

					if (App->input->CheckTornado(90, 1, playerFlip) == true)
						p2inputs.Push(IN_SPECIAL2);



					else if (App->input->CheckPunch(1, 1, playerFlip) == true)
						p2inputs.Push(IN_X2);;

				}


				if (App->input->controller_player2_A_pressed == true) {

					if (App->input->CheckTornado(90, 1, playerFlip) == true)
						p2inputs.Push(IN_SPECIAL2);



					else if (App->input->CheckPunch(1, 1, playerFlip) == true)
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

		while (SDL_PollEvent(&event2) != 0) {}

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
			case IN_X2:
				if (App->player2->close)
					state = ST_PUNCH_CLOSE_STANDING2;
				else
					state = ST_PUNCH_STANDING2;
				p2punch_timer = SDL_GetTicks();
			blocking = false; break;			case IN_KICK2: state = ST_KICK_STANDING2; p2punch_timer = SDL_GetTicks();  break;
			case IN_SPECIAL2: state = ST_SPECIAL2; p2punch_timer = SDL_GetTicks();  break;
			case IN_FALL2:state = ST_FALLING2; break;//new
			case IN_DEATH2: state = ST_FALLING2; break;
			case IN_GET_GRABBED2:state = ST_GET_GRABBED2; break;

			case IN_X_MID2: state = ST_MID_PUNCH_STANDING2; p2punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_X_STRONG2: state = ST_STRONG_PUNCH_STANDING2; p2punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_MID_KICK2: state = ST_MID_KICK2; p2punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_STRONG_KICK2: state = ST_STRONG_KICK2; p2punch_timer = SDL_GetTicks(); blocking = false; break;


			}
		}
		break;

		case ST_WALK_FORWARD2:
		{
			switch (last_input)
			{
			case IN_RIGHT_UP2: state = ST_IDLE2; blocking = false; break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE2; blocking = false; break;
			case IN_JUMP: state = ST_JUMP_FORWARD2; p2jump_timer = SDL_GetTicks(); blocking = false; break;
			case IN_X:
				if (close)
					state = ST_PUNCH_CLOSE_STANDING2;
				else
					state = ST_PUNCH_STANDING2;
				p2punch_timer = SDL_GetTicks();
				blocking = false; break;
			case IN_SPECIAL2: state = ST_SPECIAL2; p2punch_timer = SDL_GetTicks();  break;

			case IN_X_MID2: state = ST_MID_PUNCH_STANDING2; p2punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_X_STRONG2: state = ST_STRONG_PUNCH_STANDING2; p2punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_MID_KICK2: state = ST_MID_KICK2; p2punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_STRONG_KICK2: state = ST_STRONG_KICK2; p2punch_timer = SDL_GetTicks(); blocking = false; break;


			case IN_KICK2: state = ST_KICK_STANDING2; p2punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_CROUCH_DOWN2: state = ST_CROUCH2; blocking = false; break;
			case IN_FALL2:state = ST_FALLING2;  blocking = false;  break;
			case IN_GRAB2:state = ST_GRAB2; break;
			case IN_GET_GRABBED2:state = ST_GET_GRABBED2; break;
			case IN_BLOCKING2:state = ST_BLOCKING2;
			}
		}
		break;

		case ST_WALK_BACKWARD2:
		{
			switch (last_input)
			{
			case IN_LEFT_UP2: state = ST_IDLE2; blocking = false;  break;
			case IN_LEFT_AND_RIGHT2: state = ST_IDLE2; blocking = false;  break;
			case IN_JUMP2: state = ST_JUMP_BACKWARD2; p2jump_timer = SDL_GetTicks(); blocking = false; break;

			case IN_CROUCH_DOWN2: state = ST_CROUCH2; blocking = false; break;
			case IN_FALL2:state = ST_FALLING2; blocking = false;  break;
			case IN_GRAB2:state = ST_GRAB2; break;
			case IN_GET_GRABBED2:state = ST_GET_GRABBED2; break;
			case IN_BLOCKING2:state = ST_BLOCKING2; break;
			case IN_SPECIAL2: state = ST_SPECIAL2; p2punch_timer = SDL_GetTicks();  break;

			case IN_X:
				if (close)
					state = ST_PUNCH_CLOSE_STANDING2;
				else
					state = ST_PUNCH_STANDING2;
				p2punch_timer = SDL_GetTicks();
				blocking = false; break;
			case IN_KICK2: state = ST_KICK_STANDING2; p2punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_X_MID2: state = ST_MID_PUNCH_STANDING2; p2punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_X_STRONG2: state = ST_STRONG_PUNCH_STANDING2; p2punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_MID_KICK2: state = ST_MID_KICK2; p2punch_timer = SDL_GetTicks(); blocking = false; break;
			case IN_STRONG_KICK2: state = ST_STRONG_KICK2; p2punch_timer = SDL_GetTicks(); blocking = false; break;
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
			case IN_GET_GRABBED2:state = ST_GET_GRABBED2; break;
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
			case IN_FALL2:state = ST_FALLING2; break;
			}
		}
		break;
		case ST_GRAB2:
		{
			switch (last_input)
			{
			case IN_NOT_GRAB2: state = ST_IDLE2; break;
			case IN_GRABBED2:state = ST_GRABBING2; break;

			}
		}
		break;

		case ST_GRABBING2:
		{
			switch (last_input)
			{
			case IN_GRAB_FINISH2: state = ST_IDLE2; break;

			}
		}
		break;

		case ST_GET_GRABBED2:
		{
			switch (last_input)
			{
			case IN_GRABBED_FINISH2: state = ST_FALLING2; break;

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
