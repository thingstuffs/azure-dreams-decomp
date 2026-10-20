#include "common.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_floor.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct ActionState {
    u8 pad_00[0x8C];
    s32 handler;
    u8 pad_90[2];
    union { s16 signedValue; u16 unsignedValue; } heightOffset;
    u8 pad_94[4];
    u16 flags;
    u8 action;
    u8 phase;
    u8 pad_9C[0xA];
    union { s16 signedValue; u16 unsignedValue; } motionOffset;
    void *target;
    u8 pad_AC[6];
    s16 motionTicks;
} ActionState;

typedef struct ActorSprite {
    u8 pad_00[5];
    u8 frameTick;
    u8 pad_06[0xE];
    u16 flags;
    u8 pad_16[0xE];
    union {
        struct { u8 x, y; } tile;
        u16 packed;
    } position;
    u8 room;
    u8 pad_27[5];
    void *directionFrames;
} ActorSprite;

typedef struct CreatureState {
    u8 pad_00[0x1C];
    u32 flags;
    u8 pad_20[5];
    u8 tileY;
    u8 pad_26[4];
    s16 facing;
    u8 pad_2C[0x1A];
    u16 action;
    u8 pad_48[0x1C];
    s16 reaction;
    u8 pad_66[7];
    s8 actionsLeft;
} CreatureState;

typedef struct TargetKind {
    u8 pad_00[0x13];
    u8 kind;
} TargetKind;

