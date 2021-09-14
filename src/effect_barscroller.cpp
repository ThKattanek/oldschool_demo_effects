#include "effect_barscroller.h"

EffectBarscroller::EffectBarscroller(SDL_Renderer *renderer, int xw, int yw, SDL_Texture *font_tex, int char_xw, int char_yw)
{
	this->renderer = renderer;
	this->xw = xw;
	this->yw = yw;
	this->char_xw = char_xw;
	this->char_yw = char_yw;

	aSin2 = nullptr;
	text = nullptr;

	InitEffect();
}

EffectBarscroller::~EffectBarscroller()
{
	ReleaseEffect();
}

void EffectBarscroller::RenderEffect()
{

}

void EffectBarscroller::InitEffect()
{
	aSin2 = new int16_t [xw + char_xw];
	sin_index = 0;
	text = new char[1024];
	sprintf(text, "%s"," THE DEMO EFFECTS COLLECTION   \"     - CHEERS -           W.P. VAN PAASSEN         \"  -    STARTING OVER AGAIN IN -      9  8  7  6  5  4  3  2  1          ");
	characters = new char [256];
	sprintf(characters, "%s"," !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
	text_pointer = text;
	stopscroller = 0;
}

void EffectBarscroller::ReleaseEffect()
{
	if(aSin2 != nullptr) delete [] aSin2;
	if(text != nullptr) delete [] text;
}
