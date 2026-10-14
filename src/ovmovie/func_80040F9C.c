#include "modules/ovmovie_libpress.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))



typedef struct S_80040F9C_0 {
    s32 unk_00;
} S_80040F9C_0;   /* src in func_8017779C */

typedef struct S_80040F9C_1 {
    s32 unk_00;
} S_80040F9C_1;   /* dst in func_8017779C */

/* Copies two 64-byte blocks into global buffers and processes two global regions. */
s8 *func_8017779C(s8 *data) {
    s8 *data_start;
    s8 *src;
    s8 *dst;
    s32 word;
    s32 word_index;

    data_start = data;
    src = data;
    dst = D_80178240;
    word_index = 0xF;
    do {
        word = ((S_80040F9C_0 *)src)->unk_00;
        src += 4;
        word_index -= 1;
        ((S_80040F9C_1 *)dst)->unk_00 = word;
        dst += 4;
    } while (word_index != -1);

    dst = D_80178280;
    src = data_start + 0x40;
    word_index = 0xF;
    do {
        word = ((S_80040F9C_0 *)src)->unk_00;
        src += 4;
        word_index -= 1;
        ((S_80040F9C_1 *)dst)->unk_00 = word;
        dst += 4;
    } while (word_index != -1);

    func_80177A9C((s32 *)&D_8017823C, 0x20);
    func_80177A9C((s32 *)&D_801782C0, 0x20);
    return data_start;
}
