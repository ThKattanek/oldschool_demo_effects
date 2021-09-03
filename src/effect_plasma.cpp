#include "effect_plasma.h"

#include <math.h>

EffectPlasma::EffectPlasma(int xw, int yw)
{
	this->xw = xw;
	this->yw = yw;

	InitEffekt();
}

EffectPlasma::~EffectPlasma()
{

}

void EffectPlasma::InitEffekt()
{
	float rad;

	/*create sin lookup table */
	for (int i = 0; i < 512; i++)
	{
		rad =  ((float)i * 0.703125) * 0.0174532; /* 360 / 512 * degree to rad, 360 degrees spread over 512 values to be able to use AND 512-1 instead of using modulo 360*/
		aSin[i] = sin(rad) * 1024; /*using fixed point math with 1024 as base*/
	}

	/* create palette */
	for (int i = 0; i < 64; ++i)
	  {
		colors[i] = (i << 2) << 24;	// red
		colors[i] |= (255 - ((i << 2) + 1)) << 16;	// green
		colors[i+64] = 255 << 24;	// red
		colors[i+64] |= ((i << 2) + 1) << 16; // green
		colors[i+128] = (255 - ((i << 2) + 1)) << 24;	// red
		colors[i+128] |= (255 - ((i << 2) + 1)) << 16;	// green
		colors[i+192] = ((i << 2) + 1) << 16; // green
	  }
}

void EffectPlasma::RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime)
{
	uint8_t index;
	int x;

	tpos4 = pos4;
	tpos3 = pos3;

	for (int i = 0; i < yw; ++i)
	{
		tpos1 = pos1 + 5;
		tpos2 = pos2 + 3;

		tpos3 &= 511;
		tpos4 &= 511;

		for (int j = 0; j < xw; ++j)
		{
			tpos1 &= 511;
			tpos2 &= 511;

			x = aSin[tpos1] + aSin[tpos2] + aSin[tpos3] + aSin[tpos4]; /*actual plasma calculation*/

			index = 128 + (x >> 4); /*fixed point multiplication but optimized so basically it says (x * (64 * 1024) / (1024 * 1024)), x is already multiplied by 1024*/

			*pixelbuffer++ = colors[index & 0xff];

			tpos1 += 5;
			tpos2 += 3;
		}

		tpos4 += 3;
		tpos3 += 1;
	}

	pos1 +=9;
	pos3 +=8;
}
