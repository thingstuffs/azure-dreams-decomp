#include "common.h"

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ s16 unk6;
} S_800404F8;

extern s32 allocGpuScratchRing(s32 size);
extern void zeroWords(s32 *p, s32 n);
extern s32 LoadImage(void *rect, s32 *p);

/* Allocates and zeroes an image buffer, then loads it into the destination rectangle. */
void clearImageRectWithScratchBuffer(S_800404F8 *rect) {
    s32 *image_buffer;

    image_buffer = (s32 *)allocGpuScratchRing((((s16)rect->unk4) >> 1) * rect->unk6);
    zeroWords(image_buffer, (((s16)rect->unk4) >> 1) * rect->unk6);
    LoadImage(rect, image_buffer);
}
