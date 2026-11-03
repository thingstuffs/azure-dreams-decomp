/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"
#include "slus.h"
#include "town.h"
#include "town/player/action_initializers.h"
#include "shared/sprite_frame_state.h"
#include "town/player/position.h"

extern s32 D_800D0188;

/* Plays sound 0x500, selects D_800D0188, and installs D_80093524 with count 0x1E. */
void init_linked_position_action(TownObjectRecord *record, s32 unused, SpriteFrameState *setup_value) {
    SD_Call(0x500);
    call_the_handler_selects_nonzero_entry(&D_800D0188, record, setup_value);
    record->unk_00.as_pm = follow_linked_position_until_timeout;
    record->unk_0A.as_s16 = 0x1E;
}
