#ifndef __MODULEINTERFACE_H__
#define __MODULEINTERFACE_H__

#include "Module.h"
#include "Globals.h"
#include "puntuation.h"
#define PUNTUATION_TIME 120 //time it takes (in frames) for one parameter of the puntuation to reach zero
enum scorestates
{
	DEFAULT,
	IN_LIFE,
	IN_TIME,
	IN_HITTINGPERCENTATGE,
	IN_TOTAL,
	IN_FINISHED
};

class ModuleInterface : public Module
{
public:
	ModuleInterface();
	~ModuleInterface();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* ui = nullptr;
	SDL_Rect ko = { 33, 66, 28, 22 };
	SDL_Rect end = { 33, 89, 28, 22 };
	SDL_Rect powbar = { 225, 65, 65, 9 };
	SDL_Rect pow1interiorbar = { 0,24,2,8 };
	SDL_Rect pow2interiorbar = { 0,24,2,8 };
	SDL_Rect powword[7];
	iPoint powpivot1[7];
	iPoint powpivot2[7];
	SDL_Rect victory = { 225, 75, 27, 18 };
	SDL_Rect life_time = { 83,219,64,53 };
	SDL_Rect hittingperc_total = { 150,218,68,54 };
	Puntuation P1punt;
	Puntuation P2punt;



	//text vars

	int font_time = -1;
	int font_name = -1;
	int font_menu = -1;
	int font_debug = -1;
	int font_finalscore = -1;
	char time_text[10];
	char debug_buttons_text[50];
	char debug_joystick_text[50];
	char life_text_char[10];
	char time_text_char[10];
	char hittingpercent_text_char[10];
	char total_score_text_char[10];
	int startingtime = 0;
	int actualtime = 99;
	bool timerStop = false;
	bool showscore = false;
	bool scoreended = false;

	int koBlinking;
	int lifescore = 1;
	int timescore = 0;
	int hittingpercentatgescore = 33;
	int totalScore = 451;
	char p1scorechar[10];
	char p2scorechar[10];

	int pow1damage = 0;
	int pow2damage = 0;
	int actualpowwordframe = 0;
	int actualpowwordframe2 = 0;
	int powdelay = 0;
	int powdelay2 = 0;
	int criticalpowbucle = 0;
	int criticalpowbucle2 = 0;
	int playerwins = 0; //1 if p1, 2 if p2
	scorestates scoretable = DEFAULT;
	bool stopcountingtime = false;
	int varaux=0;
	// control vars


};

#endif // __MODULEINTERFACE_H__