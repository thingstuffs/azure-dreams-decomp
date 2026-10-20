#include "shared/sprite_source.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"

typedef struct ActionState {
    u8 pad_00[0x8C];
    s32 handler;
    u8 pad_90[0x8];
    u16 flags;
    u8 action;
    u8 phase;
    u8 pad_9C[0xA];
    u16 ticks;
    union { s16 s; u16 u; } specialPhase;
    u16 savedFacing;
} ActionState;

typedef struct CreatureState {
    u8 pad_00[0x14];
    u32 motionFlags;
    u8 pad_18[0x4];
    u32 flags;
    u8 pad_20[0x5];
    u8 tileY;
    u8 pad_26[0x4];
    union { s16 s; u16 u; } facing;
    u8 pad_2C[0x1A];
    u16 action;
    u8 pad_48[0x1C];
    s16 reaction;
    u8 pad_66[0x4];
    u16 moveAngle;
    u8 pad_6C[0x1];
    s8 actionsLeft;
} CreatureState;

typedef struct ActorSprite {
    u8 pad_00[0x14];
    u16 flags;
    u8 pad_16[0xE];
    union {
        struct { u8 x, y; } tile;
        u16 packed;
    } position;
    s8 room;
    u8 pad_27[0x5];
    void * directionFrames;
} ActorSprite;

typedef struct ActorMotion {
    Fixed1616 x;
    Fixed1616 y;
    u32 z;
    s32 dx;
    s32 dy;
} ActorMotion;

typedef struct EffectObject {
    u8 pad_00[0x8];
    void * motion;
    void * sprite;
    void * updateData;
    u8 pad_14[0xA6];
    u8 phase;
} EffectObject;



typedef struct EffectSprite {
    void * source;
    u8 frame;
    u8 frameTick;
    u8 pad_06[0x2];
    u32 texture;
    u32 color;
    u16 angle;
    u8 pad_12[0x2];
    u16 flags;
    u8 pad_16[0x6];
    u16 scaleX;
    u16 scaleY;
} EffectSprite;

typedef struct PlayerContext {
    u8 pad_00[0x58];
    void * actionContext;
} PlayerContext;

typedef struct PlayerAction {
    u8 pad_00[0x9A];
    u8 action;
} PlayerAction;

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern s32 func_800644B8(s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s32, s32, s32, s32, void *);
extern s32 can_entity_gain_level(void *);
extern void set_record_integer_tile_center(void *, s32, s32);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *, void *, void *, void *);
extern s32 process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *, void *, void *, void *, void *);

extern void func_80159910(void);
extern void func_80159B68(void *, void *, void *, void *);
extern s32 func_8015A314(void *, void *, void *, void *);
extern void func_8015A514(void *, void *, void *, void *);
extern s32 func_8015A658(void *, void *, void *, s32);
extern void func_8015C250(void *, void *, void *, void *);

extern void *D_800814A8[3];
extern u8 D_800DEA68[];
extern u8 D_8015D174[];
extern u8 D_8015D258[];
extern u8 D_8015D260[];
extern u8 D_8015D290[];
extern u8 D_8015D298[];
extern u8 D_8015D2A0[];

