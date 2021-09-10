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
    radius = 44;
    dradius = radius * 2;
    sradius = radius * radius;
    number_of_blobs = 40;
}
