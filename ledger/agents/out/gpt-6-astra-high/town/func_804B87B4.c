#include "common.h"

typedef struct Inner {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Inner;

typedef struct Outer {
    char pad[0x1C];
    Inner *inner;
} Outer;

extern Outer *D_80016000;

/* Set the current inner object's unk4 and unk8 values to 1696 and 864. */
void func_80016FB4(void) {
    D_80016000->inner->unk4 = 1696;
    D_80016000->inner->unk8 = 864;
}
