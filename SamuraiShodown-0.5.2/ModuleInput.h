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

/*struct History
{
	uint frame = 0u;
	KEY_STATE keyboard[MAX_KEYS];
	GamePad pads[MAX_PADS];
};*/

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
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
	KEY_STATE keys[MAX_KEYS];



	SDL_Event event_;

	//gameCOntroller1

	//Definition of the controller for the player one

	SDL_GameController*Controller_player1 = nullptr;

	bool Controller_player1_Connected = false; //bool checking if the controller is connected or not
	bool controller_player1_A_pressed = false;//bool checking if the button A is pressed
	bool controller_player1_Start_pressed = false;//bool checking if the button Start is pressed
	bool controller_player1_B_pressed = false;

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
	//values for the Joysticks Axes

	int Controller_player2_LAxisX = 0;
	int Controller_player2_LAxisY = 0;
	int controller_player2_RightShoulder_pressed = 0;



};

#endif // __ModuleInput_H__