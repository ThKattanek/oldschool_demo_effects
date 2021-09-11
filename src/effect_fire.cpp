#include "effect_fire.h"

#include <cstdlib>

EffectFire::EffectFire(int xw, int yw)
{
	this->xw = xw;
	this->yw = yw;

	fire = nullptr;

	InitEffect();
}

EffectFire::~EffectFire()
{
	ReleaseEffect();
}

void EffectFire::ResetEffect(uint32_t *pixelbuffer, int pitch)
{
	for(int y = 0; y < yw; y++)
	{
		uint32_t *line = pixelbuffer + y * pitch;
		for(int x = 0; x < xw; x++)
		{
			*line++ = 0x00000000;
		}
	}
}

void EffectFire::RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime)
{
	uint16_t temp;

	// draw random bottom line in fire array
	int j = xw * (yw - 1);

	for(int i = 0; i < xw - 1; i++)
	{
		int random = 1 + (int)(16.0 * (rand()/(RAND_MAX+1.0)));
		if (random > 9) /* the lower the value, the intenser the fire, compensate a lower value with a higher decay value*/
			fire[j + i] = 255; /*maximum heat*/
		else
			fire[j + i] = 0;
	}

	// move fire upwards, start at bottom
	for (uint8_t index = 0; index < 60 ; ++index)
	{
		for (int i = 0; i < xw - 1; ++i)
		{
			if (i == 0) /* at the left border*/
			{
				temp = fire[j];
				temp += fire[j + 1];
				temp += fire[j - xw];
				temp /=3;
			}
			else if (i == xw - 1) /* at the right border*/
			{
				temp = fire[j + i];
				temp += fire[j - xw + i];
				temp += fire[j + i - 1];
				temp /= 3;
			}
			else
			{
				temp = fire[j + i];
				temp += fire[j + i + 1];
				temp += fire[j + i - 1];
				temp += fire[j - xw + i];
				temp >>= 2;
			}
			if (temp > 1)
				temp -= 1; /* decay */

			fire[j - xw + i] = temp;
		}
		j -= xw;
	}

	// draw fire array to screen from bottom to top + 300

	uint32_t *image = pixelbuffer + (pitch * yw);

	for (int i = yw - 3; i >= 300; --i)
	{
		for (int j = xw - 1; j >= 0; --j)
		{
			*image = colors[fire[i * xw + j]];
			image--;
		}
	}
}

void EffectFire::InitEffect()
{
	fire = new uint8_t [xw * yw];

	// create fire palette
	for (int i = 0; i < 32; ++i)
	{
		/* black to blue, 32 values*/
		colors[i] = (i << 1) << 8; // blue

		/* blue to red, 32 values*/
		colors[i + 32] = (i << 3) << 24; // red
		colors[i + 32] |=  (64 - (i << 1)) << 8; // blue

		/*red to yellow, 32 values*/
		colors[i + 64] = 255 << 24;	// red
		colors[i + 64] |= (i << 3) << 16; // green

		/* yellow to white, 162 */
		colors[i + 96] = 255 << 24;	// red
		colors[i + 96] |= 255 << 16; // green
		colors[i + 96] |= (i << 2) << 8; // blue

		colors[i + 128] = 255 << 24; // red
		colors[i + 128] |= 255 << 16; // green
		colors[i + 128] |= (64 + (i << 2)) << 8; // blue

		colors[i + 160] = 255 << 24; // red
		colors[i + 160] |= 255 << 16; // green
		colors[i + 160] |= (128 + (i << 2)) << 8; // blue

		colors[i + 192] = 255 << 24; // red
		colors[i + 192] |= 255 << 16; // green
		colors[i + 192] |= (192 + i) << 8; // blue

		colors[i + 224] = 255 << 24; // red
		colors[i + 224] |= 255 << 16; // green
		colors[i + 224] |= (224 + i) << 8; // blue
	}
}

void EffectFire::ReleaseEffect()
{
	if(fire != nullptr) delete [] fire;
}
