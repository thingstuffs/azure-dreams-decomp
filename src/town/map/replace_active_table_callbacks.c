#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/map/object_callback.h"
#include "town/map.h"

extern s32 trigger_effect_when_in_range();
extern CallbackEntry map_active_callbacks[];

/* Set the preceding handler pointer and replace each active table callback. */
void replace_active_table_callbacks(TownObjectRecord *entry_data, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    CallbackEntry *p;

    *(void **)((u8 *)entry_data - 0x10) = (void *)run_callbacks_unless_suppressed;
    p = map_active_callbacks;
    if (p->callback != 0) {
        do {
            p->callback = trigger_effect_when_in_range;
            p++;
        } while (p->callback != 0);
    }
}
