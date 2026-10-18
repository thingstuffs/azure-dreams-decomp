#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"

   /* the 0x2 bytes before arg0 in update_brightening_fading_effect, addressed as arg0[-1] */

   /* arg0 in update_brightening_fading_effect */



   /* arg1 in update_brightening_fading_effect */



   /* arg2 in update_brightening_fading_effect */

   /* ((S_8195EB88_0 *)arg0)->unk_0C in update_brightening_fading_effect */








/* Updates the effect position, brightens and fades its primitive, and marks completion. */
void update_brightening_fading_effect(void *effect, S_8195EB88_2 *position, S_8195EB88_4 *primitive)
{
    s16 phase;
    u16 phase_value;
    S_8195EB88_3 *base_position;
    S_8195EB88_1 *source_state;

    (*(u16 *)&D_80027330) = (*(u16 *)&D_80027330) + 1;
    phase = ((S_8195EB88_0 *)effect)->unk_48.s;
    phase_value = ((S_8195EB88_0 *)effect)->unk_48.u;

    if (phase == 0) {
        source_state = ((S_8195EB88_5 *)(((S_8195EB88_0 *)effect)->unk_0C))->unk_0C;
        if (((S_8195EB88_0 *)effect)->unk_4A == 0) {
            if (resolve_record_orientation_or_fallback(source_state->unk_08, source_state,
                              (u8 *)effect + 0x40, 0) != 0) {
                ((S_8195EB88_0 *)effect)->unk_4A = 1;
            } else if (source_state->unk_14 & 0x8000) {
                ((S_8195EB88_0 *)effect)->unk_4A = 1;
                ((S_8195EB88_0 *)effect)->unk_44.s = -0x40;
            }
            if (((S_8195EB88_0 *)effect)->unk_4A == 0) {
                return;
            }
        }

        base_position = ((S_8195EB88_5 *)(((S_8195EB88_0 *)effect)->unk_0C))->unk_08;
        position->unk_02 =
            base_position->unk_02 + ((S_8195EB88_0 *)effect)->unk_40;
        position->unk_06 =
            base_position->unk_06 + ((S_8195EB88_0 *)effect)->unk_42;
        position->unk_0A =
            base_position->unk_0A + ((S_8195EB88_0 *)effect)->unk_44.u;
        if (allocate_nine_position_objects(position) != 0) {
            func_8004491C((u8 *)effect - 0x20, func_80045340);
            ((S_8195EB88_0 *)effect)->unk_48.u = ((S_8195EB88_0 *)effect)->unk_48.u + 1;
        }
    } else if (phase == 1) {
        if (primitive->unk_0C.u8 < 0xC0) {
            primitive->unk_0C.u32 += 0x202020;
        } else {
            ((S_8195EB88_0 *)effect)->unk_48.u = phase_value + 1;
        }
    } else if (phase == 2) {
        primitive->unk_0C.u32 += 0xFFEFEFF0;
        if (primitive->unk_0C.u8 == 0) {
            ((S_8195EB88_0_pre *)effect)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= 0x8000;
        }
    }
}
