#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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

    state = FIELD(arg0, u8, 0x9B);
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
    FIELD(arg0, s16, 0x96) = 4;
    FIELD(arg0, u8, 0x9B)++;
    if (FIELD(arg3, u8, 0x28) == 0) {
        goto reset_and_call;
    }
    if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto end;
    }
    FIELD(arg0, s16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B) = 3;
    goto end;

state_1:
    {
        s16 count;

        count = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, s16, 0x96) = count;
        if (count > 0) {
            FIELD(arg1, s32, 0xC) =
                *(s16 *)((u8 *)&D_8006CCD8 +
                    ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 19;
            FIELD(arg1, s32, 0x10) =
                *(s16 *)((u8 *)&D_8006CCE8 +
                    ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 19;
            goto end;
        }
        if (count != 0) {
            goto end;
        }
        FIELD(arg1, s32, 0xC) =
            *(s16 *)((u8 *)&D_8006CCD8 +
                ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 18;
        FIELD(arg1, s32, 0x10) =
            *(s16 *)((u8 *)&D_8006CCE8 +
                ((FIELD(arg3, u16, 0x6A) >> 8) & 0xE)) << 18;
        FIELD(arg0, s16, 0x96) = 6;
        FIELD(arg0, u8, 0x9B)++;
        goto end;
    }

state_2:
    if (FIELD(arg3, u8, 0x28) != 0) {
        goto state_2_main;
    }
reset_and_call:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800AAA54(arg0, arg1, arg2, D_801759C8);
    goto end;

state_2_main:
    {
        s16 divisor;
        s32 origin;
        u16 old_count;

        divisor = FIELD(arg0, s16, 0x96);
        if (divisor != 0) {
            FIELD(arg1, s32, 0xC) =
                (((FIELD(arg2, u8, 0x24) << 6) - ({ FIELD(arg1, s16, 2) - 0x20; })) << 16) / divisor;
            origin = FIELD(arg1, s16, 6) - 0x20;
            FIELD(arg1, s32, 0x10) =
                (((FIELD(arg2, u8, 0x25) << 6) - origin) << 16) /
                FIELD(arg0, s16, 0x96);
        }
        old_count = FIELD(arg0, u16, 0x96);
        FIELD(arg0, s16, 0x96) = old_count - 1;
        if ((s32)(old_count << 16) > 0) {
            goto end;
        }
        FIELD(arg1, s32, 0x14) = 0;
        FIELD(arg1, s32, 0x10) = 0;
        FIELD(arg1, s32, 0xC) = 0;
        FIELD(arg0, u8, 0x9B)++;
        goto end;
    }

state_3:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0xC) = 0;
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    if (FIELD(arg2, void *, 0x2C) == D_80175998) {
        u8 *table;

        table = D_80175988;
        FIELD(arg2, void *, 0x2C) = table;
        func_80047784(arg2,
            table[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
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
    FIELD(arg0, void *, 0x8C) = &D_801717F4;

end:
    return;
}
