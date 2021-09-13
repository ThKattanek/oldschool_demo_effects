#ifndef EFFECTCOPPERBARS_H
#define EFFECTCOPPERBARS_H

#include <SDL2/SDL.h>
#include <inttypes.h>

class EffectCopperBars
{
public:
	EffectCopperBars(SDL_Renderer *renderer, int xw, int yw);
    ~EffectCopperBars();

	void RenderEffect();

private:
    void InitEffect();
    void ReleaseEffect();
	void DrawCopper(SDL_Rect* r, int add);

	SDL_Renderer *renderer;
	SDL_Texture *texTarget;

    int xw,yw;

    uint32_t *copper;
    uint16_t *aSin;

	uint16_t red, red2, red3, red4, red5, red6, red7, red8, white, white2, white3, white4, white5, white6, white7, white8, blue, blue2, blue3, blue4, blue5, blue6, blue7, blue8;

	SDL_Rect drect, crect;
};

#endif // EFFECTCOPPERBARS_H
