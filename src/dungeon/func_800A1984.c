#include "common.h"

typedef struct {
    u8 pad0;
    u8 active;
    u8 pad2[2];
} ActiveEntry;

typedef struct {
    u8 x;
    u8 y;
    u8 pad2[2];
    s16 value;
    u8 pad6[6];
} PositionEntry;

extern void func_8009A350(s16, s16, s32, u16 *);
extern u8 D_800E3548[];
extern u8 D_800E36C8[];

s32 func_800A70E4(s32 arg0, s32 arg1, s32 arg2) {
    s32 held_x;
    s32 held_z;
    s32 held_y;
    s32 result;
    register s32 var_a0 ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */
    s32 y;
    u16 sp10;
    ActiveEntry *var_a2;
    PositionEntry *var_v1;
    s32 var_v0;
    s32 x;
    s32 z;

    held_x = arg0;
    held_z = arg2;
    func_8009A350((s16)(held_x - 1), (held_y = (s16)arg1), 0, &sp10);
    var_a0 = 0;
    if (sp10 & 0x800) {
        goto scan;
    }
    result = -1;
    goto done;
success:
    result = (s16)var_a0;
    goto done;
scan:
    x = (s16)held_x;
    y = held_y;
    z = (s16)held_z;
    result = 0x800E0000;
    ASM_KEEP(result);   /* MATCH pin: load-bearing for the whole function shape */
    var_v1 = (PositionEntry *)(result + 0x36C8);
    result = 0x800E0000;
    ASM_KEEP(result);   /* MATCH pin: load-bearing for the whole function shape */
    var_a2 = (ActiveEntry *)(result + 0x3548);
loop_6:
    if ((var_a2->active != 0) && (var_v1->x == x) && (var_v1->y == y)) {
        var_v0 = z - var_v1->value;
        if (var_v0 < 0) {
            var_v0 = 0 - var_v0;
        }
        if (var_v0 >= 0x40) {
            goto block_12;
        }
        goto success;
    }
block_12:
    var_v1++;
    var_a0 += 1;
    var_a2++;
    if (var_a0 >= 0x40) {
        result = -1;
        goto done;
    }
    goto loop_6;
done:
    ASM_KEEP(var_a0);   /* MATCH pin: retail delay-slot fill depends on it */
    return result;
}

/* MECHANISM: True-space epilogue targets are two pre-scan return trampolines; s32 formals
   plus guarded s1/s2/s0 carriers reproduce the raw/narrow argument lifetimes and 0x28 saves.
   Counter/y carriers fix volatile roles; v0 page keeps emit the split +36C8/+3548 bases. */
