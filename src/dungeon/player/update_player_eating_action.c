#include "engine/graphics.h"
#include "shared/dungeon_actor_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "common.h"
#include "dungeon/player/item.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"


void *get_unused_text_buffer(void);
u8 *expand_text_control_codes(u8 *src, u8 *dst);
void clear_byte_and_advance(s8 *byte_ptr);
void *write_text_byte_and_advance(s8 value, s8 *dest);
u8 * append_typed_formatted_value(s32,u8 *);
u8 * process_eligible_object_value(s32, u8 *);
u8 *append_entity_display_text(void *record, u8 *out);
void play_sound_if_enabled(s32);
void display_text_with_fullwidth_adjustment(s8 *text);
void *create_item_render_object(void *parent, void *sprite_source, s16 x, s32 y, s16 z);
extern s32 held_item_record;
extern s32 player_item_render_update_address;
extern u8 D_800DD100[];
extern u8 D_800E06E3[];
extern u8 D_800E06EB[];

   /* call_arg in update_player_eating_action */

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
void update_player_eating_action(void *controller, s32 action_id, SpriteFrameState *actor, EntityRec *transform) {
    void *text_start;
    void *text_cursor;
    s32 state;
    ObjectNodeHeader *spawned;
    ObjectPosition *position;
    S_8009255C_7 *spawned_state;
    SpriteFrameState *animation_actor;
    u8 *animation_entry;
    u8 *animation_table;

    state = ((Rec_func_8008ACDC_arg0 *)controller)->unk_9B.as_u8;
    switch (state) {
    case 0:
        if ((((g_game_work.view.camera_rotation.parts.viewAngle +
               transform->facing + 0x100) >> 9) & 7) == 2) {
            animation_actor = actor;
            animation_table = D_800DD100;
            animation_actor->frameTable = animation_table;
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
        if (find_flagged_record_by_id(actor->source, 0) == 0) {
            return;
        }
        if (((Rec_func_8008ACDC_arg0 *)controller)->unk_110 == (s32)&held_item_record) {
            ((Rec_func_8008ACDC_arg0 *)controller)->unk_124 = 0;
            ((Rec_func_8008ACDC_arg0 *)controller)->unk_1C &= 0xFFEFFFFF;
        }
        spawned = create_item_render_object(
            controller - 0x20, ((Rec_func_8008ACDC_arg0 *)controller)->unk_110, 0, 0, 0);
        if (spawned != NULL) {
            spawned->update_callback = &player_item_render_update_address;
            position = spawned->position;
            position->x.w.i =
                (actor->tile_x << 6) + 0x20;
            position->y.w.i =
                (actor->tile_y << 6) + 0x20;
            position->z.w.i =
                ((u16)transform->unk_88) - 0x30;
            spawned_state = ((void *)spawned) + 0x20;
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
        if ((actor->flags & 0xE000) == 0) {
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
