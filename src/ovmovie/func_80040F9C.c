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

s8 *func_80040F9C(s8 *arg0) {
    s8 *saved;
    s8 *src;
    s8 *dst;
    s32 temp;
    s32 i;

    saved = arg0;
    src = arg0;
    dst = D_80180000 - 0x7DC0;
    i = 0xF;
    do {
        temp = ((S_80040F9C_0 *)src)->unk_00;
        src += 4;
        i -= 1;
        ((S_80040F9C_1 *)dst)->unk_00 = temp;
        dst += 4;
    } while (i != -1);

    dst = D_80180000 - 0x7D80;
    src = saved + 0x40;
    i = 0xF;
    do {
        temp = ((S_80040F9C_0 *)src)->unk_00;
        src += 4;
        i -= 1;
        ((S_80040F9C_1 *)dst)->unk_00 = temp;
        dst += 4;
    } while (i != -1);

    func_80177A9C(&D_8017823C, 0x20);
    func_80177A9C(&D_801782C0, 0x20);
    return saved;
}
