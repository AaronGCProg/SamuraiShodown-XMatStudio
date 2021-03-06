#ifndef __ModulePlayer2_H__
#define __ModulePlayer2_H__

#include "Module.h"
#include "p2Qeue.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"


#define JUMPINGFRAMES 60
#define JUMP_INIT_VY 11.4166666666 //initial velocity on the Y coord. //16.2
#define JUMP_INIT_AY 0.47568444444 //initial acceleration on the Y coord. //0.867

#define JUMP_TIME 3000
#define PUNCH_TIME 28
#define KICK_TIME 17

#define HEALTH_VALUE 129
#define MAXNUMOFCOLLIDERS 6
#define FALLBOUNCES 0


struct SDL_Texture;
struct collider;

enum player2_states
{
	ST_UNKNOWN2,

	ST_IDLE2,
	ST_WALK_FORWARD2,
	ST_WALK_BACKWARD2,
	ST_JUMP_NEUTRAL2,
	ST_JUMP_FORWARD2,
	ST_JUMP_BACKWARD2,
	ST_CROUCH2,
	ST_PUNCH_STANDING2,
	ST_PUNCH_NEUTRAL_JUMP2,
	ST_PUNCH_FORWARD_JUMP2,
	ST_PUNCH_BACKWARD_JUMP2,
	ST_PUNCH_CROUCH2,
	ST_KICK_STANDING2,
	ST_KICK_NEUTRAL_JUMP2,
	ST_KICK_FORWARD_JUMP2,
	ST_KICK_BACKWARD_JUMP2,
	ST_SPECIAL2,
	ST_FALLING2,
	ST_KICK_CROUCH2,
	ST_GRAB2,
	ST_GRABBING2,
	ST_GET_GRABBED2,

	ST_BLOCKING2,
	ST_CROUCH_BLOCK2,

	ST_MID_PUNCH_STANDING2,
	ST_STRONG_PUNCH_STANDING2,
	ST_STRONG_KICK2,
	ST_MID_KICK2,
	ST_PUNCH_MID_CROUCH2,
	ST_PUNCH_STRONG_CROUCH2,
	ST_KICK_MID_CROUCH2,
	ST_KICK_STRONG_CROUCH2,
	ST_MID_PUNCH_NEUTRAL_JUMP2,
	ST_STRONG_PUNCH_NEUTRAL_JUMP2,
	ST_KICK_MID_NEUTRAL_JUMP2,
	ST_KICK_STRONG_NEUTRAL_JUMP2,
	ST_PUNCH_CLOSE_STANDING2,
	ST_SWORD_FIGHT2,
	ST_SWORD_GRABBING2,
	ST_SIDE_STEPPING2,
	ST_SPRINT2,
	ST_SPRINT_END2,
	ST_SECOND_GRAB2,
	ST_SECOND_GRABBING2,
	ST_PUNCH_CLOSE_STANDING_MID2,
	ST_PUNCH_CLOSE_STANDING_STRONG2,
	ST_FIRST_SPECIAL2

};

enum player2_inputs
{
	IN_LEFT_DOWN2,
	IN_LEFT_UP2,
	IN_RIGHT_DOWN2,
	IN_RIGHT_UP2,
	IN_LEFT_AND_RIGHT2,
	IN_JUMP2,
	IN_CROUCH_UP2,
	IN_CROUCH_DOWN2,
	IN_JUMP_AND_CROUCH2,
	IN_X2,
	IN_KICK2,
	IN_SPECIAL2,
	IN_JUMP_FINISH2,
	IN_JUMP_KICK_FINISH2,
	IN_JUMP_PUNCH_FINISH2,
	IN_PUNCH_FINISH2,
	IN_FALL_FINISH2,//new
	IN_FALL2,
	IN_DEATH2,
	IN_GRAB2,
	IN_NOT_GRAB2,
	IN_GRABBED2,
	IN_GRAB_FINISH2,
	IN_GRABBED_FINISH2,
	IN_GET_GRABBED2,
	IN_BLOCKING2,
	IN_BLOCK_FINISH2,
	IN_BLOCKING_CROUCH2,
	IN_X_MID2,
	IN_X_STRONG2,
	IN_STRONG_KICK2,
	IN_MID_KICK2,
	IN_SWORD_FIGHT2,
	IN_SWORD_FIGHT_LOSE2,
	IN_SWORD_FIGHT_WIN2,
	IN_SWORD_FIGHT_DRAW2,
	IN_SWORD_GRAB2,
	IN_SWORD_GRABBED2,
	IN_SIDE_STEP2,
	IN_SPRINT2,
	IN_SPRINT_END2,
	IN_SECOND_GRAB2,
	IN_FIRST_SPECIAL2,

};



class ModulePlayer2 : public Module
{
public:
	ModulePlayer2();
	~ModulePlayer2();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	bool external_input(p2Qeue<player2_inputs>& p2inputs, p2Qeue<player_inputs>& inputs);
	void internal_input(p2Qeue<player2_inputs>& p2inputs);
	player2_states process_fsm(p2Qeue<player2_inputs>& p2inputs);

public:
	p2Qeue<player2_inputs> p2inputs;
	player2_states current_state = ST_UNKNOWN2;

