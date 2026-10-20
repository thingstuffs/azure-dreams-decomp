#include "modules/dungeon_ovl_e0365c.h"
#include "shared/sprite_frame_state.h"

void advance_effect_record_counters(u16 *counter, s32 unused, SpriteFrameState *record) {
    u16 step;
    u16 field_value;

    step = *counter + 1;
    *counter = step;
    if ((s16) step < 9) {
        field_value = record->scale_y + 0x100;
        record->scale_y = field_value;
        record->scale_x = field_value;
    }
    func_800478B8(record);
}
