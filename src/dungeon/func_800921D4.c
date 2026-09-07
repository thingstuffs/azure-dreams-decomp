#include "common.h"

typedef struct S_80097934_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80097934_0;   /* arg0 in func_80097934 */

typedef struct S_80097934_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    void * unk_2C;
} S_80097934_1;   /* arg2 in func_80097934 */

typedef struct S_80097934_2 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x1];
    s16 unk_2A;
} S_80097934_2;   /* arg3 in func_80097934 */

typedef struct S_80097934_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80097934_3;   /* arg1 in func_80097934 */



extern void func_8003DB94(void *arg0, void *arg1, s32 arg2);
extern void func_80042B68(void *arg0, s32 arg1);
extern void func_8008CBD4(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_80096384(void);
extern void func_800AD4D0(void *arg0);

extern s16 D_80083228[5];
extern s32 D_80083460[5];
extern void *D_800DD274[8];

void func_80097934(S_80097934_0 *arg0, S_80097934_3 *arg1, S_80097934_1 *arg2, void *arg3)
{
    s32 value;
    s32 *global;

    if (arg0->unk_9B == 0) {
        func_800AD4D0(arg3);
        arg0->unk_9B++;
    }

    if (arg2->unk_14 & 0xE000) {
        arg2->unk_2C = D_800DD274;
        func_8003DB94(
            arg2,
            D_800DD274[
                ((D_80083228[0] + ((S_80097934_2 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);

        global = D_80083460;
        value = global[4];
        if (value == (u32)((u8 *)arg3 - 0x20)) {
            global[4] = value & 0x7FFFFFFF;
        }

        if (((S_80097934_2 *)arg3)->unk_28 == 0) {
            ((S_80097934_2 *)arg3)->unk_28 = 0;
            arg1->unk_14 = 0;
            arg1->unk_10 = 0;
            arg1->unk_0C = 0;
            func_80042B68(arg3, 10);
            func_8008CBD4(arg0, arg1, arg2, arg3);
            return;
        }

        arg0->unk_96 = 8;
        arg0->unk_8C = func_80096384;
    }
}
