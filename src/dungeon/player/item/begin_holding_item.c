#include "dungeon/player/held_item_kind_data.h"
#include "shared/item_ids.h"
#include "common.h"
#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/player/item.h"
#include "engine/graphics.h"
#include "dungeon/item/message.h"
#include "dungeon/actor/effect.h"
#include "dungeon/player.h"
#include "dungeon/player/state.h"
#include "dungeon/system.h"
#include "dungeon/item.h"

struct S_80098614_0;



typedef struct S_80098CF8_5 {
    u8 pad_00[0x8C];
    void *unk_8C;
    void * unk_90;
    u8 pad_94[0x4];
    s32 unk_98;
    void * unk_9C;
    u8 pad_A0[0x8];
    s16 unk_A8;
    u8 pad_AA[0x2];
    s16 unk_AC;
} S_80098CF8_5;   /* state in begin_holding_item */

typedef struct S_80098CF8_6 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x20];
    void * unk_BC;
    u8 pad_C0[0x64];
    s32 unk_124;
} S_80098CF8_6;   /* s3 in begin_holding_item */

extern u8 player_item_render_update_address[];
extern u8 player_carry_frames[8];
extern u8 D_800E08CC[];
extern u8 D_800E08E5[];
extern u8 D_800E08F1[];
extern u8 D_800E0919[];

/* Check the item, report restrictions, and create an action object for the actor and target. */
void *begin_holding_item(void *actor, void *action, void *target, void *item)
{
    DungeonItemEntry *item_data;
    void *message;

    s32 held_word;
    void *actor_state;
    register ObjectNodeHeader *result;
    void *message_id;
    ObjectPosition *primitive;
    S_80098CF8_5 *state;
    void *text_cursor;

    actor_state = actor;
    if (item != &held_item_record && held_item_record.kind != ITEM_KIND_NONE) {
        message_id = get_unused_text_buffer();
        text_cursor = write_text_byte_and_advance(8, message_id);
        text_cursor = append_item_name_with_value(item, text_cursor);
        text_cursor = expand_text_control_codes(D_800E08CC, text_cursor);
        text_cursor = append_item_name_with_value(&held_item_record, text_cursor);
        message = D_800E08E5;
print_message:
        text_cursor = expand_text_control_codes(message, text_cursor);
        clear_byte_and_advance(text_cursor);
        display_text_with_fullwidth_adjustment(message_id);

        return 0;
    }

    item_data = item;
    if (item_data->unk_03 & 0x20) {
        message_id = get_unused_text_buffer();
        text_cursor = write_text_byte_and_advance(8, message_id);
        if (item_data->unk_03 & 0x40) {
            play_sound_if_enabled(0x70A);
            text_cursor = append_item_name_with_value(item_data, text_cursor);
            message = D_800E08F1;
            text_cursor = expand_text_control_codes(message, text_cursor);
            clear_byte_and_advance(text_cursor);
            display_text_with_fullwidth_adjustment(message_id);

            return 0;
        }

        text_cursor = append_item_name_with_value(item_data, text_cursor);
        text_cursor = expand_text_control_codes(D_800E0919, text_cursor);
        clear_byte_and_advance(text_cursor);
        display_text_with_fullwidth_adjustment(message_id);
        if (item_data->kind == ITEM_KIND_SHIELD) {
            change_equipped_item_and_notify(actor_state, item_data);
        } else {
            equip_item_and_update_status(actor_state, item_data);
        }
    }

    result = create_item_render_object((u8 *)actor - 0x20, item, 0, 0, 0);
    if (result == 0) {
        return 0;
    }

    {
        s32 height;

        result->update_callback = player_item_render_update_address;
        primitive = result->position;
        primitive->x.w.i = (((MovingTile *)target)->tile_x << 6) + 0x20;
        primitive->y.w.i = (((MovingTile *)target)->tile_y << 6) + 0x20;
        height = ((u16)((ActorRecord *)actor_state)->ground_height);
        message = target;
        primitive->z.w.i = height - 0x30;

        state = NODE_BODY(result);
        {
            s32 data_word;
            u8 *sound_table;
            S_80098CF8_6 *actor_view = actor;
            data_word = *(s32 *)item;
            state->unk_AC = 1;
            state->unk_90 = message;
            state->unk_8C = action;
            state->unk_A8 = 6;
            state->unk_98 = data_word;
            actor_view->unk_BC = item;
            held_word = *(s32 *)item;
            state->unk_9C = &held_item_record;
            actor_view->unk_8C = 0;
            actor_view->unk_124 = 0;
            *(s32 *)&held_item_record = held_word;
            actor_view->unk_9A = 0x1B;
            actor_view->unk_9B = 0;
            sound_table = player_carry_frames;
            (*(void * *)((u8 *)message + 0x2C)) = sound_table;

            set_sprite_animation_frame(
                message,
                sound_table[((g_game_work.view.camera_rotation.parts.viewAngle + ((ActorRecord *)actor_state)->facing + 0x100) >> 9) & 7],
                0,
                1);
            play_sound_if_enabled(0x511);
            ((ActorRecord *)actor_state)->flags1C |= 0x100000;
            clear_item_slot(item);
        }
    }
    return result;

    return 0;
}
