#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

extern void func_80047784(void *, s32, s32);
extern s32 check_entity_relation(void *, void *);
extern s8 find_active_rect_containing_point(s32, s32);
extern s32 compare_monster_neighbor_values(s32, s32, s32, s32);
extern s16 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);
extern s32 can_entity_gain_level(void *);
extern void update_actor_status_and_food(void *);
extern void begin_pushed_actor_move(void *, void *, void *, void *);
extern s32 begin_ready_actor_directional_action(void *, void *, void *, void *);
extern void advance_actor_pending_action(void *, void *, void *, void *);
extern void begin_actor_move_to_target_facing(void *, void *, void *, void *);
extern s32 reset_actor_action_state(void *actor, s32 unused, void *sprite, u8 *direction_frames);
extern s32 process_selected_actor_record(void *, void *, void *, void *);
extern void begin_actor_spell_action(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state);
extern void func_8015F574(void *, void *);
extern void func_8015F784(void *, void *, void *, void *);
extern s32 func_8015FECC(void *, void *, void *, void *);
extern void func_80160090(void *, void *, void *, void *);
extern s32 func_801601B4(void *, void *, void *, void *);
extern void func_80161468(void *, void *, void *, void *);
extern void func_80161AE8(void *, void *, void *, void *);

extern u8 D_8015F014[];
extern u8 D_8016220C[];
extern u8 D_8016221C[];
extern u8 D_8016224C[];
extern u8 D_80162254[];
extern u8 D_8016225C[];

typedef struct BehaviorControllerView {
    u8 pad_00[0x8C];
    s32 nextBehavior;
    u8 pad_90[0x2];
    union { u16 unsignedValue; s16 signedValue; } baseOffset;
    u8 pad_94[0x4];
    u16 flags;
    u8 behavior;
    u8 phase;
    u8 pad_9C[0x2];
    s16 idleTicks;
    u8 pad_A0[0x2];
    union { s16 signedValue; u16 unsignedValue; } animationOffset;
} BehaviorControllerView;

typedef struct BehaviorSpriteView {
    u8 pad_00[0x5];
    u8 animationStep;
    u8 pad_06[0x1E];
    union {
        struct { u8 x; u8 y; } bytes;
        u16 packed;
    } tile;
    u8 room;
    u8 pad_27[0x5];
    void * animationTable;
} BehaviorSpriteView;

