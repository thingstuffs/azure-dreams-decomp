#include "common.h"
#include "m2c_compat.h"

M2C_UNK strcat(); /* extern */
M2C_UNK *func_800A652C();                        /* extern */
M2C_UNK func_800B5264(); /* extern */
extern s32 D_800814A8;
extern M2C_UNK D_800892C0;
extern M2C_UNK D_800892C8;
extern M2C_UNK D_800892CC;
extern M2C_UNK D_800892D8;

typedef struct {
    s32 unk0;
    s8 unk4;
    u8 pad5[0x3B];
} StackData;

typedef struct S_800B52F4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800B52F4_1;   /* arg1 in func_800B52F4 */

/* Builds a string from fixed fragments and selected text, then passes it to func_800B5264. */
void func_800B52F4(s32 text_id, S_800B52F4_1 *context) {
    StackData text_buffer;
    StackData *text;

    text = &text_buffer;
    memcpy(text, &D_800892C0, 5);
    strcat(text, D_800814A8 + 0x34);
    strcat(text, &D_800892C8);
    strcat(text, &D_800892CC);
    strcat(text, &D_800892D8);
    strcat(text, func_800A652C(text_id));
    func_800B5264(context->unk_0C, text, 0, 0x47, 0x88);
}

/* MECHANISM: A 64-byte stack object forces the 0x68 frame; s1/s2 hold args and s0 holds its address.
   The 5-byte prefix (4 chars + NUL at D_800892C0) is copied by the inline memcpy expansion:
   move_by_pieces copies the constant source address into one register, giving lw/lb 0/4($6). */
