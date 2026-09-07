#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct Copy24 {
    s32 word[6];
} Copy24;

extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
extern void func_8009C12C(void *, void *, s16, s32);
extern void func_800A2B04(void *, u8, u8);
extern void func_800A4ACC(void *);
extern void func_800A56E0(s32);
extern void func_800AD594(void *, s32);

extern s32 D_80045340;
extern s16 D_80083228;
extern s32 D_8008346C;
extern u8 D_80083498[];
extern u8 D_800D7960[];
extern void *D_800E3DE8;
extern u8 D_80170E54;
extern u8 D_80173CA4[];
extern u8 D_80173CAC[];
extern u8 D_80173CB4[];
extern u8 D_80173CBC[];

void func_80172620(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 state;
    register void *ret ASM_REG("$2");
    void *created;
    void *child;
    void *copy_dst;

    FIELD(arg0, u16, 0x96)--;
    state = FIELD(arg0, u8, 0x9B);
    if (state == 2) {
        goto state_two;
    }
    if (state < 3) {
        if (state == 0) {
            goto state_zero;
        }
        if (state == 1) {
            goto state_one;
        }
        goto done;
    }
    if (state == 3) {
        goto state_three;
    }
    if (state == 0xFF) {
        goto state_ff;
    }
    goto done;

state_zero:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 0xFF;
        FIELD(arg2, u16, 0x14) |= 0x6000;
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        goto done;
    }

    if (rand() & 3) {
        FIELD(arg2, u8 *, 0x2C) = D_80173CBC;
        FIELD(arg0, s32, 0xA4) = 0;
        func_80047784(arg2,
            FIELD(arg2, u8 *, 0x2C)
                [((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, u8, 0x9B) = 3;
        goto done;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80173CA4;
    func_80047784(arg2,
        D_80173CA4[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_one:
    if ((FIELD(arg2, s8, 4) == 2) &&
        (FIELD(arg2, u16, 0x14) & 0x1000)) {
        ret = func_8003FD64(0x112, D_80083498);
        created = ret;
        ASM_KEEP(ret);
        FIELD(arg0, void *, 0xA4) = ret;
        if (created != 0) {
            s32 linked_field;
            s32 child_field;

            func_8004491C(created, &D_80045340);
            FIELD(created, u8 *, 0x10) = D_800D7960;
            copy_dst = FIELD(created, void *, 8);
            *(Copy24 *)copy_dst = *(Copy24 *)arg1;
            FIELD(created, u8, 0xBB) = 0;
            FIELD(created, u16, 0x4A) = FIELD(arg3, u16, 0x2A);

            child = FIELD(created, void *, 0xC);
            linked_field = FIELD(arg2, s32, 0x28);
            FIELD(child, s16, 0x1E) = 0x1000;
            FIELD(child, s16, 0x1C) = 0x1000;
            FIELD(child, s32, 0x28) = linked_field;
            FIELD(child, u16, 0x14) = FIELD(arg2, u16, 0x14);
            FIELD(child, u16, 0x12) = FIELD(arg2, u16, 0x12);
            child_field = FIELD(arg2, s32, 0xC);
            FIELD(child, u8 *, 0x2C) = D_80173CB4;
            FIELD(child, s32, 0xC) = child_field;
            func_80047784(child,
                D_80173CB4[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
        }
    }

    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    FIELD(arg2, u8 *, 0x2C) = D_80173CAC;
    func_80047784(arg2,
        D_80173CAC[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u8, 0x9B)++;
    goto done;

state_two:
    if (FIELD(arg2, u16, 0x14) & 0xE000) {
        void *pending;

        FIELD(arg2, u8 *, 0x2C) = D_80173CBC;
        func_80047784(arg2,
            D_80173CBC[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        pending = FIELD(arg0, void *, 0xA4);
        if (pending != 0) {
            FIELD(pending, u8, 0xBB) = 0xFF;
            FIELD(arg0, s32, 0xA4) = 0;
        }
        FIELD(arg0, u8, 0x9B)++;
    }

state_three:
    if (((FIELD(arg2, s8, 4) == 2) &&
         (FIELD(arg2, u16, 0x14) & 0x1000)) ||
        (FIELD(arg2, u16, 0x14) & 0x8000)) {
        func_800A56E0(0x808);
        func_8009C12C(arg3, arg2, FIELD(arg3, s16, 0x2A), 1);
        FIELD(arg0, u8, 0x9B) = 0xFF;
    }
    goto done;

state_ff:
    if (!(FIELD(arg2, u16, 0x14) & 0xE000)) {
        goto done;
    }
    func_800A2B04(arg1, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25));
    func_800AD594(arg3, 0x180);
    FIELD(arg0, u8 *, 0x8C) = &D_80170E54;
    D_8008346C = 0;
    func_800A4ACC(arg3);
    if (FIELD(arg3, s8, 0x6D) == 0) {
        FIELD(arg3, u16, 0x46) &= 0x7FFF;
    } else {
        D_800E3DE8 = (u8 *)arg3 - 0x20;
    }

done:
    return;
}
