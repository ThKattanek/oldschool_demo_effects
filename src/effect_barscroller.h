#ifndef EFFECTBARSCROLLER_H
#define EFFECTBARSCROLLER_H

#include <SDL2/SDL.h>
#include <inttypes.h>

class EffectBarscroller
{
public:
	EffectBarscroller(SDL_Renderer *renderer, int xw, int yw, SDL_Texture *font_tex, int char_xw, int char_yw);
	~EffectBarscroller();

	void RenderEffect();

private:
	void InitEffect();
	void ReleaseEffect();
    int16_t CalculateFontPosition(char scroll_char);
    void PrintCharacter();

	SDL_Renderer *renderer;
    SDL_Texture *font_tex;

	int xw, yw, char_xw, char_yw;

	int16_t aSin[360];
	int16_t *aSin2;
	uint16_t sin_index = 0;
	char *text;
	char *characters;
	char* text_pointer = text;
	uint8_t stopscroller = 0;
	uint32_t time;

	SDL_Color colors[5];

	uint32_t i, j, displacement;
	SDL_Rect srect2;
	SDL_Rect drect;
	SDL_Rect srect;
	SDL_Rect frect;
	SDL_Rect rs;
	SDL_Rect rs2;
	Uint8* image;
};

#endif // EFFECTBARSCROLLER_H
