#include "modules/dungeon_ovl_192a800.h"
#include "common.h"


extern s32 try_trigger_target_record_effect(void *entity, s32 flags);
extern s32 random_dungeon_range_16(s32 bound_a, s32 bound_b);
extern s32 lower_entity_level(void *entity_data, s32 show_message);
extern void adjust_source_value_and_finalize(void *context, void *source);
extern void create_actor_value_popup(s32 flags, u8 *source_data, s16 value, u16 callback_mode);
extern const u8 D_80024004[];


/* Runs action 0x53 on the target after state and threshold checks. */
void func_800240AC(void *target, s32 threshold_arg, void *owner_context) {
    s32 value_index;
    s32 threshold;

    if (try_trigger_target_record_effect(target, 4) != 0) {
        return;
    }

    value_index = (s16)(random_dungeon_range_16(0, ((u8 *)target)[3]) - 16);
    threshold = threshold_arg & 0xFF;
    if (value_index < threshold) {
        if (lower_entity_level(target, 1) != 0) {
            return;
        }
    } else if (threshold == 0xFF) {
        if (lower_entity_level(target, 1) != 0) {
            return;
        }
    }

    adjust_source_value_and_finalize(target, D_80024004);
    create_actor_value_popup(0x53, target, -1, 1);
}
