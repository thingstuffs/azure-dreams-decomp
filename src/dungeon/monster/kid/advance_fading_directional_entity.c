#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"



void unlink_entity_node();
void update_map_cell_flags_with_item_limit();
void distribute_experience_and_report_gains();
s32 detach_record_and_update_slot_state();
s32 play_sound_if_enabled();
void announce_familiar_defeat();


typedef struct S_80173724_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u16 unk_98;
    u8 pad_9A[0x1];
    u8 unk_9B;
} S_80173724_0;   /* arg0 in advance_fading_directional_entity */

typedef struct S_80173724_1_pre {
    u16 unk_00;
} S_80173724_1_pre;   /* the 0x2 bytes before arg3 in advance_fading_directional_entity, addressed as arg3[-1] */

typedef struct S_80173724_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    union { u32 u; s32 s; } unk_1C;   /* accessed as both */
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_80173724_1;   /* arg3 in advance_fading_directional_entity */

typedef struct S_80173724_2 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80173724_2;   /* arg1 in advance_fading_directional_entity */

typedef struct S_80173724_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173724_3;   /* arg2 in advance_fading_directional_entity */

typedef struct S_80173724_4 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80173724_4;   /* global_ptr in advance_fading_directional_entity */

/* Advance an entity through directional motion, fading, and removal. */
void advance_fading_directional_entity(void *anim_state, void *motion, void *sprite, void *entity) {
    s32 sound_flags;
    s32 direction_x;
    s32 direction_y;
    s32 direction_offset;
    s32 status_flags;
    u16 next_brightness;
    u32 phase;
    u32 sound_x;
    u32 sound_y;
    u8 brightness;

    phase = ((S_80173724_0 *)anim_state)->unk_9B;
    direction_offset = ((u16) ((S_80173724_1 *)entity)->unk_6A >> 8) & 0xE;
    direction_x = *(s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset);
    direction_y = *(s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset);
    switch (phase) {
    case 0:
    {
        u32 clear_bit_27 = 0xF7FFFFFF;
        u32 clear_bit_18;
        u32 entity_flags;
        u16 anim_flags;

        anim_flags = ((S_80173724_0 *)anim_state)->unk_98;
        clear_bit_18 = 0xFFFBFFFF;
        anim_flags |= 8;
        ((S_80173724_0 *)anim_state)->unk_98 = anim_flags;
        entity_flags = ((S_80173724_1 *)entity)->unk_1C.u;
        entity_flags &= clear_bit_27;
        entity_flags &= clear_bit_18;
        ((S_80173724_1 *)entity)->unk_1C.u = entity_flags;
        ((S_80173724_2 *)motion)->unk_0C = direction_x << 0x10;
        ((S_80173724_2 *)motion)->unk_10 = direction_y << 0x10;
        ((S_80173724_2 *)motion)->unk_14 = 0xFFF40000;
        play_sound_if_enabled(0x805);
        ((S_80173724_0 *)anim_state)->unk_9B = ((S_80173724_0 *)anim_state)->unk_9B + 1;
    }
    case 1:
        (((S_80173724_2 *)motion)->unk_14) += 0x1C000;
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        ((S_80173724_0 *)anim_state)->unk_9B = ((S_80173724_0 *)anim_state)->unk_9B + 1;
    case 2:
        status_flags = ((S_80173724_1 *)entity)->unk_14;
        if (status_flags & 0x4000) {
            if (!(status_flags & 0x20000000)) {
                announce_familiar_defeat(entity);
            }
        }
        ((S_80173724_3 *)sprite)->unk_10 = 0x60;
        ((S_80173724_3 *)sprite)->unk_14 |= 0xC;
        ((S_80173724_0 *)anim_state)->unk_9B = ((S_80173724_0 *)anim_state)->unk_9B + 1;
    case 3:
        ((S_80173724_2 *)motion)->unk_14 += 0x1C000;
        if (!(((S_80173724_3 *)sprite)->unk_14 & 0x6000)) {
            return;
        }
        ((S_80173724_0 *)anim_state)->unk_96 = 0x80U;
        ((S_80173724_0 *)anim_state)->unk_9B = ((S_80173724_0 *)anim_state)->unk_9B + 1;
        return;
    case 4:
        ((S_80173724_1 *)entity)->unk_1C.s |= 0x10000000;
        ((S_80173724_2 *)motion)->unk_14 += 0x20000;
        brightness = (u8)((S_80173724_0 *)anim_state)->unk_96;
        ((S_80173724_3 *)sprite)->unk_0E = brightness;
        ((S_80173724_3 *)sprite)->unk_0D = brightness;
        ((S_80173724_3 *)sprite)->unk_0C = brightness;
        next_brightness = ((S_80173724_0 *)anim_state)->unk_96 - 0x18;
        ((S_80173724_0 *)anim_state)->unk_96 = next_brightness;
        if ((s16)next_brightness >= 0x18) {
            return;
        }
        if (((s32)g_dungeon_status.pending_display_owner) == (entity - 0x20)) {
            *(s32 *)&g_dungeon_status.pending_display_owner &= 0x7FFFFFFF;
        }
        distribute_experience_and_report_gains(entity);
        detach_record_and_update_slot_state(entity);
        sound_x = ((S_80173724_3 *)sprite)->unk_24;
        sound_y = ((S_80173724_3 *)sprite)->unk_25;
        sound_flags = 0x3000;
        if (((S_80173724_1 *)entity)->unk_1C.s & 0x2000) {
            sound_flags = 0x300;
        }
        update_map_cell_flags_with_item_limit(sound_x, sound_y, sound_flags);
        unlink_entity_node(entity);
        ((S_80173724_1_pre *)entity)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    default:
        return;
    }
}
