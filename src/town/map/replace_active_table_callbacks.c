#include "common.h"
#include "shared/sprite_frame_state.h"
#include "town/map/object_callback.h"
#include "town/map.h"

extern void apply_nearby_object_effects(void);
extern void *map_active_callbacks[];

/* Set the preceding handler pointer and replace each active table callback. */
void replace_active_table_callbacks(void *entry_data, void *unused_position, struct SpriteFrameState *unused_sprite) {
    void **p;

    *(void **)((u8 *)entry_data - 0x10) = (void *)map_active_node_key;
    p = map_active_callbacks;
    if (*p != 0) {
        do {
            *p = (void *)apply_nearby_object_effects;
            p += 6;
        } while (*p != 0);
    }
}
