#ifndef EFFECTEXPLOSION_H
#define EFFECTEXPLOSION_H

#include <inttypes.h>

class EffectExplosion
{
public:
    EffectExplosion(int xw, int yw);
    ~EffectExplosion();

    void RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime);

private:
    void InitEffekt();

    int xw,yw;
};

#endif // EFFECTEXPLOSION_H
