#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"

#include <string.h>

// Constructor
ModuleFonts::ModuleFonts() : Module()
{}

// Destructor
ModuleFonts::~ModuleFonts()
{}

// Load new texture from file path
int ModuleFonts::Load(const char* texture_path, const char* characters, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);
	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		LOG("Could not load font at %s with characters '%s'", texture_path, characters);
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].graphic == nullptr)
			break;

	if (id == MAX_FONTS)
	{
		LOG("Cannot load font %s. Array is full (max %d).", texture_path, MAX_FONTS);
		return id;
	}

	uint texturew, textureh;
	fonts[id].graphic = tex; // graphic: pointer to the texture
	fonts[id].rows = rows; // rows: rows of characters in the texture
	App->textures->GetSize(tex, texturew, textureh);
	fonts[id].len = strlen(characters); // len: length of the table
	fonts[id].char_w = texturew / (fonts[id].len / rows);
	fonts[id].char_h = (textureh / rows) - rows;//there's a blank pixel line before every row
	fonts[id].row_chars = fonts[id].len / rows;
	SDL_strlcpy(fonts[id].table, characters, fonts[id].len+1);


	// TODO 1: Finish storing font data


	// table: array of chars to have the list of characters
	// row_chars: amount of chars per row of the texture
	// char_w: width of each character
	// char_h: height of each character

	LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void ModuleFonts::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr)
	{
		App->textures->Unload(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

// Render text using a bitmap font
void ModuleFonts::BlitText(int x, int y, int font_id, const char* text) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].graphic == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}
	int charPosX = 0;
	const Font* font = &fonts[font_id];
	SDL_Rect rect;
	uint len = strlen(text);

	rect.w = font->char_w;
	rect.h = font->char_h;

	for (uint i = 0; i < len; i++)//itinerating each letter
	{
		for (uint j = 0; j < font->len; j++)//searching for the letter on the table
		{
			if (text[i] == font->table[j])//if there's a match
			{

				rect.y = rect.h*(j / font->row_chars); //x position of the rectangle in the texture
				rect.x = rect.w*(j%font->row_chars);//y position of the rectangle in the texture

				App->render->Blit(font->graphic, x + (rect.w*charPosX), y,false, &rect, 0, false);//Blit of the font, each letter goes on a greater x pos
				charPosX++;
				break;
			}

		}

	}
}
