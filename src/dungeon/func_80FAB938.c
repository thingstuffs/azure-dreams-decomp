#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

/* Partial action view: timer loads keep their observed signedness. */
typedef struct ActorActionView {
    u8 pad_00[0x8C];
    union { s32 code; void *record; u8 *frames; s32 *word; } nextAction;
    Fixed1616 motionOffset;
    u8 pad_94[2];
    union { u16 unsignedTicks; s16 signedTicks; } timer;
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[4];
    s16 frameParameter;
    u8 pad_A2[4];
    u16 effectTicks;
    union { s16 signedPhase; u16 phase; u16 startX; } effectState;
    union { u16 facing; u16 startY; } saved;
    u16 effectX;
    u16 effectY;
    u16 effectZ;
} ActorActionView;

typedef union TilePairView {
    struct { u8 x; u8 y; } tile;
    u16 packed;
} TilePairView;

typedef struct ActorSpriteView {
    u8 pad_00[4];
    s8 frame;
    u8 pad_05[3];
    s32 animationKey;
    u8 pad_0C[8];
    u16 flags;
    u8 pad_16[0xE];
    TilePairView position;
    union { s8 signedIndex; u8 unsignedIndex; } tileIndex;
    u8 pad_27[5];
    u8 *directionFrames;
} ActorSpriteView;

extern void select_sprite_entry(void *, u8, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(u8, u8);
extern s32 compare_monster_neighbor_values(u8, u8, u8, u8);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *action, s32 unused, void *sprite, u8 *direction_frames);
extern void process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *action, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8014D670(void *, void *);
extern void func_8014D82C(void *, void *, void *, void *);
extern s32 func_8014DF74(void *, void *, void *, void *);
extern void func_8014E138(void *, void *, void *, void *);
extern s32 func_8014E258(void *, void *, void *, s32);
extern void func_8014FD38(void *, void *, void *, void *);
extern void func_801500F4(void *, void *, void *, void *);

extern u8 D_8014D138[];
extern u8 D_80150AD4[];
extern u8 D_80150ADC[];
extern u8 D_80150AEC[];
extern u8 D_80150AF4[];
extern u8 D_80150AFC[];

void update_actor_action_and_facing(ActorActionView *action_input, EntityRec *motion_input, ActorSpriteView *sprite_in, EntityRec *entity_input)
{
    ActorActionView *action;
    EntityRec *motion;
    ActorSpriteView *sprite;
    EntityRec *entity;
    s32 facing_aux;
    s32 status_flags;
    s8 tile_index;
    u16 action_state;
    u32 dungeon_flags = g_dungeon_status.flags;

    action = action_input;
    motion = motion_input;
    sprite = sprite_in;
    entity = entity_input;

    if (dungeon_flags & 0x1000) {
        action->behavior = 0xE;
        func_8014D670(action_input, motion_input);
        return;
    }

    if (entity->tileY == 0) {
        advance_actor_pending_action(action, motion, sprite, entity);
        if (sprite->directionFrames == D_80150AFC) {
            return;
        }
        sprite->directionFrames = D_80150AF4;
        select_sprite_entry(sprite,
            D_80150AF4[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (entity->flags1C & 0x200) {
        if (sprite->directionFrames == D_80150AFC) {
            action->behavior = 0xD;
            action->phase = 1;
            action->nextAction.code = 0;
            entity->flags1C &= ~0x40000;
            return;
        }
        if (reset_actor_action_state(action, motion, sprite, D_80150AF4) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (entity->flags1C & 0x100) {
            begin_pushed_actor_move(action, motion, sprite, entity);
            return;
        }

        if (action->behavior != 0xE) {
            action->behavior = 0xE;
        }

        if (sprite->directionFrames != D_80150AD4) {
            action->frameParameter = 0;
            sprite->directionFrames = D_80150AD4;
            select_sprite_entry(sprite,
                D_80150AD4[((g_game_work.view.camera_rotation.parts.viewAngle + entity->facing + 0x100) >> 9) & 7],
                action->frameParameter);
        }

        entity->flags1C |= 0x40000;
        action->flags &= 0xFFF7;

        if (entity->unk_64 != 0) {
            if (begin_ready_actor_directional_action(action, motion, sprite, D_80150ADC) != 0) {
                return;
            }
        }

        if (entity->flags1C & 0x80000) {
            begin_actor_move_to_target_facing(action, motion, sprite, entity);
            action->frameParameter = 0;
            func_8014FD38(action, motion, sprite, entity);
            return;
        }

        if ((s16)can_entity_gain_level(entity) != 0) {
            process_selected_actor_record(action, motion, sprite, entity);
        }
    }

    tile_index = find_active_rect_containing_point(sprite->position.tile.x, sprite->position.tile.y);
    sprite->tileIndex.unsignedIndex = tile_index;

    if (entity->unk_6D > 0) {
        if (entity->flags1C & 0x20) {
            update_actor_status_and_food(entity);
            return;
        }
        if (!(sprite->position.packed == ((TilePairView *)&D_80082E80.tile_position.parts.tile_x)->packed)) {
            action_state = entity->unk_46;
            if (!(action_state & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((s16)check_entity_relation(entity,
                            (u8 *)D_800814A8->unk_58 + 0x20) != 0) {
                        return;
                    }
                }
                if ((s16)func_8014E258(action, motion, sprite, 0) == 0) {
                    return;
                }
                action_state = entity->unk_46 | 0x4000;
                entity->unk_46 = action_state;
            }

            if (action_state & 0x8000) {
                switch (entity->unk_46 & 0x3FFF) {
                case 9:
                    func_801500F4(action, motion, sprite, entity);
                    return;

                case 8:
                    if ((s16)func_8014DF74(action, motion, sprite, entity) != 0) {
                        return;
                    }
                    func_8014E138(action, motion, sprite, entity);
                    return;

                case 12:
                    update_actor_status_and_food(entity);
                    return;

                case 5:
                case 6:
                case 7:
                {
                    EntityRec *player;
                    s16 facing_angle;

                    facing_angle = get_rounded_facing_and_rounding_flag(
                        sprite->position.tile.x, sprite->position.tile.y,
                        D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y,
                        &facing_aux);
                    player = D_800814A8;
                    entity->facing = facing_angle;
                    if (player->unk_9A != 0x11) {
                        update_actor_status_and_food(entity);
                        return;
                    }
                }

                case 1:
                case 2:
                case 3:
                    begin_actor_spell_action(action, motion, sprite, D_80150AEC, D_8014D138);
                    return;

                case 4:
                case 10:
                case 11:
                default:
                    break;
                }
            }
        }
        func_8014D82C(action, motion, sprite, entity);
        return;
    }

    status_flags = entity->flags1C;
    if (status_flags & 0x2000) {
        return;
    }
    if (tile_index >= 0) {
        if (D_800E2970[tile_index].flags & 2) {
            return;
        }
    }
    if (status_flags & 0x430) {
        return;
    }

    {

        if ((s16)compare_monster_neighbor_values(
                sprite->position.tile.x, sprite->position.tile.y,
                D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y) != 0) {
            entity->facing = get_rounded_facing_and_rounding_flag(
                sprite->position.tile.x, sprite->position.tile.y,
                D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y, &facing_aux);
        }
    }
    return;
}
