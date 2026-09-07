#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern void func_80047784(void *, s16, s16);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);
extern void func_80175AF4(void *, void *, void *);
extern s32 func_801761AC(void *);
extern s32 func_80176258(void *);
extern void func_801762A4(s32, void *);
extern void func_80176330(s32, void *);
extern void func_801763CC(s32, void *);

extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80171094;
extern u8 D_80176460[8];

void func_80174764(void *arg0, void *arg1, void *arg2, void *arg3)
{
    u16 flags;
    u16 timer;
    void *target;

    switch (FIELD(arg0, u8, 0x9B)) {
    case 0:
        flags = FIELD(arg2, u16, 0x14);
        if (flags & 0x8000) {
            FIELD(arg2, u16, 0x14) = flags | 0x6000;
            if (FIELD(arg3, s32, 0x14) & 0x4000) {
                target = FIELD(arg3, void *, 0x60);
                if (!func_80176258(target))
                    goto state0_cc_false;
                func_801763CC(1, FIELD(arg3, void *, 0x60));
                goto state0_done;
state0_cc_false:
                func_801763CC(0, FIELD(arg3, void *, 0x60));
                goto state0_done;
            }

            target = FIELD(arg3, void *, 0x60);
            if (FIELD(target, s32, 0x14) & 0x4000) {
                if (!func_801761AC(target))
                    goto state0_330_false;
                func_80176330(1, FIELD(arg3, void *, 0x60));
                goto state0_done;
state0_330_false:
                func_80176330(0, FIELD(arg3, void *, 0x60));
                goto state0_done;
            }
            func_801761AC(target);
state0_done:
            FIELD(arg0, u8, 0x9B) = 2;
            return;
        }

        if (FIELD(arg2, s8, 4) == 1) {
            if (!(flags & 0x1000)) {
                if (!(flags & 0x6000)) {
                    break;
                }
            }
        } else if (!(flags & 0x6000)) {
            break;
        }

        func_80175AF4(arg0, arg1, arg2);
        if (FIELD(arg3, s32, 0x14) & 0x4000) {
            func_801762A4(1, arg3);
        } else if (FIELD(FIELD(arg3, void *, 0x60), s32, 0x14) & 0x4000) {
            func_801762A4(0, arg3);
        }
        func_800A56E0(0x708);
        timer = 0x20;
        FIELD(arg0, u16, 0x96) = timer;
        FIELD(arg0, u8, 0x9B)++;
        break;

    case 1:
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if ((timer << 16) == 0 || (FIELD(arg2, u16, 0x14) & 0x8000)) {
            if (FIELD(arg3, s32, 0x14) & 0x4000) {
                target = FIELD(arg3, void *, 0x60);
                if (!func_80176258(target))
                    goto state1_cc_false;
                func_801763CC(1, FIELD(arg3, void *, 0x60));
                goto state1_done;
state1_cc_false:
                func_801763CC(0, FIELD(arg3, void *, 0x60));
                goto state1_done;
            } else {
                target = FIELD(arg3, void *, 0x60);
                if (FIELD(target, s32, 0x14) & 0x4000) {
                    if (!func_801761AC(target))
                        goto state1_330_false;
                    func_80176330(1, FIELD(arg3, void *, 0x60));
                    goto state1_done;
state1_330_false:
                    func_80176330(0, FIELD(arg3, void *, 0x60));
                    goto state1_done;
                } else {
                    func_801761AC(target);
                }
            }
state1_done:
            FIELD(arg0, u16, 0x96) = 4;
            FIELD(arg0, u8, 0x9B)++;
        }
        break;

    case 2:
        timer = FIELD(arg0, u16, 0x96) - 1;
        FIELD(arg0, u16, 0x96) = timer;
        if ((timer << 16) == 0 || (FIELD(arg2, u16, 0x14) & 0xE000)) {
            func_800AD594(arg3, 0x400);
            func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
            FIELD(arg0, void *, 0x8C) = &D_80171094;
            D_8008346C = 0;
            FIELD(arg3, u16, 0x46) &= 0x7FFF;
        }
        break;
    }

    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        s32 index;

        FIELD(arg2, void *, 0x2C) = D_80176460;
        index = (D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9;
        func_80047784(arg2, D_80176460[index & 7], 0);
        FIELD(arg0, u16, 0x98) &= 0xFFF7;
    }
}
