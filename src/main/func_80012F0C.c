#include "common.h"

extern void func_8003AD08(s32 value, void *output_buffer);
extern void strcat(s32 destination, s32 source);
extern void strcpy(s32 destination, s32 source);

extern s16 D_80010208;
extern s32 D_80028294[];
extern s32 D_800282A0;

/* Build text from a one-based index, global state, and a trailing value. */
void func_80025F0C(s32 record, s32 index) {
    s32 number_buffer[4];
    s32 *text_fragments;
    s32 output_text_target;
    s32 suffix_text_target;
    s32 append_target;
    s32 saved_index;
    s32 selected_text;
    s32 trailing_value;

    saved_index = index;
    output_text_target = record + 4;
    text_fragments = D_80028294;
    strcpy(output_text_target, text_fragments[0]);
    func_8003AD08(saved_index + 1, number_buffer);
    strcat(output_text_target, (s32)number_buffer);
    strcat(output_text_target, text_fragments[3]);
    strcat(output_text_target, 0x8001020C);
    strcat(output_text_target, text_fragments[3]);

    append_target = output_text_target;
    if (D_80010208 != 0) {
        selected_text = text_fragments[1];
    } else {
        selected_text = text_fragments[2];
    }
    strcat(append_target, selected_text);

    suffix_text_target = record + 4;
    strcat(suffix_text_target, D_800282A0);
    trailing_value = *(s32 *)0x8001022C;
    func_8003AD08(trailing_value, number_buffer);
    strcat(suffix_text_target, (s32)number_buffer);
}
