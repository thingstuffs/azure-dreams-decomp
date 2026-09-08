#include "common.h"

typedef struct Inner {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Inner;

typedef struct Outer {
    u8 pad[0x1C];
    Inner *inner;
} Outer;

extern Outer *D_80016000;

/* Sets the global object's inner fields to 1248 and 1184. */
void func_80017004(void) {
    Outer *outer = D_80016000;
    outer->inner->unk4 = 1248;
    outer->inner->unk8 = 1184;
}
