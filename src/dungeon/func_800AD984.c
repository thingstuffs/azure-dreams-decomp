#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad_0[0x10];
    s32 field_10;
} State;

typedef struct {
    u8 pad_0[0x1C];
    s32 flags_1C;
} Entity;

typedef struct {
    u8 pad_0[0x24];
    u8 field_24;
    u8 field_25;
} Source;

extern void detach_record_and_update_slot_state(Entity *);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern void unlink_entity_node(Entity *);

/* Update an entity using source bytes and a flag-dependent mask, then set completion flags. */
void update_flag_masked_entity(void *unused_0, void *unused_1, Source *source, Entity *entity) {
    s32 update_mask;
    u8 source_24;
    u8 source_25;

    if (((s32)g_dungeon_status.unk_10) == (s32)((u8 *)entity - 0x20)) {
        *(s32 *)&g_dungeon_status.unk_10 &= 0x7FFFFFFF;
    }
    detach_record_and_update_slot_state(entity);
    source_24 = source->field_24;
    source_25 = source->field_25;
    update_mask = 0x3000;
    if (entity->flags_1C & 0x2000) {
        update_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(source_24, source_25, update_mask);
    unlink_entity_node(entity);
    *(u16 *)((u8 *)entity - 2) |= 0x8000;
    object_flag_block.flags |= 0x8000;
}
