#include "common.h"

extern void clear_alternate_texture_regions(s32);
extern void func_800485B8(s32);
extern u8 *register_item_object_in_free_slot(void *target, void *ptr1, void *ptr2, s16 flag);
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 write_text_byte_and_advance(s8 value, s8 *dest);
extern s32 append_typed_formatted_value(void *, s32);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);

extern u8 D_800DD2EC[];
extern u8 D_800E07C0[];
extern u8 D_800E07D3[];
extern u8 D_800E0874[];
extern u8 D_800E089C[];
extern u8 D_800E08AB[];
extern u8 D_800E08BA[];


typedef struct S_80098614_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x30];
    union { u8 * p; void * p2; } unk_50;   /* accessed as both */
    u8 pad_54[0x32];
    u8 unk_86;
} S_80098614_0;   /* arg0 in change_equipped_item_and_notify */

/* Changes the actor's equipped item and displays status messages. */
void change_equipped_item_and_notify(S_80098614_0 *actor, u8 *requested_item)
{
    u8 *item;
    u8 *equipped_item;
    s32 item_flags;
    s32 item_id;
    s32 had_equipped;
    s32 text_end;
    s32 state;
    s16 equipped;

    item = requested_item;
    equipped = 0;

    if (item != 0) {
        item = register_item_object_in_free_slot(item, D_800E07C0, D_800E07D3, 0);
        if (item == 0) {
            return;
        }
    }

    equipped_item = actor->unk_50.p;
    if (equipped_item != 0) {
        item_flags = equipped_item[3];
        if (item_flags & 0x40) {
            play_sound_if_enabled(0x70A);
            state = get_unused_text_buffer();
            text_end = write_text_byte_and_advance(8, state);
            text_end = append_typed_formatted_value(equipped_item, text_end);
            text_end = expand_text_control_codes(D_800E0874, text_end);
            func_80099290(text_end);
            display_text_with_fullwidth_adjustment(state);
            return;
        }
        equipped_item[3] = item_flags & 0xDF;
        if (equipped_item == item) {
            item = 0;
        }
        equipped = 1;
    }

    had_equipped = equipped;
    if (item != 0) {
        item[3] &= 0x7F;
        item_id = item[0];
        state = get_unused_text_buffer();
        text_end = write_text_byte_and_advance(8, state);
        text_end = append_typed_formatted_value(item, text_end);
        text_end = expand_text_control_codes(D_800E089C, text_end);
        func_80099290(text_end);
        display_text_with_fullwidth_adjustment(state);

        if (item[3] & 0x40) {
            actor->unk_1C |= 0x800;
            play_sound_if_enabled(0x70A);
            state = get_unused_text_buffer();
            text_end = append_typed_formatted_value(item, state);
            text_end = expand_text_control_codes(D_800E08AB, text_end);
            func_80099290(text_end);
            display_text_with_fullwidth_adjustment(state);
        }

        item[3] |= 0x20;
    } else {
        item_id = 0;
        if (had_equipped != 0) {
            state = get_unused_text_buffer();
            text_end = write_text_byte_and_advance(8, state);
            text_end = append_typed_formatted_value(actor->unk_50.p2, text_end);
            text_end = expand_text_control_codes(D_800E08BA, text_end);
            func_80099290(text_end);
            display_text_with_fullwidth_adjustment(state);
        }

    }

    actor->unk_50.p = item;
    play_sound_if_enabled(0x508);
    text_end = item_id;
    actor->unk_86 = D_800DD2EC[text_end];
    if (text_end != 0) {
        func_800485B8(text_end);
        return;
    }
    clear_alternate_texture_regions(0);
}
