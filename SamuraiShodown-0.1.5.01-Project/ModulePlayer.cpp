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
#include "ModuleAttack.h"
#include "ModuleInterface.h"
#include "ModuleFight.h"
#include "ModulePlayer2.h"

ModulePlayer::ModulePlayer()
{

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


	//crouch punch animation 
	const int crouchPunchCollider = 3;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox[crouchPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchPunchCollType[crouchPunchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER},{COLLIDER_PLAYER_ATTACK} };
	Module* crouchPunchCallBack[crouchPunchCollider] = { {this},{this},{this} };

	const int crouchPunchCollider2 = 2;//Collider num for the jump kick animation
	SDL_Rect crouchPunchHitbox2[crouchPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchPunchCollType2[crouchPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crouchPunchCallBack2[crouchPunchCollider2] = { {this},{this} };

	crouchPunch.PushBack({ 178,249,85,69 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);
	crouchPunch.PushBack({ 261,814,126,70 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);
	crouchPunch.PushBack({ 388,814,123,70 }, 2, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);
	crouchPunch.PushBack({ 515,812,130,71 }, 2, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 640,814,127,69 }, 6, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 767,814,87,72 }, 8, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 852,814,82,68 }, 3, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 934,813,85,71 }, 3, { 31, 2 }, crouchPunchCollider, crouchPunchHitbox, crouchPunchCollType, crouchPunchCallBack);
	crouchPunch.PushBack({ 5,66,70,77 }, 3, { 31, 2 }, crouchPunchCollider2, crouchPunchHitbox2, crouchPunchCollType2, crouchPunchCallBack2);


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
	SDL_Rect jumpPunchHitbox[jumpPunchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 },{ 40, 75, 20, 20 } };
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
	SDL_Rect jumpForwardPunchHitbox2[jumpForwardPunchCollider2] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE jumpForwardPunchCollType2[jumpForwardPunchCollider2] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* jumpForwardPunchCallBack2[jumpForwardPunchCollider2] = { {this},{this} };

	jumpFwPunch.PushBack({ 1,694,98,92 }, 2, { 31, 2 }, jumpForwardPunchCollider2, jumpForwardPunchHitbox2, jumpForwardPunchCollType2, jumpForwardPunchCallBack2);
	jumpFwPunch.PushBack({ 101,699,60,87 }, 2, { 31, 2 }, jumpForwardPunchCollider2, jumpForwardPunchHitbox2, jumpForwardPunchCollType2, jumpForwardPunchCallBack2);
	jumpFwPunch.PushBack({ 162,693,99,93 }, 1, { 31, 2 }, jumpForwardPunchCollider, jumpForwardPunchHitbox, jumpForwardPunchCollType, jumpForwardPunchCallBack);
	jumpFwPunch.PushBack({ 262,693,99,93 }, 1, { 31, 2 }, jumpForwardPunchCollider, jumpForwardPunchHitbox, jumpForwardPunchCollType, jumpForwardPunchCallBack);
	jumpFwPunch.PushBack({ 362,686,121,100 }, 2, { 31, 2 }, jumpForwardPunchCollider, jumpForwardPunchHitbox, jumpForwardPunchCollType, jumpForwardPunchCallBack);
	jumpFwPunch.PushBack({ 492,690,119,96 }, 2, { 31, 2 }, jumpForwardPunchCollider, jumpForwardPunchHitbox, jumpForwardPunchCollType, jumpForwardPunchCallBack);

	//crouch animation 
	const int crouchCollider = 2;//Collider num for the jump kick animation
	SDL_Rect crouchHitbox[crouchCollider] = { { 0, 10, 40, 65 },{ 20, 75, 20, 20 } };
	COLLIDER_TYPE crouchCollType[crouchCollider] = { {COLLIDER_PLAYER},{COLLIDER_PLAYER} };
	Module* crouchCallBack[crouchCollider] = { {this},{this} };

	crouch.PushBack({ 1499,11,70,113 }, 2, { 31, 2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);
	crouch.PushBack({ 1568,46,88,80 }, 1000, { 31, 2 }, jumpCollider, jumpHitbox, jumpCollType, jumpCallBack);

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
	fall.PushBack({ 217,284,116,42 }, 35, { 31,2 }, fallCollider, fallHitbox, fallCollType, fallCallBack);

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


	health = 0;

	LOG("Listening for Arrow keys + SPACE:\n");
	LOG("Loading player textures");

	graphics = App->textures->Load("Assets/Sprites/haohmaru.png"); // arcade version
	ui = App->textures->Load("Assets/Sprites/UIspritesheet2.png"); // health bar 
	shadow = App->textures->Load("Assets/Sprites/sombra.png"); // health bar 
	groundlevelaux = position.y;

	App->audio->effects[0] = Mix_LoadWAV("Assets/Music/haohmaru_senpuuretsuzan.wav");
	App->audio->effects[1] = Mix_LoadWAV("Assets/Music/HaohmaruTornado.wav");
	App->audio->effects[2] = Mix_LoadWAV("Assets/Music/haohmaru_getshitted1.wav");
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
	// TODO 5: Remove all memory leaks
	LOG("Unloading Character");
	App->textures->Unload(graphics);
	App->textures->Unload(ui);
	App->audio->CleanUp();

	return true;
}


