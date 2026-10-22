#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_80173A3C_0 {
    u8 pad_00[0x96];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80173A3C_0;   /* arg0 in fade_reshape_and_remove_entity */

typedef struct S_80173A3C_1 {
    u8 pad_00[0xC];
    union {
        struct { u32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_80173A3C_1;   /* arg2 in fade_reshape_and_remove_entity */


typedef struct S_80173A3C_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
} S_80173A3C_4;   /* arg1 in fade_reshape_and_remove_entity */


extern void play_sound_if_enabled(s32);
extern void distribute_experience_and_report_gains(void *);
extern void detach_record_and_update_slot_state(void *);
extern void create_effect_or_fallback(s32, s32, s32, void *);
extern s32 get_entity_effect_value(void *, s32);
extern void update_map_cell_flags_with_item_limit(s32, s32, s32);
extern void unlink_entity_node(void *);
extern void announce_familiar_defeat(void *);


/* Fades and reshapes the sprite, then removes the entity when the effect ends. */
void fade_reshape_and_remove_entity(void *fade_state, void *position, void *sprite, void *entity)
{
    u8 fade_phase;
    u16 frames_left;

    fade_phase = ((S_80173A3C_0 *)fade_state)->unk_9B;
    switch (fade_phase) {
    case 0:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }

        ((S_80173A3C_0 *)fade_state)->unk_9B = 1;
        ((S_80173A3C_1 *)sprite)->unk_10 = 0x20;
        ((S_80173A3C_1 *)sprite)->unk_12 -= 0x80;
        ((S_80173A3C_1 *)sprite)->unk_14 |= 0xC;
        ((ActorRecord *)entity)->flags1C |= 0x10000000;
        play_sound_if_enabled(0x805);
        ((S_80173A3C_1 *)sprite)->unk_0C.at00.v = 0x00808080;
        ((S_80173A3C_0 *)fade_state)->unk_96.s = 0xC;
    case 1:
        break;
    default:
        return;
    }

    ((S_80173A3C_1 *)sprite)->unk_0C.at00u.v -= ((S_80173A3C_1 *)sprite)->unk_0C.at00u.v / ((S_80173A3C_0 *)fade_state)->unk_96.s;
    ((S_80173A3C_1 *)sprite)->unk_0C.at01.v -= ((S_80173A3C_1 *)sprite)->unk_0C.at01.v / ((S_80173A3C_0 *)fade_state)->unk_96.s;
    ((S_80173A3C_1 *)sprite)->unk_0C.at02.v -= ((S_80173A3C_1 *)sprite)->unk_0C.at02.v / ((S_80173A3C_0 *)fade_state)->unk_96.s;

    ((S_80173A3C_1 *)sprite)->unk_1C >>= 2;
    ((S_80173A3C_1 *)sprite)->unk_1E >>= 1;
    ((S_80173A3C_1 *)sprite)->unk_1C *= 3;
    ((S_80173A3C_1 *)sprite)->unk_1E *= 3;

    frames_left = ((S_80173A3C_0 *)fade_state)->unk_96.u - 1;
    ((S_80173A3C_0 *)fade_state)->unk_96.u = frames_left;
    if (((s32)frames_left << 16) > 0) {
        if ((((S_80173A3C_1 *)sprite)->unk_14 & 0x8000) == 0) {
            return;
        }
    }

    if ((((u32)((ActorRecord *)entity)->flags14) & 0x20000000) == 0) {
        DungeonGlobalStatus *entity_tracker = &g_dungeon_status;
        if (entity_tracker->pending_display_owner == (u8 *)entity - 0x20) {
            (*(u32 *)&entity_tracker->pending_display_owner) &= 0x7FFFFFFF;
        }
    }

    if ((((u32)((ActorRecord *)entity)->flags14) & 0x4000) == 0) {
        distribute_experience_and_report_gains(entity);
        detach_record_and_update_slot_state(entity);
        if (((ActorRecord *)entity)->unk_49 != 0 &&
            (((ActorRecord *)entity)->unk_4B & 0x20) == 0) {
            create_effect_or_fallback(((S_80173A3C_4 *)position)->unk_02, ((S_80173A3C_4 *)position)->unk_06,
                          ((ActorRecord *)entity)->ground_height, (u8 *)entity + 0x48);
        }
        if ((get_entity_effect_value(entity, 0x1B) << 16) == 0) {
            s32 entity_flags = ((u32)((ActorRecord *)entity)->flags1C);
            s32 effect_color_0 = ((S_80173A3C_1 *)sprite)->unk_24;
            s32 effect_color_1 = ((S_80173A3C_1 *)sprite)->unk_25;
            s32 effect_mask = 0x3000;
            if (entity_flags & 0x2000) {
                effect_mask = 0x300;
            }
            update_map_cell_flags_with_item_limit(effect_color_0, effect_color_1, effect_mask);
        }
        unlink_entity_node(entity);
        (*(u16 *)((u8 *)entity + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    if ((((u32)((ActorRecord *)entity)->flags14) & 0x20000000) == 0) {
        announce_familiar_defeat(entity);
    }
    distribute_experience_and_report_gains(entity);
    detach_record_and_update_slot_state(entity);
    if ((get_entity_effect_value(entity, 0x1B) << 16) == 0) {
        s32 entity_flags = ((u32)((ActorRecord *)entity)->flags1C);
        s32 effect_color_0 = ((S_80173A3C_1 *)sprite)->unk_24;
        s32 effect_color_1 = ((S_80173A3C_1 *)sprite)->unk_25;
        s32 effect_mask = 0x3000;
        if (entity_flags & 0x2000) {
            effect_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(effect_color_0, effect_color_1, effect_mask);
    }
    unlink_entity_node(entity);
    (*(u16 *)((u8 *)entity + -2)) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    play_sound_if_enabled(0x609);
}
