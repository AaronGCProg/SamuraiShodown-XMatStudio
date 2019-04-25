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
	

};

#endif // __ModuleInput_H__