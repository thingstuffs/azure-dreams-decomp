#include "common.h"



typedef s32 M2C_UNK;
extern M2C_UNK D_80083498;
extern u8 D_80083780[12];
extern u8 *D_80175D50[3];
extern s16 func_8016F428(void *arg);

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct S_8016F79C_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_8016F79C_0;   /* s0 in func_8016F79C */

typedef struct S_8016F79C_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_8016F79C_1;   /* s2 in func_8016F79C */

void func_8016F79C(void *unused0, u8 *arg1, void *unused2) {
    u8 *base2 = (u8 *)&D_80083498;
    register volatile u8 *s2 = (volatile u8 *)(base2 + 0x20);
    u8 *base = D_80175D50[1];
    u8 *s0 = base + 0x20;
    s16 raw_value = func_8016F428(arg1);
    s32 value = raw_value;

    if (value == 9) {
        ((S_8016F79C_0 *)s0)->unk_2A = ((S_8016F79C_1 *)s2)->unk_2A;
    } else {
        ((S_8016F79C_0 *)s0)->unk_2A = (u16)(value << 9);
    }
    {
        register volatile u16 *table = (volatile u16 *)D_80083780;
        *(u16 *)(arg1 + 2) = table[1];
        *(u16 *)(arg1 + 6) = table[3];
    }
}
