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

/* Packs the source's high halfwords, preserving NULL, and calls func_8004D294 with a 16-bit value. */
s32 func_8004D45C(S_8004D45C_Src *source, void *forwarded_ptr, u32 value, s32 forwarded_value) {
    S_8004D45C_Buf high_words;
    void *packed_source = 0;

    if (source != 0) {
        high_words.f0 = source->f2;
        high_words.f2 = source->f6;
        high_words.f4 = source->fA;
        packed_source = &high_words;
    }
    return func_8004D294(packed_source, forwarded_ptr, value & 0xFFFF, forwarded_value);
}
