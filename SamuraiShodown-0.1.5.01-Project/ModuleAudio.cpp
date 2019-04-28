#include "Globals.h"
#include "ModuleAudio.h"

ModuleAudio::ModuleAudio() : Module()
{
	for (int i = 0; i < MAX_SOUNDTRACK; i++)
	{
		soundtracks[i] = nullptr;
	}

	for (int z = 0; z < MAX_EFFECTS; z++)
	{
		effects[z] = nullptr;
	}
}

// Destructor
ModuleAudio::~ModuleAudio() {};

// Called before render is available
bool ModuleAudio::Init()
{
	LOG("Init Audio library");


	SDL_Init(SDL_INIT_AUDIO);

	// load support for the OGG sample/music formats



	int flags = MIX_INIT_OGG | MIX_INIT_MOD;
	int initted = Mix_Init(flags);
	if (initted & flags != flags) {
		LOG("Mix_Init: Failed to init required ogg and mod support!\n");
		LOG("Mix_Init: %s\n", Mix_GetError());
		// handle error
	}

	Mix_OpenAudio(48000, AUDIO_U8, 2, 1024);

	/*	MIX FORMATS
	AUDIO_U8
	Unsigned 8-bit samples
	AUDIO_S8
	Signed 8-bit samples
	AUDIO_U16LSB
	Unsigned 16-bit samples, in little-endian byte order
	AUDIO_S16LSB
	Signed 16-bit samples, in little-endian byte order
	AUDIO_U16MSB
	Unsigned 16-bit samples, in big-endian byte order
	AUDIO_S16MSB
	Signed 16-bit samples, in big-endian byte order
	AUDIO_U16
	same as AUDIO_U16LSB (for backwards compatability probably)
	AUDIO_S16
	same as AUDIO_S16LSB (for backwards compatability probably)
	AUDIO_U16SYS
	Unsigned 16-bit samples, in system byte order
	AUDIO_S16SYS
	Signed 16-bit samples, in system byte order
	*/


	Mix_VolumeMusic(MUSIC_VOLUME);
	Mix_Volume(0, MIX_MAX_VOLUME / 2);
	Mix_Volume(1, MIX_MAX_VOLUME / 2);
	Mix_Volume(2, MIX_MAX_VOLUME / 2);
	Mix_Volume(3, MIX_MAX_VOLUME / 2);
	Mix_Volume(4, MIX_MAX_VOLUME / 2);


	return true;
}



// Called before quitting
bool ModuleAudio::CleanUp()
{

	for (int i = 0; i < MAX_SOUNDTRACK; i++)
	{
		if (soundtracks[i] != nullptr) {
			Mix_FreeMusic(soundtracks[i]);
			soundtracks[i] = nullptr;
		}
			
	}

	for (int z = 0; z < MAX_EFFECTS; z++)
	{
		if (effects[z] != nullptr) {
			Mix_FreeChunk(effects[z]);
			effects[z] = nullptr;
		}			
	}


	Mix_Quit();

	return true;
}