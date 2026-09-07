#include "common.h"

typedef struct S_80173734_0 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 unk_48;
    u8 pad_49[0x17];
    void * unk_60;
    u8 pad_64[0x6];
    u16 unk_6A;
    u8 pad_6C[0x1];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x10];
    u8 unk_84;
    u8 unk_85;
    u8 pad_86[0x2];
    s16 unk_88;
} S_80173734_0;   /* arg3 in func_80173734 */

typedef struct S_80173734_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80173734_1;   /* flags in func_80173734 */

typedef struct S_80173734_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80173734_2;   /* arg2 in func_80173734 */

typedef struct S_80173734_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
    s16 unk_AC;
} S_80173734_3;   /* arg0 in func_80173734 */

typedef struct S_80173734_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80173734_4_pre;   /* the 0x14 bytes before ((S_80173734_0 *)arg3)->unk_60 in func_80173734, addressed as ((S_80173734_0 *)arg3)->unk_60[-1] */


#define arg0 in0
#define arg1 in1
#define arg2 in2
#define arg3 in3

extern void func_8009C12C(void *, void *, s16, s16);
extern void func_8009C93C(void *, void *, s16, s16, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A0134(void *, void *);
extern void *func_800A04F0(void *, u8, u8, s16);
extern void *func_800A05A4(void *, u8, u8, s16, s32);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, void *);
extern void func_800C78A0(void *, s32, s32, s16, s32, s32);
extern void func_800C7930(void *, s32, s32, s32);

extern s32 D_80083460;
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];

s32 func_80173734(void *in0, s32 in1, void *in2, void *in3)
{
    void *initial;
    s32 *flags = &D_80083460;
    s32 result = 0;
    s32 count;
    s32 xoff;
    s32 yoff;
    u8 old_x;
    u8 old_y;

    ((S_80173734_0 *)arg3)->unk_71 &= 0x7F;
    if (((S_80173734_1 *)flags)->unk_02 & 0x2000) {
        return -1;
    }

    initial = func_800A04F0(arg3, ((S_80173734_2 *)arg2)->unk_24,
                            ((S_80173734_2 *)arg2)->unk_25,
                            ((S_80173734_0 *)arg3)->unk_2A);
    if ((func_800A2CB8(arg3, initial) << 16) == 0) {
        return 0;
    }
    if (((S_80173734_1 *)flags)->unk_02 & 0x2000) {
        return -1;
    }
    if (!(((S_80173734_0 *)arg3)->unk_46 & 0x8000) &&
        (((S_80173734_1 *)flags)->unk_02 & 8)) {
        return -1;
    }
    if ((u16)(-func_800A0134(initial, arg3) + 0x40) >= 0x81) {
        goto done;
    }

    result = 1;
    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }
    func_800C7930((u8 *)arg3 - 0x20, arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 16) == 0) {
        goto ready;
    }
    return -1;

