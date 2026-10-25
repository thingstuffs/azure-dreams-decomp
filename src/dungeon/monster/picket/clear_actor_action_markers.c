#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/dir_step.h"

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
extern void *probe_directional_neighbor(void *, u8, u8, s16);
extern s32 generate_random_value(void);
extern s16 find_floor_item_at_world_position(s16, s16, s16);
extern s32 is_linked_entity_flagged_80000(void *, void *);

extern s32 dungeon_actor_ring_anchor[];
extern s32 picket_slot_f_item_result[];



 s32 clear_actor_action_markers(void *, void *) ;
/*
 * Attempts to take an item from the tile ahead or a neighboring actor's inventory, rejecting
 * protected items and slots.
 */
s32 clear_actor_action_markers(void *origin, void *actor)
{
    u8 *origin_bytes = (u8 *)origin;
    u8 *actor_bytes = (u8 *)actor;
    s32 direction_offset;
    s16 ground_index;
    void *target;
    s32 item_offset;
    u8 *inventory_base;
    u8 *item_slot;

    direction_offset = (((ActorBytesFieldView_80E91000 *)actor_bytes)->field_2A.u16 >> 8) & 0xE;
    ground_index = find_floor_item_at_world_position(
        (s16)(((OriginBytesFieldView_80E91000 *)origin_bytes)->field_24 + *(u16 *)(((u8 *)dir_step_x) + direction_offset)),
        (s16)(((OriginBytesFieldView_80E91000 *)origin_bytes)->field_25 + *(u16 *)(((u8 *)dir_step_y) + direction_offset)),
        ((ActorBytesFieldView_80E91000 *)actor_bytes)->field_88);
    if (ground_index >= 0) {
        picket_slot_f_item_result[0] = ((s32 *)dungeon_ground_items)[ground_index];
        ((s32 *)dungeon_ground_items)[ground_index] = 0;
        return (s32)picket_slot_f_item_result;
    }

    target = probe_directional_neighbor(actor, ((OriginBytesFieldView_80E91000 *)origin_bytes)->field_24, ((OriginBytesFieldView_80E91000 *)origin_bytes)->field_25,
                           ((ActorBytesFieldView_80E91000 *)actor_bytes)->field_2A.s16);
    if (target != 0) {
        if (target == (void *)dungeon_actor_ring_anchor[0]) {
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
                inventory_base = (u8 *)(item_offset + 0x80010000);
                item_slot = (u8 *)(u32)((InventoryBaseFieldView_80E91000 *)inventory_base)->field_249;
                if (item_slot == 0 || (u32)item_slot == 0x13) {
                    return 0;
                }
                if (((InventoryBaseFieldView_80E91000 *)inventory_base)->field_24B & 0x20) {
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
        if (((TargetFieldView_80E91000 *)target)->field_48.u8_at_1.value == 0) {
            return 0;
        }
        if (((TargetFieldView_80E91000 *)target)->field_48.u8_at_3.value & 0x20) {
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
