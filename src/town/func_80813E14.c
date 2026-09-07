/* v15 = v13 (switch dispatch, no computed jump) + case-3 arg locals + address-taken
   split3 label. Tests whether the block split closes 188/189 once no computed jump
   exists to poison the address-taken label via flow.c find_basic_blocks. */
/* v13: dispatch as a real switch (no computed goto / no reachable_arms keep-alive).
   Purpose: remove the computed jump so an address-taken label is not given edges
   from it by flow.c find_basic_blocks. Costs the 2 jump-table address words in the
   harness (our own .rdata table) which resolve to retail's table in the real TU. */
/* v06: row inside the index, column as the added term. fold rewrites (ADDR+row400)+col40
   into row400 + (col40 + ADDR) -- retail's tree: $v1 row chain outer, $v0 column chain
   plus the global materialised in $a0. */
#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct Func80813E14Stack {
    void *object;
    u32 word0;
    u32 word1;
    u16 zero0;
    u16 half;
    u16 zero1;
} Func80813E14Stack;

typedef struct Func80813E14Object {
    u8 *base;
    u8 pad04[0x50 - 4];
    s16 mode;
    u16 timer;
    u8 pad54[2];
    s16 column;
    u16 flags;
} Func80813E14Object;

typedef struct Func80813E14State {
    s32 origin;
    s32 height;
    s32 progress;
    u8 pad0C[8];
    s32 delta;
} Func80813E14State;

typedef struct Func80813E14Base {
    u8 pad00[0x10];
    s16 column;
    u8 pad12[0x18 - 0x12];
    s16 row;
    u16 flags;
} Func80813E14Base;

typedef struct Func80813E14Input {
    u8 *kind;
    u8 pad04[8];
    union {
        u8 byte;
        u32 word;
    } value0C;
    u8 pad10[4];
    u16 flags;
} Func80813E14Input;

extern s32 D_80084D5C;
extern u8 D_8028E194[];
extern u8 D_8028E214[];
extern u8 D_80530220[];

extern void func_80034A1C(void *, void *, s32);
extern void func_8003EA54(void *);
extern u32 func_80071494(void);
extern void func_8023FB18(void *);
extern void func_8052E4C0(u32, s32, s32, u32);
extern void func_8052E5C8(void *, s32, s32);
extern void func_8052FE94(s32);

void func_8052EA14(Func80813E14Object *object,
                   Func80813E14State *state,
                   Func80813E14Input *input)
{
    static void *const keep_split[] __attribute__((used)) = { &&split3 };
    Func80813E14Base *base;
    Func80813E14Stack local;
    u8 *record;
    u16 bits;
    s32 dispatch;
    s32 i;
    s32 value0;
    s32 value;
    s32 next_value;
    s32 x;
    s32 random_low;
    u32 random;
    s32 case_0_height;
    s32 case_3_height;
    s32 position_base;

    base = (Func80813E14Base *)object->base;

    if (object->flags & 2) {
        if (input->value0C.byte != 0) {
            input->value0C.word += 0xFFFEFEFF;
        }
    }

    bits = base->flags;
    base->flags = bits | 2;
    if (object->flags & 1) {
        base->flags = bits | 6;
    }

    func_8003EA54(input);

    if (object->flags & 4) {
        if (input->kind == D_8028E194) {
            func_80034A1C(input, D_8028E214, 0);
        }
    }

    if (input->flags & 0x6000) {
        func_80034A1C(input, D_8028E194, 0);
    }

    dispatch = object->mode;
    switch (dispatch) {
    case 0:
    value0 = state->progress;
    if (value0 > 0) {
        i = 3;
        state->progress = value0 + state->delta;
        case_0_height = 0x80000;
        do {
            i--;
            x = func_80071494() & 0xFF;
            x -= 0x80;
            x <<= 14;
            x += state->origin;
            random = func_80071494();
            func_8052E4C0(0x00808080, x, state->height + case_0_height,
                          (random & 0xF) << 16);
        } while (i >= 0);
        goto cleanup;
    }
    state->progress = 0;
    state->delta = 0;
    object->mode = 1;
    goto cleanup;

    case 1:
    if (!(base->flags & 1)) {
        goto cleanup;
    }
    record = &D_80530220[base->row * 400] + base->column * 40;
    record += object->column * 12 + 4;
    local.half = FIELD(record, u16, 8);
    local.word0 = FIELD(record, u32, 0);
    local.word1 = FIELD(record, u32, 4);
    local.zero0 = 0;
    local.zero1 = 0;
    local.object = object;
    func_8052E5C8(&local, state->height, 0);
    goto cleanup;

    case 2:
    bits = object->timer - 1;
    object->timer = bits;
    if ((s16)bits > 0) {
        goto cleanup;
    }
    if (object->column == 0) {
        func_8052FE94(0x5A);
    }
    state->delta = 0x40000;
    object->mode = 3;
    goto cleanup;

    case 3:
    value = state->progress;
    if (value > 0x7FFFFF) {
        goto case_3_high;
    }
    next_value = value + state->delta;
    state->progress = next_value;
    if (next_value > 0x3FFFFF) {
        goto cleanup;
    }
    i = 3;
    position_base = 0x05600000;
    case_3_height = 0x80000;
    do {
        i--;
        x = func_80071494() & 0xFF;
        x -= 0x80;
        x <<= 14;
        x += position_base;
        random = func_80071494();
        {
            u32 arg0 = 0x00808080;
            s32 arg1 = x;
            u32 arg3 = (random & 0xF) << 16;
split3:
            func_8052E4C0(arg0, arg1, state->height + case_3_height, arg3);
        }
    } while (i >= 0);
    goto cleanup;

case_3_high:
    object->timer = 2;
    object->mode = 4;
    goto cleanup;

    case 4:
    bits = object->timer - 1;
    object->timer = bits;
    if ((s16)bits > 0) {
        goto cleanup;
    }
    func_8023FB18((u8 *)object + 4);
    FIELD(object, u16, -2) |= 0x8000;
    D_80084D5C |= 0x8000;
    }

cleanup:
    object->flags &= 0xFFFD;
}
