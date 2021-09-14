#ifndef EFFECTBARSCROLLER_H
#define EFFECTBARSCROLLER_H

#include <SDL2/SDL.h>

class EffectBarscroller
{
public:
	EffectBarscroller(SDL_Renderer *renderer, SDL_Texture *image, int xw, int yw);
	~EffectBarscroller();

	void RenderEffect();

private:

	SDL_Renderer *renderer;
	int xw,yw;
};

#endif // EFFECTBARSCROLLER_H
