#include "common.h"

typedef struct S_800847D0 {
    /* 0x00 */ u32 flags1;
    /* 0x04 */ u32 flags2;
    /* 0x08 */ u32 field8;
    /* 0x0C */ u32 fieldC;
    /* 0x10 */ u32 field10;
    /* 0x14 */ u32 field14;
    /* 0x18 */ u8 pad18[0x18];
    /* 0x30 */ u8 field30;
    /* 0x31 */ u8 field31;
    /* 0x32 */ u8 field32;
    /* 0x33 */ u8 field33;
} S_800847D0;

typedef struct S_80084858 {
    /* 0x00 */ u8 pad0[0xC];
    /* 0x0C */ s32 field_C;
    /* 0x10 */ s16 field_10;
} S_80084858;

extern S_800847D0 D_800847D0;
extern S_80084858 D_80084858;

/* Activates and clears pending state, rearms the counter and timer, and clears status flags. */
void func_80054C58(void) {
    S_800847D0 *state = &D_800847D0;
    u32 pending_word_a = state->field10;
    u32 pending_word_b = state->field14;
    u8 pending_byte_a = state->field31;
    u8 pending_byte_b = state->field33;

    state->field10 = 0;
    state->field14 = 0;
    state->field31 = 0;
    state->field33 = 0;

    D_80084858.field_C = 3;
    D_80084858.field_10 = 0x80;

    state->field8 = pending_word_a;
    state->fieldC = pending_word_b;
    state->field30 = pending_byte_a;
    state->field32 = pending_byte_b;

    state->flags1 &= ~0x400;
    state->flags1 &= ~0x4000;
    state->flags2 &= ~0x200;
}
