#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include <string.h>
#include "p2Qeue.h"
#include "SDL\include\SDL_scancode.h"


#define MAX_KEYS 300
#define JUMP_TIME 3000
#define PUNCH_TIME 1000

#define MAX_BUTTONS 150
#define DEATHZONE  10000
#define MAX_GAME_CONTROLLERS 2

#define MAX_HISTORY 180
#define MAX_COMMAND_FRAMES 100

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct GamePad
{
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool duright = false;
	bool duleft = false;
	bool ddright = false;
	bool ddleft = false;
	bool a = false;
	bool b = false;
	bool x = false;
	bool y = false;
};

struct History
{
	uint frame = 0u;
	KEY_STATE keyboard[MAX_KEYS];
	GamePad pads[MAX_GAME_CONTROLLERS];
};


enum  InputCommandTypes
{
	suigetsu,
	nikkaku,
	hasso,
	punch,
	max
};


class ModuleInput : public Module
{
public:

	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	const Uint8 *keyboard = nullptr;
	bool gamepad = NULL;
	GamePad pads[MAX_GAME_CONTROLLERS];
	KEY_STATE keys[MAX_KEYS];
	History history[MAX_HISTORY];


	const History* GetPrevious(int pointer);

	bool CheckPunch(int frames_past, int player, bool playerflip);
	bool CheckTornado(int frames_past, int player, bool playerflip);
	bool CheckKick(int frames_past, int player, bool playerflip);
	bool CheckThrow1(int frames_past, int player, bool playerflip);


	GamePad pad;



	SDL_Event event_;




	SDL_GameController*Controller_player1 = nullptr;

	bool Controller_player1_Connected = false; //bool checking if the controller is connected or not
	bool controller_player1_A_pressed = false;//bool checking if the button A is pressed
	bool controller_player1_Start_pressed = false;//bool checking if the button Start is pressed
	bool controller_player1_B_pressed = false;
	bool controller_player1_X_pressed = false;
	bool controller_player1_Y_pressed = false;


	//values for the Joysticks Axes

	int Controller_player1_LAxisX = 0;
	int Controller_player1_LAxisY = 0;
	int controller_player1_RightShoulder_pressed = 0;


	//_________________________________________________________________________________________

	//gameCOntroller2

	//Definition of the controller for the player two

	SDL_GameController*Controller_player2 = nullptr;

	bool Controller_player2_Connected = false; //bool checking if the controller is connected or not
	bool controller_player2_A_pressed = false;//bool checking if the button A is pressed
	bool controller_player2_Start_pressed = false;//bool checking if the button Start is pressed
	bool controller_player2_B_pressed = false;
	bool controller_player2_X_pressed = false;
	bool controller_player2_Y_pressed = false;
	//values for the Joysticks Axes

	int Controller_player2_LAxisX = 0;
	int Controller_player2_LAxisY = 0;
	int controller_player2_RightShoulder_pressed = 0;

	int history_cursor = 0;

};

#endif // __ModuleInput_H__