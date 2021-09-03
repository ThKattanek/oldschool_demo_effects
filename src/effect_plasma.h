#ifndef EFFECTPLASMA_H
#define EFFECTPLASMA_H

#include <inttypes.h>

class EffectPlasma
{
public:
	EffectPlasma(int xw, int yw);
	~EffectPlasma();

	void RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime);

private:
	void InitEffekt();

	int xw,yw;
	uint16_t pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 0, tpos1, tpos2, tpos3, tpos4;
	int aSin[512];
	uint32_t colors[256];
};

#endif // EFFECTPLASMA_H
