#include "common.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

#ifndef DUNGEON_ACTOR_ITEM_SLOTS_VIEW
#define DUNGEON_ACTOR_ITEM_SLOTS_VIEW
/* Three adjacent 3-byte action records begin at +0x08. */
typedef struct ActorItemSlotsView {
    u8 pad_00[8];
    u8 slots[3][3];
} ActorItemSlotsView;
#endif

#ifndef DUNGEON_PLAYER_ACTION_COUNT_VIEW
#define DUNGEON_PLAYER_ACTION_COUNT_VIEW
typedef struct PlayerActionCountView {
    u8 pad_00[0xA6];
    u16 remainingActions;
} PlayerActionCountView;
#endif

typedef struct ObjectActionState {
    u8 pad_00[0x8C];
    void * nextBehavior;
    u8 pad_90[0x8];
    u16 flags;
    u8 pad_9A[0x1];
    u8 phase;
} ObjectActionState;

typedef struct ActionActorView {
    u8 pad_00[0x1C];
    s32 flags;
    u8 pad_20[0xA];
    s16 facing;
    u8 pad_2C[0x1A];
    u16 actionFlags;
    u8 pad_48[0x18];
    void * target;
    u8 pad_64[0x9];
    u8 remainingActions;
    u8 pad_6E[0x4];
    union { u8 unsignedByte; s8 signedByte; } targetX;
    union { u8 unsignedByte; s8 signedByte; } targetY;
} ActionActorView;

typedef struct ActionSpriteView {
    u8 pad_00[0x4];
    s8 animationState;
    u8 pad_05[0xF];
    u16 flags;
    u8 pad_16[0xE];
    u8 tileX;
    u8 tileY;
    u8 pad_26[0x6];
    u8 * animationTable;
} ActionSpriteView;

typedef struct MotionResetView {
    u8 pad_00[0xC];
    s32 velocityX;
    s32 velocityY;
    s32 motionFlags;
} MotionResetView;

extern s32 abs(s32);
extern s32 get_cd_command_queue_depth(void);
extern void func_80047784(void *, u8, s32);
extern void *scan_monster_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *, u8 *, s32, u16 *);
extern void create_actor_linked_effect(void *);

extern u8 D_8015F014[];
extern u8 D_8016220C[];

