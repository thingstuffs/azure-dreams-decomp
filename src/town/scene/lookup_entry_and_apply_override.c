#include "script_symbols.h"
#include "common.h"
#include "town/player/state.h"
#include "town/scene/motion.h"
#include "town/scene.h"

extern s32 resolve_entry_flag(void *, s32, s32); /* Unprototyped: retail call passes more arguments than the callee reads */

extern u8 D_800178D8[];
extern u8 D_800179CC[];
extern u8 D_80018481[];
extern u8 D_80018642[];
extern u8 D_80018B70[];

/* Looks up entry data and applies entry-specific overrides. */
s32 lookup_entry_and_apply_override(s32 lookup_key, s32 unused, s32 entry_id)
{
    s32 entry_data;

    entry_data = apply_entry_position(D_800178D8, D_800179CC, lookup_key, entry_id);

    if (entry_id == 50 && resolve_entry_flag(D_800178D8, lookup_key, 50)) {
        return (s32)D_80018481;
    }
    if (entry_id == 33 && resolve_entry_flag(D_800178D8, lookup_key, 33)) {
        return (s32)D_80018642;
    }
    if (entry_id == 12) {
        if (!resolve_entry_flag(D_800178D8, lookup_key, 12)) {
            clear_script_flag_bit(F_sbs43_pad14);
        }
        if (get_script_flag_mask(F_sbs43_pad14)) {
            return (s32)D_80018B70;
        }
    }
    return entry_data;
}
