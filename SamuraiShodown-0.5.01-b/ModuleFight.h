#ifndef __MODULEFIGHT_H__
#define __MODULEFIGHT_H__

#include "Module.h"
#include "Globals.h"


class ModuleFight : public Module
{
public:
	ModuleFight();
	~ModuleFight();

	bool Start();
	update_status Update();
	bool CleanUp();

	void WinRound1(int player, bool final, bool perfect);

public:

	int rounds = 1;
	int letterTime = 0;
	int timerTime = 0;
	int playerControlTime = 0;
	bool playerControl = false;
	bool showHealthBar = false;
	int played = 0;
	bool roundfinish = false;
	int startingtime = 0;
	
	bool winplayer1 = false;
	bool winplayer2 = false;
	bool firstWin = false;
	bool start = true;
	bool finalwin1 = false;
	bool finalwin2 = false;
	bool perfect = false;
	bool timer = false;
	bool timerRound = false;
};

#endif // __MODULEFIGHT_H__