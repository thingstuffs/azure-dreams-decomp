#include "common.h"

extern s16 func_8008CF48();

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} Unk800C5388;

/* Queries the position after lowering its third coordinate by eight fixed-point units. */
s16 func_800C2AE8(void *position) {
    Unk800C5388 adjusted_position;
    long long result_storage;
    long long *result_ptr;

    adjusted_position.unk0 = *(s32 *)((s8 *)position + 0);
    adjusted_position.unk4 = *(s32 *)((s8 *)position + 4);
    result_ptr = &result_storage;
    adjusted_position.unk8 = *(s32 *)((s8 *)position + 8) + 0xFFF80000;
    return func_8008CF48(&adjusted_position, &result_ptr);
}

/* MECHANISM: A 24-byte escaped record plus an 8-byte pointee force the retail 0x40 frame.
   Copying both leading fields before linking sp30 to sp28 delays that address live range,
   reproducing the exact prologue, stack-store order, callee ABI setup, and s16 return. */
