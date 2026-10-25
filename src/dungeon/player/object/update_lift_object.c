#include "shared/dungeon_actor_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/graphics.h"

extern s32 rand();
extern s32 get_unused_text_buffer(); /* Unprototyped: zero, one or three arguments; retail replaces all incoming arguments. */
extern s32 expand_text_control_codes();
extern void *clear_byte_and_advance();
extern s32 append_entity_display_text();
extern void adjust_source_value_and_finalize(void *context, const void *source);
extern void process_unflagged_linked_entries();
extern void process_unflagged_linked_entries_alt();
extern s32 play_sound_if_enabled(s32 query_value);
extern s32 display_text_with_fullwidth_adjustment(s8 *text);
extern s32 random_dungeon_range_16(u32 bound_a, u32 bound_b);

extern u8 player_action_tag[];
extern u8 player_wait_frames[8];
extern u8 player_carry_frames[8];
extern u8 D_800E0523[];
extern u8 D_800E0683[];
extern s32 saved_held_item_word;
extern s16 lift_jitter_offsets[2];

#line 1 "a"

typedef struct S_8008F428_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x80];
    void * unk_11C;
    u8 pad_120[0x4];
    void * unk_124;
} S_8008F428_0;   /* arg0 in update_lift_object */

typedef struct S_8008F428_2 {
    u8 pad_00[0x1484];
    s32 unk_1484;
} S_8008F428_2;   /* old_value_page in update_lift_object */

   /* entity in update_lift_object */

typedef struct S_8008F428_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x30];
    void * unk_5C;
} S_8008F428_4;   /* arg3 in update_lift_object */

   /* flags_base in update_lift_object */

   /* ((S_8008F428_0 *)arg0)->unk_124 in update_lift_object */

/* Updates the timed effect state, entity flags, and directional animation. */
void update_lift_object(void *effect_state, void *saved_effect_id, void *animation, void *owner) {
    s32 effect_result;
    u16 ticks_left;
    u8 state;
    void *target;

    if (((S_8008F428_0 *)effect_state)->unk_124 != 0) {
        if (!(((SpriteFrameState *)animation)->flags & 0x6000)) {
            return;
        }

        state = ((S_8008F428_0 *)effect_state)->unk_9B;
        if (state == 0) {
            void *effect_target;
            s32 entity_flags;
            s32 wait_roll;

            lift_jitter_offsets[0] = 0;
            lift_jitter_offsets[1] = 0;
            entity_flags = ((ActorRecord *)(((S_8008F428_0 *)effect_state)->unk_124))->flags1C;
            effect_target = animation;
            if (!(entity_flags & 0x2000)) {
                if (!(entity_flags & 0x228)) {
                    wait_roll = random_dungeon_range_16(0, 0x10);
                    effect_target = animation;
                    if ((s16)wait_roll < 6) {
                        ((S_8008F428_0 *)effect_state)->unk_96 = 0x10;
                        ((S_8008F428_0 *)effect_state)->unk_9B = ((S_8008F428_0 *)effect_state)->unk_9B + 1;
                        return;
                    }
                }
            }
            ((S_8008F428_0 *)effect_state)->unk_8C = player_action_tag;
            (*(u8 * *)((u8 *)effect_target + (0x2C))) = player_carry_frames;
            set_sprite_animation_frame(effect_target,
                player_carry_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8008F428_4 *)owner)->unk_2A + 0x100) >> 9) & 7],
                0, 1);
            return;
        }

        if (state == 1) {
            lift_jitter_offsets[0] = (rand() & 0xF) - 8;
            lift_jitter_offsets[1] = (rand() & 0xF) - 8;
            ticks_left = ((S_8008F428_0 *)effect_state)->unk_96 - 1;
            ((S_8008F428_0 *)effect_state)->unk_96 = ticks_left;
            if ((s16)ticks_left > 0) {
                return;
            }
            play_sound_if_enabled(0x510);
            adjust_source_value_and_finalize(((S_8008F428_0 *)effect_state)->unk_124, D_800E0523);
            {
                void *entity;
                s32 saved_global;
                u32 entity_mask;
                u32 owner_mask;
                u8 *global_page;
                s32 flags;

                entity_mask = 0xFFF7FFFF;
                owner_mask = 0xFFEF0000;
                global_page = (u8 *)0x80080000;
                entity = ((S_8008F428_0 *)effect_state)->unk_124;
                saved_global = ((S_8008F428_2 *)global_page)->unk_1484;
                flags = ((ActorRecord *)entity)->flags1C;
                owner_mask |= 0xFFFF;
                ((S_8008F428_2 *)global_page)->unk_1484 = 0;
                ((ActorRecord *)entity)->flags1C = flags & entity_mask;
                saved_held_item_word = saved_global;
                ((S_8008F428_4 *)owner)->unk_1C = ((S_8008F428_4 *)owner)->unk_1C & owner_mask;
            }
            ((S_8008F428_0 *)effect_state)->unk_9B = ((S_8008F428_0 *)effect_state)->unk_9B + 1;
            return;
        }

        {

            g_dungeon_status.flags |= 0x412;
        }
        process_unflagged_linked_entries_alt(((S_8008F428_4 *)owner)->unk_5C);
        process_unflagged_linked_entries(((S_8008F428_4 *)owner)->unk_5C);
        target = animation;
        ((S_8008F428_0 *)effect_state)->unk_8C = (u8 *)handle_player_input;
        (*(u8 * *)((u8 *)target + (0x2C))) = player_wait_frames;
        set_sprite_animation_frame(target,
            player_wait_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8008F428_4 *)owner)->unk_2A + 0x100) >> 9) & 7],
            0, 1);
        return;
    }

    state = ((S_8008F428_0 *)effect_state)->unk_9B;
    if (state == 0) {
        if (((SpriteFrameState *)animation)->unk_04 < 2) {
            return;
        }
        ((SpriteFrameState *)animation)->flags |= 0x800;
        ((S_8008F428_0 *)effect_state)->unk_96 = 0x10;
        ((S_8008F428_0 *)effect_state)->unk_9B = ((S_8008F428_0 *)effect_state)->unk_9B + 1;
        return;
    }

    ticks_left = ((S_8008F428_0 *)effect_state)->unk_96 - 1;
    ((S_8008F428_0 *)effect_state)->unk_96 = ticks_left;
    if ((s16)ticks_left > 0) {
        return;
    }
    ((SpriteFrameState *)animation)->flags &= 0xF7FF;
    play_sound_if_enabled(0x506);
    {
        s32 effect_id;

        effect_result = get_unused_text_buffer();
        target = ((S_8008F428_0 *)effect_state)->unk_11C;
        effect_id = effect_result;
        effect_result = append_entity_display_text(target, effect_id);
        saved_effect_id = effect_id;
        clear_byte_and_advance(expand_text_control_codes(D_800E0683, effect_result));
        display_text_with_fullwidth_adjustment(saved_effect_id);
        target = animation;
        ((S_8008F428_0 *)effect_state)->unk_8C = (u8 *)handle_player_input;
        (*(u8 * *)((u8 *)target + (0x2C))) = player_wait_frames;
        set_sprite_animation_frame(target,
            player_wait_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_8008F428_4 *)owner)->unk_2A + 0x100) >> 9) & 7],
            0, 1);
    }
}
