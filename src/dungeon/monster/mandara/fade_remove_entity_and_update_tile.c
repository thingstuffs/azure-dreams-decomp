#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80083460.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801735B8_0 {
    u8 pad_00[0x96];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801735B8_0;   /* arg0 in fade_remove_entity_and_update_tile */


typedef struct S_801735B8_3 {
    u8 pad_00[0xC];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801735B8_3;   /* held_arg2 in fade_remove_entity_and_update_tile */

typedef struct S_801735B8_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_801735B8_4;   /* global_ptr in fade_remove_entity_and_update_tile */


void unlink_entity_node(void *);
void update_map_cell_flags_with_item_limit(s32, s32, s32);
void distribute_experience_and_report_gains(void *);
void detach_record_and_update_slot_state(void *);
void play_sound_if_enabled(s32);
void announce_familiar_defeat(void *);

/* Fades out an entity, then removes it and updates its tile flags. */
void fade_remove_entity_and_update_tile(void *fade_state, void *unused, void *visual_data, void *entity) {
    s32 state;
    s32 entity_flags;
    s32 tracked_entity;
    s32 tile_x;
    s32 tile_y;
    s32 tile_mask;
    u16 countdown;

    state = ((S_801735B8_0 *)fade_state)->unk_9B;
    switch (state) {
    case 0:
        if (((Rec_D_80083460 *)(&g_dungeon_status.unk_00))->unk_0A != 0) {
            return;
        }
        ((S_801735B8_0 *)fade_state)->unk_9B = 1;
                        /* fallthrough */
    case 1:
        entity_flags = ((Rec_D_80082E80 *)entity)->unk_14.at00_s32.v;
        if (entity_flags & 0x4000) {
            if (!(entity_flags & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        ((S_801735B8_0 *)fade_state)->unk_96.u = 6;
        ((S_801735B8_0 *)fade_state)->unk_9B =
            (u8)(((S_801735B8_0 *)fade_state)->unk_9B + 1);
        ((S_801735B8_3 *)visual_data)->unk_12 = 0xFF80;
                        /* fallthrough */
    case 2:
        ((Rec_D_80082E80 *)entity)->unk_1C.at00_s32.v |= 0x10000000;
        countdown = ((S_801735B8_0 *)fade_state)->unk_96.u - 1;
        ((S_801735B8_0 *)fade_state)->unk_96.u = countdown;
        if ((countdown << 16) <= 0) {
            if (((S_801735B8_3 *)visual_data)->unk_0C.u8 >= 0x10U) {
                ((S_801735B8_3 *)visual_data)->unk_0C.s32 += (s32)0xFFEFEFF0;
            }
            ((S_801735B8_3 *)visual_data)->unk_10 = 0x20;
            ((S_801735B8_3 *)visual_data)->unk_14 |= 0xC;
        } else {
            ((S_801735B8_3 *)visual_data)->unk_0C.s32 = 0x00808080;
        }

        if (((S_801735B8_0 *)fade_state)->unk_96.s == 0) {
            play_sound_if_enabled(0x805);
        }
        if (!(((S_801735B8_3 *)visual_data)->unk_14 & 0x8000)) {
            if (((S_801735B8_3 *)visual_data)->unk_0C.u8 >= 0x10U) {
                return;
            }
        }

        tracked_entity = ((s32)g_dungeon_status.unk_10);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.unk_10 =
                tracked_entity & 0x7FFFFFFF;
        }
        distribute_experience_and_report_gains(entity);
        detach_record_and_update_slot_state(entity);

        tile_x = ((S_801735B8_3 *)visual_data)->unk_24;
        tile_y = ((S_801735B8_3 *)visual_data)->unk_25;
        tile_mask = 0x3000;
        if (((Rec_D_80082E80 *)entity)->unk_1C.at00_s32.v & 0x2000) {
            tile_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_mask);
        unlink_entity_node(entity);
        (*(u16 *)((u8 *)entity + -2)) |= 0x8000;
        object_flag_block.flags |= 0x8000;
        break;
    default:
        return;
    }
}

/* MECHANISM: A natural three-case switch preserves the retail dispatch and fallthrough block order.
   True-space targets remain local joins. Direct D_80083460+0xA access schedules the page base, and u16
   0xFF80 selects the ori encoding. */
