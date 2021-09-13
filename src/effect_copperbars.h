#ifndef EFFECTCOPPERBARS_H
#define EFFECTCOPPERBARS_H

#include <inttypes.h>

class EffectCopperBars
{
public:
    EffectCopperBars(int xw, int yw);
    ~EffectCopperBars();

    void RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime);

private:
    void InitEffect();
    void ReleaseEffect();

    int xw,yw;

    uint32_t *copper;
    uint16_t *aSin;
};

#endif // EFFECTCOPPERBARS_H
