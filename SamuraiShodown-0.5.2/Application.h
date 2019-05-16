#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneWelcome;
class ModuleSceneHanzo;
class ModuleSceneCongrats;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class ModuleAudio;
class ModuleParticles;
class ModuleCollision;
class ModuleFonts;
class ModuleInterface;
class ModuleFight;
class ModuleReferee;
class Module;


class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneWelcome* scene_welcome;
	ModuleSceneHanzo* scene_hanzo;
	ModuleSceneCongrats* scene_congrats;
	ModulePlayer2* player2;
	ModulePlayer* player;
	ModuleAudio* audio;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleFonts* fonts;
	ModuleInterface* interface;
	ModuleFight* fight;
	ModuleReferee *referee;
	ModuleFadeToBlack* fade;




public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__