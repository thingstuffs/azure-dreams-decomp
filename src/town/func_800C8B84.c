#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern void func_800C2E84(void *arg0, s32 arg2, void *arg3);
extern u8 D_80082660;
extern M2C_UNK D_800C3B7C;
extern M2C_UNK D_800D5670;

typedef struct S_800C62E4_0 {
    u8 pad_00[0x54];
    M2C_UNK * unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
    u8 pad_64[0x8];
    s16 unk_6C;
} S_800C62E4_0;   /* arg0 in func_800C62E4 */

void func_800C62E4(void *arg0, s32 unused1, s32 arg2) {
    func_800C2E84(arg0, arg2, &D_800D5670);
    *((((S_800C62E4_0 *)arg0)->unk_60 * 8) + &D_80082660) = 0;
    ((S_800C62E4_0 *)arg0)->unk_54 = &D_800C3B7C;
    ((S_800C62E4_0 *)arg0)->unk_6C = 0x20;
}
