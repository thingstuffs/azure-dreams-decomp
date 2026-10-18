#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80098CF8_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x6];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_80098CF8_0;   /* s0 in begin_holding_item */

typedef struct S_80098CF8_1 {
    union {
        struct { s32 v; } at00;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_00;   /* overlapping accesses */
} S_80098CF8_1;   /* s2 in begin_holding_item */

typedef struct S_80098CF8_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80098CF8_2;   /* primitive in begin_holding_item */

   /* s5 in begin_holding_item */

typedef struct S_80098CF8_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80098CF8_4;   /* s4 in begin_holding_item */

typedef struct S_80098CF8_5 {
    u8 pad_00[0x8C];
    s32 unk_8C;
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
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x20];
    void * unk_BC;
    u8 pad_C0[0x64];
    s32 unk_124;
} S_80098CF8_6;   /* s3 in begin_holding_item */

typedef struct S_80098CF8_7 {
    u8 pad_00[0x1484];
    s32 unk_1484;
} S_80098CF8_7;   /* (void *)a1 in begin_holding_item */


extern void func_80048A44();
extern void equip_item_and_update_status();
extern void change_equipped_item_and_notify();
extern void clear_slot_and_update_linked_state();
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes();
extern void func_80099290();
extern s32 write_text_byte_and_advance();
extern s32 append_typed_formatted_value();
extern void play_sound_if_enabled();
extern void display_text_with_fullwidth_adjustment();
extern void *create_item_render_object();

extern u8 D_80081484[];
extern u8 D_8008D470[];
extern u8 D_800DD0B8[8];
extern u8 D_800E08CC[];
extern u8 D_800E08E5[];
extern u8 D_800E08F1[];
extern u8 D_800E0919[];

/* Check the item, report restrictions, and create an action object for the actor and target. */
void *begin_holding_item(void *actor, s32 action, void *target, void *item)
{
    void *message;

    void *target_arg;
    void *actor_state;
    register void *result;
    s32 message_id;
    void *primitive;
    void *state;
    s32 text_cursor;

    actor_state = actor;
    if ((item != ((void *)(D_80081484))) && (((S_80098CF8_0 *)((void *)(D_80081484)))->unk_01 != 0)) {
        message_id = get_unused_text_buffer();
        text_cursor = write_text_byte_and_advance(8, message_id);
        text_cursor = append_typed_formatted_value(item, text_cursor);
        text_cursor = expand_text_control_codes(D_800E08CC, text_cursor);
        text_cursor = append_typed_formatted_value(((void *)(D_80081484)), text_cursor);
        message = D_800E08E5;
print_message:
        text_cursor = expand_text_control_codes(message, text_cursor);
        func_80099290(text_cursor);
        display_text_with_fullwidth_adjustment(message_id);

        return 0;
    }

    if ((*(u8 *)((u8 *)item + 3)) & 0x20) {
        message_id = get_unused_text_buffer();
        result = (void *)write_text_byte_and_advance(8, message_id);
        if (((S_80098CF8_1 *)item)->unk_00.at03.v & 0x40) {
            play_sound_if_enabled(0x70A);
            text_cursor = append_typed_formatted_value(item, result);
            message = D_800E08F1;
            text_cursor = expand_text_control_codes(message, text_cursor);
            func_80099290(text_cursor);
            display_text_with_fullwidth_adjustment(message_id);

            return 0;
        }

        text_cursor = append_typed_formatted_value(item, result);
        text_cursor = expand_text_control_codes(D_800E0919, text_cursor);
        func_80099290(text_cursor);
        display_text_with_fullwidth_adjustment(message_id);
        if (((S_80098CF8_1 *)item)->unk_00.at01.v == 0x11) {
            change_equipped_item_and_notify(actor_state, item);
        } else {
            equip_item_and_update_status(actor_state, item);
        }
    }

    result = create_item_render_object((u8 *)actor - 0x20, item, 0, 0, 0);
    if (result == 0) {
        return 0;
    }

    {
        s32 height;

        ((S_80098CF8_0 *)result)->unk_10 = D_8008D470;
        primitive = ((S_80098CF8_0 *)result)->unk_08;
        ((S_80098CF8_2 *)primitive)->unk_02 = (((MovingTile *)target)->unk_24 << 6) + 0x20;
        ((S_80098CF8_2 *)primitive)->unk_06 = (((MovingTile *)target)->unk_25 << 6) + 0x20;
        height = ((S_80098CF8_4 *)actor_state)->unk_88;
        message = target;
        ((S_80098CF8_2 *)primitive)->unk_0A = height - 0x30;

        state = (u8 *)result + 0x20;
        {
            register s32 data_word;
            u8 *sound_table;
            data_word = ((S_80098CF8_1 *)item)->unk_00.at00.v;
            ((S_80098CF8_5 *)state)->unk_AC = 1;
            ((S_80098CF8_5 *)state)->unk_90 = message;
            ((S_80098CF8_5 *)state)->unk_8C = action;
            ((S_80098CF8_5 *)state)->unk_A8 = 6;
            ((S_80098CF8_5 *)state)->unk_98 = data_word;
            ((S_80098CF8_6 *)actor)->unk_BC = item;
            target_arg = (void *)((S_80098CF8_1 *)item)->unk_00.at00.v;
            ((S_80098CF8_5 *)state)->unk_9C = D_80081484;
            ((S_80098CF8_6 *)actor)->unk_8C = 0;
            ((S_80098CF8_6 *)actor)->unk_124 = 0;
            *(s32 *)D_80081484 = (s32)target_arg;
            ((S_80098CF8_6 *)actor)->unk_9A = 0x1B;
            ((S_80098CF8_6 *)actor)->unk_9B = 0;
            sound_table = D_800DD0B8;
            (*(void * *)((u8 *)message + 0x2C)) = sound_table;

            func_80048A44(
                message,
                sound_table[((g_game_work.view.viewAngle + ((S_80098CF8_4 *)actor_state)->unk_2A + 0x100) >> 9) & 7],
                0,
                1);
            play_sound_if_enabled(0x511);
            ((S_80098CF8_4 *)actor_state)->unk_1C |= 0x100000;
            clear_slot_and_update_linked_state(item);
        }
    }
    return result;

    return 0;
}
