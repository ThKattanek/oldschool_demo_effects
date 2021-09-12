#ifndef EFFECTBOB_H
#define EFFECTBOB_H

#include <SDL2/SDL.h>
#include <inttypes.h>

class EffectBob
{
public:
	EffectBob(SDL_Renderer *renderer, SDL_Texture *image, int xw, int yw);
	~EffectBob();

	void RenderEffect();

private:
	void InitEffect();
	void ReleaseEffect();

	SDL_Renderer *renderer;
	SDL_Texture *image;
	int image_xw;
	int image_yw;

	int xw,yw;

	int xpath[512];
	int ypath[512];

	int number_of_bobs;

	uint32_t i, j, l, m;

	SDL_Rect *rects;
	//SDL_Rect *oldrects;
};

#endif // EFFECTBOB_H
