#include "shared/object_node.h"
#include "shared/dungeon_floor.h"
#include "shared/entity.h"
#include "shared/tile_object.h"
#include "shared/sprite_frame_state.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;

typedef void (*DungeonCallback)(void *, void *, void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern s16 check_entity_relation(ActorRecord *entry, ActorRecord *anchor);
extern s8 find_active_rect_containing_point(s32, s32);
extern s16 test_neighbor_position_relation(s32 src_x, s32 src_y, s32 dst_x, s32 dst_y);
extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void *probe_directional_neighbor(void *entity, s32 x, s32 y, u32 direction);
extern s32 check_global_or_linked_flag_20000(void *);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, u8 *direction_frames);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern s32 reset_actor_action_state(void *actor, void *unused, SpriteFrameState *sprite, u8 *direction_frames);
extern s32 process_selected_actor_record(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor);
extern void begin_actor_spell_action(void *actor, void *effect_param, SpriteFrameState *target, u8 *direction_table, void *next_state);
extern void func_801715F0(void *controller, ObjectPosition *context, void *entity, void *path_state);
extern void func_80171848(void *, void *, void *, void *);
extern s32 func_80171FF4(ActorRecord *action_state, ObjectPosition *motion_param, SpriteFrameState *sprite_arg, ActorRecord *actor);
extern void func_801721B8(ActorRecord *action_state, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *actor);
void advance_actor_walk_animation(ActorRecord *owner, ObjectPosition *unused, SpriteFrameState *part, ActorRecord *actor);
extern s32 func_80172414(void *, void *, void *, s32);
extern void func_80173834(void *, void *, void *, void *);
extern u8 garuda_walk_direction_frames[];
extern u8 D_80174890[];
extern u8 garuda_frame_set;
extern u8 D_801748D8[];
extern u8 garuda_frame_set_2[];

