#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

void set_sprite_animation_frame(void *, u8, s32, s32);
s32 find_flagged_record_by_id(s32, s32);
void begin_deferred_player_item_effect(void *, s32, void *, void *);
s32 get_unused_text_buffer(void);
s32 expand_text_control_codes(u8 *src, u8 *dst);
void clear_byte_and_advance(s8 *byte_ptr);
s32 write_text_byte_and_advance(s8 value, s8 *dest);
s32 append_typed_formatted_value(s32, s32);
s32 process_eligible_object_value(s32, s32);
s32 append_entity_display_text(void *record, u8 *out);
void play_sound_if_enabled(s32);
void display_text_with_fullwidth_adjustment(s8 *text);
void *create_item_render_object(s32 parent, s32 sprite_source, s16 x, s32 y, s16 z);
extern s32 held_item_record;
extern s32 D_8008D470;
extern u8 D_800DD100[];
extern u8 D_800E06E3[];
extern u8 D_800E06EB[];


typedef struct S_8009255C_1 {
    u8 pad_00[0xC8];
    s16 unk_C8;
} S_8009255C_1;   /* base in update_player_eating_action */


typedef struct S_8009255C_3 {
    u8 pad_00[0x2C];
    u8 * unk_2C;
} S_8009255C_3;   /* call_arg in update_player_eating_action */


typedef struct S_8009255C_5 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
} S_8009255C_5;

typedef struct S_8009255C_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8009255C_6;

typedef struct S_8009255C_7 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    void * unk_90;
    u8 pad_94[0x8];
    void * unk_9C;
    u8 pad_A0[0x8];
    s16 unk_A8;
    s16 unk_AA;
} S_8009255C_7;

/* Turn the actor, spawn the action object and message, and handle completion. */
void update_player_eating_action(void *controller, s32 action_id, Rec_D_80082E80 *actor, EntityRec *transform) {
    s32 text_start;
    s32 text_cursor;
    s32 state;
    void *spawned;
    S_8009255C_6 *position;
    S_8009255C_7 *spawned_state;
    S_8009255C_3 *animation_actor;
    u8 *animation_entry;
    u8 *animation_table;

    state = ((Rec_func_8008ACDC_arg0 *)controller)->unk_9B.as_u8;
    switch (state) {
    case 0:
        if ((((g_game_work.view.camera_rotation.parts.viewAngle +
               transform->facing + 0x100) >> 9) & 7) == 2) {
            animation_actor = actor;
            animation_table = D_800DD100;
            animation_actor->unk_2C = animation_table;
            animation_entry = (u8 *)((s32)(((g_game_work.view.camera_rotation.parts.viewAngle +
                                    transform->facing + 0x100) >> 9) &
                                  7) +
                           (s32)animation_table);
            set_sprite_animation_frame(
                animation_actor,
                *animation_entry,
                0,
                1);
            ((Rec_func_8008ACDC_arg0 *)controller)->unk_9B.as_u8++;
            break;
        }
        transform->facing =
            (u16)transform->facing + 0x200;
        break;
    case 1:
        if (find_flagged_record_by_id(actor->unk_08, 0) == 0) {
            return;
        }
        if (((Rec_func_8008ACDC_arg0 *)controller)->unk_110 == (s32)&held_item_record) {
            ((Rec_func_8008ACDC_arg0 *)controller)->unk_124 = 0;
            ((Rec_func_8008ACDC_arg0 *)controller)->unk_1C &= 0xFFEFFFFF;
        }
        spawned = create_item_render_object(
            controller - 0x20, ((Rec_func_8008ACDC_arg0 *)controller)->unk_110, 0, 0, 0);
        if (spawned != NULL) {
            ((S_8009255C_5 *)spawned)->unk_10 = (s32)&D_8008D470;
            position = ((S_8009255C_5 *)spawned)->unk_08;
            position->unk_02 =
                (actor->unk_24 << 6) + 0x20;
            position->unk_06 =
                (actor->unk_25 << 6) + 0x20;
            position->unk_0A =
                ((u16)transform->unk_88) - 0x30;
            spawned_state = spawned + 0x20;
            spawned_state->unk_A8 = 0x1E;
            spawned_state->unk_AA = 2;
            spawned_state->unk_90 = actor;
            spawned_state->unk_8C = action_id;
            spawned_state->unk_9C = controller + 0x108;
            text_cursor = get_unused_text_buffer();
            text_start = text_cursor;
            text_cursor = write_text_byte_and_advance(8, text_cursor);
            text_cursor = append_entity_display_text(transform, text_cursor);
            text_cursor = expand_text_control_codes(D_800E06E3, text_cursor);
            text_cursor = append_typed_formatted_value(
                ((Rec_func_8008ACDC_arg0 *)controller)->unk_110, text_cursor);
            text_cursor = expand_text_control_codes(D_800E06EB, text_cursor);
            text_cursor = process_eligible_object_value(
                ((Rec_func_8008ACDC_arg0 *)controller)->unk_110, text_cursor);
            clear_byte_and_advance(text_cursor);
            display_text_with_fullwidth_adjustment(text_start);
            play_sound_if_enabled(0x509);
        }

        ((Rec_func_8008ACDC_arg0 *)controller)->unk_9B.as_u8++;
        break;
    case 2:
        if ((actor->unk_14.at00_u16.v & 0xE000) == 0) {
            return;
        }
        if (((Rec_func_8008ACDC_arg0 *)controller)->unk_110 != 0) {
            begin_deferred_player_item_effect(controller, action_id, actor, transform);
            return;
        }
        ((Rec_func_8008ACDC_arg0 *)controller)->unk_8C.as_s32 = (s32)handle_player_input;
        break;
    }
}

/* MECHANISM: True-space local joins restore retail block order and the increment path.
   A volatile held 0x80083160 base reproduces both loads; short-lived a0/v1 roles
   plus index-first entry arithmetic preserve the final addu destination. */
