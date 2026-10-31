#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "dungeon/effect.h"
#include "m2c_compat.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "records/Rec_func_80173D78_arg0.h"
#include "dungeon/monster/manoeva.h"
#include "dungeon/system.h"
#include "dungeon/level.h"
#include "engine/node.h"
#include "dungeon/item/message.h"
#include "dungeon/item/message/text.h"
#include "dungeon/actor/effect.h"
#include "dungeon/effect/screen.h"

typedef struct S_80173D78_1 {
    u8 pad_00[0xC];
    union {
        struct { u8 v; } at00;
        struct { u32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x3]; u8 v; } at03;
        struct { u8 pad[0x3]; u8 v; } at03u;
    } unk_0C;   /* overlapping accesses */
    u8 pad_10[0x2];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_80173D78_1;   /* arg2 in update_actor_target_effect_action */

typedef struct S_80173D78_2 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    union { s32 i; void * p; } unk_60;   /* accessed as both */
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x1A];
    s16 unk_88;
} S_80173D78_2;   /* arg3 in update_actor_target_effect_action */

typedef struct S_80173D78_3 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80173D78_3;   /* found in update_actor_target_effect_action */


typedef struct S_80173D78_5 {
    u8 pad_00[0x10];
    u32 unk_10;
} S_80173D78_5;   /* base in update_actor_target_effect_action */

extern u8 D_8017086C[];
extern u8 D_80170898[];
void func_80170EE4(ActorRecord *actor_state_in, ObjectPosition *update_context_in, SpriteFrameState *map_object, ActorRecord *actor_data);
void transfer_linked_object_state(ActorRecord *owner, ObjectPosition *object_id, SpriteFrameState *dest_object, ActorRecord *dest_state);

s32 register_node(ObjectNodeHeader *entry, void *registration_id);
void unlink_entity_node();
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
void *find_eligible_actor_at_tile_and_height();
s32 display_text_with_fullwidth_adjustment(s8 *text);
void update_actor_status_and_mp();
void *spawn_manoeva_from_record();

/* Updates target selection, effect creation, and the sprite fade-out sequence. */
/* Selects an actor or item on the tile ahead, creates Manoeva's replacement, then fades the old sprite and
 * transfers state. */
