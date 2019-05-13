#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_gamecontroller.h"

#define MAX_BUTTONS 150
#define DEATHZONE  10000
#define MAX_GAME_CONTROLLERS 2

class ModuleGameControllers :public Module
{
public:
	ModuleGameControllers();
	~ModuleGameControllers();


	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:

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