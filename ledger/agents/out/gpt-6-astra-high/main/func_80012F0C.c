#include "common.h"

extern void func_8003AD08(s32 arg0, void *arg1);
extern void strcat(s32 arg0, s32 arg1);
extern void strcpy(s32 arg0, s32 arg1);

extern s16 D_80010208;
extern s32 D_80028294[];
extern s32 D_800282A0;

/* Build text from a one-based index, global state, and a trailing value. */
void func_80025F0C(s32 record, s32 index) {
    s32 number_text[4];
    s32 *text_parts;
    s32 output_text;
    s32 append_text;
    s32 saved_index;
    s32 state_text;
    s32 suffix_value;

    saved_index = index;
    output_text = record + 4;
    text_parts = D_80028294;
    strcpy(output_text, text_parts[0]);
    func_8003AD08(saved_index + 1, number_text);
    strcat(output_text, (s32)number_text);
    strcat(output_text, text_parts[3]);
    strcat(output_text, 0x8001020C);
    strcat(output_text, text_parts[3]);

    append_text = output_text;
    if (D_80010208 != 0) {
        state_text = text_parts[1];
    } else {
        state_text = text_parts[2];
    }
    ASM_KEEP(saved_index);   /* MATCH pin: load-bearing for the whole function shape */
    strcat(append_text, state_text);

    output_text = record + 4;
    strcat(output_text, D_800282A0);
    suffix_value = *(s32 *)0x8001022C;
    func_8003AD08(suffix_value, number_text);
    strcat(output_text, (s32)number_text);
}
