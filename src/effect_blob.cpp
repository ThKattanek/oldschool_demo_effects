#include "effect_blob.h"

EffectBlob::EffectBlob(int xw, int yw)
{
    this->xw = xw;
    this->yw = yw;

    InitEffekt();
}

EffectBlob::~EffectBlob()
{

}

void EffectBlob::RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime)
{

}

void EffectBlob::InitEffekt()
{

}
