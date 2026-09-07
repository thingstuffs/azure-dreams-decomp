#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *D_80170838[];

extern void func_80047784(void *, s32, s32);
extern void func_8009C12C(void *, void *, s32, s32);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_8017121C(void *, void *, void *, void *);
extern void func_801714FC(void *, void *, void *, void *);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_801724BC[];
extern u8 D_80175DDC[8];
extern u8 D_80175DE4[8];
extern u8 D_80175DEC[8];

void func_801743C4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_c0, &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5
    };
    s16 timer;
    u8 state;

    state = FIELD(arg0, u8, 0x9B);
    if (state >= 6) {
        goto jt_c4;
    }
    (void)jt_keep;
    goto *D_80170838[state];

jt_c0:
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg1, s32, 0x10) = 0;
    FIELD(arg1, s32, 0x0C) = 0;
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    if (!(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto jt_c4;
    }

jt_c1:
    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((timer != 4) && !(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto jt_c4;
    }
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B)++;
    switch (FIELD(arg3, u8, 0x48)) {
    case 13:
        FIELD(arg2, u8 *, 0x2C) = D_80175DDC;
        func_80047784(arg2,
            D_80175DDC[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        goto jt_c4;
    case 14:
        FIELD(arg2, u8 *, 0x2C) = D_80175DE4;
        func_80047784(arg2,
            D_80175DE4[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        goto jt_c4;
    case 15:
        FIELD(arg2, u8 *, 0x2C) = D_80175DEC;
        func_80047784(arg2,
            D_80175DEC[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, u8, 0x9B) = 5;
        func_800A56E0(0x60C);
        goto jt_c4;
    default:
        goto jt_c4;
    }

jt_c2:
    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((timer == 5) || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        FIELD(arg0, u16, 0x96) = 0;
        FIELD(arg0, u8, 0x9B)++;
    }
    if (FIELD(arg0, s16, 0x96) == 3) {
        func_800A56E0(0x804);
        goto jt_c4;
    }
    goto jt_c4;

jt_c3:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        func_800AD594(arg3, 0x100);
        FIELD(arg0, u8 *, 0x8C) = D_801724BC;
        D_8008346C = 0;
        func_800A4ACC(arg3);
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
    }
    goto jt_c4;

jt_c5:
    timer = FIELD(arg0, u16, 0x96) + 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((timer == 10) || (FIELD(arg2, u16, 0x14) & 0x8000)) {
        FIELD(arg2, u16, 0x14) |= 0x0800;
        func_800A56E0(0x804);
        func_8017121C(arg0, arg1, arg2, arg3);
        func_801714FC(arg0, arg1, arg2, arg3);
    }
    if ((FIELD(arg0, s16, 0x96) == 12) ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A),
            FIELD(arg0, s16, 0xAA));
    }
    if ((FIELD(arg0, s16, 0x96) != 20) &&
        !(FIELD(arg2, u16, 0x14) & 0x8000)) {
        goto jt_c4;
    }
    FIELD(arg2, u16, 0x14) &= 0xF7FF;
    FIELD(arg0, u16, 0x96) = 0;
    FIELD(arg0, u8, 0x9B) = 3;

jt_c4:
    return;
}
