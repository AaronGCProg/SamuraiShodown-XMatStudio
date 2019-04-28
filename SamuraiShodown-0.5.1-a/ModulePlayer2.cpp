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

#include<math.h>


ModulePlayer2::ModulePlayer2()
{
	const int idleCollider = 2;//Collider num for the idle animation
	SDL_Rect idleHitbox[idleCollider] = { { 10, 0, 40, 75 },{ 25, 75, 20, 20 } };
	COLLIDER_TYPE idleCollType[idleCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE backCollType[backCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE forCollType[forCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE kickCollType[kickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	COLLIDER_TYPE kickCollType2[kickCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE punchCollType[punchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* punchCallBack[punchCollider] = { {this},{this},{this} };

	SDL_Rect punchHitbox2[punchCollider2] = { { 35, 10, 40, 60 },{ 50, 60, 20, 20 } };
	COLLIDER_TYPE punchCollType2[punchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY}, };
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
	COLLIDER_TYPE jumpCollType[jumpCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE jumpKickCollType[jumpKickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpKickCallBack[jumpKickCollider] = { {this},{this},{this} };

	const int jumpKickCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpKickHitbox2[jumpKickCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpKickCollType2[jumpKickCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* jumpKickCallBack2[jumpKickCollider2] = { {this},{this} };

	jumpKick.PushBack({ 1278,564,79,91 }, 2, { 31,2 }, jumpKickCollider2, jumpKickHitbox2, jumpKickCollType2, jumpKickCallBack2);
	jumpKick.PushBack({ 1357,574,99,81 }, 19, { 31,2 }, jumpKickCollider, jumpKickHitbox, jumpKickCollType, jumpKickCallBack);
	jumpKick.PushBack({ 620,38,76,83 }, 10000, { 31,2 }, jumpKickCollider2, jumpKickHitbox2, jumpKickCollType2, jumpKickCallBack2);


	//jump backwards animation 
	const int jumpBackCollider = 2;//Collider num for the jump kick animation
	SDL_Rect jumpBackHitbox[jumpBackCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpBackCollType[jumpBackCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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


	//crouch punch animation 
	const int crouchPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox[crouchPunchCollider] = { { 30, 10, 40, 35 },{ 50, 35, 20, 20 },{ 75, 5, 50, 20 } };
	COLLIDER_TYPE crouchPunchCollType[crouchPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* crouchPunchCallBack[crouchPunchCollider] = { {this},{this},{this} };

	const int crouchPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox2[crouchPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchPunchCollType2[crouchPunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* crouchPunchCallBack2[crouchPunchCollider2] = { {this},{this} };

	crouchPunch.PushBack({ 178,814,83,69 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);
	crouchPunch.PushBack({ 262,815,126,68 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);
	crouchPunch.PushBack({ 389,815,126,68 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);
	crouchPunch.PushBack({ 516,813,130,71 }, 2, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 640,814,127,69 }, 6, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 767,814,87,72 }, 8, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 852,814,82,68 }, 3, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 934,813,85,71 }, 3, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);



	//jump backward animation 
	const int jumpBackwardCollider = 2;//Collider num for the jump kick animation
	SDL_Rect jumpBackwardHitbox[jumpBackwardCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpBackwardCollType[jumpBackwardCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	SDL_Rect jumpPunchHitbox[jumpPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 40, 75, 20, 20 } };
	COLLIDER_TYPE jumpPunchCollType[jumpPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpPunchCallBack[jumpPunchCollider] = { {this},{this},{this} };

	const int jumpPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpPunchHitbox2[jumpPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpPunchCollType2[jumpPunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* jumpPunchCallBack2[jumpPunchCollider2] = { {this},{this} };

	jumpPunch.PushBack({ 1028,566,60,87 }, 2, { 31, 2 }, jumpPunchCollider2, jumpPunchHitbox2, jumpPunchCollType2, jumpPunchCallBack2);
	jumpPunch.PushBack({ 1089,564,90,90 }, 3, { 31, 2 }, jumpPunchCollider, jumpPunchHitbox, jumpPunchCollType, jumpPunchCallBack);
	jumpPunch.PushBack({ 1180,560,98,92 }, 13, { 31, 2 }, jumpPunchCollider, jumpPunchHitbox, jumpPunchCollType, jumpPunchCallBack);
	jumpPunch.PushBack({ 1089,564,90,90 }, 2, { 31, 2 }, jumpPunchCollider, jumpPunchHitbox, jumpPunchCollType, jumpPunchCallBack);
	jumpPunch.PushBack({ 1028,566,60,87 }, 500, { 31, 2 }, jumpPunchCollider2, jumpPunchHitbox2, jumpPunchCollType2, jumpPunchCallBack2);


	//jump foward animation 
	const int jumpForwardCollider = 2;//Collider num for the jump kick animation
	SDL_Rect jumpForwardHitbox[jumpForwardCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpForwardCollType[jumpForwardCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE jumpForwardPunchCollType[jumpForwardPunchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* jumpForwardPunchCallBack[jumpForwardPunchCollider] = { {this},{this},{this} };

	const int jumpForwardPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect jumpForwardPunchHitbox2[jumpForwardPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpForwardPunchCollType2[jumpForwardPunchCollider2] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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
	COLLIDER_TYPE crouchCollType[crouchCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
	Module* crouchCallBack[crouchCollider] = { {this},{this} };

	crouch.PushBack({ 1499,11,70,113 }, 6, { 40, 6 }, crouchCollider, crouchHitbox2, crouchCollType, crouchCallBack);
	crouch.PushBack({ 1568,46,88,80 }, 2, { 60, 8 }, crouchCollider, crouchHitbox, crouchCollType, crouchCallBack);
	crouch.firstLoopFrame = 1;
	crouch.loop = true;

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


	const int crouchKickCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchKickHitbox[crouchPunchCollider] = { { 5, 10, 40, 35 },{ 20, 35, 20, 20 },{ 78,0,20,20 } };
	COLLIDER_TYPE crouchKickCollType[crouchKickCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY},{COLLIDER_ENEMY_ATTACK} };
	Module* crouchKickCallBack[crouchKickCollider] = { {this},{this},{this} };
	crouchKick.PushBack({ 1019,803,78,80 }, 2, { 31,2 }, crouchPunchCollider, crouchKickHitbox, crouchKickCollType, crouchKickCallBack);
	crouchKick.PushBack({ 1098,810,98,73 }, 8, { 31,2 }, crouchKickCollider, crouchKickHitbox, crouchPunchCollType, crouchKickCallBack);


	const int tornadoCollider = 2;//Collider num for the tornado animation
	SDL_Rect tornadoHitbox[tornadoCollider] = { { 40, 10, 40, 65 },{ 55, 75, 20, 20 } };
	COLLIDER_TYPE tornadoCollType[tornadoCollider] = { {COLLIDER_ENEMY},{COLLIDER_ENEMY} };
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

	graphics = App->textures->Load("Assets/Sprites/haohmaru2.png"); // arcade version
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
					App->particles->AddParticle(App->particles->tornadoHao, position.x + 18, position.y - 70, COLLIDER_ENEMY_SHOT);


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
					App->particles->AddParticle(App->particles->tornadoHao, position.x - 18, position.y - 70, COLLIDER_ENEMY_SHOT);

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
					current_animation = &jumpFwPunch;
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
					current_animation = &jumpFwPunch;
				else if (JumpKicking)
					current_animation = &jumpKick;
				else
					current_animation = &jumpBackward; //Jumpforward animation



				if (JumpPunching)
					current_animation = &jumpFwPunch;
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
					current_animation = &jumpFwPunch;
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
					current_animation = &jumpFwPunch;
				else if (JumpKicking)
					current_animation = &jumpKick;
				else
					current_animation = &jumpBackward; //Jumpforward animation



				if (JumpPunching)
					current_animation = &jumpFwPunch;
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

				position.y = groundlevelaux - (10 * jumpingframe) + (0.5*(0.5*JUMP_INIT_AY + (0.2f*(fall_bounces + 1)))*pow(jumpingframe, 2));//MRUA formula
				if (playerFlip)position.x += 2 - (fall_bounces);
				else position.x -= 2 - (fall_bounces);

				hasjumped = true;
				jumpingframe++;
				if (position.y > groundlevelaux)
				{
					jumpingframe = 0;
					position.y = groundlevelaux;
					fall_bounces++;
				}
			}
			if (fall_bounces > FALLBOUNCES &&hasjumped == true && delay > 45)
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
		App->render->Blit(shadow, position.x - 39, 190, playerFlip, &shadowrect);
		App->render->Blit(graphics, position.x - (r.w - playerPivotX), position.y + playerPivotY - r.h, playerFlip, &r); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)
	}
	else
	{    //blit if player is NOT flipped
		App->render->Blit(shadow, position.x - 31, 190, playerFlip, &shadowrect);
		App->render->Blit(graphics, position.x - playerPivotX, position.y + playerPivotY - r.h, playerFlip, &r); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)
	}



	SDL_Rect healthBar = { 90, 81, 134, 15 };

	if ((App->fight->showHealthBar) == true) {
		App->render->Blit(ui, 167, 15, false, &healthBar, NULL, true);
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

			}
		}
		if (c2->type == COLLIDER_PLAYER_ATTACK) {
			if (App->player2->position.y < groundlevelaux){
				p2inputs.Push(IN_FALL2);
				airhit = true;

			}
			Mix_PlayChannel(-1, App->audio->effects[2], 0);
			health += 20;
			getsHit = true; doingAction = true;
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

	SDL_Event event2;
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
	else if (!App->fight->playerControl && App->interface->actualtime == 0) {
		p2inputs.Push(IN_CROUCH_UP2);
		down2 = false;

		up2 = false;

		p2inputs.Push(IN_LEFT_UP2);
		left2 = false;

		p2inputs.Push(IN_RIGHT_UP2);
		right2 = false;
		inputs.Push(IN_CROUCH_UP);
		down = false;

		up = false;

		inputs.Push(IN_LEFT_UP);
		left = false;

		inputs.Push(IN_RIGHT_UP);


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
