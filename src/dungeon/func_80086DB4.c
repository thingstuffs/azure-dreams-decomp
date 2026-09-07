#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80048A44(void *, u8, s32, s32);
extern void func_8008C598() __attribute__((noreturn));
extern void func_800A56E0(u32);
extern s16 D_80083228[];
extern u8 D_800DD030[];

typedef struct S_8008C514_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
} S_8008C514_0;   /* arg0 in func_8008C514 */

typedef struct S_8008C514_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_8008C514_1;   /* arg3 in func_8008C514 */

typedef struct S_8008C514_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_8008C514_2;   /* arg2 in func_8008C514 */

void func_8008C514(S_8008C514_0 *arg0, s32 arg1, S_8008C514_2 *arg2, S_8008C514_1 *arg3) {
    arg0->unk_9A = 0x1A;
    arg0->unk_9B = 0;
    arg0->unk_8C = 0;
    if (arg3->unk_1C & 0x100000) {
        arg2->unk_14 |= 0x4000;
        func_8008C598(arg2);
    }
    arg2->unk_2C = D_800DD030;
    func_80048A44(arg2, D_800DD030[((s32)(D_80083228[0] + arg3->unk_2A + 0x100) >> 9) & 7], 0, 1);
    func_800A56E0(0x50A);
    arg0->unk_96 = 0;
    arg0->unk_A2 = (u16)(arg0->unk_A2 & 0xFFEF);
}
