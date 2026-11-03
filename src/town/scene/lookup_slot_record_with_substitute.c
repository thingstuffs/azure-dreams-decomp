#include "script_symbols.h"
#include "common.h"
#include "town/scene.h"
#include "town/player/state.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"
#include "town.h"

extern s32 D_80018974;
extern s32 D_80018AD0;
extern s32 D_80019F15;
extern s32 D_8001A0A1;

/* Look up the slot's record; when it is already claimed, substitute one of two fixed records. */
s32 *lookup_slot_record_with_substitute(s32 slot, s32 unused, s32 context) {
    s32 *record;
    s32 *result;

    record = apply_entry_position(&D_80018974, &D_80018AD0, slot, context);
    result = record;
    if (resolve_entry_flag(&D_80018974, slot, context) != 0) {
        if (town_table_contains_first_byte_b(8) != 0) {
            result = &D_8001A0A1;
        } else {
            set_script_flag_bit(F_gym_build);
            result = &D_80019F15;
        }
    }
    return result;
}
