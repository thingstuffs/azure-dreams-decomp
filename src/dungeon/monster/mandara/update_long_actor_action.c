#include "shared/sprite_source.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/dungeon_floor.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "engine/node/allocation.h"
#include "dungeon/player/object.h"
#include "engine/node.h"

typedef struct S_80170F6C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    union { s16 s; u16 u; } unk_A8;   /* accessed as both */
    u16 unk_AA;
} S_80170F6C_0;   /* arg0 in update_long_actor_action */

typedef struct S_80170F6C_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x4];
    u16 unk_6A;
    u8 pad_6C[0x1];
    s8 unk_6D;
} S_80170F6C_1;   /* arg3 in update_long_actor_action */

typedef struct S_80170F6C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
    u32 unk_08;
    s32 unk_0C;
    s32 unk_10;
} S_80170F6C_3;   /* arg1 in update_long_actor_action */

typedef struct S_80170F6C_4 {
    ObjectNodeHeader node;
    u8 pad_20[0x9A];
    u8 unk_BA;
} S_80170F6C_4;   /* object in update_long_actor_action */

typedef struct S_80170F6C_8 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80170F6C_8;   /* D_800814A8[0] in update_long_actor_action */

typedef struct S_80170F6C_10 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170F6C_10;   /* status_object in update_long_actor_action */

typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern s32 register_node(ObjectNodeHeader *entry, void *registration_id);
extern void select_sprite_entry(void *, s16, s16);
extern s32 rsin(s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);

