#ifndef EFFECTEXPLOSION_H
#define EFFECTEXPLOSION_H

#include <inttypes.h>

#define NUMBER_OF_PARTICLES 500

/*particle structure*/
typedef struct
{
  uint16_t xpos,ypos,xdir,ydir;
  uint8_t colorindex;
  uint8_t dead;
} PARTICLE;

class EffectExplosion
{
public:
    EffectExplosion(int xw, int yw);
    ~EffectExplosion();

    void RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime);
    void StartNewExplosion();

private:
    void InitEffekt();
    void InitParticle(PARTICLE* particle);

    int xw,yw;
    uint8_t *fire;
    uint32_t colors[256];

    PARTICLE particles[NUMBER_OF_PARTICLES];
};

#endif // EFFECTEXPLOSION_H
