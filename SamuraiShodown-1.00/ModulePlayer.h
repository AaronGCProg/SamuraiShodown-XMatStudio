#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#define JUMPINGFRAMES 60
#define JUMP_INIT_VY 11.4166666666 //initial velocity on the Y coord. //16.2
#define JUMP_INIT_AY 0.47568444444 //initial acceleration on the Y coord. //0.867

#define JUMP_TIME 3000
#define PUNCH_TIME 28
#define KICK_TIME 17
#define FALLBOUNCES2 1

#define HEALTH_VALUE 129
#define MAXNUMOFCOLLIDERS 6



#include "Module.h"
#include"ModuleRender.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2Qeue.h"

struct SDL_Texture;
struct collider;

enum player_states
{
	ST_UNKNOWN,

	ST_IDLE,
	ST_WALK_FORWARD,
	ST_WALK_BACKWARD,
	ST_JUMP_NEUTRAL,
	ST_JUMP_FORWARD,
	ST_JUMP_BACKWARD,
	ST_CROUCH,
	ST_PUNCH_STANDING,
	ST_PUNCH_NEUTRAL_JUMP,
	ST_PUNCH_FORWARD_JUMP,
	ST_PUNCH_BACKWARD_JUMP,
	ST_PUNCH_CROUCH,
	ST_KICK_STANDING,
	ST_KICK_NEUTRAL_JUMP,
	ST_KICK_FORWARD_JUMP,
	ST_KICK_BACKWARD_JUMP,
	ST_SPECIAL,
	ST_KICK_CROUCH,
	ST_FALLING,
	ST_GRAB,
	ST_GRABBING,
	ST_GET_GRABBED,
	ST_BLOCKING,
	ST_CROUCH_BLOCK,

	ST_MID_PUNCH_STANDING,
	ST_STRONG_PUNCH_STANDING,
	ST_STRONG_KICK,
	ST_MID_KICK,
	ST_PUNCH_MID_CROUCH,
	ST_PUNCH_STRONG_CROUCH,
	ST_KICK_MID_CROUCH,
	ST_KICK_STRONG_CROUCH,
	ST_MID_PUNCH_NEUTRAL_JUMP,
	ST_STRONG_PUNCH_NEUTRAL_JUMP,
	ST_KICK_MID_NEUTRAL_JUMP,
	ST_KICK_STRONG_NEUTRAL_JUMP,
	ST_PUNCH_CLOSE_STANDING,
	ST_SWORD_FIGHT,
	ST_SWORD_GRABBING,
	ST_SIDE_STEPPING,
	ST_SPRINT,
	ST_SPRINT_END,

	ST_SECOND_GRAB,
	ST_SECOND_GRABBING,
	ST_PUNCH_CLOSE_STANDING_MID,
	ST_PUNCH_CLOSE_STANDING_STRONG,
	ST_FIRST_SPECIAL,
	ST_SECOND_SPECIAL
};

enum player_inputs
{
	IN_LEFT_DOWN,
	IN_LEFT_UP,
	IN_RIGHT_DOWN,
	IN_RIGHT_UP,
	IN_LEFT_AND_RIGHT,
	IN_JUMP,
	IN_CROUCH_UP,
	IN_CROUCH_DOWN,
	IN_JUMP_AND_CROUCH,
	IN_X,
	IN_KICK,
	IN_SPECIAL,
	IN_JUMP_FINISH,
	IN_JUMP_KICK_FINISH,
	IN_JUMP_PUNCH_FINISH,
	IN_PUNCH_FINISH,
	IN_FALL_FINISH,
	IN_FALL,
	IN_DEATH,
	IN_GRAB,
	IN_NOT_GRAB,
	IN_GRABBED,
	IN_GRAB_FINISH,
	IN_GRABBED_FINISH,
	IN_GET_GRABBED,
	IN_BLOCKING,
	IN_BLOCK_FINISH,
	IN_BLOCKING_CROUCH,
	IN_X_MID,
	IN_X_STRONG,
	IN_STRONG_KICK,
	IN_MID_KICK,
	IN_SWORD_FIGHT,
	IN_SWORD_FIGHT_LOSE,
	IN_SWORD_FIGHT_WIN,
	IN_SWORD_FIGHT_DRAW,
	IN_SWORD_GRAB,
	IN_SWORD_GRABBED,
	IN_SIDE_STEP,
	IN_SPRINT,
	IN_SPRINT_END,
	IN_NOT_SWORD_FIGHT,
	IN_SECOND_GRAB,
	IN_FIRST_SPECIAL,
	IN_SECOND_SPECIAL
};



class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	void OnCollision(Collider* c1, Collider* c2);

	bool external_input(p2Qeue<player_inputs>& inputs);
	void internal_input(p2Qeue<player_inputs>& inputs);
	player_states process_fsm(p2Qeue<player_inputs>& inputs);

public:
	p2Qeue<player_inputs> inputs;
	player_states current_state = ST_UNKNOWN;

	Collider *colisionadores[MAXNUMOFCOLLIDERS];
	SDL_Texture* graphics = nullptr;
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
	Animation blockingIdle;
	Animation crouchBlock;
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
	Animation crouchstrongKick;
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
	Animation NWsprintEnd;
	Animation NwcrouchBlock;
	Animation NWblockingIdle;
	Animation NWbackward;
	Animation NWforward;
	Animation NWgrab;
	Animation getGrab2;
	Animation midgrab;
	Animation NWfall;
	Animation midshortPunch;
	Animation shortstrongPunch;
	Animation lose1;
	Animation NWlose1;
	Animation lose2;
	Animation win1;
	Animation NWwin1;
	Animation win2;
	Animation special;
	Animation special2;



	iPoint position;

	Uint32 jump_timer = 0;
	Uint32 punch_timer = 0;
	Uint32 kick_timer = 0;
	Uint32 fall_bounces = 0;

	bool showingshadow = false;//shadow semitransparent
	bool jumping = false;
	bool jumpingBackward = false;
	bool jumpingForward = false;
	bool doingAction = false;
	bool punching = false;
	bool kicking = false;
	bool tornading = false;
	bool crouchkicking = false;
	bool crouchpunching = false;
	int jumpingframe = 0;
	int jumpingSwordFrame = 0;
	int groundlevelaux = 0;
	bool getsHit = false;
	bool hasjumped = false;
	char sAction;
	bool godMode = false;
	bool playerFlip = false;
	bool jumpdiagonal = false;
	bool jumpleft = false;
	bool crouching = false;
	bool audioPlayed = false;
	bool blocking = false;
	bool invencibleframes = false;
	int falling = false;
	int delay = 0;
	bool JumpKicking = false;
	bool JumpPunching = false;
	bool airhit = false;
	bool close = false;
	bool grabbing = false;
	bool getGrabbed = false;
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
	bool alredycollided2 = false;
	bool grabbing2 = false;
	int powValue = 0;
	bool powActivated = false;
	bool powOff = false;
	int healthAnim = 0;
	bool critical = false;
	int healthBlinking = 0;
	int score = 0;
	int swordfightaux = 10;
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
	bool secondSpecial = false;
	bool randomStart = false;


	int invencibleaux = 0;
	int health = 0;
	int aux = 5;
	//int attack_life = 0;
	//int attack_born = 0;
	int playerPivotX = 0; //declare & inizialize pivot
	int playerPivotY = 0;//declare & inizialize pivot
};


#endif