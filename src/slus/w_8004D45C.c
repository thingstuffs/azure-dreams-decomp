#include "common.h"

/* Source struct: only the high halfwords (offsets 2, 6, 0xA) of what appear to be
   three consecutive 32-bit fields are read -- likely a Vec3 of fixed-point/s32
   values, of which only the upper 16 bits (integer part) are used here. */
typedef struct S_8004D45C_Src {
    s16 unk0;
    s16 f2;
    s16 unk4;
    s16 f6;
    s16 unk8;
    s16 fA;
} S_8004D45C_Src;

typedef struct S_8004D45C_Buf {
    s16 f0;
    s16 f2;
    s16 f4;
} S_8004D45C_Buf;

extern s32 func_8004D294(void *a0, void *a1, u16 a2, s32 a3);

/* Builds a compact 3xs16 buffer from a0's high halfwords (or passes NULL through
   if a0 is NULL), then tail-calls func_8004D294 forwarding a1/a3 and masking a2. */
s32 func_8004D45C(S_8004D45C_Src *a0, void *a1, u32 a2, s32 a3) {
    S_8004D45C_Buf buf;
    void *v1 = 0;

    if (a0 != 0) {
        buf.f0 = a0->f2;
        buf.f2 = a0->f6;
        buf.f4 = a0->fA;
        v1 = &buf;
    }
    return func_8004D294(v1, a1, a2 & 0xFFFF, a3);
}
