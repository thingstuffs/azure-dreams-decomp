#include "common.h"
#include "shared/object_flags.h"

typedef struct EntitySlot {
    u8 pad_00[6];
    u8 x;
    u8 y;
    u8 pad_08[4];
    void *entity;
    u8 pad_10[8];
} EntitySlot;

typedef struct Entity {
    u8 pad_00[0x1E];
    u16 flags;
} Entity;

typedef struct GlobalFlags {
    s32 value;
    s32 pad[2];
} GlobalFlags;

extern s32 floor_objects[0x20];
extern EntitySlot dungeon_floor_object_positions[0x20];

extern void update_map_cell_flags_with_item_limit(u8 x, u8 y, s32 type);

/* Clears a slot's state and flags any attached entity before detaching it. */
void clear_slot_and_detach_entity(s32 slot_index) {
    s32 slot_offset;
    EntitySlot *slot_base;
    EntitySlot *slot;
    Entity *entity;
    u16 entity_flags;
    s32 global_flags;

    slot_base = dungeon_floor_object_positions;
    floor_objects[slot_index] = 0;
    slot_offset = slot_index * 0x18;

    slot = (EntitySlot *)((u8 *)slot_base + slot_offset);
    update_map_cell_flags_with_item_limit(slot->x, slot->y, 0x20);
    entity = slot->entity;
    if (entity != 0) {
        entity_flags = entity->flags;
        global_flags = object_flag_block.flags;
        entity->flags = entity_flags | 0x8000;
        object_flag_block.flags = global_flags | 0x8000;
        slot->entity = 0;
    }
}
