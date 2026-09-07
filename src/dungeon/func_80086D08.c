#include "common.h"


extern s16 D_80083228;
extern u8 D_800DD050[];
extern u8 D_800DD0E0[];

extern void func_80048A44(void *, s16, s16, s32);
extern void func_8008C4C8(void *, u8 *);


typedef struct S_8008C468_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
} S_8008C468_0;   /* arg0 in func_8008C468 */

typedef struct S_8008C468_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
} S_8008C468_1;   /* arg3 in func_8008C468 */

void func_8008C468(void *arg0, void *arg1, void *arg2, void *arg3) {
    if (!(((S_8008C468_0 *)arg0)->unk_98 & 0xC)) {
        ((S_8008C468_0 *)arg0)->unk_9A = 0x16;
        ((S_8008C468_0 *)arg0)->unk_9B = 0;
        ((S_8008C468_0 *)arg0)->unk_8C = 0;
        ((S_8008C468_0 *)arg0)->unk_A2 &= 0xFFFE;
        if (((S_8008C468_1 *)arg3)->unk_1C & 0x100000) {
#ifndef NON_MATCHING
            register u8 *page_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
#endif
            u8 *dead_v1;

#ifndef NON_MATCHING
            page_v0 = (u8 *)0x800E0000;
            ASM_KEEP(page_v0);   /* MATCH pin: load-bearing for the whole function shape */
#endif
            dead_v1 = (*(u8 * volatile *)((u8 *)arg2 + 0x2C));
#ifndef NON_MATCHING
            return func_8008C4C8(arg0, page_v0 - 0x2F20);
#else
            return func_8008C4C8(arg0, D_800DD0E0);
#endif
        }
        if ((*(u8 * *)((u8 *)arg2 + 0x2C)) != D_800DD050) {
            register void *call_arg ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */

            call_arg = arg2;
            (*(u8 * *)((u8 *)call_arg + 0x2C)) = D_800DD050;
            func_80048A44(call_arg, D_800DD050[((D_80083228 + ((S_8008C468_1 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0, 1);
        }
    }
}
