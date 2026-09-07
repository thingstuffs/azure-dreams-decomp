#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct {
    s32 current;
    u8 pad04[0x28];
    s32 previous_owner;
} TownState;

typedef void (*DispatchFn)(void *, void *, void *, s32);

extern TownState D_800834B8;
extern s32 D_80083780[];
extern s32 D_800D0420[];
extern u8 D_800FE488[];

extern s32 D_80090A6C;
extern s32 D_80092698;
extern s32 D_800927EC;
extern s32 D_80092A84;
extern s32 D_80092CD4;
extern s32 D_80092DA8;
extern s32 D_80092ECC;
extern s32 D_80092FF0;
extern s32 D_800930E4;
extern s32 D_80093250;
extern s32 D_80093328;
extern s32 D_800933FC;
extern s32 D_80093638;
extern s32 D_800AA5F8;

extern void func_8008F170(void *, void *);
extern void func_8008F294(void *, void *);
extern void func_8008F664(void *, void *);
extern s32 func_800352FC();
extern s32 func_8009B120(void *);
extern void func_8009C340(void *, void *, void *, s32);
extern void func_800C172C(void);

void func_7FFFE25C(void *arg0, void *arg1, void *arg2, s32 arg3)
{
    TownState *state = &D_800834B8;
    s32 *position = D_80083780;
    s32 *offset = D_800D0420;
    register s32 previous_owner ASM_REG("$23") = state->previous_owner;
    s32 current;
    s32 target;
    s32 flag;

    FIELD(arg2, s32, 0) = D_80083780[0];
    FIELD(arg2, s32, 4) = position[1];
    FIELD(arg2, s32, 8) = position[2] + offset[2];

    func_8008F170(arg2, D_800FE488);
    func_8008F294(arg1, arg2);
    func_8008F664(arg1, arg2);

    target = position[2] + offset[2];
    if (target - FIELD(arg2, s32, 8) >= 0x10) {
        FIELD(arg2, s32, 8) =
            target + FIELD(FIELD(arg1, void *, 0xC), s32, 0x14);
    }

    current = D_800834B8.current;
    flag = 1;

    {
        register void *a0r ASM_REG("$4");
        register void *a1r ASM_REG("$5");
        register void *a2r ASM_REG("$6");
        void *handler;

        if (current == (s32)&D_800930E4 || current == (s32)&D_80093250) {
            ASM_USE2(arg3, arg3);
            a0r = arg0;
            a1r = arg1;
            handler = FIELD(FIELD(arg0, void *, 0x58), void *, 8);
            a2r = arg2;
            goto dispatch;
        }

        if (current == (s32)&D_800AA5F8) {
            ASM_USE2(arg3, arg3);
            a0r = arg0;
            a1r = arg1;
            handler = FIELD(FIELD(arg0, void *, 0x58), void *, 0x14);
            a2r = arg2;
            goto dispatch;
        }

        if (current == (s32)&D_80093328) {
            ASM_USE2(arg3, arg3);
            a0r = arg0;
            a1r = arg1;
            handler = FIELD(FIELD(arg0, void *, 0x58), void *, 0xC);
            a2r = arg2;
            goto dispatch;
        }

        if (current == (s32)&D_80093638) {
            func_8009C340(arg0, arg1, arg2, arg3);
            goto flagcheck;
        }

        if (current == (s32)&D_80092698 || current == (s32)&D_800927EC ||
            current == (s32)&D_80092A84 || current == (s32)&D_80092FF0 ||
            current == (s32)&D_80092CD4 || current == (s32)&D_80092DA8 ||
            current == (s32)&D_80092ECC || current == (s32)&D_800933FC ||
            current == (s32)&D_80090A6C || func_800352FC() != 0) {
            if (previous_owner == (s32)arg1) {
                goto skip;
            }
        }

        a0r = arg0;
        a1r = arg1;
        handler = FIELD(FIELD(arg0, void *, 0x58), void *, 0x10);
        a2r = arg2;
dispatch:
        ((DispatchFn)handler)(a0r, a1r, a2r, arg3);
        goto flagcheck;
    }

skip:
    flag = 0;
    ASM_KEEP(flag);
flagcheck:
    if (flag != 0 && func_8009B120((u8 *)arg0 + 0x4C) != 0) {
        func_800C172C();
    }
}
