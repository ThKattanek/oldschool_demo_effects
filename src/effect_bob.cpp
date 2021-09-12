#include "effect_bob.h"

EffectBob::EffectBob(SDL_Renderer *renderer, SDL_Texture *image, int xw, int yw)
{
	this->renderer = renderer;
	this->image = image;
	this->xw = xw;
	this->yw = yw;

	SDL_QueryTexture(image, NULL, NULL, &image_xw, &image_yw);



	InitEffect();
}

EffectBob::~EffectBob()
{
	ReleaseEffect();
}

void EffectBob::RenderEffect()
{
	l = i;
	m = j;

	// clear and compute bob positions

	SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_NONE);
	for (int k = 0; k < number_of_bobs; ++k)
	{
		oldrects[k].x = rects[k].x;
		rects[k].x = xpath[l & 511];
		oldrects[k].y = rects[k].y;
		rects[k].y = ypath[m & 511];

		SDL_RenderFillRect(renderer, oldrects + k);

		l += 20;
		m += 20;
	}

	// blit bobs

	SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);
		SDL_SetTextureBlendMode(image, SDL_BLENDMODE_BLEND);
	for (int k = 0; k < number_of_bobs; ++k)
	{
		SDL_RenderCopy(renderer, image, 0, rects + k);
	}

	// update positions in x and y pos table

	i += 2;
	j += 3;
	i &= 511;
	j &= 511;
}

void EffectBob::InitEffect()
{
	int hw = (xw - 60) >> 1;
	int hh = (yw - 60) >> 1;

	// create x and y values for the bobs
	for (int i = 0; i < 512; ++i)
	{
		double rad = ((float)i * 0.703125) * 0.0174532;  // spread 360 degrees over 512 values and convert to rad
		xpath[i] = sin(rad) * hw + hw;
		ypath[i] = cos(rad) * hh + hh;
	}

	number_of_bobs = 14;
	rects = new SDL_Rect [number_of_bobs];
	oldrects = new SDL_Rect [number_of_bobs];

	i = 0;
	j = 40;

	l = i;
	m = j;

	for(int k = 0; k < number_of_bobs; ++k)
	{
		rects[k].w = oldrects[k].w = image_xw;
		rects[k].h = oldrects[k].h = image_yw;
		rects[k].x = xpath[l & 511];
		rects[k].y = ypath[m & 511];
		l += 20;
		m += 20;
	}
}

void EffectBob::ReleaseEffect()
{
	delete [] rects;
	delete [] oldrects;
}