void update_actor_action_variant(void *actor, void *actor_context, void *map_object, EntityRec *creature)
{
    s32 direction_flags;
    s8 room_id;
    u16 action_state;

    if (g_dungeon_status.flags & 0x1000) {
        ((BehaviorControllerView *)actor)->behavior = 0xE;
        func_8015F574(actor, actor_context);
        return;
    }
    if (creature->tileY == 0) {
        void *animation_table;

        advance_actor_pending_action(actor, actor_context, map_object, creature);
        if (((BehaviorSpriteView *)map_object)->animationTable == D_8016225C) {
            return;
        }
        animation_table = D_80162254;
        ((BehaviorSpriteView *)map_object)->animationTable = animation_table;
        func_80047784(map_object,
            ((u8 *)animation_table)[((g_game_work.view.viewAngle + creature->facing + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((u32)creature->flags1C) & 0x200) {
        if (((BehaviorSpriteView *)map_object)->animationTable == D_8016225C) {
            ((BehaviorControllerView *)actor)->behavior = 0xD;
            ((BehaviorControllerView *)actor)->phase = 1;
            ((BehaviorControllerView *)actor)->nextBehavior = 0;
            creature->flags1C &= 0xFFFBFFFF;
            return;
        }
        if (reset_actor_action_state(actor, actor_context, map_object, D_80162254) != 0) {
            return;
        }
    }

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (((u32)creature->flags1C) & 0x100) {
            begin_pushed_actor_move(actor, actor_context, map_object, creature);
            return;
        }

        {
            u8 current_state = ((BehaviorControllerView *)actor)->behavior;
            u32 next_state = 0xE;
            void *current_animation;
            void *animation_table;

            if (current_state != next_state) {
                ((BehaviorControllerView *)actor)->behavior = next_state;
            }
            current_animation = ((BehaviorSpriteView *)map_object)->animationTable;
            animation_table = D_8016220C;
            if (current_animation != animation_table) {
                ((BehaviorSpriteView *)map_object)->animationTable = animation_table;
                func_80047784(map_object,
                    ((u8 *)animation_table)[((g_game_work.view.viewAngle + creature->facing + 0x100) >> 9) & 7],
                    0);
                ((BehaviorSpriteView *)map_object)->animationStep = 1;
                ((BehaviorControllerView *)actor)->animationOffset.signedValue = 0;
                ((BehaviorControllerView *)actor)->idleTicks = 0;
            }
        }

        creature->flags1C |= 0x40000;
        ((BehaviorControllerView *)actor)->flags &= 0xFFF7;

        if (creature->unk_64 != 0) {
            if (begin_ready_actor_directional_action(actor, actor_context, map_object, D_8016221C) != 0) {
                return;
            }
        }

        if (((u32)creature->flags1C) & 0x80000) {
            s16 offset_delta;

            begin_actor_move_to_target_facing(actor, actor_context, map_object, creature);
            offset_delta = ((BehaviorControllerView *)actor)->baseOffset.unsignedValue - ((BehaviorControllerView *)actor)->animationOffset.unsignedValue;
            ((BehaviorControllerView *)actor)->animationOffset.signedValue = 0;
            ((BehaviorControllerView *)actor)->idleTicks = 0;
            ((BehaviorControllerView *)actor)->baseOffset.signedValue = offset_delta;
            func_80161468(actor, actor_context, map_object, creature);
            return;
        }

        if ((can_entity_gain_level(creature) << 16) != 0) {
            if ((process_selected_actor_record(actor, actor_context, map_object, creature) << 16) != 0) {
                func_80161AE8(actor, actor_context, map_object, creature);
                return;
            }
        }
    }

    room_id = find_active_rect_containing_point(((BehaviorSpriteView *)map_object)->tile.bytes.x, ((BehaviorSpriteView *)map_object)->tile.bytes.y);
    ((BehaviorSpriteView *)map_object)->room = room_id;

    if (creature->unk_6D > 0) {
        if (((u32)creature->flags1C) & 0x20) {
            update_actor_status_and_food(creature);
            return;
        }
        if (((BehaviorSpriteView *)map_object)->tile.packed != *(u16 *)(&D_80082E80.tileX)) {
            if (!(creature->unk_46 & 0x8000)) {
                if (g_dungeon_status.flags & 0x2000) {
                    if ((check_entity_relation(creature,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                        return;
                    }
                }
                if ((func_801601B4(actor, actor_context, map_object, 0) << 16) == 0) {
                    return;
                }
                action_state = creature->unk_46 | 0x4000;
                creature->unk_46 = action_state;
            }

            if (creature->unk_46 & 0x8000) {
                action_state = creature->unk_46 & 0x3FFF;
                switch (action_state - 1) {

                case 7:
                case 8:
                    if ((func_8015FECC(actor, actor_context, map_object, creature) << 16) != 0) {
                        return;
                    }
                    func_80160090(actor, actor_context, map_object, creature);
                    return;

                case 4:
                case 5:
                case 6:
                    {
                        EntityRec *player;
                        s16 facing_angle;

                        facing_angle = get_rounded_facing_and_rounding_flag(
                            ((BehaviorSpriteView *)map_object)->tile.bytes.x, ((BehaviorSpriteView *)map_object)->tile.bytes.y,
                            D_80082E80.tileX, D_80082E80.tileY,
                            &direction_flags);
                        player = D_800814A8;
                        creature->facing = facing_angle;
                        if (player->unk_9A == 0x11) {
                            begin_actor_spell_action(actor, actor_context, map_object, D_8016224C, D_8015F014);
                            return;
                        }
                    }

                case 11:
                    update_actor_status_and_food(creature);
                    return;

                case 0:
                case 1:
                case 2:
                    begin_actor_spell_action(actor, actor_context, map_object, D_8016224C, D_8015F014);
                    return;

                case 3:
                case 9:
                case 10:
                default:
                    break;
                }
            }
        }
        func_8015F784(actor, actor_context, map_object, creature);
        return;
    }

    if (!(((u32)creature->flags1C) & 0x2000)) {
        s32 room_index = room_id;

        if ((room_index < 0) ||
            !(D_800E2970[room_index].flags & 2)) {
            if (!(((u32)creature->flags1C) & 0x430)) {

                if ((compare_monster_neighbor_values(
                    ((BehaviorSpriteView *)map_object)->tile.bytes.x, ((BehaviorSpriteView *)map_object)->tile.bytes.y,
                    D_80082E80.tileX, D_80082E80.tileY) << 16) != 0) {
                    creature->facing = get_rounded_facing_and_rounding_flag(
                        ((BehaviorSpriteView *)map_object)->tile.bytes.x, ((BehaviorSpriteView *)map_object)->tile.bytes.y,
                        D_80082E80.tileX, D_80082E80.tileY,
                        &direction_flags);
                }
            }
        }
    }
}
