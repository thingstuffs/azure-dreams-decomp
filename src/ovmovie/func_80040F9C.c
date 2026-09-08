#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80177A9C(void *arg0, s32 arg1);

extern u8 D_8017823C;
extern u8 D_80178240[];
extern u8 D_80178280[];
extern u8 D_801782C0;
extern u8 D_80180000[];

typedef struct S_80040F9C_0 {
    s32 unk_00;
} S_80040F9C_0;   /* src in func_80040F9C */

typedef struct S_80040F9C_1 {
    s32 unk_00;
} S_80040F9C_1;   /* dst in func_80040F9C */

/* Copies two 64-byte blocks into global buffers and processes two global regions. */
s8 *func_80040F9C(s8 *data) {
    s8 *data_start;
    s8 *src;
    s8 *dst;
    s32 word;
    s32 word_index;

    data_start = data;
    src = data;
    dst = D_80180000 - 0x7DC0;
    word_index = 0xF;
    do {
        word = ((S_80040F9C_0 *)src)->unk_00;
        src += 4;
        word_index -= 1;
        ((S_80040F9C_1 *)dst)->unk_00 = word;
        dst += 4;
    } while (word_index != -1);

    dst = D_80180000 - 0x7D80;
    src = data_start + 0x40;
    word_index = 0xF;
    do {
        word = ((S_80040F9C_0 *)src)->unk_00;
        src += 4;
        word_index -= 1;
        ((S_80040F9C_1 *)dst)->unk_00 = word;
        dst += 4;
    } while (word_index != -1);

    func_80177A9C(&D_8017823C, 0x20);
    func_80177A9C(&D_801782C0, 0x20);
    return data_start;
}
