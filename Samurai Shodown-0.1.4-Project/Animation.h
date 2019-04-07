#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#define MAX_FRAMES 25

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	SDL_Rect frames[MAX_FRAMES];
	float firstLoopFrame = 0.0f;

private:
	float current_frame;
	int last_frame = 0;
	bool animEnded = false;
	int loops = 0;

public:

	void PushBack(const SDL_Rect& rect)
	{
		frames[last_frame++] = rect;
	}

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
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