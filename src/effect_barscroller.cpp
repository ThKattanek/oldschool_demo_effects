#include "effect_barscroller.h"

#include <iostream>

EffectBarscroller::EffectBarscroller(SDL_Renderer *renderer, int xw, int yw, SDL_Texture *font_tex, int char_xw, int char_yw)
{
	this->renderer = renderer;
	this->xw = xw;
	this->yw = yw;
	this->char_xw = char_xw;
	this->char_yw = char_yw;

    this->font_tex = font_tex;

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
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    //SDL_RenderClear(renderer);

    PrintCharacter();
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

	float rad;
	short centery = yw >> 1;

	// create sin lookup table
	for (int i = 0; i < 360; i++)
	  {
		rad =  (float)i * 0.0174532;
		aSin[i] = centery + (short)((sin(rad) * 75.0));
	  }

	for (int i = 0; i < xw + char_xw; i++)
	  {
		rad =  (float)i * 0.0174532 * (360.0 / (xw + char_xw)) ; /* spread 360 degrees over SCREEN_WIDTH  + CHARACTER_WIDTH values */
		aSin2[i] = (short)((sin(rad) * 100.0));
	  }

	// create palette
	colors[1].g = 64;
	colors[2].g = 128;
	colors[3].g = 200;
	colors[4].g = 255;

	displacement = 0;
	j = 0;
	srect2 = {0, 0, 1, char_yw};
	drect = {0, 0, 1, char_yw};
	srect = {2, 0, xw + (char_xw * 2), char_yw};
	frect = {0, xw / 2 - 75, xw, 182};
	rs = {0, 0, 1, char_yw};
	rs2 = {0, 0, 1, char_yw};
}

void EffectBarscroller::ReleaseEffect()
{
	if(aSin2 != nullptr) delete [] aSin2;
    if(text != nullptr) delete [] text;
}

int16_t EffectBarscroller::CalculateFontPosition(char scroll_char)
{
    char* p = characters;
    Uint16 pos = 0;

    if (scroll_char == '\0')
      {
        text_pointer = text;
        scroll_char = *text_pointer++;
      }
    else if (scroll_char =='"')
      {
        stopscroller = 1;
        time = SDL_GetTicks();
        return 0;
      }

    while (*p++ != scroll_char)
      {
        pos += char_xw;
      }

    if (pos > 0)
      return pos - 1;

    return 0;
}

void EffectBarscroller::PrintCharacter()
{
    static SDL_Rect frect = {0, 0, char_xw, char_yw};
    static SDL_Rect srect = {xw + char_xw, 0, char_xw, char_yw};

    // determine font character according to position in scroll text
    frect.x = CalculateFontPosition(*text_pointer++) - 1;
    srect.x = 300;

    // copy character to scroll_screen
    SDL_RenderCopy(renderer, font_tex, &frect, &srect);
}