update_status ModulePlayer::PreUpdate()
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
update_status ModulePlayer::Update()
{

	current_animation = &idle;

	int speed = 2;

	if (invencibleframes) {
		if (SDL_GetTicks() - (invencibleaux) >= 500) {
			invencibleframes = false;
		}
	}

	internal_input(inputs);
	player_states state = process_fsm(inputs);
	current_state = state;

	if (!playerFlip) {



		if (!doingAction) {
			switch (state)
			{
			case ST_IDLE:
				LOG("IDLE\n");
				current_animation = &idle;
				break;
			case ST_WALK_FORWARD:
				LOG("FORWARD >>>\n");
				current_animation = &forward;
				position.x += speed + 1;
				break;
			case ST_WALK_BACKWARD:
				LOG("BACKWARD <<<\n");
				current_animation = &backward;
				position.x -= speed;
				break;
			case ST_JUMP_NEUTRAL:
				LOG("JUMPING NEUTRAL ^^^^\n");
				jumping = true; doingAction = true;
				Mix_PlayChannel(-1, App->audio->effects[15], 0);
				break;
			case ST_JUMP_FORWARD:
				LOG("JUMPING FORWARD ^^>>\n");
				jumpright = true;
				Mix_PlayChannel(-1, App->audio->effects[15], 0);
				doingAction = true;
				break;
			case ST_JUMP_BACKWARD:
				LOG("JUMPING BACKWARD ^^<<\n");
				jumpleft = true;
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
				break;
			case ST_PUNCH_STANDING:
				LOG("PUNCH STANDING ++++\n");
				punching = true; doingAction = true;
				break;
			case ST_KICK_STANDING:
				LOG("KICK STANDING ----\n");
				kicking = true; doingAction = true;
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

				if (playerFlip) {
					App->particles->tornadoHao.speed.x = -3;
					App->particles->AddParticle(App->particles->tornadoHao, position.x - 18, position.y - 70, COLLIDER_PLAYER_SHOT);
				}
				else {
					App->particles->tornadoHao.speed.x = +3;
					App->particles->AddParticle(App->particles->tornadoHao, position.x + 18, position.y - 70, COLLIDER_PLAYER_SHOT);
				}

				break;

			}
		}
	}
	else {


		if (!doingAction) {
			switch (state)
			{
			case ST_IDLE:
				LOG("IDLE\n");
				current_animation = &idle;
				break;
			case ST_WALK_FORWARD:
				LOG("FORWARD >>>\n");
				current_animation = &backward;
				position.x += speed;
				break;
			case ST_WALK_BACKWARD:
				LOG("BACKWARD <<<\n");
				current_animation = &forward;
				position.x -= speed + 1;
				break;
			case ST_JUMP_NEUTRAL:
				LOG("JUMPING NEUTRAL ^^^^\n");
				jumping = true; doingAction = true;
				Mix_PlayChannel(-1, App->audio->effects[15], 0);
				break;
			case ST_JUMP_FORWARD:
				LOG("JUMPING FORWARD ^^>>\n");

				if (!playerFlip)
					jumpleft = true;
				else
					jumpright = true;

				Mix_PlayChannel(-1, App->audio->effects[15], 0);

				doingAction = true;
				break;
			case ST_JUMP_BACKWARD:
				LOG("JUMPING BACKWARD ^^<<\n");

				if (!playerFlip)
					jumpright = true;
				else
					jumpleft = true;

				Mix_PlayChannel(-1, App->audio->effects[15], 0);

				doingAction = true;
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
				break;
			case ST_KICK_STANDING:
				LOG("KICK STANDING ----\n");
				kicking = true; doingAction = true;
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

				if (playerFlip) {
					App->particles->tornadoHao.speed.x = -3;
					App->particles->AddParticle(App->particles->tornadoHao, position.x - 18, position.y - 70, COLLIDER_PLAYER_SHOT);
				}
				else {
					App->particles->tornadoHao.speed.x = +3;
					App->particles->AddParticle(App->particles->tornadoHao, position.x + 18, position.y - 70, COLLIDER_PLAYER_SHOT);
				}

				break;

			}
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



	if (doingAction)
	{
		if (kicking) {
			//set kick anim
			current_animation = &kick;

			if (current_animation->current_frame > 2 && !App->player2->getsHit && !audioPlayed) {
				Mix_PlayChannel(-1, App->audio->effects[19], 0);
				audioPlayed = true;
			}

			//stop kick anim
			if (kick.GetAnimEnd() == true) {
				kicking = false; doingAction = false; kick.SetAnimEnd(false);
				audioPlayed = false;
			}



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

		if (tornading) {
			//set punch anim
			current_animation = &tornado;


			//stop punch anim
			if (tornado.GetAnimEnd() == true) { tornading = false; doingAction = false; tornado.SetAnimEnd(false); }
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
			current_animation = &jump;
			position.y = groundlevelaux - (JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY)*pow(jumpingframe, 2));//MRUA formula
			hasjumped = true;
			//stop jump anim
			if (position.y > groundlevelaux && hasjumped == true)	//end of the jump
			{
				jumpingframe = 0;
				hasjumped = false;
				jumping = false;
				Mix_PlayChannel(-1, App->audio->effects[14], 0);
				position.y = groundlevelaux;
				doingAction = false;
				inputs.Push(IN_JUMP_FINISH);
				jump.Reset();


			}
			jumpingframe++;
		}
		if (jumpright)
		{
			//set jump anim
			if (!playerFlip)
				current_animation = &jumpFw; //Jumpforward animation
			else
				current_animation = &jumpBackward; //Jumpbackward animation
			position.y = groundlevelaux - (JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY)*pow(jumpingframe, 2));//MRUA formula
			position.x += 4;
			hasjumped = true;
			//stop jump anim
			if (position.y > groundlevelaux && hasjumped == true)	//end of the jump
			{
				jumpingframe = 0;
				hasjumped = false;
				jumpright = false;
				Mix_PlayChannel(-1, App->audio->effects[14], 0);
				position.y = groundlevelaux;
				doingAction = false;
				inputs.Push(IN_JUMP_FINISH);
				jumpFw.Reset();
				jumpBackward.Reset();


			}
			jumpingframe++;
		}
		if (jumpleft)
		{
			//set jump anim
			if (playerFlip)
				current_animation = &jumpFw; //Jumpforward animation
			else
				current_animation = &jumpBackward; //Jumpbackward animation
			position.y = groundlevelaux - (JUMP_INIT_VY*jumpingframe) + (0.5*(JUMP_INIT_AY)*pow(jumpingframe, 2));//MRUA formula
			position.x -= 4;
			hasjumped = true;
			//stop jump anim
			if (position.y > groundlevelaux && hasjumped == true)	//end of the jump
			{
				jumpingframe = 0;
				hasjumped = false;
				jumpleft = false;
				Mix_PlayChannel(-1, App->audio->effects[14], 0);
				position.y = groundlevelaux;
				doingAction = false;
				inputs.Push(IN_JUMP_FINISH);
				jumpFw.Reset();
				jumpBackward.Reset();


			}
			jumpingframe++;
		}
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
				colisionadores[i] = App->collision->AddCollider({ position.x - (r.w - playerPivotX) - r.x , position.y - r.h + playerPivotY - r.y,r.w,r.h }, COLLIDER_NONE, current_animation->callback[i]);
			else
				colisionadores[i] = App->collision->AddCollider({ position.x - playerPivotX + r.x , position.y + playerPivotY - r.h - r.y,r.w,r.h }, current_animation->tipo[i], current_animation->callback[i]);

		else if (!godMode || current_animation->tipo[i] != COLLIDER_ENEMY)
			if (playerFlip)
				colisionadores[i] = App->collision->AddCollider({ position.x - (r.w - playerPivotX) - r.x , position.y - r.h + playerPivotY - r.y,r.w,r.h }, current_animation->tipo[i], current_animation->callback[i]);
			else
				colisionadores[i] = App->collision->AddCollider({ position.x - playerPivotX + r.x , position.y + playerPivotY - r.h - r.y,r.w,r.h }, current_animation->tipo[i], current_animation->callback[i]);
	}
	r = current_animation->GetCurrentFrame();//returns the rectangle displaying the current animation

	SDL_Rect shadowrect = { 0,0,70,14 };
	//Blits player + collisions_____________
	if (playerFlip) 
	{		//blit if player is flipped(compensates for pivot)
		App->render->Blit(shadow, position.x - 39, 190, playerFlip, &shadowrect);
		App->render->Blit(graphics, position.x - (r.w - playerPivotX), position.y + playerPivotY - r.h, playerFlip, &r); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)
	}
	else 
	{   //blit if player is NOT flipped
		App->render->Blit(shadow, position.x - 31, 190, playerFlip, &shadowrect);
		App->render->Blit(graphics, position.x - playerPivotX, position.y + playerPivotY - r.h, playerFlip, &r); // playerFlip es la booleana que girará las texturas (true = girado) (false = original)
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


	if (godMode)//deletes all the collision boxes if in god mode
	{
		for (int i = 0; i < MAXNUMOFCOLLIDERS; i++)
		{
			if (colisionadores[i] != nullptr)
				colisionadores[i]->to_delete = true;
		}
	}


	return UPDATE_CONTINUE;
}




// TODO 4: Detect collision with a wall. If so, do something.
void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	for (int i = 0; i < MAXNUMOFCOLLIDERS; i++)
	{
		if (c2->type == COLLIDER_ENEMY) {
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
		getsHit = true; doingAction = true;
	}
	if (c2->type == COLLIDER_ENEMY_ATTACK) {
		Mix_PlayChannel(-1, App->audio->effects[2], 0);
		health += 20;
		getsHit = true; doingAction = true;
		if (App->player2->kicking)
			Mix_PlayChannel(-1, App->audio->effects[17], 0);

		else
			Mix_PlayChannel(-1, App->audio->effects[16], 0);


	}
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
			case IN_X: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
			case IN_KICK: state = ST_KICK_STANDING; punch_timer = SDL_GetTicks();  break;
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
			case IN_X: state = ST_PUNCH_STANDING; punch_timer = SDL_GetTicks();  break;
			case IN_KICK: state = ST_KICK_STANDING; punch_timer = SDL_GetTicks();  break;
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