	Collider *colisionadores[MAXNUMOFCOLLIDERS];
	SDL_Texture * graphics = nullptr;
	SDL_Texture* ui = nullptr;
	SDL_Texture* shadow = nullptr;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation jump;
	Animation kick;
	Animation punch;
	Animation tornado;
	Animation hurtLow;
	Animation* current_animation;
	Animation jumpKick;
	Animation jumpPunch;
	Animation jumpBackward;
	Animation jumpFw;
	Animation jumpFwPunch;
	Animation crouch;
	Animation crouchKick;
	Animation crouchPunch;
	Animation getUp;
	Animation fall;
	Animation getGrab;

	Animation midpunch;
	Animation strongpunch;
	Animation midkick;
	Animation strongkick;
	Animation jumpmidPunch;
	Animation jumpstrongPunch;
	Animation jumpmidKick;
	Animation jumpstrongKick;
	Animation crouchmidPunch;
	Animation crouchstrongPunch;
	Animation crouchmidKick;
	Animation grab;
	Animation shortPunch;
	Animation blockingIdle;
	Animation crouchBlock;

	Animation swordFight;
	Animation NWidle;
	Animation pickUpSword;
	Animation sideStep;

	Animation NWpunch;
	Animation NWbacksprint;
	Animation sprint;
	Animation sprintEnd;
	Animation backsprint;
	Animation NWcrouch;
	Animation NWjump;
	Animation NWstrongpunch;
	Animation NWkick;
	Animation NWstrongkick;
	Animation NWcrouchPunch;
	Animation NWstrongcrouchPunch;
	Animation NWcrouchKick;
	Animation NWcrouchmidKick;
	Animation NWcrouchstrongKick;
	Animation NWjumpPunch;
	Animation NWjumpKick;
	Animation NWjumpstrongPunch;
	Animation NWjumpstrongKick;
	Animation NWsprint;
	Animation crouchstrongKick;
	Animation NWsprintEnd;
	Animation NWblockingIdle;
	Animation NwcrouchBlock;
	Animation NWbackward;
	Animation NWforward;
	Animation NWgrab;
	Animation getGrab2;
	Animation midgrab;
	Animation NWfall;
	Animation lose1;
	Animation NWlose1;
	Animation lose2;
	Animation win1;
	Animation NWwin1;
	Animation win2;
	Animation midshortPunch;
	Animation shortstrongPunch;
	Animation special;

	iPoint position;

	Uint32 p2jump_timer = 0;
	Uint32 p2punch_timer = 0;
	Uint32 p2kick_timer = 0;
	Uint32 fall_bounces = 0;//new

	SDL_Event event2;


	//Collider* body = nullptr;

	bool showingshadow = false;//shadow semitransparent
	bool jumping = false;
	bool doingAction = false;
	bool punching = false;
	bool kicking = false;
	int jumpingframe = 0;
	int groundlevelaux = 0;
	int posyaux = 0;//new
	bool tornading = false;
	bool getsHit = false;
	bool hasjumped = false;
	char sAction;
	bool godMode2 = false;
	bool debugmode = false;
	bool playerFlip = true;
	bool blocking = false;
	bool invencibleframes = false;
	bool JumpPunching = false;
	bool JumpKicking = false;
	bool crouchpunching = false;
	bool crouchkicking = false;
	bool airhit = false;
	bool jumpdiagonal = false;
	bool grabbing = false;
	bool getGrabbed = false;
	bool gettingGrabbed = false;
	bool blockingAction = false;
	bool midPunching = false;
	bool strongPunching = false;
	bool midKicking = false;
	bool strongKicking = false;
	bool blockingActionCrouch = false;
	int invencibleTotalTime = 750;
	bool closeLowpunching = false;
	int grabStates = 0;
	bool flipAux = false;
	bool swordFighting = false;
	int swordFightCount = 0;
	int swordFightCount2 = 0;
	bool swordDrop = false;
	int swordTrack = NULL;
	bool swordDropped = false;
	bool swordOnTheGround = false;
	bool closeSword = false;
	int swordTrackGround = NULL;
	bool noSword = false;
	bool grabbingSword = false;
	bool sideStepping = false;
	bool sprinting = false;
	int sideStepAux = 0;
	int internalAux = 0;
	int jumpingSwordFrame = 0;
	bool grabbing2 = false;
	int powValue = 0;
	bool powActivated = false;
	bool powOff = false;
	int health = 0;
	int healthAnim = 0;
	int healthBlinking = 0;
	bool closemidpunching = false;
	bool closestrongpunching = false;
	bool winning1 = false;
	bool winning2 = false;
	bool winnw = false;
	bool losenw = false;
	bool lost1 = false;
	bool lost2 = false;
	bool firstSpecial = false;
	int special1Timer = 0;

	bool critical = false;
	int score = 0;



	bool jumpleft = false;
	bool jumpright = false;
	bool crouching = false;
	bool neutralJumpPunching = false;
	bool audioPlayed = false;
	int falling = false;//new
	int aux = 10;
	int invencibleaux = 0;
	int delay = 0;

	int playerPivotX = 0; //declare & inizialize pivot
	int playerPivotY = 0;//declare & inizialize pivot

};

#endif
