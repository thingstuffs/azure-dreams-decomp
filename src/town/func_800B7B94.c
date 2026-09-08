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

typedef struct S_800B52F4_0 {
    s32 unk_00;
    s8 unk_04;
} S_800B52F4_0;   /* source in func_800B52F4 */

typedef struct S_800B52F4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800B52F4_1;   /* arg1 in func_800B52F4 */

/* Builds a string from fixed fragments and selected text, then passes it to func_800B5264. */
void func_800B52F4(s32 text_id, S_800B52F4_1 *context) {
    StackData text_buffer;
    StackData *text;
    M2C_UNK *prefix;
    register u32 prefix_page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 prefix_word ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 prefix_tail ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 display_param ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    StackData *call_text;

    prefix_page = 0x80090000;
    ASM_KEEP(prefix_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    prefix = (M2C_UNK *)(prefix_page - 0x6D40);
    ASM_KEEP(prefix);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    prefix_word = ((S_800B52F4_0 *)prefix)->unk_00;
    prefix_tail = ((S_800B52F4_0 *)prefix)->unk_04;
    text_buffer.unk0 = prefix_word;
    text_buffer.unk4 = prefix_tail;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    text = &text_buffer;
    strcat(text, D_800814A8 + 0x34, prefix);
    strcat(text, &D_800892C8);
    strcat(text, &D_800892CC);
    strcat(text, &D_800892D8);
    strcat(text, func_800A652C(text_id));
    call_text = text;
    ASM_KEEP(call_text);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    display_param = 0x88;
    func_800B5264(context->unk_0C, call_text, 0, 0x47, display_param);
}

/* MECHANISM: A 64-byte stack object forces the 0x68 frame; s1/s2 hold args and s0 holds its address.
   A pinned page/base split plus separately fenced v1/a0 copy temps emits the retail lw/lb/sw/sb order.
   Held a1/v0 final-call arguments preserve the closing move/li/move ABI sequence. */
