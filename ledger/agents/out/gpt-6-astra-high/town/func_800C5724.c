#include "common.h"

extern void func_800C2CB0(void *arg0, void *arg1, s32 arg2, s32 arg3);
extern s32 func_800C2E1C(s16 arg0, s16 arg1, s32 *arg2);

typedef struct {
    /* 0x64 */ char pad0[0x64];
    /* 0x64 */ s16 unk64;
    /* 0x66 */ char pad1[0x0C];
    /* 0x72 */ s16 unk72;
    /* 0x74 */ char pad2[0x02];
    /* 0x78 */ s32 *unk78;
} Struct800C5724;

/* Store and count a zero-terminated entry list, then initialize the output with a selected entry. */
void func_800C2E84(Struct800C5724 *state, s8 *output, s32 *entries) {
    s32 *entry_end;
    s16 entry_count;

    entry_end = entries;
    state->unk78 = entry_end;
    entry_count = 0;
    if (*entry_end != 0) {
        do {
            entry_end += 1;
            entry_count++;
        } while (*entry_end != 0);
    }
    state->unk64 = entry_count;
    func_800C2CB0(state, output, state->unk78[func_800C2E1C(state->unk72, entry_count, entry_end)], 0);
    output[5] = 0;
}
