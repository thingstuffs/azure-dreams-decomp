#include "common.h"

typedef struct S_8017380C_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8017380C_0;   /* arg0 in func_8017380C */

typedef struct S_8017380C_1 {
    u8 pad_00[0x28];
    u8 unk_28;
    u8 pad_29[0x1];
    s16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
} S_8017380C_1;   /* arg3 in func_8017380C */

typedef struct S_8017380C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8017380C_2;   /* arg2 in func_8017380C */

typedef struct S_8017380C_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8017380C_3;   /* arg1 in func_8017380C */



extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_801717F4;
extern u8 D_80175988[];
extern u8 D_80175998[];
extern u8 D_801759C8[];

extern void func_80047784(void *, s32, s32);
extern void func_800A2B04(void *, s32, s32);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);

void func_8017380C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;

    state = ((S_8017380C_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto end;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto end;

state_0:
    func_800AD4D0(arg3);
    ((S_8017380C_0 *)arg0)->unk_96.s = 4;
    ((S_8017380C_0 *)arg0)->unk_9B++;
    if (((S_8017380C_1 *)arg3)->unk_28 == 0) {
        goto reset_and_call;
    }
    if (!(((S_8017380C_2 *)arg2)->unk_14 & 0x8000)) {
        goto end;
    }
    ((S_8017380C_0 *)arg0)->unk_96.s = 0;
    ((S_8017380C_0 *)arg0)->unk_9B = 3;
    goto end;

state_1:
    {
        s16 count;

        count = ((S_8017380C_0 *)arg0)->unk_96.u - 1;
        ((S_8017380C_0 *)arg0)->unk_96.s = count;
        if (count > 0) {
            ((S_8017380C_3 *)arg1)->unk_0C =
                *(s16 *)((u8 *)&D_8006CCD8 +
                    ((((S_8017380C_1 *)arg3)->unk_6A >> 8) & 0xE)) << 19;
            ((S_8017380C_3 *)arg1)->unk_10 =
                *(s16 *)((u8 *)&D_8006CCE8 +
                    ((((S_8017380C_1 *)arg3)->unk_6A >> 8) & 0xE)) << 19;
            goto end;
        }
        if (count != 0) {
            goto end;
        }
        ((S_8017380C_3 *)arg1)->unk_0C =
            *(s16 *)((u8 *)&D_8006CCD8 +
                ((((S_8017380C_1 *)arg3)->unk_6A >> 8) & 0xE)) << 18;
        ((S_8017380C_3 *)arg1)->unk_10 =
            *(s16 *)((u8 *)&D_8006CCE8 +
                ((((S_8017380C_1 *)arg3)->unk_6A >> 8) & 0xE)) << 18;
        ((S_8017380C_0 *)arg0)->unk_96.s = 6;
        ((S_8017380C_0 *)arg0)->unk_9B++;
        goto end;
    }

state_2:
    if (((S_8017380C_1 *)arg3)->unk_28 != 0) {
        goto state_2_main;
    }
reset_and_call:
    ((S_8017380C_3 *)arg1)->unk_14 = 0;
    ((S_8017380C_3 *)arg1)->unk_10 = 0;
    ((S_8017380C_3 *)arg1)->unk_0C = 0;
    func_800AAA54(arg0, arg1, arg2, D_801759C8);
    goto end;

state_2_main:
    {
        s16 divisor;
        s32 origin;
        u16 old_count;

        divisor = ((S_8017380C_0 *)arg0)->unk_96.s;
        if (divisor != 0) {
            ((S_8017380C_3 *)arg1)->unk_0C =
                (((((S_8017380C_2 *)arg2)->unk_24 << 6) - ({ ((S_8017380C_3 *)arg1)->unk_02 - 0x20; })) << 16) / divisor;
            origin = ((S_8017380C_3 *)arg1)->unk_06 - 0x20;
            ((S_8017380C_3 *)arg1)->unk_10 =
                (((((S_8017380C_2 *)arg2)->unk_25 << 6) - origin) << 16) /
                ((S_8017380C_0 *)arg0)->unk_96.s;
        }
        old_count = ((S_8017380C_0 *)arg0)->unk_96.u;
        ((S_8017380C_0 *)arg0)->unk_96.s = old_count - 1;
        if ((s32)(old_count << 16) > 0) {
            goto end;
        }
        ((S_8017380C_3 *)arg1)->unk_14 = 0;
        ((S_8017380C_3 *)arg1)->unk_10 = 0;
        ((S_8017380C_3 *)arg1)->unk_0C = 0;
        ((S_8017380C_0 *)arg0)->unk_9B++;
        goto end;
    }

state_3:
    ((S_8017380C_3 *)arg1)->unk_14 = 0;
    ((S_8017380C_3 *)arg1)->unk_10 = 0;
    ((S_8017380C_3 *)arg1)->unk_0C = 0;
    func_800A2B04(arg1, ((S_8017380C_2 *)arg2)->unk_24, ((S_8017380C_2 *)arg2)->unk_25);
    if (((S_8017380C_2 *)arg2)->unk_2C == D_80175998) {
        u8 *table;

        table = D_80175988;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_8017380C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
    {
        s32 *global;
        s32 value;

        global = &D_80083460;
        value = global[4];
        if (value == (s32)((u8 *)arg3 - 0x20)) {
            global[4] = value & 0x7FFFFFFF;
        }
    }
    ((S_8017380C_0 *)arg0)->unk_8C = &D_801717F4;

end:
    return;
}
