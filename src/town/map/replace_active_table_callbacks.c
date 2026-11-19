#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "town/map/object_callback.h"
#include "town/map.h"

extern s32 trigger_effect_when_in_range();

/* Set the preceding handler pointer and replace each active table callback. */
void replace_active_table_callbacks(TownObjectRecord *entry_data, ObjectPosition *unused_position, struct SpriteFrameState *unused_sprite) {
    CallbackEntry *p;

    NODE_HEADER(entry_data)->update_callback = run_callbacks_unless_suppressed;
    p = map_active_callbacks;
    if (p->callback != 0) {
        do {
            p->callback = trigger_effect_when_in_range;
            p++;
        } while (p->callback != 0);
    }
}
