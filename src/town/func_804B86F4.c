#include "common.h"
#include "shared/record_ptrs.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Inner;

typedef struct {
    char pad[0x1C];
    Inner *inner;
} Outer;


/* Set the inner object's unk4 and unk8 fields to 1248 and 1184. */
void func_80016EF4(void) {
    ((Outer *)D_80016000)->inner->unk4 = 1248;
    ((Outer *)D_80016000)->inner->unk8 = 1184;
}
