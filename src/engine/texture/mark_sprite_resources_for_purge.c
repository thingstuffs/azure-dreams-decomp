#include "common.h"
#include "engine/texture.h"

typedef struct {
    s32 flag;
    u16 status;
    u16 pad6;
} S_80083D08;

extern S_80083D08 sprite_resource_slots[6];

/* Sets status bit 0 for each entry with a nonzero flag. */
void mark_sprite_resources_for_purge(void) {
    s32 entry_index;

    for (entry_index = 0; entry_index < 6; entry_index++) {
        S_80083D08 *entry = &sprite_resource_slots[entry_index];
        if (entry->flag) {
            entry->status |= 1;
        }
    }
}
