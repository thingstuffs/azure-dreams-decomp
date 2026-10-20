#include "town/menu/window.h"

/* Updates an object's pulse brightness and handles its completion state. */
void update_object_pulse_brightness(func_800A0FB4_S_func_8009E714_0 *object, s32 context, func_800A0FB4_S_func_8009E714_1 *primitive) {
    s32 status_match;
    s16 phase;
    s32 wave;
    s32 wave_step;
    s32 brightness;

    status_match = classify_record_by_state_and_position(object, context) == 1;
    if (classify_record_by_state_and_position(object, context) == 1) {
        s8 *active_flag = object->unk_98;
        if (active_flag != 0) {
            *active_flag = 0;
        }
        unlink_node_if_registered(object);
        ((func_800A0FB4_S_func_8009E714_2 *)object)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= 0x8000;
        return;
    }
    if (status_match == 2) {
        unlink_node_if_registered(object);
        return;
    }
    register_node_if_unregistered(object, project_sprite_chain);
    phase = object->unk_6C + 0x60;
    object->unk_6C = phase;
    wave = func_800644B8(phase);
    wave_step = wave >> 7;
    if (wave < 0) {
        wave_step = (wave + 0x7F) >> 7;
    }
    brightness = (wave_step + 0x20) * 0x30;
    if (brightness < 0) {
        brightness += 0x3F;
    }
    brightness >>= 6;
    primitive->unk_0E = (s8)brightness;
    primitive->unk_0D = (s8)brightness;
    primitive->unk_0C = (s8)brightness;
    if (!(((func_800A0FB4_S_func_8009E714_2 *)object)[-1].unk_00 & 0x8000) &&
        object->unk_4D == 0x13) {
        func_800478B8(primitive);
    }
}
