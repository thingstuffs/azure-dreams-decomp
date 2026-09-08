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

void func_800B52F4(s32 arg0, S_800B52F4_1 *arg1) {
    StackData sp18;
    StackData *data;
    M2C_UNK *source;
    register u32 page ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 word ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 byte ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 fifth ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    StackData *call_data;

    page = 0x80090000;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    source = (M2C_UNK *)(page - 0x6D40);
    ASM_KEEP(source);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    word = ((S_800B52F4_0 *)source)->unk_00;
    byte = ((S_800B52F4_0 *)source)->unk_04;
    sp18.unk0 = word;
    sp18.unk4 = byte;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    data = &sp18;
    strcat(data, D_800814A8 + 0x34, source);
    strcat(data, &D_800892C8);
    strcat(data, &D_800892CC);
    strcat(data, &D_800892D8);
    strcat(data, func_800A652C(arg0));
    call_data = data;
    ASM_KEEP(call_data);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    fifth = 0x88;
    func_800B5264(arg1->unk_0C, call_data, 0, 0x47, fifth);
}

/* MECHANISM: A 64-byte stack object forces the 0x68 frame; s1/s2 hold args and s0 holds its address.
   A pinned page/base split plus separately fenced v1/a0 copy temps emits the retail lw/lb/sw/sb order.
   Held a1/v0 final-call arguments preserve the closing move/li/move ABI sequence. */