void update_creature_animation_action(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite_arg, ActorRecord *creature);
/* Update creature animation and dispatch its dungeon action. */
void update_creature_animation_action(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite_arg, ActorRecord *creature) {
    u16 direction_aux;
    s8 room_id;
    u16 action;
    SpriteFrameState *sprite;
    u32 dungeon_flags = g_dungeon_status.flags;
    if (dungeon_flags & 0x1000) {
        actor->action_id.u = 0xE;
        func_801715F0(actor, context, sprite_arg, creature);
        return;
    }
    if (creature->mp_value.parts.whole == 0) {
        void *anim_table;
        advance_actor_pending_action(actor, context, sprite_arg, creature);
        if (sprite_arg->frameTable == garuda_frame_set_2) {
            return;
        }
        anim_table = D_801748D8;
        sprite_arg->frameTable = anim_table;
        select_sprite_entry(sprite_arg, ((u8 *) anim_table)[(((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing) + 0x100) >> 9) & 7], 0);
        return;
    }
    sprite = sprite_arg;
    if ((*((u32 *) (((u8 *) creature) + 0x1C))) & 0x200) {
        if ((sprite->frameTable) == garuda_frame_set_2) {
            actor->action_id.u = 0xD;
            actor->action_phase.u = 1;
            *((s32 *) (((u8 *) actor) + 0x8C)) = 0;
            *((u32 *) (((u8 *) creature) + 0x1C)) &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_801748D8) != 0) {
            return;
        }
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        if ((*((u32 *) (((u8 *) creature) + 0x1C))) & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, creature);
            return;
        }
        {
            register void *current_anim;
            void *anim_table;
            switch (actor->action_id.u) {
            case 0xE:
                break;

            default:
                actor->action_id.u = 0xE;
                break;

            }

            current_anim = sprite->frameTable;
            anim_table = garuda_walk_direction_frames;
            if (current_anim != anim_table) {
                sprite->frameTable = anim_table;
                select_sprite_entry(sprite, ((u8 *) anim_table)[(((g_game_work.view.camera_rotation.parts.viewAngle + creature->facing) + 0x100) >> 9) & 7], 0);
                sprite->frame_ticks = 1;
                *((s16 *) (((u8 *) actor) + 0xA6)) = 0;
                *((s16 *) (((u8 *) actor) + 0xB2)) = 0;
            }
        }
        *((u32 *) (((u8 *) creature) + 0x1C)) |= 0x40000;
        actor->action_state_flags &= 0xFFF7;
        if (creature->hp_delta != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_80174890) != 0) {
                return;
            }
        }
        if ((*((u32 *) (((u8 *) creature) + 0x1C))) & 0x80000) {
            s16 adjusted_offset;
            begin_actor_move_to_target_facing(actor, context, sprite, creature);
            adjusted_offset = actor->unk_90.parts.high.u - (*((u16 *) (((u8 *) actor) + 0xA6)));
            *((s16 *) (((u8 *) actor) + 0xA6)) = 0;
            *((s16 *) (((u8 *) actor) + 0xB2)) = 0;
            actor->unk_90.parts.high.s = adjusted_offset;
            func_80173834(actor, context, sprite, creature);
            return;
        }
        if ((can_entity_gain_level(creature) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, creature);
        }
    }
    room_id = find_active_rect_containing_point(sprite->tile_x, sprite->tile_y);
    sprite->room_index = room_id;
    if (creature->pending_turn_updates > 0) {
        if ((*((u32 *) (((u8 *) creature) + 0x1C))) & 0x20) {
            update_actor_status_and_mp(creature);
            return;
        }
        if ((*(u16 *)&sprite->tile_x) == (reference_tile_object.tile_position.word)) {
            func_80171848(actor, context, sprite, creature);
            return;
        }
        if (!(creature->action_flags & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                {
                    ObjectNodeHeader *previous_node;
                    void *previous_body;
                    ActorRecord *previous_actor;

                    previous_node = primary_actor_record->previous_actor_header;
                    previous_body = previous_node + 1;
                    previous_actor = previous_body;
                    if ((check_entity_relation(creature, previous_actor) << 16) != 0) {
                        return;
                    }
                }
            }
            if ((func_80172414(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action = creature->action_flags | 0x4000;
            creature->action_flags = action;
            if (!(action & 0x8000)) {
                func_80171848(actor, context, sprite, creature);
                return;
            }
        }
        action = creature->action_flags & 0x3FFF;
        if (((u32) (action - 1)) >= 12) {
            func_80171848(actor, context, sprite, creature);
            return;
        }
        switch (action - 1) {
        case 8:
        {
            void *target = probe_directional_neighbor(creature, sprite->tile_x, sprite->tile_y, creature->facing);
            *((void **) (((u8 *) actor) + 0xA8)) = target;
            if (target == 0) {
                func_80171848(actor, context, sprite, creature);
                return;
            }
            if (check_global_or_linked_flag_20000(target) != 0) {
                func_80171848(actor, context, sprite, creature);
                return;
            }
            if ((*((u8 *) (((u8 *) (*((void **) (((u8 *) actor) + 0xA8)))) + 0x13))) < 0x33) {
                advance_actor_walk_animation(actor, context, sprite, creature);
                return;
            }
            func_80171848(actor, context, sprite, creature);
            return;
        }
        case 7:
            if ((func_80171FF4(actor, context, sprite, creature) << 16) != 0) {
                return;
            }
            func_801721B8(actor, context, sprite, creature);
            return;
        case 4:
        case 5:
        case 6:
        {
            TileObject *player_pos = &reference_tile_object;
            void *player;
            s16 facing_angle;
            facing_angle = get_rounded_facing_and_rounding_flag(sprite->tile_x, sprite->tile_y,
                player_pos->tile_position.parts.tile_x, player_pos->tile_position.parts.tile_y, &direction_aux);
            player = primary_actor_record;
            creature->facing = facing_angle;
            if ((*((u8 *) (((u8 *) player) + 0x9A))) == 0x11) {
                begin_actor_spell_action(actor, context, sprite, &garuda_frame_set, update_creature_animation_action);
                return;
            }
        }
        case 11:
            update_actor_status_and_mp(creature);
            return;
        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(actor, context, sprite, &garuda_frame_set, update_creature_animation_action);
            return;
        case 3:
        case 9:
        case 10:
        default:
            func_80171848(actor, context, sprite, creature);
            return;
        }
    }
    if (!((*((u32 *) (((u8 *) creature) + 0x1C))) & 0x2000)) {
        s32 room_index = room_id;
        if ((room_index < 0) || (!(dungeon_rooms[room_index].flags & 2))) {
            if (!((*((u32 *) (((u8 *) creature) + 0x1C))) & 0x430)) {
                TileObject *player_pos = &reference_tile_object;
                if ((test_neighbor_position_relation(sprite->tile_x, sprite->tile_y,
                    player_pos->tile_position.parts.tile_x, player_pos->tile_position.parts.tile_y) << 16) != 0) {
                    creature->facing = get_rounded_facing_and_rounding_flag(sprite->tile_x,
                        sprite->tile_y, player_pos->tile_position.parts.tile_x,
                        player_pos->tile_position.parts.tile_y, &direction_aux);
                }
            }
        }
    }
    return;

}