void update_actor_motion_variant(void *owner, void *motion, void *actor, void *object_in)
{
    void *object = object_in;
    register s32 is_special;
    u8 *item_slot;
    s16 action_value;
    s32 absolute_x;
    s32 absolute_y;
    s32 action_id;
    u32 action_index;
    void *target;
    DefEntry *definition;
    u8 *target_sprite;
    DefEntry *definitions;
    u32 item_id;
    s32 state;
    state = ((ObjectActionState *)owner)->phase;
    is_special = 0;
    switch (state) {
    case 0:
        if (((ActionActorView *)object)->flags & 0x2000) {
            action_index = (((ActionActorView *)object)->actionFlags & 0x3FFF) - 1;
            switch (action_index) {
            case 6:
                is_special = 1;
            case 2:
                item_slot = ((ActorItemSlotsView *)object)->slots[2];
                break;
            case 5:
                is_special = 1;
            case 1:
                item_slot = ((ActorItemSlotsView *)object)->slots[1];
                break;
            case 4:
                is_special = 1;
            case 0:
                item_slot = ((ActorItemSlotsView *)object)->slots[0];
                break;
            default:
                item_slot = 0;
                break;
            }
        } else {
            action_id = ((ActionActorView *)object)->actionFlags & 0x3FFF;
            switch (action_id) {
            case 3:
                item_slot = ((ActorItemSlotsView *)object)->slots[2];
                break;
            case 2:
                item_slot = ((ActorItemSlotsView *)object)->slots[1];
                break;
            case 1:
                item_slot = ((ActorItemSlotsView *)object)->slots[0];
                break;
            default:
                item_slot = 0;
                break;
            }
        }
        if (*item_slot != 0) {
            action_value = ((ObjectActionState *)owner)->flags & 0xFF7F;
            ((ObjectActionState *)owner)->flags = action_value;
            action_value = is_special;
            if (action_value) {
                target = D_800814A8;
                ((ActionActorView *)object)->target = target;
                target_sprite = ((ObjectNodeHeader *)((u8 *)target - 0x20))->unk_0C;
                action_value = ((ActionSpriteView *)target_sprite)->tileX;
                ((ActionActorView *)object)->targetX.unsignedByte = action_value;
                action_value = ((ActionSpriteView *)target_sprite)->tileY;
                ((ActionActorView *)object)->targetY.unsignedByte = action_value;
            } else {
                definitions = D_8006DE24;
                item_id = *item_slot;
                definition = &definitions[item_id];
                if (definition->kind == 2) {
                    target = ((ActionActorView *)object)->target;
                    if (target != 0) {
                        target_sprite = ((ObjectNodeHeader *)((u8 *)target - 0x20))->unk_0C;
                        action_value = ((ActionSpriteView *)target_sprite)->tileX;
                        ((ActionActorView *)object)->targetX.unsignedByte = action_value;
                        action_value = ((ActionSpriteView *)target_sprite)->tileY;
                        ((ActionActorView *)object)->targetY.unsignedByte = action_value;
                    }
                } else {
                    target = scan_monster_along_heading(
                        object,
                        ((ActionSpriteView *)actor)->tileX,
                        ((ActionSpriteView *)actor)->tileY,
                        ((ActionActorView *)object)->facing,
                        0x10);
                    ((ActionActorView *)object)->target = target;

                    absolute_x = abs(((ActionActorView *)object)->targetX.signedByte);
                    absolute_y = abs(((ActionActorView *)object)->targetY.signedByte);

                    ((ActionActorView *)object)->targetX.unsignedByte = absolute_x;
                    ((ActionActorView *)object)->targetY.unsignedByte = absolute_y;

                }
            }

            if (create_actor_spell_effect(object, item_slot, is_special,
                              &((ObjectActionState *)owner)->flags) == 0) {
                return;
            }
            create_actor_linked_effect(object);
            ((ObjectActionState *)owner)->phase++;
            return;
        }

        ((MotionResetView *)motion)->motionFlags = 0;
        ((MotionResetView *)motion)->velocityY = 0;
        ((MotionResetView *)motion)->velocityX = 0;
        set_record_integer_tile_center(motion, ((ActionSpriteView *)actor)->tileX, ((ActionSpriteView *)actor)->tileY);
        g_dungeon_status.unk_0C = 0;
        ((PlayerActionCountView *)D_800814A8)->remainingActions--;
        advance_status_timers(object);
        ((ActionActorView *)object)->remainingActions--;
        ((ObjectActionState *)owner)->nextBehavior = D_8015F014;
        ((ActionActorView *)object)->targetY.unsignedByte = 0;
        ((ActionActorView *)object)->targetX.unsignedByte = 0;
        ((ActionActorView *)object)->actionFlags &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            ((ActionSpriteView *)actor)->flags |= 0x0800;
            return;
        }
        ((ActionSpriteView *)actor)->flags &= 0xF7FF;
        ((ObjectActionState *)owner)->phase++;

    case 2:
        if (((ActionSpriteView *)actor)->animationState != 4 || !(((ActionSpriteView *)actor)->flags & 0x1000)) {
            if ((((ActionSpriteView *)actor)->flags & 0xE000) == 0) {
                return;
            }
        }
        ((ObjectActionState *)owner)->flags |= 0x80;
        if ((((ActionSpriteView *)actor)->flags & 0xE000) == 0) {
            return;
        }

        ((MotionResetView *)motion)->motionFlags = 0;
        ((MotionResetView *)motion)->velocityY = 0;
        ((MotionResetView *)motion)->velocityX = 0;
        set_record_integer_tile_center(motion, ((ActionSpriteView *)actor)->tileX, ((ActionSpriteView *)actor)->tileY);

        {
            u8 *direction_table = D_8016220C;
            if (((ActionSpriteView *)actor)->animationTable != direction_table) {
                ((ActionSpriteView *)actor)->animationTable = direction_table;
                func_80047784(
                    actor,
                    direction_table[((g_game_work.view.viewAngle + ((ActionActorView *)object)->facing + 0x100) >> 9) & 7],
                    0);
            }
        }

        {
            if (((s32)g_dungeon_status.unk_0C) != 0) {
                return;
            }
            g_dungeon_status.unk_0A--;
        }
        ((ObjectActionState *)owner)->nextBehavior = D_8015F014;
        advance_status_timers(object);
        ((ActionActorView *)object)->targetY.unsignedByte = 0;
        ((ActionActorView *)object)->targetX.unsignedByte = 0;
        ((ActionActorView *)object)->remainingActions--;
        ((ActionActorView *)object)->actionFlags &= 0x7FFF;
        play_sound_if_enabled(0xB4);
        return;
    default:
        return;
    }
}
