#include "effect_copperbars.h"

#include <math.h>

EffectCopperBars::EffectCopperBars(int xw, int yw)
{
    this->xw = xw;
    this->yw = yw;

    copper = nullptr;
    aSin = nullptr;

    InitEffect();
}

EffectCopperBars::~EffectCopperBars()
{
    ReleaseEffect();
}

void EffectCopperBars::RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime)
{

}

void EffectCopperBars::InitEffect()
{
    copper = new uint32_t [46];
    aSin = new uint16_t [360];

    int centery = yw >> 1;
    float rad;

    // create sin lookup table
    for (int i = 0; i < 360; i++)
    {
        rad =  (float)i * 0.0174532;
        aSin[i] = centery + (sin(rad) * 100.0);
    }

    // red copper bar
    copper[1] = 0x22 << 24;
    copper[2] = 0x44 << 24;
    copper[3] = 0x66 << 24;
    copper[4] = 0x88 << 24;
    copper[5] = 0xaa << 24;
    copper[6] = 0xcc << 24;
    copper[7] = 0xee << 24;
    copper[8] = 0xff << 24;
    copper[9] = 0xee << 24;
    copper[10] = 0xcc << 24;
    copper[11] = 0xaa << 24;
    copper[12] = 0x88 << 24;
    copper[13] = 0x66 << 24;
    copper[14] = 0x44 << 24;
    copper[15] = 0x22 << 24;

    // white copper bar
    copper[16] = 0x22222200;
    copper[17] = 0x44444400;
    copper[18] = 0x66666600;
    copper[19] = 0x88888800;
    copper[20] = 0xaaaaaa00;
    copper[21] = 0xcccccc00;
    copper[22] = 0xeeeeee00;
    copper[23] = 0xffffff00;
    copper[24] = 0xeeeeee00;
    copper[25] = 0xcccccc00;
    copper[26] = 0xaaaaaa00;
    copper[27] = 0x88888800;
    copper[28] = 0x66666600;
    copper[29] = 0x44444400;
    copper[30] = 0x22222200;

    // blue copper bar
    copper[31] = 0x22 << 8;
    copper[32] = 0x44 << 8;
    copper[33] = 0x66 << 8;
    copper[34] = 0x88 << 8;
    copper[35] = 0xaa << 8;
    copper[36] = 0xcc << 8;
    copper[37] = 0xee << 8;
    copper[38] = 0xff << 8;
    copper[39] = 0xee << 8;
    copper[40] = 0xcc << 8;
    copper[41] = 0xaa << 8;
    copper[42] = 0x88 << 8;
    copper[43] = 0x66 << 8;
    copper[44] = 0x44 << 8;
    copper[45] = 0x22 << 8;
}

void EffectCopperBars::ReleaseEffect()
{
    if(copper != nullptr) delete [] copper;
    if(aSin != nullptr) delete [] aSin;
}