extern void func_80171910(void *controller, ObjectPosition *context, void *entity, void *path_state);
extern void advance_actor_path_step(void *, void *, void *, void *);
s32 validate_transition_and_update_action(ActorRecord *state, ObjectPosition *transition_id, SpriteFrameState *sprite, ActorRecord *actor);
void reset_action_and_select_facing_animation(ActorRecord *action_state, ObjectPosition *action_context, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 func_80172658(void *, void *, void *, s32);
extern void func_80174250(void *, void *, void *, void *);

#include "shared/record_ptrs.h"
extern u8 secondary_sprite[];
extern u8 mandara_object_callback_2[];
#include "dungeon/monster/mandara.h"
#include "dungeon/item.h"
#include "dungeon/actor.h"
extern u8 D_80175260[];
extern u8 D_80175290[];
extern u8 mandara_frame_set_1[];
extern u8 mandara_frame_set[];

/* Selects movement, attacks, and spells from actor status, including a timed directional particle
 * sequence. */
void update_long_actor_action(ActorRecord *self_object, ObjectPosition *aux_entity, SpriteFrameState *sprite, ActorRecord *entity) {
    ObjectNodeHeader *previous_node;
    void *previous_body;
    ActorRecord *previous_actor;
    u16 initial_flags = g_dungeon_status.flags;
    void *post_current;
    u8 *post_table;
    u16 scratch;
    s8 result;

    if (initial_flags & 0x1000) {
        self_object->action_id.u = 0xE;
        func_80171910(self_object, aux_entity, sprite, entity);
        return;
    }

    if (entity->mp_value.parts.whole == 0) {
        advance_actor_pending_action(self_object, aux_entity, sprite, entity);
        {
            void *current =
                sprite->frameTable;
            void *table;
            table = (u8 *)&mandara_frame_set_1;
            post_current = current;
            post_table = table;
            if (post_current != post_table) {
                u32 post_index;

                sprite->frameTable = post_table;
                post_index = ((g_game_work.view.camera_rotation.parts.viewAngle +
                    entity->facing + 0x100) >> 9) & 7;
                select_sprite_entry(sprite,
                    *(u8 *)((unsigned long)post_index +
                            (unsigned long)post_table),
                    0);
            }
            return;
        }
    }

    if (((S_80170F6C_1 *)entity)->unk_1C & 0x200) {
        if (sprite->frameTable == mandara_frame_set_1) {
            self_object->action_id.u = 0xD;
            self_object->action_phase.u = 1;
            ((S_80170F6C_0 *)self_object)->unk_8C = 0;
            ((S_80170F6C_1 *)entity)->unk_1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(self_object, aux_entity, sprite, mandara_frame_set_1) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((S_80170F6C_1 *)entity)->unk_1C & 0x100) {
            begin_pushed_actor_move(self_object, aux_entity, sprite, entity);
            return;
        }

        {
            u32 state;
            u32 current_state = self_object->action_id.u;
            state = 0xE;
            if (current_state != state) {
                if (sprite->frameTable != mandara_direction_frames) {
                    sprite->frameTable = mandara_direction_frames;
                    select_sprite_entry(sprite,
                        mandara_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                }
                self_object->action_id.u = state;
            }
        }

        if (((S_80170F6C_1 *)entity)->unk_14 & 0x20000) {
            switch (self_object->unk_A8.s) {
            case 0:
                if (sprite->frameTable != mandara_frame_set) {
                    g_dungeon_status.activity_counts.parts.pending_action_count++;
                    self_object->unk_AA = ((S_80170F6C_1 *)entity)->unk_2A.u;
                    entity->facing =
                        (entity->movement_facing + 0x800) & 0xFFF;
                    sprite->flags &= 0x9FFF;
                    ((S_80170F6C_0 *)self_object)->unk_A6 = 300;
                }
                self_object->unk_A8.u++;
                return;

            case 1:
            {
                u16 timer = ((S_80170F6C_0 *)self_object)->unk_A6 - 1;

                ((S_80170F6C_0 *)self_object)->unk_A6 = timer;
                if (((s32)timer << 16) <= 0 ||
                    entity->hp_delta != 0) {
                    g_dungeon_status.activity_counts.parts.pending_action_count--;
                    aux_entity->velocity_y = 0;
                    aux_entity->velocity_x = 0;
                    set_record_integer_tile_center(aux_entity,
                        sprite->tile_x, sprite->tile_y);
                    ((S_80170F6C_1 *)entity)->unk_14 &= ~0x20000;
                    self_object->unk_A8.u = 0;
                    return;
                }
                if (((S_80170F6C_1 *)entity)->unk_14 & 0x1000000) {
                    self_object->unk_A8.u++;
                    sprite->frameTable = mandara_frame_set;
                    select_sprite_entry(sprite,
                        mandara_frame_set[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    ((S_80170F6C_0 *)self_object)->unk_A6 = 0;
                    return;
                }
                return;
            }

            case 2:
            {
                s32 scale;
                S_80170F6C_4 *object;
                SpriteFrameState *part;
                ObjectPosition *payload;
                u32 color;
                u32 payload_word;
                u32 texture_word;

                aux_entity->velocity_x =
                    dir_step_x[((s32)(entity->movement_facing << 16)) >> 25] << 16;
                aux_entity->velocity_y =
                    dir_step_y[((s32)(entity->movement_facing << 16)) >> 25] << 16;
                scale = rsin((s16)((S_80170F6C_0 *)self_object)->unk_A6 << 8);
                aux_entity->velocity_x = aux_entity->velocity_x +
                    (aux_entity->velocity_x * scale >> 9);
                scale = rsin((s16)((S_80170F6C_0 *)self_object)->unk_A6 << 8);
                aux_entity->velocity_y = aux_entity->velocity_y +
                    (aux_entity->velocity_y * scale >> 9);

                object = allocate_list_node(0x312, &scene_object_list_anchor.next);
                if (object != 0) {
                    register_node(&object->node, project_sprite_chain);
                    payload = object->node.position;
                    object->node.update_callback = mandara_object_callback_2;
                    part = object->node.sprite;
                    payload->x.v = aux_entity->x.v;
                    payload = object->node.position;
                    payload->y.v = aux_entity->y.v;
                    payload = object->node.position;
                    payload_word = ((S_80170F6C_3 *)aux_entity)->unk_08;
                    color = 0x00800000;
                    payload->z.v = payload_word;
                    part->scale_y = 0x1000;
                    part->scale_x = 0x1000;
                    part->tpage_abr = 0;
                    part->unk_00 = secondary_sprite;
                    part->flags |= 0xC;
                    texture_word = ((u32)((SpriteSourceEntry *)secondary_sprite)->source);
                    color |= 0x8080;
                    part->unk_04 = 0;
                    part->frame_ticks = 0;
                    part->color.word = color;
                    part->source = texture_word;
                    object->unk_BA = 0;
                }

                {
                    u16 old_timer = ((S_80170F6C_0 *)self_object)->unk_A6;
                    ((S_80170F6C_0 *)self_object)->unk_A6 = old_timer + 1;
                    if ((s16)old_timer >= 3) {
                        sprite->flags &= 0xF7FF;
                        aux_entity->velocity_y = 0;
                        aux_entity->velocity_x = 0;
                        ((S_80170F6C_0 *)self_object)->unk_A6 = 4;
                        self_object->unk_A8.u++;
                        return;
                    }
                }
                return;
            }

            case 3:
            {
                u16 timer = ((S_80170F6C_0 *)self_object)->unk_A6 - 1;

                ((S_80170F6C_0 *)self_object)->unk_A6 = timer;
                if (((s32)timer << 16) <= 0) {
                    sprite->flags &= 0xF7FF;
                    aux_entity->velocity_y = 0;
                    aux_entity->velocity_x = 0;
                    ((S_80170F6C_0 *)self_object)->unk_A6 = 3;
                    self_object->unk_A8.u++;
                    return;
                }
                return;
            }

            case 4:
            {
                s32 x;
                s32 y;
                s32 coord;
                s32 coord_2;
                s32 delta;
                s32 delta_2;
                u16 timer;

                coord_2 = sprite->tile_x << 6;
                delta_2 = aux_entity->x.w.i - 0x20;
                x = coord_2 - delta_2;
                aux_entity->velocity_x = (s32)((u32)x << 15) >> 1;
                coord = sprite->tile_y << 6;
                delta = aux_entity->y.w.i - 0x20;
                y = coord - delta;
                aux_entity->velocity_y = (s32)((u32)y << 15) >> 1;
                timer = ((S_80170F6C_0 *)self_object)->unk_A6 - 1;
                ((S_80170F6C_0 *)self_object)->unk_A6 = timer;
                if (((s32)timer << 16) <= 0) {
                    g_dungeon_status.activity_counts.parts.pending_action_count--;
                    aux_entity->velocity_y = 0;
                    aux_entity->velocity_x = 0;
                    set_record_integer_tile_center(aux_entity,
                        sprite->tile_x, sprite->tile_y);
                    ((S_80170F6C_1 *)entity)->unk_14 &= ~0x20000;
                    entity->facing = ((S_80170F6C_0 *)self_object)->unk_AA;
                    sprite->frameTable = mandara_direction_frames;
                    select_sprite_entry(sprite,
                        mandara_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                        0);
                    self_object->unk_A8.u = 0;
                    return;
                }
                return;
            }
            default:
                return;
            }
        } else {
            self_object->action_state_flags &= 0xFFF3;
            if (entity->hp_delta == 0 ||
                begin_ready_actor_directional_action(self_object, aux_entity, sprite, D_80175260) == 0) {
                if (((S_80170F6C_1 *)entity)->unk_1C & 0x80000) {
                    begin_actor_move_to_target_facing(self_object, aux_entity, sprite, entity);
                    func_80174250(self_object, aux_entity, sprite, entity);
                    return;
                }
                if ((can_entity_gain_level(entity) << 16) != 0) {
                    process_selected_actor_record(self_object, aux_entity, sprite, entity);
                }
            } else {
                return;
            }
        }
    }

    result = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = result;

    if (entity->pending_turn_updates > 0) {
        if (((S_80170F6C_1 *)entity)->unk_1C & 0x20) {
            update_actor_status_and_mp(entity);
            return;
        }
        if (*(u16 *)&sprite->tile_x == reference_tile_object.tile_position.word) {
            advance_actor_path_step(self_object, aux_entity, sprite, entity);
            return;
        }
        if (!(entity->action_flags & 0x8000)) {
            if ((g_dungeon_status.flags & 0x2000) &&
                ((check_entity_relation(entity,
                    (previous_node = primary_actor_record->previous_actor_header,
                    previous_body = previous_node + 1, previous_actor = previous_body)) << 16) != 0)) {
                return;
            }
            if ((func_80172658(self_object, aux_entity, sprite, 0) << 16) == 0) {
                return;
            }
            entity->action_flags |= 0x4000;
            if (!(entity->action_flags & 0x8000)) {
                advance_actor_path_step(self_object, aux_entity, sprite, entity);
                return;
            }
        }

        switch (entity->action_flags & 0x3FFF) {
        case 8:
        case 9:
        {
            u32 case_flags;
            if ((entity->action_flags & 0x3FFF) == 9) {
                case_flags = self_object->action_state_flags | 0x8000;
            } else {
                case_flags = self_object->action_state_flags & 0x7FFF;
            }
            self_object->action_state_flags = case_flags;
        }
            if ((validate_transition_and_update_action(self_object, aux_entity, sprite, entity) << 16) != 0) {
                return;
            }
            reset_action_and_select_facing_animation(self_object, aux_entity, sprite, entity);
            return;

        case 5:
        case 6:
        case 7:
        {
            s16 next_position;
            void *status_object;

            next_position = get_rounded_facing_and_rounding_flag(
                sprite->tile_x, sprite->tile_y,
                reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                &scratch);
            status_object = primary_actor_record;
            entity->facing = next_position;
            if (((S_80170F6C_10 *)status_object)->unk_9A == 0x11) {
                begin_actor_spell_action(self_object, aux_entity, sprite, D_80175290, update_long_actor_action);
                return;
            }
        }
        case 12:
            update_actor_status_and_mp(entity);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(self_object, aux_entity, sprite, D_80175290, update_long_actor_action);
            return;

        case 4:
        case 10:
        case 11:
        default:
            advance_actor_path_step(self_object, aux_entity, sprite, entity);
            return;
        }
    }

    {
        u32 final_flags =
            ((S_80170F6C_1 *)entity)->unk_1C;
        if (!(final_flags & 0x2000)) {
            if ((result < 0) || !(dungeon_rooms[result].flags & 2)) {
                u32 final_mask =
                    final_flags & 0x430;
                if (!final_mask) {

                    if ((test_neighbor_position_relation(
                            sprite->tile_x, sprite->tile_y,
                            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y) << 16) != 0) {
                        entity->facing = get_rounded_facing_and_rounding_flag(
                            sprite->tile_x, sprite->tile_y,
                            reference_tile_object.tile_position.parts.tile_x, reference_tile_object.tile_position.parts.tile_y,
                            &scratch);
                    }
                }
            }
        }
    }

    if (!(g_dungeon_status.flags & 0x2000) &&
        !(sprite->flags & 0x40)) {
        post_current =
            sprite->frameTable;
        post_table = (u8 *)&mandara_direction_frames;
        if (post_current != post_table) {
            u32 post_index;

            sprite->frameTable = post_table;
            post_index = ((g_game_work.view.camera_rotation.parts.viewAngle +
                entity->facing + 0x100) >> 9) & 7;
            select_sprite_entry(sprite,
                *(u8 *)((unsigned long)post_index +
                        (unsigned long)post_table),
                0);
        }
    }

    return;
}
