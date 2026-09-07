#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern void func_800C2E84(void *arg0, s32 arg2, void *arg3);
extern void func_800C4174(void *arg0, M2C_UNK arg1, void *arg2);
extern u8 D_80082660;
extern M2C_UNK D_800D5518;
extern M2C_UNK D_800D5624;
extern M2C_UNK D_800D562C;
extern M2C_UNK D_800D5654;
extern M2C_UNK D_800D5658;

typedef struct S_800C5C70_0 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800C5C70_0;   /* arg2 in func_800C5C70 */

typedef struct S_800C5C70_1 {
    u8 pad_00[0x58];
    M2C_UNK * unk_58;
    M2C_UNK * unk_5C;
    s32 unk_60;
    u8 pad_64[0xC];
    s8 unk_70;
    u8 unk_71;
    u8 pad_72[0xA];
    M2C_UNK * unk_7C;
    M2C_UNK * unk_80;
} S_800C5C70_1;   /* arg0 in func_800C5C70 */

void func_800C5C70(void *arg0, M2C_UNK arg1, void *arg2) {
    if (((S_800C5C70_0 *)arg2)->unk_14 & 0x6000) {
        func_800C2E84(arg0, arg2, &D_800D5518);
        *((((S_800C5C70_1 *)arg0)->unk_60 * 8) + &D_80082660) = 0;
        ((S_800C5C70_1 *)arg0)->unk_58 = &D_800D5654;
        ((S_800C5C70_1 *)arg0)->unk_5C = &D_800D5658;
        ((S_800C5C70_1 *)arg0)->unk_7C = &D_800D5624;
        ((S_800C5C70_1 *)arg0)->unk_80 = &D_800D562C;
        ((S_800C5C70_1 *)arg0)->unk_70 = 1;
        ((S_800C5C70_1 *)arg0)->unk_71 = (u8) (((S_800C5C70_1 *)arg0)->unk_71 | 1);
        func_800C4174(arg0, arg1, arg2);
    }
}
