#include "common.h"

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ u16 unk4;
    /* 0x06 */ s16 unk6;
} S_800404F8;

extern s32 func_80040574(s32 size);
extern void func_8003DB4C(s32 *p, s32 n);
extern s32 LoadImage(void *rect, s32 *p);

/* Allocates a load-buffer sized from the struct's fields, zeroes it, then
 * kicks off a LoadImage using the struct itself as the destination rect. */
void func_800404F8(S_800404F8 *s) {
    s32 *p;

    p = (s32 *)func_80040574((((s16)s->unk4) >> 1) * s->unk6);
    func_8003DB4C(p, (((s16)s->unk4) >> 1) * s->unk6);
    LoadImage(s, p);
}
