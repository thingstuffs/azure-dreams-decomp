#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"

typedef struct {
    u8 pad_0[0x10];
    s32 field_10;
} State;

typedef struct {
    u8 pad_0[0x1C];
    s32 flags_1C;
} Entity;



extern void detach_record_and_update_slot_state(Entity *);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern void unlink_entity_node(Entity *);

/* Update an entity using source bytes and a flag-dependent mask, then set completion flags. */
void update_flag_masked_entity(void *unused_0, void *unused_1, MovingTile *source, Entity *entity) {
    s32 update_mask;
    u8 source_24;
    u8 source_25;

    if (((s32)g_dungeon_status.pending_display_owner) == (s32)((u8 *)entity - 0x20)) {
        *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
    }
    detach_record_and_update_slot_state(entity);
    source_24 = source->unk_24;
    source_25 = source->unk_25;
    update_mask = 0x3000;
    if (entity->flags_1C & ACTOR_PLAYER_SIDE) {
        update_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(source_24, source_25, update_mask);
    unlink_entity_node(entity);
    *(u16 *)((u8 *)entity - 2) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
