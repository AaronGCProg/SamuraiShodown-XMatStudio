#include "ModuleGameControllers.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleSceneWelcome.h"


ModuleGameControllers::ModuleGameControllers() :Module()
{

}


ModuleGameControllers::~ModuleGameControllers()
{
}
bool ModuleGameControllers::Init()
{
	LOG("Init gamepads");
	bool ret = true;

	SDL_Init(SDL_INIT_GAMECONTROLLER);


	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
		LOG("Error, gamecontroller fail to initilize", SDL_GetError());

	}




	return ret;
}

update_status  ModuleGameControllers::PreUpdate()
{

	for (int i = 0; i < SDL_NumJoysticks(); ++i) {

		if (SDL_IsGameController(i)) {
			if (i == 0) {

				Controller_player1 = SDL_GameControllerOpen(i);

				if (SDL_GameControllerGetAttached(Controller_player1)) {


					Controller_player1_LAxisX = SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTX);
					Controller_player1_LAxisY = SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTY);


					controller_player1_A_pressed = SDL_GameControllerGetButton(Controller_player1, SDL_CONTROLLER_BUTTON_A);
					controller_player1_Start_pressed = SDL_GameControllerGetButton(Controller_player1, SDL_CONTROLLER_BUTTON_START);
					controller_player1_B_pressed = SDL_GameControllerGetButton(Controller_player1, SDL_CONTROLLER_BUTTON_B); ;

					Controller_player1_Connected = true;
				}

				else {

					SDL_GameControllerClose(Controller_player1);
					Controller_player1 = nullptr;
					Controller_player1_Connected = false;

				}
			}

			else if (i < 1) {

				Controller_player2_Connected = false;
				SDL_GameControllerClose(Controller_player2);
				Controller_player2 = nullptr;

			}

			else if (i == 1 || i == 0 && Controller_player1_Connected == false) {

				Controller_player2 = SDL_GameControllerOpen(i);
				if (SDL_GameControllerGetAttached(Controller_player2)) {

					Controller_player2_LAxisX = SDL_GameControllerGetAxis(Controller_player2, SDL_CONTROLLER_AXIS_LEFTX);
					Controller_player2_LAxisY = SDL_GameControllerGetAxis(Controller_player2, SDL_CONTROLLER_AXIS_LEFTY);


					controller_player2_A_pressed = SDL_GameControllerGetButton(Controller_player2, SDL_CONTROLLER_BUTTON_A);

					controller_player2_Start_pressed = SDL_GameControllerGetButton(Controller_player2, SDL_CONTROLLER_BUTTON_START);
					controller_player2_B_pressed = SDL_GameControllerGetButton(Controller_player2, SDL_CONTROLLER_BUTTON_B);
					Controller_player2_Connected = true;
					break;


				}
				else {

					SDL_GameControllerClose(Controller_player2);
					Controller_player2 = nullptr;
					Controller_player2_Connected = false;

				}
			}
		}
	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool  ModuleGameControllers::CleanUp()
{

	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	SDL_GameControllerClose(Controller_player1);
	SDL_GameControllerClose(Controller_player2);

	Controller_player1 = nullptr;
	Controller_player2 = nullptr;



	return true;
}