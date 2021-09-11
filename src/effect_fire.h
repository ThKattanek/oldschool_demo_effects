#ifndef EFFECTFIRE_H
#define EFFECTFIRE_H

#include <inttypes.h>

class EffectFire
{
public:
	EffectFire(int xw, int yw);
	~EffectFire();

	void ResetEffect(uint32_t *pixelbuffer, int pitch);
	void RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime);

private:
	void InitEffect();
	void ReleaseEffect();

	int xw,yw;

	uint8_t *fire;
	uint32_t colors[256];
};

#endif // EFFECTFIRE_H
