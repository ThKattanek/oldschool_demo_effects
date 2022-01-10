#ifndef EFFECTSTARFIELD_H
#define EFFECTSTARFIELD_H

#include <inttypes.h>

/*star struct*/
typedef struct
{
  float xpos, ypos;
  short zpos, speed;
  uint8_t color;
} STAR;

#define NUMBER_OF_STARS 1020

class EffectStarfield
{
public:
    EffectStarfield(int xw, int yw);
    ~EffectStarfield();

    void RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime);

private:
    void InitEffekt();
    void InitStar(STAR* star, int i);

    int xw,yw;
    STAR stars[NUMBER_OF_STARS];
    uint32_t colors[256];

    uint16_t centerx, centery;
};

#endif // EFFECTSTARFIELD_H
