#include "common.h"
#include "shared/record_ptrs.h"

typedef struct Inner {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Inner;

typedef struct Outer {
    char pad[0x1C];
    Inner *inner;
} Outer;


/* Set the current inner object's unk4 and unk8 values to 1696 and 864. */
void func_80016FB4(void) {
    ((Outer *)D_80016000)->inner->unk4 = 1696;
    ((Outer *)D_80016000)->inner->unk8 = 864;
}
