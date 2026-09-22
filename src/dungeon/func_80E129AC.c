#include "common.h"

typedef struct S_801761AC_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0xD];
    u8 unk_11;
} S_801761AC_0;   /* actor in func_801761AC */



extern void *D_800E3D7C;

extern s32 func_800A48F0();
extern s32 func_800A6D30();

/* Roll a random slot for the actor and, when it lands below 16, request effect 0x19 on it; returns 1 when that request succeeded. */
s32 func_801761AC(S_801761AC_0 *actor) {
    s32 seed;
    register s32 divisor;
    s32 remainder;
    s16 slot;

    if (actor == D_800E3D7C) {
        goto fail;
    }
    seed = func_800A6D30() & 0xFFFF;
    if (((s32)(actor->unk_03)) != 0) {
        divisor = ((s32)(actor->unk_03));
        remainder = seed % divisor;
        slot = remainder;
    } else {
        slot = 0;
    }
    if (slot >= 16) {
        goto fail;
    }
    if ((s16)func_800A48F0(actor, 0x19,
            (s8)((actor->unk_11 >> 2) + 0x20 + (func_800A6D30() & 3))) >= 0) {
        return 1;
    }
fail:
    return 0;
}

/* MECHANISM: the row is TRUE-SPACE (rowbase region sweep_0E32504_tail, delta
   0x7F343800, true base 0x801761AC).  m2c's `func_801761F8` is a PHANTOM: that
   word is this function's own local `j` over the else arm of the slot ternary,
   and three prior waves floored at aligned 8 fighting an invented
   "internal v0/v1 entry contract" for a callee that does not exist.
   Single shared `fail:` label keeps gcc's jump.c from store-flagging the final
   `return 1 / return 0` into nor+srl, reproducing retail's bgez + delay `li v0,1`.
   $v0 divisor hold and $v1 remainder (KEEP_DEP chain) reproduce the two extra
   copies retail carries around `rem`; the $v1 count pin puts seed in $a0 and
   fixes the andi/move-$a0 argument-setup order; the else-arm ASM_KEEP(count)
   blocks gcc's cross-jump merge of `slot = 0` into `move $v0,$v1` (it can prove
   count == 0 there), which is what restores the local `j` word. */
