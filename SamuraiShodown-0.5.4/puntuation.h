#ifndef __PUNTUATION_H__
#define __PUNTUATION_H__



class Puntuation
{
public:
	Puntuation() {};
	~Puntuation() {};
	// the functions will return true once their objective is completed, otherwhise they return false
	//bool CalculeTotal(){total = hitting_perc + time + life;};
	bool Resetactual()//equals the actual puntuation to the initial one
	{
		actuallife = life;
		actualtime = time;
		actualhitting_perc = hitting_perc;
		actualtotal = total;
		return true;
	};

	bool LifeSubstraction(int timetodoit) 
	{
		int substraction= life / timetodoit; //substraction of x every frame
		int substractionmodule = life % timetodoit;//more substraction the first pass to equal 0 at the end
		if (!lifemodulesubstracted)
		{
			lifemodulesubstracted = true;
			substraction += substractionmodule;
		}
		actuallife -= substraction;
		actualtotal += substraction;
		if (actuallife == 0)return true;
		else return false;
	};

	bool TimeSubstraction(int timetodoit)
	{
		int substraction = time / timetodoit; //substraction of x every frame
		int substractionmodule = time % timetodoit;//more substraction the first pass to equal 0 at the end
		if (!timemodulesubstracted)
		{
			timemodulesubstracted = true;
			substraction += substractionmodule;
		}
		actualtime -= substraction;
		actualtotal += substraction;
		if (actualtime == 0)return true;
		else return false;
	};

	bool HittingPercSubtraction(int timetodoit)
	{
		int substraction = hitting_perc / timetodoit; //substraction of x every frame
		int substractionmodule = hitting_perc % timetodoit;//more substraction the first pass to equal 0 at the end
		if (!hittingmodulesubstracted)
		{
			hittingmodulesubstracted = true;
			substraction += substractionmodule;
		}
		actualhitting_perc -= substraction;
		actualtotal += substraction;
		if (actualhitting_perc == 0)return true;
		else return false;
	};

	bool CountDelayInFrames(int delayframes)//returns false if the time set hasn't passed but true if it has
	{
		if (!countingdelay) { countingdelay = true; delayleft = delayframes; }
		delayleft--;
		if (delayleft==0)
		{
			countingdelay = false;
			return true;
		}
		else return false;
	};

public:

	int life=0;
	int time=0;
	int hitting_perc=0;//betweeen 0 and 100 (percentatge)
	int total=0;

	int actuallife=0;
	int actualtime=0;
	int actualhitting_perc=0;
	int actualtotal=0;

	bool lifemodulesubstracted = false;
	bool timemodulesubstracted = false;
	bool hittingmodulesubstracted = false;
	bool countingdelay = false;
	int delayleft = 0;

};

#endif
