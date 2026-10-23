#include "shared/dungeon_actor_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "dungeon/player/object.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[6];
    s16 fieldA;
} D_80083460_t;

extern void process_unflagged_linked_entries_alt(s32);
extern void process_unflagged_linked_entries(s32);
extern void set_sprite_animation_frame(void *, u8, s16, s32);
extern s16 measure_directional_stopping_distance(s16, void *, void *, s32);

extern s32 held_item_record[3];
extern u8 player_action_tag[];
extern u8 player_wait_frames[8];
extern u8 player_jump_frame_set[8];
extern u8 player_throw_followup_frames[8];
extern u8 player_carry_frames[8];
extern u8 player_throw_frame_set[8];
extern s32 saved_held_item_word[];

   /* state0_call_arg in update_throw_carried_object */

typedef struct S_8008FA7C_2 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
} S_8008FA7C_2;   /* arg3 in update_throw_carried_object */

typedef struct S_8008FA7C_3 {
    u8 pad_00[0x8C];
    union { u8 * p; s32 * p2; } unk_8C;   /* accessed as both */
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0xA];
    u16 unk_A2;
    u8 pad_A4[0x80];
    union { u8 * p; u32 i; } unk_124;   /* accessed as both */
} S_8008FA7C_3;   /* arg0 in update_throw_carried_object */

typedef struct S_8008FA7C_4 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_8008FA7C_4;   /* object in update_throw_carried_object */

   /* object2 in update_throw_carried_object */

typedef struct S_8008FA7C_6 {
    u8 pad_00[0xA];
    s16 unk_0A;
    u8 pad_0C[0x78];
    u8 unk_84;
    u8 unk_85;
    u8 pad_86[0x34BA];
    s32 unk_3540;
} S_8008FA7C_6;   /* (u8 *)state1_v1 in update_throw_carried_object */

typedef struct S_8008FA7C_7 {
    u8 pad_00[0x1484];
    s32 unk_1484;
} S_8008FA7C_7;   /* (u8 *)state1_a1 in update_throw_carried_object */

   /* call_arg in update_throw_carried_object */

   /* state2_call_arg in update_throw_carried_object */

