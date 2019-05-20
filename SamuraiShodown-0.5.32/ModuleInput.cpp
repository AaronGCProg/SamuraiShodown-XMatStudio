#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for (uint i = 0; i < MAX_KEYS; ++i)
		keys[i] = KEY_IDLE;

}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);



	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}


	SDL_Init(SDL_INIT_GAMECONTROLLER);


	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0) {
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;

	}


	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	keyboard = SDL_GetKeyboardState(NULL);


	for (int i = 0; i < MAX_KEYS; ++i)
	{
		if (keyboard[i] == 1)
		{
			if (keys[i] == KEY_IDLE)
				keys[i] = KEY_DOWN;
			else
				keys[i] = KEY_REPEAT;
		}
		else
		{
			if (keys[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keys[i] = KEY_UP;
			else
				keys[i] = KEY_IDLE;
		}
	}

	if (keys[SDL_SCANCODE_ESCAPE])
		return update_status::UPDATE_STOP;



	if ((SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTX) < 10922 && SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTX) > -10922) && SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTY) < -DEATHZONE)
	{
		pads[0].up = true;
	}
	else if ((SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTX) < 10922 && SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTX) > -10922) && SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTY) > DEATHZONE)
	{
		pads[0].down = true;
	}
	else if (SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTX) > DEATHZONE && (SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTY) > -DEATHZONE && SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTY) < DEATHZONE))
	{
		pads[0].right = true;
	}
	else if (SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTX) < -DEATHZONE && (SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTY) > -DEATHZONE && SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTY) < DEATHZONE))
	{
		pads[0].left = true;
	}
	else if (SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTX) > 10922 && (SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTY) < -10922))
	{
		pads[0].duright = true;
	}
	else if (SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTX) < -10922 && (SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTY) < -10922))
	{
		pads[0].duleft = true;
	}
	else if (SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTX) > 10922 && (SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTY) > 10922))
	{
		pads[0].ddright = true;
	}
	else if (SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTX) < -10922 && (SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_LEFTY) > 10922))
	{
		pads[0].ddleft = true;
	}
	else {
		pads[0].ddleft = false;
		pads[0].ddright = false;
		pads[0].duleft = false;
		pads[0].duright = false;
		pads[0].left = false;
		pads[0].right = false;
		pads[0].down = false;
		pads[0].up = false;

	}
	if (SDL_GameControllerGetButton(Controller_player1, SDL_CONTROLLER_BUTTON_A))
		pads[0].a = true;

	if (SDL_GameControllerGetButton(Controller_player1, SDL_CONTROLLER_BUTTON_B))
		pads[0].b = true;

	if (history_cursor >= MAX_HISTORY) history_cursor = 0;

	memcpy(history[history_cursor].keyboard, keyboard, sizeof(KEY_STATE)*MAX_KEYS);
	memcpy(history[history_cursor].pads, pads, sizeof(GamePad)*MAX_GAME_CONTROLLERS);
	history_cursor++;


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
					controller_player1_RightShoulder_pressed = SDL_GameControllerGetAxis(Controller_player1, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);

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
					controller_player2_RightShoulder_pressed = SDL_GameControllerGetAxis(Controller_player2, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
					Controller_player2_Connected = true;


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

bool CommandSuigetsu::Check(uint frames_past) const
{
	//press A

	int count = 0;
	uint frame = 0;

	for (uint i = 0; i < frames_past; i++)
	{
		if (count > 0 && (i - frame) > MAX_COMMAND_FRAMES) return false;


		/*const History* history = GetPrevious(i);
		if (!history)
			break;*/


		switch (count)
		{
		case 0:
			if ((App->input->Controller_player1_LAxisX > -10922 && App->input->Controller_player1_LAxisX < 10922) && (App->input->Controller_player1_LAxisY < -DEATHZONE)) { count++; frame = i; }
			break;


		case 1:
			if ((App->input->Controller_player1_LAxisX > 10922 && App->input->Controller_player1_LAxisX < 21845) && (App->input->Controller_player1_LAxisY < -DEATHZONE)) { count++; frame = i; }
			break;

		case 2:
			if (App->input->Controller_player1_LAxisX > 21845) { count++; frame = i; }
			break;

		case 3:
			if (App->input->controller_player1_A_pressed || App->input->controller_player1_B_pressed) { return true; } break;

		}
	}
}

bool CommandNikkaku::Check(uint frames_past) const
{

	int count = 0;
	uint frame = 0;

	for (uint i = 0; i < frames_past; i++)
	{
		if (count > 0 && (i - frame) > MAX_COMMAND_FRAMES) return false;


		/*const History* history = GetPrevious(i);
		if (!history)
			break;*/


		switch (count)
		{
		case 0:
			if ((App->input->Controller_player1_LAxisX > -10922 && App->input->Controller_player1_LAxisX < 10922) && ((App->input->Controller_player1_LAxisY < DEATHZONE && App->input->Controller_player1_LAxisY < -DEATHZONE))) { count++; frame = i; }
			break;


		case 1:
			if (App->input->Controller_player1_LAxisX > 21845) { count++; frame = i; }
			break;

		case 2:
			if ((App->input->Controller_player1_LAxisX > -10922 && App->input->Controller_player1_LAxisX < 10922) && (App->input->Controller_player1_LAxisY < -DEATHZONE)) { count++; frame = i; }
			break;

		case 3:
			if ((App->input->Controller_player1_LAxisX > 10922 && App->input->Controller_player1_LAxisX < 21845) && (App->input->Controller_player1_LAxisY < -DEATHZONE)) { count++; frame = i; } break;

		case 4:
			if (App->input->controller_player1_A_pressed || App->input->controller_player1_B_pressed) { return true; } break;


		}
	}
}

bool CommandHasso::Check(uint frames_past) const
{
	int count = 0;
	uint frame = 0;

	for (uint i = 0; i < frames_past; i++)
	{
		if (count > 0 && (i - frame) > MAX_COMMAND_FRAMES) return false;


		/*const History* history = GetPrevious(i);
		if (!history)
			break;*/


		switch (count)
		{
		case 0:
			if ((App->input->Controller_player1_LAxisX > -10922 && App->input->Controller_player1_LAxisX < 10922) && ((App->input->Controller_player1_LAxisY < DEATHZONE && App->input->Controller_player1_LAxisY < -DEATHZONE))) { count++; frame = i; }
			break;


		case 1:
			if (App->input->Controller_player1_LAxisX > 21845) { count++; frame = i; }
			break;

		case 2:
			if ((App->input->Controller_player1_LAxisX > -10922 && App->input->Controller_player1_LAxisX < 10922) && (App->input->Controller_player1_LAxisY < -DEATHZONE)) { count++; frame = i; }
			break;

		case 3:
			if ((App->input->Controller_player1_LAxisX > 10922 && App->input->Controller_player1_LAxisX < 21845) && (App->input->Controller_player1_LAxisY < -DEATHZONE)) { return true; } break;

		}
	}
}

bool CommandPunch::Check(uint frames_past) const
{
	int count = 0;
	uint frame = 0;

	for (uint i = 0; i < frames_past; i++)
	{
		if (count > 0 && (i - frame) > MAX_COMMAND_FRAMES) return false;


		const History* story = App->input->GetPrevious(i);
		if (!story)
			break;

		const GamePad * pad = &story->pads[0];


		switch (count)
		{
		case 0:
			if (pad->a) { count++; frame = i; }
			break;

		case 1:
			if (pad->a) { return true; }
			break;

		}
	}
}

bool ModuleInput::CheckPunch(int frames_past) {

	int count = 0;
	uint frame = 0;

	for (uint i = 0; i < frames_past; i++)
	{
		if (count > 0 && (i - frame) > MAX_COMMAND_FRAMES) return false;


		const History* story = App->input->GetPrevious(i);
		if (!story)
			break;

		const GamePad * pad = &story->pads[0];


		switch (count)
		{

		case 0:
			if (pad->a) { return true; } break;

		}
	}
}

bool ModuleInput::CheckTornado(int frames_past) {

	int count = 0;
	uint frame = 0;

	for (uint i = 0; i < frames_past; i++)
	{
		if (count > 0 && (i - frame) > MAX_COMMAND_FRAMES) return false;


		const History* story = App->input->GetPrevious(i);
		if (!story)
			break;

		const GamePad * pad = &story->pads[0];


		switch (count)
		{
		case 0:
			if (pad->down) { count++; frame = i; }
			break;


		case 1:
			if (pad->ddright) { count++; frame = i; }
			break;

		case 2:
			if (pad->right) { count++; frame = i; }
			break;

		case 3:
			if (pad->a || pad->b) { return true; } break;

		}
	}
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);


	SDL_GameControllerClose(Controller_player1);
	SDL_GameControllerClose(Controller_player2);

	Controller_player1 = nullptr;
	Controller_player2 = nullptr;
	return true;
}


const History* ModuleInput::GetPrevious(int pointer) {

	return (&history[pointer]);
}