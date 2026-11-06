#include "common.h"
#include "town/player/motion.h"
#include "shared/sprite_frame_state.h"

   /* arg1 in move_value_toward_300 */

extern s32 init_record_target_approach(TownObjectRecord *record, ObjectPosition *field_ptr, SpriteFrameState *other_value);

/* Moves the halfword at +6 toward 0x300 by four and calls the next handler when it reaches that value. */
s32 move_value_toward_300(TownObjectRecord *record, ObjectPosition *field_ptr, SpriteFrameState *other_value)
{
    s16 current;
    u16 raw;
    s32 result;

    current = field_ptr->y.w.i;
    raw = field_ptr->y.unsigned_parts.integer;
    if (current < 0x300) {
        current = raw + 4;
        field_ptr->y.w.i = current;
        if (current >= 0x300) {
            result = 0x300;
            field_ptr->y.w.i = result;
            result = init_record_target_approach(record, field_ptr, other_value);
            return result;
        }
    } else {
        current = raw - 4;
        field_ptr->y.w.i = current;
        if (current < 0x301) {
            result = 0x300;
            field_ptr->y.w.i = result;
            result = init_record_target_approach(record, field_ptr, other_value);
            return result;
        }
    }
    result = 0x300;
    return result;
}
