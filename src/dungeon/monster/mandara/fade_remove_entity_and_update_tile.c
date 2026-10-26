#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80083460.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor.h"
#include "dungeon/monster/mandara.h"

typedef struct S_801735B8_0 {
    u8 pad_00[0x96];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801735B8_0;   /* arg0 in fade_remove_entity_and_update_tile */


void unlink_entity_node(void *);
void update_map_cell_flags_with_item_limit(s32, s32, s32);
void distribute_experience_and_report_gains(void *);
void * detach_record_and_update_slot_state(void *);
void play_sound_if_enabled(s32);

/* Fades out an entity, then removes it and updates its tile flags. */
void fade_remove_entity_and_update_tile(void *fade_state, void *unused, SpriteFrameState *visual_data, ActorRecord *entity) {
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
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        ((S_801735B8_0 *)fade_state)->unk_9B = 1;
                        /* fallthrough */
    case 1:
        entity_flags = entity->flags14;
        if (entity_flags & 0x4000) {
            if (!(entity_flags & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        ((S_801735B8_0 *)fade_state)->unk_96.u = 6;
        ((S_801735B8_0 *)fade_state)->unk_9B =
            (u8)(((S_801735B8_0 *)fade_state)->unk_9B + 1);
        visual_data->clut = 0xFF80;
                        /* fallthrough */
    case 2:
        entity->flags1C |= 0x10000000;
        countdown = ((S_801735B8_0 *)fade_state)->unk_96.u - 1;
        ((S_801735B8_0 *)fade_state)->unk_96.u = countdown;
        if ((countdown << 16) <= 0) {
            if (visual_data->color.c.r >= 0x10U) {
                visual_data->color.word += (s32)0xFFEFEFF0;
            }
            visual_data->tpage_abr = 0x20;
            visual_data->flags |= 0xC;
        } else {
            visual_data->color.word = 0x00808080;
        }

        if (((S_801735B8_0 *)fade_state)->unk_96.s == 0) {
            play_sound_if_enabled(0x805);
        }
        if (!(visual_data->flags & 0x8000)) {
            if (visual_data->color.c.r >= 0x10U) {
                return;
            }
        }

        tracked_entity = ((s32)g_dungeon_status.pending_display_owner);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.pending_display_owner =
                tracked_entity & 0x7FFFFFFF;
        }
        distribute_experience_and_report_gains(entity);
        detach_record_and_update_slot_state(entity);

        tile_x = visual_data->tile_x;
        tile_y = visual_data->tile_y;
        tile_mask = 0x3000;
        if (entity->flags1C & 0x2000) {
            tile_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_mask);
        unlink_entity_node(entity);
        (*(u16 *)((u8 *)entity + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        break;
    default:
        return;
    }
}

/* MECHANISM: A natural three-case switch preserves the retail dispatch and fallthrough block order.
   True-space targets remain local joins. Direct D_80083460+0xA access schedules the page base, and u16
   0xFF80 selects the ori encoding. */
