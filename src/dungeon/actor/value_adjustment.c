#include "dungeon/actor/value_adjustment.h"


s32 apply_random_actor_value_adjustment(Row_818FE800_Target *target, s32 level) {
    s32 random;
    s32 value;
    s32 aux;
    s32 half;
    s32 counter;
    s32 level_low;

    if (try_trigger_target_record_effect(target, 1) != 0) {
        return;
    }
    random = generate_random_value() & 0xFFFF;
    if (target->field3 != 0) {
        counter = random % target->field3;
    } else {
        counter = 0;
    }
    level_low = level & 0xFF;
    if (counter < (level_low << 5) || level_low == 0xFF) {
        if (target->field26 >= 2) {
            half = ((s32)target->field26 + 1) >> 1;
            target->field26 -= half;
            value = get_unused_text_buffer();
            aux = value;
            value = write_text_byte_and_advance(8, aux);
            value = append_entity_display_text(target, value);
            value = expand_text_control_codes(&D_800E2096, value);
            func_80099290(value);
            display_text_with_fullwidth_adjustment(aux);
            create_actor_value_popup(0x53, target, half, 1);
            return;
        }
    }
    adjust_source_value_and_finalize(target, &D_800E20BC);
    create_actor_value_popup(0x53, target, -1, 1);
}
