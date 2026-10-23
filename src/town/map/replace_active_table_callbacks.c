#include "common.h"

extern u8 map_active_node_key[];
extern void apply_nearby_object_effects(void);
extern void *map_active_callbacks[];

/* Set the preceding handler pointer and replace each active table callback. */
void replace_active_table_callbacks(void *entry_data) {
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
