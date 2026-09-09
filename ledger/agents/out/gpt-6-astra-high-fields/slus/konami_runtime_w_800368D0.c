#include "common.h"

#include "common.h"

typedef void (*Callback)(void);

extern void func_800368F8(void);

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct S_func_800368D0_0 {
    u8 pad_00[0x44];
    u8 *unk_44;
    u8 pad_48[0x2];
    s16 unk_4A;
    u8 pad_4C[0x1C];
    Callback unk_68;
} S_func_800368D0_0;

typedef struct S_func_800368D0_1 {
    u8 pad_00[0x50];
    u8 unk_50;
} S_func_800368D0_1;

/* Writes 0xFF to the selected buffer byte and selects func_800368F8 as the callback. */
void func_800368D0(S_func_800368D0_0 *state) {
    u8 *buffer;
    s16 byte_offset;

    buffer = state->unk_44;
    byte_offset = state->unk_4A;
    ((S_func_800368D0_1 *)(buffer + byte_offset))->unk_50 = 0xFF;
    state->unk_68 = func_800368F8;
}
