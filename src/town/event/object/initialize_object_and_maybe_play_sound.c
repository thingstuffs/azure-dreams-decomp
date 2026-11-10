#include "common.h"
#include "engine/audio.h"
#include "town/event/object.h"
#include "town/event.h"
#include "slus.h"

/* Clear object state, assign the context handler, and trigger effects if the check succeeds. */
void initialize_object_and_maybe_play_sound(u8 *context, s8 *object, s32 *state, s32 unused)
{
    object[0x15] = 0;
    state[3] = 0;
    state[4] = 0;
    state[5] = 0;
    *(void **)(context + 0x50) = resolve_owner_position_and_dispatch;
    if (check_object_type_and_data_tag(context + 0x4C) != 0) {
        select_sound_stream(0x26, 0);
        SD_Call(0x200);
    }
}
