#include "effect_copperbars.h"

#include <math.h>

EffectCopperBars::EffectCopperBars(SDL_Renderer *renderer, int xw, int yw)
{
	this->renderer = renderer;
    this->xw = xw;
    this->yw = yw;

    copper = nullptr;
    aSin = nullptr;

	texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, xw, yw);

    InitEffect();
}

EffectCopperBars::~EffectCopperBars()
{
    ReleaseEffect();

	SDL_DestroyTexture(texTarget);
}

void EffectCopperBars::RenderEffect()
{
	SDL_SetRenderTarget(renderer, texTarget);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// draw copperbars back to front

	drect.y = aSin[blue7];
	blue8 = drect.y;
	blue7 += 2;
	blue7 %= 360;

	DrawCopper(&drect, 31);

	drect.y = aSin[blue5];
	blue6 = drect.y;
	blue5 += 2;
	blue5 %= 360;

	DrawCopper(&drect, 31);

	drect.y = aSin[blue3];
	blue4 = drect.y;
	blue3 += 2;
	blue3 %= 360;

	DrawCopper(&drect, 31);

	drect.y = aSin[blue];
	blue2 = drect.y;
	blue += 2;
	blue %= 360;

	DrawCopper(&drect, 31);

	drect.y = aSin[white7];
	white8 = drect.y;
	white7 += 2;
	white7 %= 360;

	DrawCopper(&drect, 16);

	drect.y = aSin[white5];
	white6 = drect.y;
	white5 += 2;
	white5 %= 360;

	DrawCopper(&drect, 16);

	drect.y = aSin[white3];
	white4 = drect.y;
	white3 += 2;
	white3 %= 360;

	DrawCopper(&drect, 16);

	drect.y = aSin[white];
	white2 = drect.y;
	white += 2;
	white %= 360;

	DrawCopper(&drect, 16);

	drect.y = aSin[red7];
	red8 = drect.y;
	red7 += 2;
	red7 %= 360;

	DrawCopper(&drect, 1);

	drect.y = aSin[red5];
	red6 = drect.y;
	red5 += 2;
	red5 %= 360;

	DrawCopper(&drect, 1);

	drect.y = aSin[red3];
	red4 = drect.y;
	red3 += 2;
	red3 %= 360;

	DrawCopper(&drect, 1);

	drect.y = aSin[red];
	red2 = drect.y;
	red += 2;
	red %= 360;

	DrawCopper(&drect, 1);

	SDL_SetRenderTarget(renderer, NULL);
	SDL_RenderCopy(renderer, texTarget, 0, 0);
}

void EffectCopperBars::InitEffect()
{
    copper = new uint32_t [46];
    aSin = new uint16_t [360];

    int centery = yw >> 1;
    float rad;

    // create sin lookup table
    for (int i = 0; i < 360; i++)
    {
        rad =  (float)i * 0.0174532;
        aSin[i] = centery + (sin(rad) * 100.0);
    }

    // red copper bar
    copper[1] = 0x22 << 24;
    copper[2] = 0x44 << 24;
    copper[3] = 0x66 << 24;
    copper[4] = 0x88 << 24;
    copper[5] = 0xaa << 24;
    copper[6] = 0xcc << 24;
    copper[7] = 0xee << 24;
    copper[8] = 0xff << 24;
    copper[9] = 0xee << 24;
    copper[10] = 0xcc << 24;
    copper[11] = 0xaa << 24;
    copper[12] = 0x88 << 24;
    copper[13] = 0x66 << 24;
    copper[14] = 0x44 << 24;
    copper[15] = 0x22 << 24;

    // white copper bar
    copper[16] = 0x22222200;
    copper[17] = 0x44444400;
    copper[18] = 0x66666600;
    copper[19] = 0x88888800;
    copper[20] = 0xaaaaaa00;
    copper[21] = 0xcccccc00;
    copper[22] = 0xeeeeee00;
    copper[23] = 0xffffff00;
    copper[24] = 0xeeeeee00;
    copper[25] = 0xcccccc00;
    copper[26] = 0xaaaaaa00;
    copper[27] = 0x88888800;
    copper[28] = 0x66666600;
    copper[29] = 0x44444400;
    copper[30] = 0x22222200;

    // blue copper bar
    copper[31] = 0x22 << 8;
    copper[32] = 0x44 << 8;
    copper[33] = 0x66 << 8;
    copper[34] = 0x88 << 8;
    copper[35] = 0xaa << 8;
    copper[36] = 0xcc << 8;
    copper[37] = 0xee << 8;
    copper[38] = 0xff << 8;
    copper[39] = 0xee << 8;
    copper[40] = 0xcc << 8;
    copper[41] = 0xaa << 8;
    copper[42] = 0x88 << 8;
    copper[43] = 0x66 << 8;
    copper[44] = 0x44 << 8;
    copper[45] = 0x22 << 8;

	red = 96;
	red2 = 0;
	red3 = 88;
	red4 = 0;
	red5 = 80;
	red6 = 0;
	red7 = 72;
	red8 = 0;
	white = 64;
	white2 = 0;
	white3 = 56;
	white4 = 0;
	white5 = 48;
	white6 = 0;
	white7 = 40;
	white8 = 0;
	blue = 32;
	blue2 = 0;
	blue3 = 24;
	blue4 = 0;
	blue5 = 16;
	blue6 = 0;
	blue7 = 8;
	blue8 = 0;

	drect.x = 0;
	drect.w = xw;
	drect.h = 1;

	crect.x = 0;
	crect.w = xw;
	crect.h = 15;
}

void EffectCopperBars::ReleaseEffect()
{
    if(copper != nullptr) delete [] copper;
	if(aSin != nullptr) delete [] aSin;
}

void EffectCopperBars::DrawCopper(SDL_Rect *r, int add)
{
	for (int i = 0; i < 15; i++)
	{
		SDL_SetRenderDrawColor(renderer, (copper[i + add] >> 24) & 0xff, (copper[i + add] >> 16) & 0xff, (copper[i + add] >> 8) & 0xff, 0x00);
		SDL_RenderFillRect(renderer, r);
		r->y++;
	}
}
