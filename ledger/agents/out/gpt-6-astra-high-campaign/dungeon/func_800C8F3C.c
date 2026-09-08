#include "common.h"

extern s32 D_800E296C[3];

s32 func_800CE4E8(u8 arg0, u8 arg1, s16 arg2, void *arg3, s32 arg4);

/* Return success if either global high flag is set, otherwise test the record lookup. */
s32 func_800CE69C(void *record) {
    void *source_record;

    if (D_800E296C[0] & 0xC0000000) {
        return 1;
    }
    source_record = *(void **)((s8 *)record - 0x14);
    return func_800CE4E8(((u8 *)source_record)[0x24], ((u8 *)source_record)[0x25], *(s16 *)((s8 *)record + 0x88), record, 0) != 0;
}
