#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_FRAMES 40

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	float speedinframes = 1.0f;
	
	float firstLoopFrame = 0.0f;
	int framesXframe[MAX_FRAMES]; //array of time elapsed in frames for each step of the animation
	SDL_Rect frames[MAX_FRAMES];  //rectangles containing the image for each frame of the animation
	p2Point <int> pivotpos[MAX_FRAMES]; //array of (x,y) coordinates, containing the pivot for each animation frame
	SDL_Rect hitbox[MAX_FRAMES]; //rectangles containing the hitboxes for each frame
	COLLIDER_TYPE tipo[MAX_FRAMES]; //enum describing the type of each collider
	Module *callback[MAX_FRAMES]; //array of pointers to module
	int collidersmax[MAX_FRAMES]; //number of collision boxes in every animation frame
	int damage = 0;
	int playerDelay = 0;
	int enemyDelay = 0;
	int attackType = 0;

public:
	float current_frame;
	int last_frame = 0;
	bool animEnded = false;
	int loops = 0;

	

public:

	void PushBack(const SDL_Rect& rect,int frXfr,p2Point <int> PivPos,int nColliders, SDL_Rect rhitbox[],COLLIDER_TYPE ctipo[], Module *pcallback[], int cdamage, int cplayerDelay, int cenemyDelay, int cattackType)
	{
		framesXframe[last_frame] = frXfr; //saves frame lenght of the frame animation
		pivotpos[last_frame] = PivPos;
		frames[last_frame] = rect;

		damage = cdamage;
		playerDelay = cplayerDelay;
		enemyDelay = cenemyDelay;
		attackType = cattackType;
		
		collidersmax[last_frame] = nColliders;
		for (int i = 0; i < nColliders; i++)
		{
			
			hitbox[i] = rhitbox[i];
			tipo[i] = ctipo[i];

			callback[i]=pcallback[i];
		}
		last_frame++;
	}

	SDL_Rect& GetCurrentFrame() 
	{//returns the rectangle displaying the current animation
		//current_frame += speed;
		float auxframe2 = current_frame;
		float auxframe = (1.0f/(framesXframe[(int)current_frame]));
		current_frame += auxframe;// frames per frame (24 frames x sec) 
		//!!have to do it for the actual game speed
		if (current_frame >= last_frame) {
			current_frame = (loop) ? firstLoopFrame :  - 1;
			animEnded = true;
			loops++;
		}
			
		return frames[(int)auxframe2];
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		current_frame = 0;
	}

	bool GetAnimEnd() { return animEnded; }
	void SetAnimEnd(bool end) { animEnded = end; }
};

#endif