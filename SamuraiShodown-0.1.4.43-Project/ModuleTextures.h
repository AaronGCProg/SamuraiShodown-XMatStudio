#ifndef __ModuleTextures_H__
#define __ModuleTextures_H__

#include "Module.h"
#include "Globals.h"

#define MAX_TEXTURES 50

struct SDL_Texture;
struct SDL_Surface;

class ModuleTextures : public Module
{
public:
	ModuleTextures();
	~ModuleTextures();

	bool Init();
	bool CleanUp();

	SDL_Texture* const Load(const char* path);
	bool Unload(SDL_Texture * texture);
	SDL_Texture* LoadSurface(SDL_Surface* surface);
	void GetSize(const SDL_Texture* texture, uint& width, uint& height) const;
public:
	SDL_Texture* textures[MAX_TEXTURES];
};

#endif // __ModuleTextures_H__