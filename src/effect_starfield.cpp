#include "effect_starfield.h"

#include <stdlib.h>

EffectStarfield::EffectStarfield(int xw, int yw)
{
    this->xw = xw;
    this->yw = yw;

    InitEffekt();
}

EffectStarfield::~EffectStarfield()
{

}

void EffectStarfield::RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime)
{
    int i, tempx, tempy;

    for(int i=0; i < xw*yw; i++)
            pixelbuffer[i] = 0;

    for (int i = 0; i < NUMBER_OF_STARS; i++)
    {
        stars[i].zpos -= stars[i].speed;

        if (stars[i].zpos <= 0)
            InitStar(stars + i, i + 1);

        /*compute 3D position*/
        tempx = (stars[i].xpos / stars[i].zpos) + centerx;
        tempy = (stars[i].ypos / stars[i].zpos) + centery;

        if (tempx < 0 || tempx > xw - 1 || tempy < 0 || tempy > yw - 1) /*check if a star leaves the screen*/
        {
            InitStar(stars + i, i + 1);
            continue;
        }

        *(pixelbuffer + (tempy * pitch) + tempx) = colors[stars[i].color];
    }
}

void EffectStarfield::InitEffekt()
{
    /* create and set palette */
    colors[0] = 0;

    for (int i = 0; i < 255; ++i)
    {
        colors[255 - i] = i << 24; // red
        colors[255 - i] |= i << 16; // green
        colors[255 - i] |= i << 8; // blue
    }

    for (int i = 0; i < NUMBER_OF_STARS; i++)
    {
        InitStar(stars + i, i + 1);
    }

    centerx = xw >> 1;
    centery = yw >> 1;
}

void EffectStarfield::InitStar(STAR *star, int i)
{
    /* randomly init stars, generate them around the center of the screen */

    star->xpos =  -10.0 + (20.0 * (rand()/(RAND_MAX+1.0)));
    star->ypos =  -10.0 + (20.0 * (rand()/(RAND_MAX+1.0)));

    star->xpos *= 3072.0; /*change viewpoint */
    star->ypos *= 3072.0;

    star->zpos =  i;
    star->speed =  2 + (int)(2.0 * (rand()/(RAND_MAX+1.0)));

    star->color = i >> 2; /*the closer to the viewer the brighter*/
}
