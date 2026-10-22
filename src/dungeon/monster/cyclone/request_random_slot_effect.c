#include "common.h"
#include "shared/record_ptrs.h"

typedef struct S_801761AC_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0xD];
    u8 unk_11;
} S_801761AC_0;   /* actor in request_random_slot_effect */


extern s32 set_or_clear_actor_status_slot();
extern s32 generate_random_value();

/* Roll a random slot for the actor and, when it lands below 16, request effect 0x19 on it; returns 1 when that request succeeded. */
/* For a non-player actor, rolls against its byte at +3 to request status 0x19; returns 1 only if the
 * request succeeds. */
s32 request_random_slot_effect(S_801761AC_0 *actor) {
    s32 seed;
    register s32 divisor;
    s32 remainder;
    s16 slot;

    if (actor == dungeon_actor_ring_anchor) {
        return 0;
    }
    seed = generate_random_value() & 0xFFFF;
    if (((s32)(actor->unk_03)) != 0) {
        divisor = ((s32)(actor->unk_03));
        remainder = seed % divisor;
        slot = remainder;
    } else {
        slot = 0;
    }
    if (slot < 16) {
        if ((s16)set_or_clear_actor_status_slot(actor, 0x19,
                (s8)((actor->unk_11 >> 2) + 0x20 + (generate_random_value() & 3))) >= 0) {
            return 1;
        }
    }
    return 0;
}

/* MECHANISM: the row is TRUE-SPACE (rowbase region sweep_0E32504_tail, delta
   0x7F343800, true base 0x801761AC).  m2c's `func_801761F8` is a PHANTOM: that
   word is this function's own local `j` over the else arm of the slot ternary,
   and three prior waves floored at aligned 8 fighting an invented
   "internal v0/v1 entry contract" for a callee that does not exist.
   Single shared `fail:` label keeps gcc's jump.c from store-flagging the final
   `return 1 / return 0` into nor+srl, reproducing retail's bgez + delay `li v0,1`. */
