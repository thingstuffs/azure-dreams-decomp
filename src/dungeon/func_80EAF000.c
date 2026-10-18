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
} ActorBytesFieldView_80EAF000;

typedef struct {
    u8 pad_00[0x24];
    u8 field_24;
    u8 field_25;
} OriginBytesFieldView_80EAF000;

typedef struct {
    u8 pad_00[0x249];
    u8 field_249;
    u8 pad_24A[0x1];
    u8 field_24B;
} SlotBaseFieldView_80EAF000;


/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x48];
    union {
        s32 s32;
        struct { u8 pad[0x1]; u8 value; } u8_at_1;
        struct { u8 pad[0x3]; u8 value; } u8_at_3;
    } field_48;
} TargetFieldView_80EAF000;

extern void clear_slot_and_update_linked_state(void *);
extern void *place_actor_at_directional_neighbor(void *, u8, u8, s16);
extern s32 generate_random_value(void);
extern s16 find_floor_item_at_world_position(s16, s16, s16);
extern s32 func_800C8310(void *, void *);

extern s32 D_800E3D7C[];
extern s32 D_80150FE4[];



 s32 transfer_eligible_ground(void *, void *) ;
/* Transfer an eligible ground or carried item to the pending item slot. */
 s32 transfer_eligible_ground(void *origin, void *actor) {
    u8 *origin_bytes = (u8 *)origin;
    u8 *actor_bytes = (u8 *)actor;
    s32 direction_offset;
    s16 ground_slot;
    void *target;
    s32 slot_offset;
    u8 *slot_base;
    u8 *item_ptr;

    direction_offset = (((ActorBytesFieldView_80EAF000 *)actor_bytes)->field_2A.u16 >> 8) & 0xE;
    ground_slot = find_floor_item_at_world_position(
        (s16)(((OriginBytesFieldView_80EAF000 *)origin_bytes)->field_24 + *(u16 *)(((u8 *)dir_step_x) + direction_offset)),
        (s16)(((OriginBytesFieldView_80EAF000 *)origin_bytes)->field_25 + *(u16 *)(((u8 *)dir_step_y) + direction_offset)),
        ((ActorBytesFieldView_80EAF000 *)actor_bytes)->field_88);
    if (ground_slot >= 0) {
        D_80150FE4[0] = ((s32 *)D_800E3548)[ground_slot];
        ((s32 *)D_800E3548)[ground_slot] = 0;
        return (s32)D_80150FE4;
    }

    target = place_actor_at_directional_neighbor(actor, ((OriginBytesFieldView_80EAF000 *)origin_bytes)->field_24, ((OriginBytesFieldView_80EAF000 *)origin_bytes)->field_25,
                           ((ActorBytesFieldView_80EAF000 *)actor_bytes)->field_2A.s16);
    if (target != 0) {
        if (target == (void *)D_800E3D7C[0]) {
            if (func_800C8310(target, target) != 0) {
                return 0;
            }
            {
#ifdef __mips__
                s16 item_count;
                register s32 slot_index;
#else
                s32 slot_index;
                s16 item_count;
                s32 *inventory_scan;
#endif
                slot_index = 0;
                item_count = slot_index;
                item_ptr = (u8 *)0x80010000;
scan_loop:
                if (((s32 *)item_ptr)[167] != 0) {
                    item_count++;
                }
                slot_index++;
                item_ptr += sizeof(s32);
                if (slot_index < 20) {
                    goto scan_loop;
                }
                if (item_count == 0) {
                    return 0;
                }
                slot_offset = (s32)((((generate_random_value() & 0xFFFF) % item_count) << 16) >> 14);
                slot_base = (u8 *)(slot_offset + 0x80010000);
                item_ptr = (u8 *)(u32)((SlotBaseFieldView_80EAF000 *)slot_base)->field_249;
                if ((u32)item_ptr == 0 || (u32)item_ptr == 0x13) {
                    return 0;
                }
                if (((SlotBaseFieldView_80EAF000 *)slot_base)->field_24B & 0x20) {
                    return 0;
                }
                {
                    s32 item_word;

                    item_ptr = (u8 *)0x80010248;
                    item_ptr += slot_offset;
                    item_word = *(s32 *)item_ptr;
                    D_80150FE4[0] = item_word;
                    clear_slot_and_update_linked_state(item_ptr);
                    return (s32)D_80150FE4;
                }
            }
        }
        if (((TargetFieldView_80EAF000 *)target)->field_48.u8_at_1.value == 0) {
            return 0;
        }
        if (((TargetFieldView_80EAF000 *)target)->field_48.u8_at_3.value & 0x20) {
            return 0;
        }
        {
            s32 item_word;

            item_word = ((TargetFieldView_80EAF000 *)target)->field_48.s32;
            D_80150FE4[0] = item_word;
            ((TargetFieldView_80EAF000 *)target)->field_48.s32 = 0;
            return (s32)D_80150FE4;
        }
    }
    return 0;
}
