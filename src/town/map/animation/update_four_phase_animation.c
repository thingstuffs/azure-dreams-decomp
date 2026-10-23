#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in update_four_phase_animation, addressed as arg0[-1] */

typedef struct S_800BB030_0 {
    u8 pad_00[0x66];
    s16 unk_66;
    union { s16 s; u16 u; } unk_68;   /* accessed as both */
    u8 pad_6A[0x2];
    union { u16 s; s16 u; } unk_6C;   /* accessed as both */
    u8 pad_6E[0x29];
    s8 unk_97;
    s8 * unk_98;
} S_800BB030_0;   /* arg0 in update_four_phase_animation */


extern s32 classify_object_against_bounds(void *, void *);

/* Updates a four-phase animation and clears its activity flag on completion. */
void update_four_phase_animation(void *entity, void *context) {
    s8 *activity_flag;
    s32 phase;
    s32 phase_ticks;
    s32 quarter_ticks;
    s8 intensity;

    if (classify_object_against_bounds(entity, context) != 0) {
        activity_flag = ((S_800BB030_0 *)entity)->unk_98;
        if (activity_flag != 0) {
            *activity_flag = 0;
        }
        ((ObjectRetirementFlags *)entity)[-1].flags |= 0x8000;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        return;
    }

    phase_ticks = ((S_800BB030_0 *)entity)->unk_6C.s + 1;
    phase = ((S_800BB030_0 *)entity)->unk_68.s;
    ((S_800BB030_0 *)entity)->unk_6C.s = phase_ticks;
    switch (phase) {
    case 0:
        quarter_ticks = (s16)phase_ticks / 4;
        ((S_800BB030_0 *)entity)->unk_66 = quarter_ticks * 3;
        intensity = (s16)((S_800BB030_0 *)entity)->unk_6C.s / 2;
        ((S_800BB030_0 *)entity)->unk_97 = intensity;
        if (((S_800BB030_0 *)entity)->unk_6C.u < 0x40) {
            break;
        }
        ((S_800BB030_0 *)entity)->unk_6C.s = 0;
        ((S_800BB030_0 *)entity)->unk_68.u++;
        break;
    case 1:
    {
        s32 quarter_ticks;

        quarter_ticks = (s16)phase_ticks / 4;
        ((S_800BB030_0 *)entity)->unk_66 = 0x30 - quarter_ticks * 3;
        ((S_800BB030_0 *)entity)->unk_97 = 0x20;
        if (((S_800BB030_0 *)entity)->unk_6C.u >= 0x40) {
            ((S_800BB030_0 *)entity)->unk_6C.s = 0;
            ((S_800BB030_0 *)entity)->unk_68.u++;
        }
        break;
    }
    case 2:
    {
        s32 half_ticks;

        quarter_ticks = (s16)phase_ticks / 4;
        ((S_800BB030_0 *)entity)->unk_66 = quarter_ticks * 3;
        half_ticks = (s16)((S_800BB030_0 *)entity)->unk_6C.s / 2;
        intensity = 0x20 - half_ticks;
        ((S_800BB030_0 *)entity)->unk_97 = intensity;
        if (((S_800BB030_0 *)entity)->unk_6C.u < 0x40) {
            break;
        }
        ((S_800BB030_0 *)entity)->unk_6C.s = 0;
        ((S_800BB030_0 *)entity)->unk_68.u++;
        break;
    }
    case 3:
    {
        s32 quarter_ticks;

        quarter_ticks = (s16)phase_ticks / 4;
        ((S_800BB030_0 *)entity)->unk_66 = 0x30 - quarter_ticks * 3;
        ((S_800BB030_0 *)entity)->unk_97 = 0;
        if (((S_800BB030_0 *)entity)->unk_6C.u < 0x40) {
            break;
        }
        ((S_800BB030_0 *)entity)->unk_6C.s = 0;
        ((S_800BB030_0 *)entity)->unk_68.s = 0;
        break;
    }
    default:
        break;
    }
}