ready:

    ((S_80173734_3 *)arg0)->unk_9B = 0;
    ((S_80173734_3 *)arg0)->unk_8C = 0;
    ((S_80173734_3 *)arg0)->unk_9A = 0x11;

    switch (((S_80173734_0 *)arg3)->unk_48) {
    case 13:
        ((S_80173734_0 *)arg3)->unk_84 = 0x78;
        ((S_80173734_0 *)arg3)->unk_85 = 8;
        break;
    case 14:
        ((S_80173734_0 *)arg3)->unk_84 = 0x70;
        ((S_80173734_0 *)arg3)->unk_85 = 2;
        break;
    case 15:
        ((S_80173734_0 *)arg3)->unk_84 = 0x74;
        ((S_80173734_0 *)arg3)->unk_85 = result;
        break;
    }

    ((S_80173734_0 *)arg3)->unk_6D--;
    if (((S_80173734_0 *)arg3)->unk_48 != 15) {
        goto not_fifteen;
    }

    ((S_80173734_0 *)arg3)->unk_60 =
        func_800A05A4(arg3, ((S_80173734_2 *)arg2)->unk_24,
                      ((S_80173734_2 *)arg2)->unk_25, ((S_80173734_0 *)arg3)->unk_2A, 10);
    ((S_80173734_3 *)arg0)->unk_AC = 0;
    if (((S_80173734_0 *)arg3)->unk_60 == 0) {
        goto initial_null;
    }

    {
        s16 hit = func_8009FD40(
            ((S_80173734_4_pre *)(((S_80173734_0 *)arg3)->unk_60))[-1].unk_00, arg2);
        ((S_80173734_3 *)arg0)->unk_AA = hit;
        func_8009C93C(arg3, arg2, ((S_80173734_0 *)arg3)->unk_2A, hit,
                      ((S_80173734_0 *)arg3)->unk_60);
    }

    if (((S_80173734_0 *)arg3)->unk_14 & 0x04000000) {
        count = 10;
        old_x = ((S_80173734_2 *)arg2)->unk_24;
        old_y = ((S_80173734_2 *)arg2)->unk_25;

loop:
        xoff = ((S_80173734_0 *)arg3)->unk_72;
        yoff = ((S_80173734_0 *)arg3)->unk_73;
        func_8009C12C(arg3, arg2, ((S_80173734_0 *)arg3)->unk_2A,
                      ((S_80173734_3 *)arg0)->unk_AA);
        count -= ((S_80173734_3 *)arg0)->unk_AA;
        if (count == 0) {
            goto restore_coords;
        }

        ((S_80173734_2 *)arg2)->unk_24 = xoff;
        ((S_80173734_2 *)arg2)->unk_25 = yoff;
        ((S_80173734_0 *)arg3)->unk_60 =
            func_800A05A4(arg3, ((S_80173734_2 *)arg2)->unk_24,
                          ((S_80173734_2 *)arg2)->unk_25,
                          ((S_80173734_0 *)arg3)->unk_2A, (s16)count);
        if (((S_80173734_0 *)arg3)->unk_60 == 0) {
            goto loop_null;
        }

        ((S_80173734_2 *)arg2)->unk_24 = old_x;
        ((S_80173734_2 *)arg2)->unk_25 = old_y;
        {
            s16 hit = func_8009FD40(
                ((S_80173734_4_pre *)(((S_80173734_0 *)arg3)->unk_60))[-1].unk_00, arg2);
            ((S_80173734_3 *)arg0)->unk_AA = hit;
            func_8009C93C(arg3, arg2, ((S_80173734_0 *)arg3)->unk_2A, hit,
                          ((S_80173734_0 *)arg3)->unk_60);
        }
        if (((S_80173734_0 *)arg3)->unk_14 & 0x04000000) {
            goto loop;
        }
        goto restore_coords;
    }
    goto render;

loop_null:
    func_8009C93C(arg3, arg2, ((S_80173734_0 *)arg3)->unk_2A, 1, 0);
    ((S_80173734_3 *)arg0)->unk_AA = 1;

restore_coords:
    ((S_80173734_2 *)arg2)->unk_24 = old_x;
    ((S_80173734_2 *)arg2)->unk_25 = old_y;
    goto render;

initial_null:
    func_8009C93C(arg3, arg2, ((S_80173734_0 *)arg3)->unk_2A, 1, 0);
    ((S_80173734_3 *)arg0)->unk_AA = 1;

render:
    {
        u32 index = (((S_80173734_0 *)arg3)->unk_6A >> 8) & 0xE;
        func_800C78A0(
            (u8 *)arg3 - 0x20,
            (((S_80173734_2 *)arg2)->unk_24 << 6) +
                ((s16)*(u16 *)((u8 *)D_800DCEAC + index) >> 1) + 0x20,
            (((S_80173734_2 *)arg2)->unk_25 << 6) +
                ((s16)*(u16 *)((u8 *)D_800DCEBC + index) >> 1) + 0x20,
            ((S_80173734_0 *)arg3)->unk_88, 8, 0x300);
    }
    goto done;

not_fifteen:
    func_8009C93C(arg3, arg2, ((S_80173734_0 *)arg3)->unk_2A, 1, 0);
    ((S_80173734_3 *)arg0)->unk_AA = 1;

done:
    return result;
}
