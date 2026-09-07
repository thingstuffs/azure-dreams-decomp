#include "common.h"


#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, s32);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_80174218(void *, void *, void *, void *);

extern void *D_800814A8;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80171400[];
extern u8 D_80175180[];
extern u8 D_80175188[];

void func_80173ED8(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register void *p0 ASM_REG("$18");
    register void *p1 ASM_REG("$19");
    register void *p2 ASM_REG("$17");
    register void *global;
    register void *p3 ASM_REG("$16");
    u8 state;
    register u8 *effect ASM_REG("$5");
    s32 index;

    p0 = arg0;
    p1 = arg1;
    p2 = arg2;
#define arg0 p0
#define arg1 p1
#define arg2 p2
    ASM_KEEP_NV(p0);
    ASM_KEEP_NV(p1);
    ASM_KEEP_NV(p2);

    state = FIELD(arg0, u8, 0x9B);
    p3 = arg3;
#define arg3 p3
    switch (state) {
    case 0:
    {
        register u8 *counter ASM_REG("$3");

        if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
            return;
        }

        counter = (u8 *)&D_80083460;
#ifndef __mips__
        ASM_KEEP_NV(counter);
#endif
        FIELD(counter, u16, 0xA)--;
        effect = D_80175188;
        FIELD(arg2, void *, 0x2C) = effect;
        index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
        func_80047784(arg2, effect[index & 7], 0);
        goto increment_state;
    }

    case 1:
        if (FIELD(arg3, u8, 0x25) != 0) {
            register u8 *counter;

            effect = D_80175180;
            FIELD(arg2, void *, 0x2C) = effect;
            index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
            func_80047784(arg2, effect[index & 7], 0);
            FIELD(arg3, u32, 0x1C) |= 0x40000;
            counter = (u8 *)&D_80083460;
#ifndef __mips__
            ASM_KEEP_NV(counter);
#endif
            FIELD(counter, u16, 0xA)++;
            goto increment_state;
        }

        global = &D_80083460;
        ASM_KEEP_NV(global);
        if (FIELD(global, u16, 2) & 0x1000) {
            return;
        }

        if ((FIELD(arg3, s16, 0x64) != 0) &&
            func_800AA6B4(arg0, arg1, arg2, 0)) {
            return;
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            return;
        }

        if (FIELD(arg3, u32, 0x1C) & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (FIELD(arg3, u32, 0x1C) & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            FIELD(arg0, s16, 0xA8) = 0;
            func_80174218(arg0, arg1, arg2, arg3);
            return;
        }

        if (FIELD(arg3, s8, 0x6D) == 0) {
            return;
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            void *owner = D_800814A8;

            if ((func_8009A180(arg3,
                    (u8 *)FIELD(owner, void *, 0x58) + 0x20) << 16) != 0) {
                return;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if (FIELD(arg3, u8, 0x25) == 0) {
            return;
        }

        effect = D_80175180;
        FIELD(arg2, void *, 0x2C) = effect;
        index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
        func_80047784(arg2, effect[index & 7], 0);
        FIELD(arg3, u32, 0x1C) |= 0x40000;
        FIELD(global, u16, 0xA)++;

increment_state:
        FIELD(arg0, u8, 0x9B)++;
        return;

    case 2:
    {
        register u8 *counter ASM_REG("$3");

        if ((FIELD(arg2, u16, 0x14) & 0xE000) == 0) {
            return;
        }

        counter = (u8 *)&D_80083460;
#ifndef __mips__
        ASM_KEEP_NV(counter);
#endif
        FIELD(counter, u16, 0xA)--;
        FIELD(arg3, u32, 0x1C) &= ~0x208;
        FIELD(arg0, void *, 0x8C) = D_80171400;
        return;
    }

    default:
        return;
    }
}