void update_actor_target_effect_action(ActorRecord *body, void *context, S_80173D78_1 *sprite, S_80173D78_2 *actor)
{
    S_80173D78_3 *target;
    void *effect;
    ObjectNodeHeader *object;
    S_80173D78_5 *callback_flags;
    void *node_storage;
    s32 target_x;
    s32 target_y;
    s32 direction_offset;
    u8 *text_start;
    u8 *text_end;
    u8 *text_buffer;
    s32 tile_mask;
    s32 map_flags;
    u32 sound_x;
    u32 sound_y;
    s16 tile_index;
    u16 sprite_flags;
    u16 ticks_left;
    u8 state;

    state = body->action_phase.u;
    if (state >= 5U) {
        return;
    }
    switch (state) {
    case 0:
        sprite_flags = sprite->unk_14;
        if (!(sprite_flags & 0xE000)) {
            return;
        }
        if (!(sprite_flags & 0x8000)) {
            play_sound_if_enabled(0x80D);
        }
        body->action_phase.u = body->action_phase.u + 1;
        if (sprite->unk_14 & 0x8000) {
            body->action_timer.u = 0;
            return;
        }
        body->action_timer.u = 0x10;
        return;

    case 1:
        if (!(body->action_timer.u & 3)) {
            if (!(sprite->unk_14 & 0x8000)) {
                spawn_offset_motion_object(body, context, sprite, 0);
                spawn_offset_motion_object(body, context, sprite, 1);
            }
        }
        ticks_left = body->action_timer.u - 1;
        body->action_timer.u = ticks_left;
        if ((s16)ticks_left > 0) {
            return;
        }

        direction_offset = ((u16)actor->unk_2A >> 8) & 0xE;
        target_x = sprite->unk_24 + *(u16 *)((s8 *)((s8 *)dir_step_x) + direction_offset);
        target_y = sprite->unk_25 + *(u16 *)((s8 *)((s8 *)dir_step_y) + direction_offset);
        actor->unk_60.i = 0;

        if (body->unk_AC.byte == 0) {
            target = find_eligible_actor_at_tile_and_height(actor, target_x & 0xFFFF, target_y & 0xFFFF,
                                   actor->unk_88);
            actor->unk_60.p = target;
            if (target != 0) {
                state = target->unk_13;
                if (((u32)(state - 1) >= 0x2DU) || (state == 0x1E)) {
                    text_end = get_unused_text_buffer();
                    text_buffer = text_end;
                    text_end = append_entity_display_text(actor, text_start = text_buffer);
                    clear_byte_and_advance(
                        expand_text_control_codes(D_80170898,
                            append_entity_display_text(target,
                                write_text_byte_and_advance(0xA,
                                    expand_text_control_codes(D_8017086C, text_end)))));
                    display_text_with_fullwidth_adjustment(text_start);
                    play_sound_if_enabled(0x506);
                    actor->unk_60.i = 0;
                }
            }
        }

        if (body->unk_AC.byte < 2U) {
            if (actor->unk_60.i == 0) {
                tile_index = find_floor_item_at_world_position((s16)target_x, (s16)target_y,
                                     actor->unk_88);
                if (tile_index >= 0) {
                    actor->unk_60.i = tile_index + 1;
                }
            }
        }

        if (actor->unk_60.i == 0) {

            update_actor_status_and_mp(actor);
            body->unk_8C.address = &func_80170EE4;
            g_dungeon_status.activity_counts.parts.pending_action_count =
                ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
            actor->unk_1C &= 0xEFFFFFFF;
            return;
        }

        body->action_phase.u = body->action_phase.u + 1;
    case 2:
        map_flags = actor->unk_14;
        sound_x = sprite->unk_24;
        sound_y = sprite->unk_25;
        tile_mask = 0x3000;
        if (map_flags & 0x2000) {
            tile_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(sound_x, sound_y, tile_mask);

        actor->unk_1C |= 0x10000;
        effect = spawn_manoeva_from_record(body, context, sprite, actor);
        ((Rec_func_80173D78_arg0 *)body)->unk_A4 = effect;
        if (effect != 0) {
            node_storage = (s8 *)body - 0x20;
            object = node_storage;
            unlink_node(object);
            register_node(object, process_linked_states_mode_zero);
            sprite->unk_0C.at03.v = 0;
            sprite->unk_12 = sprite->unk_12 - 0x80;
            sprite->unk_14 |= 0xC;
            unlink_entity_node(actor);
            callback_flags = node_storage;
            callback_flags->unk_10 |= 0x80000000;
            body->action_phase.u = body->action_phase.u + 1;
            return;
        }

        map_flags = actor->unk_14;
        sound_x = sprite->unk_24;
        sound_y = sprite->unk_25;
        tile_mask = 0x3000;
        if (map_flags & 0x2000) {
            tile_mask = 0x300;
        }
        cycle_map_cell_flags(sound_x, sound_y, tile_mask);
        actor->unk_1C &= 0xFFFEFFFF;
        return;

    case 3:
        state = sprite->unk_0C.at03.v;
        if (state < 7U) {
            sprite->unk_0C.at03.v = state + 1;
            sprite->unk_0C.at00.v =
                sprite->unk_0C.at00.v +
                (-(s32)sprite->unk_0C.at00.v /
                 (8 - sprite->unk_0C.at03u.v));
            sprite->unk_0C.at01.v =
                sprite->unk_0C.at01.v +
                (-(s32)sprite->unk_0C.at01.v /
                 (8 - sprite->unk_0C.at03.v));
            sprite->unk_0C.at02.v =
                sprite->unk_0C.at02.v +
                (-(s32)sprite->unk_0C.at02.v /
                 (8 - sprite->unk_0C.at03.v));
            return;
        }

        node_storage = (s8 *)body - 0x20;
            object = node_storage;
        unlink_node(object);
        retire_tracked_effect_by_id(object);
        sprite->unk_0C.at03.v = 0;
        sprite->unk_0C.at00u.v = 0x00808080;
        sprite->unk_14 |= 0x800;
        sprite->unk_12 = sprite->unk_12 + 0x80;
        sprite->unk_14 &= 0xFFF3;
        body->action_phase.u = body->action_phase.u + 1;
        return;

    case 4:
        {

            body->action_id.u = 0x18;
            body->action_phase.u = 0;
            body->unk_8C.address = &transfer_linked_object_state;
            g_dungeon_status.activity_counts.parts.pending_action_count =
                ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1;
            actor->unk_6D = 0;
            actor->unk_1C &= 0xEFFFFFFF;
            actor->unk_46 &= 0x7FFF;
        }
    }
}
