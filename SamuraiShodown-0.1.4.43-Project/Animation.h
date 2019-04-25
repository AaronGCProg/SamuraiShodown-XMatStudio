#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"

#define MAX_FRAMES 25

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	float speedinframes = 1.0f;//
	SDL_Rect frames[MAX_FRAMES];
	int framesXframe[MAX_FRAMES];
	float firstLoopFrame = 0.0f;

public:
	float current_frame;
	int last_frame = 0;
	bool animEnded = false;
	int loops = 0;

public:

	void PushBack(const SDL_Rect& rect,int frXfr)
	{
		framesXframe[last_frame] = frXfr; //saves frame lenght of the frame animation
		frames[last_frame++] = rect;
	}

	SDL_Rect& GetCurrentFrame()
	{
		//current_frame += speed;
		float auxframe = (1.0f/(framesXframe[(int)current_frame]));
		current_frame += auxframe;// frames per frame (24 frames x sec) 
		//!!have to do it for the actual game speed
		if (current_frame >= last_frame) {
			current_frame = (loop) ? firstLoopFrame : last_frame - 1;
			animEnded = true;
			loops++;
		}
			
		return frames[(int)current_frame];
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