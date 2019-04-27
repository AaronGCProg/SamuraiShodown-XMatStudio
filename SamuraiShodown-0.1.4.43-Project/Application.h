#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 18

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneUky;
class ModuleSceneWelcome;
class ModuleSceneHao;
class ModuleSceneCongrats;
class ModulePlayer;
class ModulePlayer2;
class ModuleFadeToBlack;
class ModuleAudio;
class ModuleParticles;
class ModuleCollision;
class ModuleFonts;
class ModuleAttack;
class ModuleInterface;
class ModuleFight;
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
	ModuleSceneUky* scene_uky;
	ModuleSceneHao* scene_hao;
	ModuleSceneCongrats* scene_congrats;
	ModulePlayer2* player2;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleFonts* fonts;
	ModuleAttack* attack;
	ModuleInterface* interface;
	ModuleFight* fight;



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