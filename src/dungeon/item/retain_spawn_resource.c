#include "common.h"
#include "shared/dungeon_status.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct {
    u8 unk0;
    s8 type;
    u8 count;
} Entry;

extern Entry *find_or_retain_sprite_resource_slot(s16 requested_id, s16 requested_type);

/* Normalize the entry type and increment the matching entry and dungeon counts. */
s32 retain_spawn_resource(s16 entry_type, s16 entry_key) {
    s16 type;
    Entry *entry;

    type = entry_type;
    if (entry_type == 0x39) {
        type = 2;
    }
    entry = find_or_retain_sprite_resource_slot(type, entry_key);
    if (entry != NULL) {
        entry->type = type;
        entry->count++;
        g_dungeon_status.monster_count++;
        return 1;
    }
    return 0;
}
