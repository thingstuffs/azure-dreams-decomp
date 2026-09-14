#include "common.h"

typedef struct S_func_800B361C_0 {
    u8 pad_00[0x10];
    volatile s32 unk_10;
    volatile s32 unk_14;
    u8 pad_18[0x4];
    volatile s32 unk_1C;
    u8 pad_20[0xAC];
    void *unk_CC;
} S_func_800B361C_0;

typedef struct S_func_800B361C_1 {
    u8 pad_00[0x74];
    void *unk_74;
    void *unk_78;
} S_func_800B361C_1;

extern s32 D_800786DC[];
extern s32 D_800786E8[];

/* Update status flags and state pointers from the current value and its limit. */
void func_800B0D7C(S_func_800B361C_0 *object) {
    if (object->unk_10 > 0) {
        S_func_800B361C_1 *state;
        s32 branch_flags;

        state = object->unk_CC;
        *(void **)state->unk_74 = D_800786DC;
        branch_flags = object->unk_1C;
        branch_flags &= ~2;
        object->unk_1C = branch_flags;
    } else {
        s32 branch_flags;

        branch_flags = object->unk_1C;
        branch_flags |= 2;
        object->unk_1C = branch_flags;
    }

    if (object->unk_10 < object->unk_14) {
        s32 clear_mask;
        S_func_800B361C_1 *state;

        do {
            clear_mask = ~1;
        } while (0);
        object->unk_1C &= clear_mask;

        state = object->unk_CC;
        *(void **)state->unk_78 = D_800786E8;
        return;
    }

    object->unk_1C |= 1;
}
