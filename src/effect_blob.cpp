#include "effect_blob.h"

#include <math.h>

EffectBlob::EffectBlob(int xw, int yw)
{
    this->xw = xw;
    this->yw = yw;

	screenbuffer_8bit = nullptr;
	blob = nullptr;
	blobs = nullptr;

    InitEffekt();
}

EffectBlob::~EffectBlob()
{
	ReleaseEffect();
}

void EffectBlob::ResetEffect()
{
	for(int i = 0; i < number_of_blobs; i++)
	{
		InitBlob(blobs + i);
	}
}

void EffectBlob::RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime)
{
	uint32_t start1, start2;

	for(int i = 0; i < xw * yw; i++)
		screenbuffer_8bit[i] = 0;

	for(int y = 0; y < yw; y++)
	{
		uint32_t *line = pixelbuffer + y * pitch;
		for(int x = 0; x < xw; x++)
		{
			*line++ = 0x00000000;
		}
	}

	for(int i = 0; i < number_of_blobs; i++)
	{
		blobs[i].xpos += -2 + (int)(5.0 * (rand()/(RAND_MAX + 1.0)));
		blobs[i].ypos += -2 + (int)(5.0 * (rand()/(RAND_MAX + 1.0)));
	}

	for(int k = 0; k < number_of_blobs; ++k)
	{
		if (blobs[k].xpos > 0 && blobs[k].xpos < xw - dradius && blobs[k].ypos > 0 && blobs[k].ypos < yw - dradius)
		{
			start1 = blobs[k].xpos + blobs[k].ypos * xw;
			start2 = blobs[k].xpos + blobs[k].ypos * pitch;

			for(int i=0; i < dradius; ++i)
			{
				for(int j=0; j < dradius; ++j)
				{
					if (screenbuffer_8bit[start1 + j] + blob[i + j * dradius] > 255)
						screenbuffer_8bit[start1 + j] = 255;
					else
						screenbuffer_8bit[start1 + j] += blob[i + j * dradius];

					pixelbuffer[start2 + j] = colors[screenbuffer_8bit[start1 + j]];
				}
				start1 += xw;
				start2 += pitch;
			}
		}
		else
			InitBlob(blobs + k);
	}
}

void EffectBlob::InitEffekt()
{
	radius = 44;
    dradius = radius * 2;
    sradius = radius * radius;
	number_of_blobs = 40;

	screenbuffer_8bit = new uint8_t [xw * yw];
	blob = new uint8_t [dradius * dradius];
	blobs = new BLOB_TYPE [number_of_blobs];

	// create palette
	for(int c = 0; c < 256; c++)
	{
		colors[c] = c << 24;	// red
		colors[c] |= c << 16;	// green
		colors[c] |= c << 8;	// blue
	}

	// create blob
	uint32_t distance_squared;
	float fraction;

	for(int i = -radius; i < radius; ++i)
	{
		for(int j = -radius; j < radius; ++j)
		{
			distance_squared = i * i + j * j;
			if(distance_squared <= sradius)
			{
				// compute density
				fraction = (float)distance_squared / (float)sradius;
				blob[(i + radius) + (j + radius) * dradius] = pow((1.0f - (fraction * fraction)),4.0f) * 255.0f;
			}
			else
				blob[(i + radius) + (j + radius) * dradius] = 0;
		}
	}

	for(int i = 0; i < number_of_blobs; i++)
	{
		InitBlob(blobs + i);
	}
}

void EffectBlob::ReleaseEffect()
{
	if(blobs != nullptr) delete [] blobs;
	if(blob != nullptr) delete [] blob;
	if(screenbuffer_8bit != nullptr) delete [] screenbuffer_8bit;
}

void EffectBlob::InitBlob(BLOB_TYPE *blob)
{
	blob->xpos = (xw >> 1) - radius;
	blob->ypos = (yw >> 1) - radius;
}
