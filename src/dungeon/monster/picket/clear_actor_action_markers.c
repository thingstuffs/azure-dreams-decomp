#include "shared/entity.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/dir_step.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x2A];
    union {
        s16 s16;
        u16 u16;
    } field_2A;
    u8 pad_2C[0x5C];
    s16 field_88;
} ActorBytesFieldView_80E91000;

typedef struct {
    u8 pad_00[0x24];
    u8 field_24;
    u8 field_25;
} OriginBytesFieldView_80E91000;

typedef struct {
    u8 pad_00[0x249];
    u8 field_249;
    u8 pad_24A[0x1];
    u8 field_24B;
} InventoryBaseFieldView_80E91000;


/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x48];
    union {
        s32 s32;
        struct { u8 pad[0x1]; u8 value; } u8_at_1;
        struct { u8 pad[0x3]; u8 value; } u8_at_3;
    } field_48;
} TargetFieldView_80E91000;

extern void clear_slot_and_update_linked_state(void *);
extern s32 generate_random_value(void);
extern s32 find_floor_item_at_world_position(s32 input_x, s32 input_y, s32 input_z);

extern s32 picket_slot_f_item_result[];



 s32 clear_actor_action_markers(void *, void *) ;
/*
 * Attempts to take an item from the tile ahead or a neighboring actor's inventory, rejecting
 * protected items and slots.
 */
s32 clear_actor_action_markers(void *origin, void *actor)
{
    OriginBytesFieldView_80E91000 *origin_bytes = (OriginBytesFieldView_80E91000 *)origin;
    ActorBytesFieldView_80E91000 *actor_bytes = (ActorBytesFieldView_80E91000 *)actor;
    s32 direction_offset;
    s16 ground_index;
    ActorRecord *target;
    s32 item_offset;
    InventoryBaseFieldView_80E91000 *inventory_base;
    u8 *item_slot;

    direction_offset = (actor_bytes->field_2A.u16 >> 8) & 0xE;
    ground_index = find_floor_item_at_world_position(
        (s16)(origin_bytes->field_24 + *(u16 *)(((u8 *)dir_step_x) + direction_offset)),
        (s16)(origin_bytes->field_25 + *(u16 *)(((u8 *)dir_step_y) + direction_offset)),
        actor_bytes->field_88);
    if (ground_index >= 0) {
        picket_slot_f_item_result[0] = ((s32 *)dungeon_ground_items)[ground_index];
        ((s32 *)dungeon_ground_items)[ground_index] = 0;
        return (s32)picket_slot_f_item_result;
    }

    target = probe_directional_neighbor(actor, origin_bytes->field_24, origin_bytes->field_25,
                           actor_bytes->field_2A.s16);
    if (target != 0) {
        if (target == dungeon_actor_ring_anchor) {
            if (is_linked_entity_flagged_80000(target, target) != 0) {
                return 0;
            }
            {
                s16 occupied_count;
                register s32 slot_index;
                slot_index = 0;
                occupied_count = slot_index;
                item_slot = (u8 *)0x80010000;
scan_loop:
                if (((s32 *)item_slot)[167] != 0) {
                    occupied_count++;
                }
                slot_index++;
                item_slot += sizeof(s32);
                if (slot_index < 20) {
                    goto scan_loop;
                }
                if (occupied_count == 0) {
                    return 0;
                }
                item_offset =
                    (s32)((((generate_random_value() & 0xFFFF) % occupied_count) << 16) >> 14);
                inventory_base = (InventoryBaseFieldView_80E91000 *)(item_offset + 0x80010000);
                item_slot = (u8 *)(u32)inventory_base->field_249;
                if (item_slot == 0 || (u32)item_slot == 0x13) {
                    return 0;
                }
                if (inventory_base->field_24B & 0x20) {
                    return 0;
                }
                {
                    s32 item_data;

                    item_slot = (u8 *)0x80010248;
                    item_slot += item_offset;
                    item_data = *(s32 *)item_slot;
                    picket_slot_f_item_result[0] = item_data;
                    clear_slot_and_update_linked_state(item_slot);
                    return (s32)picket_slot_f_item_result;
                }
            }
        }
        if (target->unk_49 == 0) {
            return 0;
        }
        if (target->unk_4B & 0x20) {
            return 0;
        }
        {
            s32 item_data;

            item_data = ((TargetFieldView_80E91000 *)target)->field_48.s32;
            picket_slot_f_item_result[0] = item_data;
            ((TargetFieldView_80E91000 *)target)->field_48.s32 = 0;
            return (s32)picket_slot_f_item_result;
        }
    }
    return 0;
}