extern void select_sprite_entry(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void *place_actor_at_directional_neighbor(void *, s32, s32, s32);
extern s32 check_global_or_linked_flag_20000(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_801595F0(void *, void *, void *, void *);
extern void func_80159848(void *, void *, void *, void *);
extern s32 func_80159FF4(void *, void *, void *, void *);
extern void func_8015A1B8(void *, void *, void *, void *);
extern void func_8015A2E0(void *, void *, void *, void *);
extern s32 func_8015A414(void *, void *, void *, s32);
extern void func_8015B834(void *, void *, void *, void *);
extern u8 D_8015C880[];
extern u8 D_8015C890[];
extern u8 D_8015C8C8;
extern u8 D_8015C8D8[];
extern u8 D_8015C8E0[];
void update_creature_action(ActionState *, void *, ActorSprite *, CreatureState *);
/* Update creature animation and dispatch its dungeon action. */
void update_creature_action(ActionState *actor, void *context, ActorSprite *sprite_arg, CreatureState *creature)
{
    s32 direction_aux;
    s8 room_id;
    u16 action;
    ActorSprite *sprite;
    u32 dungeon_flags = g_dungeon_status.flags;
    if (dungeon_flags & 0x1000) {
        actor->action = 0xE;
        func_801595F0(actor, context, sprite_arg, creature);
        return;
    }
    if ((creature->tileY) == 0) {
        void *anim_table;
        advance_actor_pending_action(actor, context, sprite_arg, creature);
        if ((sprite_arg->directionFrames) == D_8015C8E0) {
            return;
        }
        anim_table = D_8015C8D8;
        sprite_arg->directionFrames = anim_table;
        select_sprite_entry(sprite_arg, ((u8 *) anim_table)[(((g_game_work.view.camera_rotation.parts.viewAngle + (creature->facing)) + 0x100) >> 9) & 7], 0);
        return;
    }
    sprite = sprite_arg;
    if ((creature->flags) & 0x200) {
        if ((sprite->directionFrames) == D_8015C8E0) {
            actor->action = 0xD;
            actor->phase = 1;
            actor->handler = 0;
            creature->flags &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, context, sprite, D_8015C8D8) != 0) {
            return;
        }
    }
    if (!(g_dungeon_status.flags & 0x2000)) {
        if ((creature->flags) & 0x100) {
            begin_pushed_actor_move(actor, context, sprite, creature);
            return;
        }
        {
            void *current_anim;
            void *anim_table;
            if (actor->action != 0xE) {
                actor->action = 0xE;
            }

            current_anim = sprite->directionFrames;
            anim_table = D_8015C880;
            if (current_anim != anim_table) {
                sprite->directionFrames = anim_table;
                select_sprite_entry(sprite, ((u8 *) anim_table)[(((g_game_work.view.camera_rotation.parts.viewAngle + (creature->facing)) + 0x100) >> 9) & 7], 0);
                sprite->frameTick = 1;
                actor->motionOffset.signedValue = 0;
                actor->motionTicks = 0;
            }
        }
        creature->flags |= 0x40000;
        actor->flags &= 0xFFF7;
        if ((creature->reaction) != 0) {
            if (begin_ready_actor_directional_action(actor, context, sprite, D_8015C890) != 0) {
                return;
            }
        }
        if ((creature->flags) & 0x80000) {
            s16 adjusted_offset;
            begin_actor_move_to_target_facing(actor, context, sprite, creature);
            adjusted_offset = (actor->heightOffset.unsignedValue) - (actor->motionOffset.unsignedValue);
            actor->motionOffset.signedValue = 0;
            actor->motionTicks = 0;
            actor->heightOffset.signedValue = adjusted_offset;
            func_8015B834(actor, context, sprite, creature);
            return;
        }
        if ((can_entity_gain_level(creature) << 16) != 0) {
            process_selected_actor_record(actor, context, sprite, creature);
        }
    }
    room_id = find_active_rect_containing_point(sprite->position.tile.x, sprite->position.tile.y);
    sprite->room = room_id;
    if ((creature->actionsLeft) > 0) {
        if ((creature->flags) & 0x20) {
            update_actor_status_and_food(creature);
            return;
        }
        if ((sprite->position.packed) == *(u16 *)&D_80082E80.tile_position.parts.tile_x) {
            func_80159848(actor, context, sprite, creature);
            return;
        }
        if (!((creature->action) & 0x8000)) {
            if (g_dungeon_status.flags & 0x2000) {
                if ((check_entity_relation(creature, ((u8 *) D_800814A8->unk_58) + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8015A414(actor, context, sprite, 0) << 16) == 0) {
                return;
            }
            action = (creature->action) | 0x4000;
            creature->action = action;
            if (!(action & 0x8000)) {
                func_80159848(actor, context, sprite, creature);
                return;
            }
        }
        action = (creature->action) & 0x3FFF;
        if (((u32) (action - 1)) >= 12) {
            func_80159848(actor, context, sprite, creature);
            return;
        }
        switch (action - 1) {
        case 8:
        {
            void *target = place_actor_at_directional_neighbor(creature, sprite->position.tile.x, sprite->position.tile.y, creature->facing);
            actor->target = target;
            if (target == 0) {
                func_80159848(actor, context, sprite, creature);
                return;
            }
            if (check_global_or_linked_flag_20000(target) != 0) {
                func_80159848(actor, context, sprite, creature);
                return;
            }
            if (((TargetKind *)actor->target)->kind < 0x33) {
                func_8015A2E0(actor, context, sprite, creature);
                return;
            }
            func_80159848(actor, context, sprite, creature);
            return;
        }
        case 7:
            if ((func_80159FF4(actor, context, sprite, creature) << 16) != 0) {
                return;
            }
            func_8015A1B8(actor, context, sprite, creature);
            return;
        case 4:
        case 5:
        case 6:
        {
            TileObject *player_pos = &D_80082E80;
            void *player;
            s16 facing_angle;
            facing_angle = get_rounded_facing_and_rounding_flag(sprite->position.tile.x, sprite->position.tile.y,
                player_pos->tile_position.parts.tile_x, player_pos->tile_position.parts.tile_y, &direction_aux);
            player = D_800814A8;
            creature->facing = facing_angle;
            if ((((EntityRec *)player)->unk_9A) == 0x11) {
                begin_actor_spell_action(actor, context, sprite, &D_8015C8C8, update_creature_action);
                return;
            }
        }
        case 11:
            update_actor_status_and_food(creature);
            return;
        case 0:
        case 1:
        case 2:
            begin_actor_spell_action(actor, context, sprite, &D_8015C8C8, update_creature_action);
            return;
        case 3:
        case 9:
        case 10:
        default:
            func_80159848(actor, context, sprite, creature);
            return;
        }
    }
    if (!((creature->flags) & 0x2000)) {
        s32 room_index = room_id;
        if ((room_index < 0) || (!(D_800E2970[room_index].flags & 2))) {
            if (!((creature->flags) & 0x430)) {
                TileObject *player_pos = &D_80082E80;
                if ((compare_monster_neighbor_values(sprite->position.tile.x, sprite->position.tile.y,
                    player_pos->tile_position.parts.tile_x, player_pos->tile_position.parts.tile_y) << 16) != 0) {
                    creature->facing = get_rounded_facing_and_rounding_flag(sprite->position.tile.x,
                        sprite->position.tile.y, player_pos->tile_position.parts.tile_x,
                        player_pos->tile_position.parts.tile_y, &direction_aux);
                }
            }
        }
    }
    return;

}
