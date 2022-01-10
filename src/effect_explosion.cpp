#include "effect_explosion.h"

#include <cstdlib>

EffectExplosion::EffectExplosion(int xw, int yw)
{
    this->xw = xw;
    this->yw = yw;

    fire = new uint8_t[xw * yw];

    InitEffekt();
}

EffectExplosion::~EffectExplosion()
{
    delete [] fire;
}

void EffectExplosion::RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime)
{
    uint32_t buf, temp, index;
    uint32_t *current_pixel_line;

    /* move and draw particles into fire array */
    for (int i = 0; i < NUMBER_OF_PARTICLES; i++)
    {
        if (!particles[i].dead)
        {
            particles[i].xpos += particles[i].xdir;
            particles[i].ypos += particles[i].ydir;

            // is particle dead? //
            if ((particles[i].ypos >= yw - 3) || particles[i].colorindex == 0 || particles[i].xpos <= 1 || particles[i].xpos >= xw - 3)
            {
                particles[i].dead = 1;
                continue;
            }

            // gravity takes over //
            particles[i].ydir++;

            // particle cools off //
            particles[i].colorindex--;

            // draw particle //
            temp = particles[i].ypos * xw + particles[i].xpos;

            fire[temp] = particles[i].colorindex;
            fire[temp - 1] = particles[i].colorindex;
            fire[temp + xw] = particles[i].colorindex;
            fire[temp - xw] = particles[i].colorindex;
            fire[temp + 1] = particles[i].colorindex;
        }
    }

    /* create fire effect */
    for (int i = 1; i < yw - 2; i++)
    {
        index = (i  - 1) * xw;

        for (int j = 1; j < xw - 2; j++)
        {
            buf = index + j;

            temp = fire[buf];
            temp += fire[buf + 1];
            temp += fire[buf - 1];
            buf += xw;
            temp += fire[buf - 1];
            temp += fire[buf + 1];
            buf += xw;
            temp += fire[buf];
            temp += fire[buf + 1];
            temp += fire[buf - 1];

            temp >>= 3;

            if (temp > 4)
                temp -= 4;
            else
                temp = 0;

            fire[buf - xw] = temp;
        }
    }

    /* draw fire array to screen from bottom to top*/
    for (int i = 0; i < yw; i++)
    {
        temp = i * xw;
        current_pixel_line = pixelbuffer + i * pitch;
        for (int j = 0; j < xw; j++)
        {
           *current_pixel_line++ = colors[(fire[temp + j]) & 0xff];
        }
    }
}

void EffectExplosion::StartNewExplosion()
{
    for (int i = 0; i < NUMBER_OF_PARTICLES; i++)
      {
        InitParticle(particles + i);
      }
}

void EffectExplosion::InitEffekt()
{
    /* create a suitable fire palette, this is crucial for a good effect */
    /* black to blue, blue to red, red to yellow, yellow to white*/

    for (int i = 0; i < 32; ++i)
    {
        /* black to blue, 32 values*/
        colors[i] = (i << 1) << 8;  // blue

        /* blue to red, 32 values*/
        colors[i + 32] = (i << 3) << 24; // red
        colors[i + 32] |=  (64 - (i << 1)) << 8; // blue

        /*red to yellow, 32 values*/
        colors[i + 64] = 255 << 24; // red
        colors[i + 64] |= (i << 3) << 16; // green

        /* yellow to white, 162 */
        colors[i + 96] = 255 << 24; // red
        colors[i + 96] |= 255 << 16; // green
        colors[i + 96] |= (i << 2) << 8; // blue
        colors[i + 128] = 255 << 24; // red
        colors[i + 128] |= 255 << 16; // green
        colors[i + 128] |= (64 + (i << 2)) << 16; // green
        colors[i + 160] = 255 << 24; // red
        colors[i + 160] |= 255 << 16;  // green
        colors[i + 160] |= (128 + (i << 2)) << 8;  // blue
        colors[i + 192] = 255 << 24; // red
        colors[i + 192] |= 255 << 16; // green
        colors[i + 192] |= (192 + i) << 8; // blue
        colors[i + 224] = 255 << 24; // red
        colors[i + 224] |= 255 << 16; // green
        colors[i + 224] |= (224 + i) << 8; // blue
      }
}

void EffectExplosion::InitParticle(PARTICLE *particle)
{
    /* randomly init particles, generate them in the center of the screen */
    particle->xpos =  (xw >> 1) - 20 + (int)(40.0 * (rand()/(RAND_MAX+1.0)));
    particle->ypos =  (yw >> 1) - 20 + (int)(40.0 * (rand()/(RAND_MAX+1.0)));
    particle->xdir =   -10 + (int)(20.0 * (rand()/(RAND_MAX+1.0)));
    particle->ydir =   -17 + (int)(19.0 * (rand()/(RAND_MAX+1.0)));
    particle->colorindex = 255;
    particle->dead = 0;
}