void update_actor_special_action(ActionState *action_state, ActorMotion *motion, ActorSprite *sprite, CreatureState *entity)
{
    u16 initial_flags = g_dungeon_status.flags;
    void *current_frames;
    u8 *next_frames;
    s32 direction_aux;
    s8 room_id;

    if (initial_flags & 0x1000) {
        action_state->action = 0xE;
        func_80159910();
        return;
    }

    /* Inactive entities share the final animation update and return path. */
    if (entity->tileY == 0) {
        advance_actor_pending_action(action_state, motion, sprite, entity);
        {
            void *current =
                sprite->directionFrames;
            void *table;
            table = (u8 *)&D_8015D298;
            current_frames = current;
            next_frames = table;
            if (current_frames != next_frames) {
                u32 post_index;

                sprite->directionFrames = next_frames;
                post_index = ((g_game_work.view.viewAngle +
                    entity->facing.s + 0x100) >> 9) & 7;
                select_sprite_entry(sprite,
                    *(u8 *)((unsigned long)post_index +
                            (unsigned long)next_frames),
                    0);
            }
            return;
        }
    }

    if (entity->flags & 0x200) {
        if (sprite->directionFrames == D_8015D298) {
            action_state->action = 0xD;
            action_state->phase = 1;
            action_state->handler = 0;
            entity->flags &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(action_state, motion, sprite, D_8015D298) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (entity->flags & 0x100) {
            begin_pushed_actor_move(action_state, motion, sprite, entity);
            return;
        }

        {
            u32 state;
            u32 current_state = action_state->action;
            state = 0xE;
            if (current_state != state) {
                if (sprite->directionFrames != D_8015D258) {
                    sprite->directionFrames = D_8015D258;
                    select_sprite_entry(sprite,
                        D_8015D258[((g_game_work.view.viewAngle + entity->facing.s + 0x100) >> 9) & 7],
                        0);
                }
                action_state->action = state;
            }
        }

        if (entity->motionFlags & 0x20000) {
            switch (action_state->specialPhase.s) {
            case 0:
                if (sprite->directionFrames != D_8015D2A0) {
                    g_dungeon_status.unk_0A++;
                    action_state->savedFacing = entity->facing.u;
                    entity->facing.s =
                        (entity->moveAngle + 0x800) & 0xFFF;
                    sprite->flags &= 0x9FFF;
                    action_state->ticks = 300;
                }
                action_state->specialPhase.u++;
                return;

            case 1:
            {
                u16 timer = action_state->ticks - 1;

                action_state->ticks = timer;
                if (((s32)timer << 16) <= 0 ||
                    entity->reaction != 0) {
                    g_dungeon_status.unk_0A--;
                    motion->dy = 0;
                    motion->dx = 0;
                    set_record_integer_tile_center(motion,
                        sprite->position.tile.x, sprite->position.tile.y);
                    entity->motionFlags &= ~0x20000;
                    action_state->specialPhase.u = 0;
                    return;
                }
                if (entity->motionFlags & 0x1000000) {
                    action_state->specialPhase.u++;
                    sprite->directionFrames = D_8015D2A0;
                    select_sprite_entry(sprite,
                        D_8015D2A0[((g_game_work.view.viewAngle + entity->facing.s + 0x100) >> 9) & 7],
                        0);
                    action_state->ticks = 0;
                    return;
                }
                return;
            }

            case 2:
            {
                s32 scale;
                EffectObject *object;
                void *part;
                void *payload;
                u32 color;
                u32 payload_word;
                u32 texture_word;

                motion->dx =
                    dir_step_x[((s32)(entity->moveAngle << 16)) >> 25] << 16;
                motion->dy =
                    dir_step_y[((s32)(entity->moveAngle << 16)) >> 25] << 16;
                scale = func_800644B8((s16)action_state->ticks << 8);
                motion->dx = motion->dx +
                    (motion->dx * scale >> 9);
                scale = func_800644B8((s16)action_state->ticks << 8);
                motion->dy = motion->dy +
                    (motion->dy * scale >> 9);

                object = allocate_list_node(0x312, ((u8 *)(&D_80083498)));
                if (object != 0) {
                    register_node(object, project_sprite_chain);
                    payload = object->motion;
                    object->updateData = D_8015D174;
                    part = object->sprite;
                    ((EntityRec *)payload )->x.v = motion->x.v;
                    payload = object->motion;
                    ((EntityRec *)payload )->y.v = motion->y.v;
                    payload = object->motion;
                    payload_word = motion->z;
                    color = 0x00800000;
                    ((EntityRec *)payload)->z.v = payload_word;
                    ((EffectSprite *)part)->scaleY = 0x1000;
                    ((EffectSprite *)part)->scaleX = 0x1000;
                    ((EffectSprite *)part)->angle = 0;
                    ((EffectSprite *)part)->source = D_800DEA68;
                    ((EffectSprite *)part)->flags |= 0xC;
                    texture_word = ((u32)((SpriteSourceEntry *)D_800DEA68)->unk_04);
                    color |= 0x8080;
                    ((EffectSprite *)part)->frame = 0;
                    ((EffectSprite *)part)->frameTick = 0;
                    ((EffectSprite *)part)->color = color;
                    ((EffectSprite *)part)->texture = texture_word;
                    object->phase = 0;
                }

                {
                    u16 old_timer = action_state->ticks;
                    action_state->ticks = old_timer + 1;
                    if ((s16)old_timer >= 3) {
                        sprite->flags &= 0xF7FF;
                        motion->dy = 0;
                        motion->dx = 0;
                        action_state->ticks = 4;
                        action_state->specialPhase.u++;
                        return;
                    }
                }
                return;
            }

            case 3:
            {
                u16 timer = action_state->ticks - 1;

                action_state->ticks = timer;
                if (((s32)timer << 16) <= 0) {
                    sprite->flags &= 0xF7FF;
                    motion->dy = 0;
                    motion->dx = 0;
                    action_state->ticks = 3;
                    action_state->specialPhase.u++;
                    return;
                }
                return;
            }

            case 4:
            {
                s32 x;
                s32 y;
                s32 tile_center_y;
                s32 tile_center_x;
                s32 world_y_from_center;
                s32 world_x_from_center;
                u16 timer;

                tile_center_x = sprite->position.tile.x << 6;
                world_x_from_center = motion->x.w.i - 0x20;
                x = tile_center_x - world_x_from_center;
                motion->dx = (s32)((u32)x << 15) >> 1;
                tile_center_y = sprite->position.tile.y << 6;
                world_y_from_center = motion->y.w.i - 0x20;
                y = tile_center_y - world_y_from_center;
                motion->dy = (s32)((u32)y << 15) >> 1;
                timer = action_state->ticks - 1;
                action_state->ticks = timer;
                if (((s32)timer << 16) <= 0) {
                    g_dungeon_status.unk_0A--;
                    motion->dy = 0;
                    motion->dx = 0;
                    set_record_integer_tile_center(motion,
                        sprite->position.tile.x, sprite->position.tile.y);
                    entity->motionFlags &= ~0x20000;
                    entity->facing.s = action_state->savedFacing;
                    sprite->directionFrames = D_8015D258;
                    select_sprite_entry(sprite,
                        D_8015D258[((g_game_work.view.viewAngle + entity->facing.s + 0x100) >> 9) & 7],
                        0);
                    action_state->specialPhase.u = 0;
                    return;
                }
                return;
            }
            default:
                return;
            }
        } else {
            action_state->flags &= 0xFFF3;
            if (entity->reaction == 0 ||
                begin_ready_actor_directional_action(action_state, motion, sprite, D_8015D260) == 0) {
                if (entity->flags & 0x80000) {
                    begin_actor_move_to_target_facing(action_state, motion, sprite, entity);
                    func_8015C250(action_state, motion, sprite, entity);
                    return;
                }
                if ((can_entity_gain_level(entity) << 16) != 0) {
                    process_selected_actor_record(action_state, motion, sprite, entity);
                }
            } else {
                return;
            }
        }
    }

    room_id = find_active_rect_containing_point(sprite->position.tile.x, sprite->position.tile.y);
    sprite->room = room_id;

    if (entity->actionsLeft > 0) {
        if (entity->flags & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (sprite->position.packed == *(u16 *)(&D_80082E80.tileX)) {
            func_80159B68(action_state, motion, sprite, entity);
            return;
        }
        if (!(entity->action & 0x8000)) {
            if ((g_dungeon_status.flags & 0x2000) &&
                ((check_entity_relation(entity,
                    (u8 *)((PlayerContext *)(D_800814A8[0]))->actionContext + 0x20) << 16) != 0)) {
                return;
            }
            if ((func_8015A658(action_state, motion, sprite, 0) << 16) == 0) {
                return;
            }
            entity->action |= 0x4000;
            if (!(entity->action & 0x8000)) {
                func_80159B68(action_state, motion, sprite, entity);
                return;
            }
        }

        switch (entity->action & 0x3FFF) {
        case 8:
        case 9:
        {
            u32 case_flags;
            if ((entity->action & 0x3FFF) == 9) {
                case_flags = action_state->flags | 0x8000;
            } else {
                case_flags = action_state->flags & 0x7FFF;
            }
            action_state->flags = case_flags;
        }
            if ((func_8015A314(action_state, motion, sprite, entity) << 16) != 0) {
                return;
            }
            func_8015A514(action_state, motion, sprite, entity);
            return;

        case 5:
        case 6:
        case 7:
        {
            s16 next_facing;
            void *status_object;

            next_facing = get_rounded_facing_and_rounding_flag(
                sprite->position.tile.x, sprite->position.tile.y,
                D_80082E80.tileX, D_80082E80.tileY,
                &direction_aux);
            status_object = D_800814A8[0];
            entity->facing.s = next_facing;
            if (((PlayerAction *)status_object)->action == 0x11) {
                begin_actor_spell_action(action_state, motion, sprite, D_8015D290, update_actor_special_action);
                return;
            }
        }
        case 12:
            update_actor_status_and_food(entity);
            return;

        case 1:
        case 2:
        case 3:
            begin_actor_spell_action(action_state, motion, sprite, D_8015D290, update_actor_special_action);
            return;

        case 4:
        case 10:
        case 11:
        default:
            func_80159B68(action_state, motion, sprite, entity);
            return;
        }
    }

    {
        u32 final_flags =
            entity->flags;
        if (!(final_flags & 0x2000)) {
            if ((room_id < 0) || !(D_800E2970[room_id].flags & 2)) {
                u32 final_mask =
                    final_flags & 0x430;
                if (!final_mask) {

                    if ((compare_monster_neighbor_values(
                            sprite->position.tile.x, sprite->position.tile.y,
                            D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                        entity->facing.s = get_rounded_facing_and_rounding_flag(
                            sprite->position.tile.x, sprite->position.tile.y,
                            D_80082E80.tileX, D_80082E80.tileY,
                            &direction_aux);
                    }
                }
            }
        }
    }

    if (!(g_dungeon_status.flags & 0x2000) &&
        !(sprite->flags & 0x40)) {
        current_frames =
            sprite->directionFrames;
        next_frames = (u8 *)&D_8015D258;
        if (current_frames != next_frames) {
            u32 post_index;

            sprite->directionFrames = next_frames;
            post_index = ((g_game_work.view.viewAngle +
                entity->facing.s + 0x100) >> 9) & 7;
            select_sprite_entry(sprite,
                *(u8 *)((unsigned long)post_index +
                        (unsigned long)next_frames),
                0);
        }
    }

    return;
}
