#include "common.h"

typedef struct S_80171F90_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80171F90_0;   /* arg3 in func_80171F90 */

typedef struct S_80171F90_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    s8 unk_9B;
} S_80171F90_1;   /* arg0 in func_80171F90 */



extern s32 func_800A2B5C();
extern void func_800C7930();
extern void func_80047784();
extern void func_8009C93C();
extern void func_80172050(void) __attribute__((noreturn));

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_8017386C[];

void func_80171F90(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    ((S_80171F90_0 *)arg3)->unk_71 &= 0x7F;

    if (!(D_80083462 & 0x2000) &&
        ((func_800A2B5C(arg3) << 0x10) == 0) &&
        (func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300),
         ((func_800A2B5C(arg3) << 0x10) == 0))) {
        ((S_80171F90_1 *)arg0)->unk_8C = 0;
        ((S_80171F90_1 *)arg0)->unk_9B = 0;

        if (((S_80171F90_1 *)arg0)->unk_98 & 0x8000) {
            ((S_80171F90_1 *)arg0)->unk_9A = 0x17;
            ((S_80171F90_0 *)arg3)->unk_84 = 0x10;
            ((S_80171F90_0 *)arg3)->unk_85 = 0x10;
            func_80172050();
        }

        ((S_80171F90_1 *)arg0)->unk_9A = 0x11;
        ((S_80171F90_0 *)arg3)->unk_84 = 0x7C;
        ((S_80171F90_0 *)arg3)->unk_85 = 0;
        ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = D_8017386C;
        func_80047784(arg2,
                      D_8017386C[((D_80083228 + ((S_80171F90_0 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                      0);
        ((S_80171F90_0 *)arg3)->unk_6D--;

        if (((S_80171F90_1 *)arg0)->unk_9A == 0x11) {
            func_8009C93C(arg3, arg2, ((S_80171F90_0 *)arg3)->unk_2A, 1, 0);
        }
    }
}
