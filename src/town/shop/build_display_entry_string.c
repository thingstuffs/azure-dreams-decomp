#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "sdk/libc.h"
#include "town/shop.h"
#include "town/shop/position.h"
s32 select_object_state_value(void *object);                        /* extern */
extern M2C_UNK D_800892C0;
extern char D_800892C8[];
extern char D_800892CC[];
extern char D_800892D8[];

typedef struct {
    s32 unk0;
    s8 unk4;
    u8 pad5[0x3B];
} StackData;

typedef struct S_800B52F4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800B52F4_1;   /* arg1 in build_display_entry_string */

/* Builds a string from fixed fragments and selected text, then passes it to set_display_entry_text_and_position. */
void build_display_entry_string(s32 text_id, S_800B52F4_1 *context) {
    StackData text_buffer;
    StackData *text;

    text = &text_buffer;
    memcpy(text, &D_800892C0, 5);
    strcat(text, ((s32)primary_actor_record) + 0x34);
    strcat(text, D_800892C8);
    strcat(text, D_800892CC);
    strcat(text, D_800892D8);
    strcat(text, select_object_state_value(text_id));
    set_display_entry_text_and_position(context->unk_0C, text, 0, 0x47, 0x88);
}

/* MECHANISM: A 64-byte stack object forces the 0x68 frame; s1/s2 hold args and s0 holds its address.
   The 5-byte prefix (4 chars + NUL at D_800892C0) is copied by the inline memcpy expansion:
   move_by_pieces copies the constant source address into one register, giving lw/lb 0/4($6). */
