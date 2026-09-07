#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((u8 *)(obj) + (offset)))
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

    FIELD(arg3, u8, 0x71) &= 0x7F;
    if (FIELD(flags, u16, 2) & 0x2000) {
        return -1;
    }

    initial = func_800A04F0(arg3, FIELD(arg2, u8, 0x24),
                            FIELD(arg2, u8, 0x25),
                            FIELD(arg3, s16, 0x2A));
    if ((func_800A2CB8(arg3, initial) << 16) == 0) {
        return 0;
    }
    if (FIELD(flags, u16, 2) & 0x2000) {
        return -1;
    }
    if (!(FIELD(arg3, u16, 0x46) & 0x8000) &&
        (FIELD(flags, u16, 2) & 8)) {
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

    FIELD(arg0, u8, 0x9B) = 0;
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(arg0, u8, 0x9A) = 0x11;

    switch (FIELD(arg3, u8, 0x48)) {
    case 13:
        FIELD(arg3, u8, 0x84) = 0x78;
        FIELD(arg3, u8, 0x85) = 8;
        break;
    case 14:
        FIELD(arg3, u8, 0x84) = 0x70;
        FIELD(arg3, u8, 0x85) = 2;
        break;
    case 15:
        FIELD(arg3, u8, 0x84) = 0x74;
        FIELD(arg3, u8, 0x85) = result;
        break;
    }

    FIELD(arg3, u8, 0x6D)--;
    if (FIELD(arg3, u8, 0x48) != 15) {
        goto not_fifteen;
    }

    FIELD(arg3, void *, 0x60) =
        func_800A05A4(arg3, FIELD(arg2, u8, 0x24),
                      FIELD(arg2, u8, 0x25), FIELD(arg3, s16, 0x2A), 10);
    FIELD(arg0, s16, 0xAC) = 0;
    if (FIELD(arg3, void *, 0x60) == 0) {
        goto initial_null;
    }

    {
        s16 hit = func_8009FD40(
            FIELD(FIELD(arg3, void *, 0x60), void *, -0x14), arg2);
        FIELD(arg0, s16, 0xAA) = hit;
        func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), hit,
                      FIELD(arg3, void *, 0x60));
    }

    if (FIELD(arg3, u32, 0x14) & 0x04000000) {
        count = 10;
        old_x = FIELD(arg2, u8, 0x24);
        old_y = FIELD(arg2, u8, 0x25);

loop:
        xoff = FIELD(arg3, s8, 0x72);
        yoff = FIELD(arg3, s8, 0x73);
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A),
                      FIELD(arg0, s16, 0xAA));
        count -= FIELD(arg0, s16, 0xAA);
        if (count == 0) {
            goto restore_coords;
        }

        FIELD(arg2, u8, 0x24) = xoff;
        FIELD(arg2, u8, 0x25) = yoff;
        FIELD(arg3, void *, 0x60) =
            func_800A05A4(arg3, FIELD(arg2, u8, 0x24),
                          FIELD(arg2, u8, 0x25),
                          FIELD(arg3, s16, 0x2A), (s16)count);
        if (FIELD(arg3, void *, 0x60) == 0) {
            goto loop_null;
        }

        FIELD(arg2, u8, 0x24) = old_x;
        FIELD(arg2, u8, 0x25) = old_y;
        {
            s16 hit = func_8009FD40(
                FIELD(FIELD(arg3, void *, 0x60), void *, -0x14), arg2);
            FIELD(arg0, s16, 0xAA) = hit;
            func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), hit,
                          FIELD(arg3, void *, 0x60));
        }
        if (FIELD(arg3, u32, 0x14) & 0x04000000) {
            goto loop;
        }
        goto restore_coords;
    }
    goto render;

loop_null:
    func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1, 0);
    FIELD(arg0, s16, 0xAA) = 1;

restore_coords:
    FIELD(arg2, u8, 0x24) = old_x;
    FIELD(arg2, u8, 0x25) = old_y;
    goto render;

initial_null:
    func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1, 0);
    FIELD(arg0, s16, 0xAA) = 1;

render:
    {
        u32 index = (FIELD(arg3, u16, 0x6A) >> 8) & 0xE;
        func_800C78A0(
            (u8 *)arg3 - 0x20,
            (FIELD(arg2, u8, 0x24) << 6) +
                ((s16)*(u16 *)((u8 *)D_800DCEAC + index) >> 1) + 0x20,
            (FIELD(arg2, u8, 0x25) << 6) +
                ((s16)*(u16 *)((u8 *)D_800DCEBC + index) >> 1) + 0x20,
            FIELD(arg3, s16, 0x88), 8, 0x300);
    }
    goto done;

not_fifteen:
    func_8009C93C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1, 0);
    FIELD(arg0, s16, 0xAA) = 1;

done:
    return result;
}