/* Advances an actor's action state, updating linked-object flags and directional animation. */
void update_throw_carried_object(u8 *actor, ObjectPosition *motion, u8 *animation, u8 *entity) {
    s16 countdown;
    s32 direction;
    s16 state;
    s32 saved_value;
    s16 action_result;
    u32 mask_or_base;
    u32 object_or_base;
    u8 *init_anim;

    state = actor[0x9B];
    switch (state) {
    case 0:
        init_anim = animation;
        motion->velocity_z = 0xFFEA0000;
        ((SpriteAnimationTableView *)init_anim)->frame_table = player_throw_frame_set;
        {
            s32 init_entry;
            u8 init_frame;

            init_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8008FA7C_2 *)entity)->unk_2A + 0x100) >> 9) & 7;
            init_entry += (u32)player_throw_frame_set;
            {
                init_frame = *(u8 *)init_entry;
            }
            /* MATCH: Keep the zero argument in the shared-call jump delay slot. */
            set_sprite_animation_frame(init_anim, init_frame, 0, 1);
            actor[0x9B]++;
        }
        return;

    case 1:
        countdown = ((S_8008FA7C_3 *)actor)->unk_96 - 1;
        ((S_8008FA7C_3 *)actor)->unk_96 = countdown;
        if (countdown > 0) {
            return;
        }

        action_result = measure_directional_stopping_distance(((S_8008FA7C_2 *)entity)->unk_2A, motion, animation, 8);
        if (action_result == 0) {
            actor[0x9B]++;
            return;
        }
        {
            u32 set_mask;
            u32 linked_flags;
            u8 *linked_object;
            u8 *linked_result;
            u8 *active_anim;
            u8 *active_table;
            s32 entity_angle;
            s32 active_entry;
            s32 effect_duration;
            u32 entity_flags;

            mask_or_base = 0xFFEF0000;
            linked_object = ((S_8008FA7C_3 *)actor)->unk_124.p;
            set_mask = 0x200000;
            linked_flags = ((S_8008FA7C_4 *)linked_object)->unk_1C;
            mask_or_base |= 0xFFFF;
            linked_flags |= set_mask;
            ((S_8008FA7C_4 *)linked_object)->unk_1C = linked_flags;
            linked_result = ((S_8008FA7C_3 *)actor)->unk_124.p;
            active_anim = animation;
            ((ActorRecord *)linked_result)->unk_8A = action_result;
            effect_duration = 0x78;
            object_or_base = ((S_8008FA7C_3 *)actor)->unk_124.i;
            ((S_8008FA7C_6 *)((u8 *)object_or_base))->unk_84 = effect_duration;
            object_or_base = ((S_8008FA7C_3 *)actor)->unk_124.i;
            ((S_8008FA7C_6 *)((u8 *)object_or_base))->unk_85 = 2;
            entity_flags = ((S_8008FA7C_2 *)entity)->unk_1C;
            entity_flags &= mask_or_base;
            mask_or_base = 0x80080000;
            saved_value = ((S_8008FA7C_7 *)((u8 *)mask_or_base))->unk_1484;
            object_or_base = (u32)((D_80083460_t *)&g_dungeon_status);
            ((S_8008FA7C_7 *)((u8 *)mask_or_base))->unk_1484 = 0;
            active_table = player_jump_frame_set;
            ((S_8008FA7C_2 *)entity)->unk_1C = entity_flags;
            countdown = ((S_8008FA7C_6 *)((u8 *)object_or_base))->unk_0A;
            countdown++;
            ((S_8008FA7C_6 *)((u8 *)object_or_base))->unk_0A = countdown;
            ((SpriteAnimationTableView *)active_anim)->frame_table = active_table;
            active_entry = g_game_work.view.camera_rotation.parts.viewAngle;
            entity_angle = ((S_8008FA7C_2 *)entity)->unk_2A;
            saved_held_item_word[0] = saved_value;
            active_entry += entity_angle;
            active_entry += 0x100;
            active_entry >>= 9;
            active_entry &= 7;
            active_entry += (s32)active_table;
            set_sprite_animation_frame(active_anim, *(u8 *)active_entry, 5, 1);
            actor[0x9B]++;
        }
        return;

    case 2:
        {
            u8 *next_anim;

            if (!(((S_8008FA7C_3 *)actor)->unk_A2 & 0x10)) {
                return;
            }
            motion->velocity_z = 0;
            next_anim = animation;
            if (((S_8008FA7C_2 *)entity)->unk_1C & 0x100000) {
                actor[0x9B]++;
            return;
            }
            ((SpriteAnimationTableView *)next_anim)->frame_table = player_throw_followup_frames;
            {
                s32 next_entry;

                next_entry = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8008FA7C_2 *)entity)->unk_2A + 0x100) >> 9) & 7;
                next_entry += (u32)player_throw_followup_frames;
                set_sprite_animation_frame(next_anim, *(u8 *)next_entry, 0, 1);
                actor[0x9B]++;
            }
            return;
        }

    case 3:
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        g_dungeon_status.flags |= 0x412;
        process_unflagged_linked_entries_alt(((S_8008FA7C_2 *)entity)->unk_5C);
        process_unflagged_linked_entries(((S_8008FA7C_2 *)entity)->unk_5C);
        if (((S_8008FA7C_2 *)entity)->unk_1C & 0x100000) {
            ((S_8008FA7C_3 *)actor)->unk_8C.p = player_action_tag;
            (*(u8 * *)((u8 *)animation + (0x2C))) = player_carry_frames;
        } else {
            ((S_8008FA7C_3 *)actor)->unk_8C.p2 = handle_player_input;
            (*(u8 * *)((u8 *)animation + (0x2C))) = player_wait_frames;
        }
        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8008FA7C_2 *)entity)->unk_2A + 0x100) >> 9) & 7;
        set_sprite_animation_frame(animation, (*(u8 * *)((u8 *)animation + (0x2C)))[direction], 0, 1);
        actor[0x9B]++;
    }
}
