#ifndef EFFECTBLOB_H
#define EFFECTBLOB_H

#include <inttypes.h>

class EffectBlob
{
public:
    EffectBlob(int xw, int yw);
    ~EffectBlob();

    void RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime);

private:
    void InitEffekt();

    int xw,yw;
};

#endif // EFFECTBLOB_H
