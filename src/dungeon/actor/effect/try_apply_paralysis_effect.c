#include "common.h"
#include "dungeon/item.h"
#include "dungeon/actor/effect.h"
#include "dungeon/menu.h"

extern u8 paralyzed_message[];
extern u8 paralysis_failed_message[];
extern s32 paralysis_status_label;

/* Apply the chance-based status and select its success or failure message. */
s32 try_apply_paralysis_effect(void *actor, s32 chance, s32 action)
{
    if (roll_paralysis_effect(actor, (s16)chance, (s16)action)) {
        adjust_source_value_and_finalize(actor, paralyzed_message);
        if (((u8 *)actor)[0x13] == 0) {
            wrap_position_and_set_state_value(paralysis_status_label);
        }
        return 1;
    }
    adjust_source_value_and_finalize(actor, paralysis_failed_message);
    return 0;
}
