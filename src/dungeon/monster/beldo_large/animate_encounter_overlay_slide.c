#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/monster/beldo_large.h"

typedef struct S_8016F99C_0_pre {
    u16 unk_00;
} S_8016F99C_0_pre;   /* the 0x2 bytes before arg0 in animate_encounter_overlay_slide, addressed as arg0[-1] */


typedef struct S_8016F99C_1 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8016F99C_1;   /* arg1 in animate_encounter_overlay_slide */


extern void *encounter_object_slots[];
extern void *encounter_overlay_object[];

/* Advances a timed transition, updates its target, and marks completion. */
void animate_encounter_overlay_slide(EncounterOverlayBody *transition_arg, ObjectPosition *target)
{
    EncounterOverlayBody *transition = transition_arg;
    s32 state;
    u16 timer;
    u32 next_state;
    u32 next_timer;

    state = transition->unk_12.s;
    switch (state) {
    case 0:
    default:
        return;

    case 1:
        target->z.unsigned_parts.integer = 1;
        return;

    case 2:
        next_state = transition->unk_12.u;
        next_timer = 0x11;
        transition->unk_18 = next_timer;
        transition->unk_12.u = next_state + 1;
        return;

    case 3:
        target->y.unsigned_parts.integer = target->y.unsigned_parts.integer - 8;
        timer = transition->unk_18 - 1;
        transition->unk_18 = timer;
        if ((timer << 16) > 0) {
            return;
        }
        transition->unk_18 = 0x11;
        transition->unk_12.u = transition->unk_12.u + 1;
        target->z.unsigned_parts.integer = 3;
        return;

    case 4:
        target->y.unsigned_parts.integer = target->y.unsigned_parts.integer + 8;
        timer = transition->unk_18 - 1;
        transition->unk_18 = timer;
        if ((timer << 16) > 0) {
            return;
        }
        if (transition->unk_1C == 0) {
            *encounter_object_slots = 0;
        } else {
            *encounter_overlay_object = 0;
        }
        ((S_8016F99C_0_pre *)transition)[-1].unk_00 |= 0x8000;
        next_timer = 0x80080000;
        *(s32 *)(next_timer + 0x14A0) |= 0x8000;
        return;

    case 10:
        next_state = transition->unk_12.u;
        next_timer = 0x14;
        transition->unk_18 = next_timer;
        transition->unk_12.u = next_state + 1;
        return;

    case 11:
        target->y.unsigned_parts.integer = target->y.unsigned_parts.integer - 8;
        timer = transition->unk_18 - 1;
        transition->unk_18 = timer;
        if ((timer << 16) > 0) {
            return;
        }
        if (transition->unk_1C == 0) {
            *encounter_object_slots = 0;
        } else {
            *encounter_overlay_object = 0;
        }
        ((S_8016F99C_0_pre *)transition)[-1].unk_00 |= 0x8000;
        next_timer = 0x80080000;
        *(s32 *)(next_timer + 0x14A0) |= 0x8000;
        return;
    }
}

/* MECHANISM: Frameless leaf recovers every apparent 0x8016FAxx call as a local CFG join. A direct 0..11
   switch and shared advance/clear/finish labels restore retail layout. Placing the page births after
   flag branches produces the exact delay-slot luis and stores. */
