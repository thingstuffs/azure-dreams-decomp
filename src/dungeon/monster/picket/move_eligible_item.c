#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"

extern void clear_slot_and_update_linked_state(void *, void *);
extern void *probe_directional_neighbor(void *, u8, u8, s16);
extern s32 generate_random_value(void);
extern s16 find_floor_item_at_world_position(s16, s16, s16);
extern s32 is_linked_entity_flagged_80000(void *, void *);

extern s32 dungeon_actor_ring_anchor[];
extern s32 D_80162FE4[];

typedef struct { s32 value; } ItemWord;


 s32 move_eligible_item(void *, void *) ;
/* Moves an eligible item from a nearby slot or target into the shared item slot. */
 s32 move_eligible_item(void *origin, void *actor) {
    u8 *origin_bytes = (u8 *)origin;
    u8 *actor_bytes = (u8 *)actor;
    s32 direction_offset;
    s16 tile_slot;
    void *target;
    u8 *item_ptr;

    direction_offset = (*(u16 *)(actor_bytes + 0x2A) >> 8) & 0xE;
    tile_slot = find_floor_item_at_world_position(
        (s16)(*(u8 *)(origin_bytes + 0x24) + *(u16 *)(((u8 *)dir_step_x) + direction_offset)),
        (s16)(*(u8 *)(origin_bytes + 0x25) + *(u16 *)(((u8 *)dir_step_y) + direction_offset)),
        *(s16 *)(actor_bytes + 0x88));
    if (tile_slot >= 0) {
        s32 *shared_base;
        s32 *shared_slot;
        shared_base = D_80162FE4;
        shared_slot = shared_base;
        *(ItemWord *)shared_base = *(ItemWord *)&((s32 *)dungeon_ground_items)[tile_slot];
        ((s32 *)dungeon_ground_items)[tile_slot] = 0;
        return (s32)shared_slot;
    }

    target = probe_directional_neighbor(actor, *(u8 *)(origin_bytes + 0x24), *(u8 *)(origin_bytes + 0x25),
                           *(s16 *)(actor_bytes + 0x2A));
    if (target != NULL) {
        if (target == (void *)dungeon_actor_ring_anchor[0]) {
            if (is_linked_entity_flagged_80000(target, target) != 0) {
                return 0;
            }
            {
                s32 slot_index;
                s16 item_count;
                s32 *slot_scan;
                s32 count;
                slot_index = 0;
                count = 0;
                slot_scan = (s32 *)0x80010000;
                for (;;) {
                    if (slot_scan[167] != 0) {
                        count++;
                    }
                    slot_scan++;
                    if (++slot_index >= 20) {
                        break;
                    }
                }
                item_count = count;
                if (item_count == 0) {
                    return 0;
                }
                count =
                    (s32)((((generate_random_value() & 0xFFFF) % item_count) << 16) >> 14);
                slot_index = count + 0x80010000;
                if (*(u8 *)(slot_index + 0x249) == 0 || *(u8 *)(slot_index + 0x249) == 0x13) {
                    return 0;
                }
                if (*(u8 *)(slot_index + 0x24B) & 0x20) {
                    return 0;
                }
                {
                    s32 item_data;
                    s32 *shared_base;

                    item_ptr = (u8 *)(count + 0x80010248);
                    item_data = *(s32 *)item_ptr;
                    shared_base = D_80162FE4;
                    shared_base[0] = item_data;


                    clear_slot_and_update_linked_state(item_ptr, (void *)slot_index);
                    return (s32)shared_base;
                }
            }
        }
        if (*(u8 *)((u8 *)target + 0x49) == 0) {
            return 0;
        }
        if (*(u8 *)((u8 *)target + 0x4B) & 0x20) {
            return 0;
        }
        {
            s32 *shared_base;
            s32 *shared_slot;
            s32 item_data;

            shared_base = D_80162FE4;

            item_data = *(s32 *)((u8 *)target + 0x48);
            shared_slot = shared_base;
            shared_base[0] = item_data;

            *(s32 *)((u8 *)target + 0x48) = 0;
            return (s32)shared_slot;
        }
entry_zero:
    }
    return 0;
}
