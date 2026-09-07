#include "common.h"

typedef struct S_801720D8_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_801720D8_0;   /* arg3 in func_801720D8 */

typedef struct S_801720D8_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_801720D8_1;   /* arg0 in func_801720D8 */


typedef struct {
    u8 pad[0xA];
    u16 counter;
} State;


extern void func_80047784(void *, u8, s32);
extern s32 func_800A2BDC(void *);
extern s32 func_800A6D30(void);
extern s16 D_80083228;
extern State D_80083460;
extern u16 D_80083462;
extern u8 D_80174AE4[];

void func_801720D8(void *arg0, void *arg1, void *arg2, void *arg3) {
    register s32 value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    ((S_801720D8_0 *)arg3)->unk_71 = (u8)(((S_801720D8_0 *)arg3)->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2BDC(arg3) << 16) == 0)) {
        ((S_801720D8_1 *)arg0)->unk_8C = 0;
        ((S_801720D8_1 *)arg0)->unk_9A = 0x17;
        ((S_801720D8_1 *)arg0)->unk_9B = 0;
        if (((S_801720D8_0 *)arg3)->unk_1C & 0x400) {
            value = ((S_801720D8_0 *)arg3)->unk_14;
            if (value >= 0) {
                ((S_801720D8_0 *)arg3)->unk_14 = (s32)(value | 0x80000000);
                ((S_801720D8_0 *)arg3)->unk_2A = (u16)(((S_801720D8_0 *)arg3)->unk_2A + ((func_800A6D30() & 7) << 9));
            }
        }
        ((S_801720D8_1 *)arg0)->unk_96 = 0;
        D_80083460.counter = (u16)(D_80083460.counter + 1);
        ((S_801720D8_0 *)arg3)->unk_6D = (u8)(((S_801720D8_0 *)arg3)->unk_6D - 1);
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174AE4;
        func_80047784(arg2, D_80174AE4[((D_80083228 + (s16)((S_801720D8_0 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
    }
}
