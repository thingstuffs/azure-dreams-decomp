#include "common.h"

typedef struct {
    u8 pad0[0x92];
    s16 field92;
    u8 pad94[2];
    u16 field96;
    u16 field98;
    u8 pad9A;
    u8 state;
    u8 pad9C[6];
    u16 flagsA2;
} FuncArg0;

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[2];
    u16 field6;
    u8 pad8[0xC];
    s32 field14;
} FuncArg1;

typedef struct {
    u8 pad0[0x24];
    u8 field24;
    u8 field25;
} FuncArg2;

typedef struct {
    u8 pad0[0x1C];
    s32 field1C;
    u8 pad20[0xA];
    u16 field2A;
    u8 pad2C[0x3E];
    u16 field6A;
    u8 pad6C[0x1C];
    s16 field88;
} FuncArg3;

typedef struct {
    u8 pad0[0xA];
    u16 fieldA;
} D80083460;

extern D80083460 D_80083460;
extern u8 D_800DCF58[9];

extern void func_8009A21C(u8, u8, s32);
extern void func_800A2B04(FuncArg1 *, u8, u8);
extern s16 func_800BCB04(u16, u16, s32);
extern void func_80096088(FuncArg0 *, FuncArg3 *);

/* Updates a spinning movement sequence and restores the actor's original rotation. */
void func_80090548(FuncArg0 *motion, FuncArg1 *position, FuncArg2 *tile, FuncArg3 *actor_arg) {
    FuncArg3 *actor;
    register s32 flags_mask;
    s32 state;
    s32 height_offset;
    s32 actor_flags;
    u16 ticks_left;

    actor = actor_arg;
    state = motion->state;
    if (state == 1) {
        goto state1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state0;
        }
        goto done;
    }
    if (state == 2) {
        goto state2;
    }
    if (state == 3) {
        goto state3;
    }
    goto done;

state0:
    actor->field6A = actor->field2A & 0xFFF;
    actor->field1C &= 0xFFFEFFFF;
    motion->state++;

state1:
    actor->field2A += 0x200;
    position->field14 += 0xFFFF0000;
    ticks_left = motion->field96 - 1;
    motion->field96 = ticks_left;
    if ((ticks_left << 16) > 0) {
        goto done;
    }
    position->field14 = 0;
    func_800A2B04(position, tile->field24, tile->field25);
    height_offset = -0x400;
    actor->field88 = func_800BCB04(position->field2, position->field6,
                                (D_800DCF58[0] = 1, height_offset));
    motion->field92 = -0x200;
    motion->field96 = 0x10;
    motion->field98 &= 0xFFF7;
    motion->state++;
    goto done;

state2:
    actor->field2A += 0x200;
    if (motion->flagsA2 & 0x10) {
        motion->field96 = 0x20;
        motion->state++;
    }
    goto done;

state3:
    actor->field2A += 0x200;
    if ((actor->field2A & 0xFFF) != (actor->field6A & 0xFFF)) {
        goto done;
    }
    func_8009A21C(tile->field24, tile->field25,
                  (actor->field1C & 0x2000) ? 0x300 : 0x3000);
    flags_mask = 0xFFFEFFFF;
    D_80083460.fieldA--;
    actor_flags = actor->field1C & flags_mask;
    actor->field2A = actor->field6A;
    actor->field1C = actor_flags;
    func_80096088(motion, actor);

done:
    return;
}
