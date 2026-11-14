#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "engine/object.h"
#include "town/player.h"

#include "town/player/initialize_record_with_handler_table_api.h"        /* extern */
#include "shared/sprite_frame_state.h"


/* Move the record value toward 0x4C2 by four and invoke completion handlers on arrival. */
void step_x_toward_fixed_target(TownObjectRecord *context, ObjectPosition *record, SpriteFrameState *sprite) {
    s16 raised_value;
    s16 lowered_value;
    u16 current_value;

    current_value = (u16) record->x.w.i;
    if (record->x.w.i < 0x4C2
            ? (raised_value = current_value + 4,
               record->x.w.i = raised_value,
               raised_value >= 0x4C2)
            : (lowered_value = current_value - 4,
               record->x.w.i = lowered_value,
               lowered_value < 0x4C3)) {
        record->x.w.i = 0x4C2;
        set_resident_bitmap_bit(sn_open_sekkyo_ready);
        initialize_record_with_handler_table(context, (record), sprite);
    }
}
