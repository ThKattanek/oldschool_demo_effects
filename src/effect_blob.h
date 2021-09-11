#ifndef EFFECTBLOB_H
#define EFFECTBLOB_H

#include <inttypes.h>

typedef struct
{
  int16_t xpos,ypos;
} BLOB_TYPE;

class EffectBlob
{
public:
    EffectBlob(int xw, int yw);
    ~EffectBlob();

	void ResetEffect();
    void RenderEffect(uint32_t *pixelbuffer, int pitch, float frametime);

private:
    void InitEffekt();
	void ReleaseEffect();
	void InitBlob(BLOB_TYPE *blob);

    int xw,yw;

    int radius;
    int dradius;
	uint32_t sradius;
    int number_of_blobs;

	uint8_t *screenbuffer_8bit;

    uint32_t colors[256];

	uint8_t *blob;
	BLOB_TYPE *blobs;
};

#endif // EFFECTBLOB_H
