#include "common.h"
#include "shared/dungeon_status.h"

typedef struct S_800CA788_0 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800CA788_0;   /* global_base in select_target_tile_for_actor_action */

typedef struct S_800CA788_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_800CA788_1;   /* actor in select_target_tile_for_actor_action */

typedef struct S_800CA788_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800CA788_2;   /* held_arg2 in select_target_tile_for_actor_action */

typedef struct S_800CA788_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
} S_800CA788_3;   /* object in select_target_tile_for_actor_action */


extern s32 find_eligible_entry_at_coordinates(u8 *entry, s16 x, s16 y);
extern void prepare_directional_attack(void *, void *, s32, s32, s32);
extern s32 get_actor_height_difference(s32, void *);
extern s32 try_claim_dungeon_action_slot(void *);
extern void apply_camera_offset_and_select_target(void *, void *, s32, s32);

/* Attempt an action toward the target and decrement the actor counter on success. */
s32 select_target_tile_for_actor_action(void *object_ptr, void *action_context, void *target_ptr, void *actor_ptr)
{
    s32 target_direction;
    s32 clear_action_flag;
    u8 *object;
    u8 *actor;
    void *context;
    void *target;
    u16 global_flags;

    object = object_ptr;
    actor = actor_ptr;
    actor[0x71] &= 0x7F;
    context = action_context;
    if (!(g_dungeon_status.flags & 0x2000)) {
        target = target_ptr;

        ((S_800CA788_1 *)actor)->unk_14 |= 0x2000;
        ((S_800CA788_1 *)actor)->unk_1C |= 0x2000;
        target_direction = find_eligible_entry_at_coordinates(actor, ((S_800CA788_2 *)target)->unk_24, ((S_800CA788_2 *)target)->unk_25);
        clear_action_flag = ~0x2000;
        ((S_800CA788_1 *)actor)->unk_14 &= clear_action_flag;
        ((S_800CA788_1 *)actor)->unk_1C &= clear_action_flag;
        global_flags = g_dungeon_status.flags;
        if (!(global_flags & 0x2000)) {
            goto check_flag_8;
        }
    }
fail:
    return -1;
check_flag_8:
    if (global_flags & 8) {
        goto fail;
    }

    if ((u32)((-get_actor_height_difference(target_direction, actor) + 0x40) & 0xFFFF) >= 0x81U) {
        return 0;
    }
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        goto fail;
    }

    apply_camera_offset_and_select_target(actor - 0x20, context, 8, 0x300);
    if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
        goto fail;
    }

    {
        void *action_actor;
        void *action_target;
        s32 actor_param;
        s32 action_mode;

        action_actor = actor;
        action_target = target;
        object[0x9B] = 0;
        ((S_800CA788_3 *)object)->unk_8C = 0;
        object[0x9A] = 0x11;
        actor_param = ((S_800CA788_1 *)actor)->unk_2A;
        actor[0x84] = 0x80;
        action_mode = 0;
        actor[0x85] = 0;
        ((S_800CA788_1 *)actor)->unk_14 |= 0x2000;
        ((S_800CA788_1 *)actor)->unk_1C |= 0x2000;
        prepare_directional_attack(action_actor, action_target, actor_param, action_mode, 0);
    }
    ((S_800CA788_1 *)actor)->unk_14 &= clear_action_flag;
    ((S_800CA788_1 *)actor)->unk_1C &= clear_action_flag;
    actor[0x6D]--;
    return 1;
}
