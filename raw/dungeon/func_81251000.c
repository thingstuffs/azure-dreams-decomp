#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern s32 func_8003DE58(s32, void *, s16 *, s16);
extern void func_800478B8(void *);
extern void func_800A56E0(s32);
extern void func_80170A38() __attribute__((noreturn));
extern void func_80170AA8() __attribute__((noreturn));

extern s32 D_800814A0[3];

#ifdef __mips__
extern void func_80170F84(void);
extern void func_8017112C(void);
extern void func_801718C0(void);
extern void func_801718E8(void);
extern void func_80171894(void);
extern void func_80171884(void);
extern void func_801725D0(void);
extern void func_80172814(void);
extern void func_8017285C(void);
extern void func_8017289C(void);
extern void func_8017293C(void);
extern void func_801729A8(void);
extern void func_80172A10(void);
extern void func_80172A30(void);
extern void func_80172AC4(void);
extern void func_80172680(void);
extern void func_80172678(void);
extern void func_80172670(void);
extern void func_80172688(void);
extern void func_8017262C(void);
extern void func_80172624(void);
extern void func_8017261C(void);
extern void func_80172F20(void);
extern void func_80172F90(void);
extern void func_80172FA8(void);
extern void func_80172FD4(void);
extern void func_80173250(void);
extern void func_801732C0(void);

static void (*const bank_table[])(void)
    __asm__("func_81251000") __attribute__((section(".text.func_81251000"))) = {
    func_80170F84, func_8017112C,
    func_801718C0, func_801718C0, func_801718C0,
    func_801718E8,
    func_80171894, func_80171894, func_80171894, func_80171894,
    func_80171894,
    func_801718E8, func_801718E8,
    func_80171884,
    func_801725D0, func_80172814, func_8017285C, func_8017289C,
    func_8017293C, func_801729A8, func_80172A10, func_80172A30,
    func_80172AC4,
    0,
    func_80172680, func_80172678, func_80172670, func_80172688,
    func_8017262C, func_80172624, func_8017261C,
    0,
    func_80172F20, func_80172F90, func_80172FA8, func_80172FD4,
    func_80173250, func_801732C0,
};

#define BODY_NAME func_81251098
#else
#define BODY_NAME func_81251000
#endif

void BODY_NAME(void *arg0, void *arg1, void *arg2)
    __attribute__((section(".text.func_81251000")));
void BODY_NAME(void *arg0, void *arg1, void *arg2)
{
    s16 pos[3];
    register void *root ASM_REG("$19") = arg0;
    register void *out ASM_REG("$17") = arg1;
    register void *dst ASM_REG("$16") = arg2;
    register void *owner ASM_REG("$20");
    register void *part ASM_REG("$18");
    void *copy;
    void *callee_part;
    s8 value;

    owner = FIELD(root, void *, 0xAC);
    part = FIELD(owner, void *, 0xC);
    copy = FIELD(owner, void *, 8);

    if (!(FIELD(part, u16, 0x14) & 0x80)) {
        FIELD(dst, u16, 0x14) &= 0xFF7F;
    }

    FIELD(out, u16, 2) = FIELD(copy, u16, 2);
    FIELD(out, u16, 6) = FIELD(copy, u16, 6);
    FIELD(out, u16, 0xA) = FIELD(copy, u16, 0xA);

    callee_part = FIELD(owner, void *, 0xC);
    if (func_8003DE58(FIELD(callee_part, s32, 8), callee_part, pos,
                      FIELD(root, s16, 0xB6)) != 0) {
        FIELD(out, u16, 2) +=
            (pos[0] + FIELD(root, s16, 0xB0)) / 2;
        FIELD(out, u16, 6) +=
            (pos[1] + FIELD(root, s16, 0xB2)) / 2;
        FIELD(out, u16, 0xA) +=
            (pos[2] + FIELD(root, s16, 0xB4)) / 2;
        FIELD(root, s16, 0xB0) = pos[0];
        FIELD(root, s16, 0xB2) = pos[1];
        FIELD(root, s16, 0xB4) = pos[2];
    }

    copy = FIELD(dst, void *, 8);
    FIELD(dst, u16, 0x1C) = FIELD(part, u16, 0x1C);
    FIELD(dst, u16, 0x1E) = FIELD(part, u16, 0x1E);
    FIELD(dst, u16, 0x14) = FIELD(part, u16, 0x14);
    FIELD(copy, u8, 1) &= 0xFE;

    if (FIELD(root, s16, 0xB6) == 1) {
        value = FIELD(part, s8, 4);
        if (value < 8) {
            register s32 tail_value ASM_REG("$2") = value * 7;

            ASM_TAILSLOT_PIN(tail_value);
            func_80170A38(value);
            return;
        }
        ASM_SCHED_BARRIER();
        {
            register s32 color ASM_REG("$2") =
                ((15 - value) * 14) + 0x20;

            FIELD(dst, s8, 0xE) = color;
            FIELD(dst, s8, 0xD) = color;
            FIELD(dst, s8, 0xC) = color;
        }
        if (!(FIELD(part, u16, 0x14) & 0x8000) &&
            FIELD(part, u16, 4) == 0x10C) {
            func_800A56E0(0x709);
        }
    }

    if (FIELD(root, s16, 0xB6) == 2) {
        value = FIELD(part, s8, 4);
        if (value < 8) {
            register s32 tail_value ASM_REG("$3") = 7 - value;

            ASM_TAILSLOT_PIN(tail_value);
            func_80170AA8(value);
            return;
        }
        ASM_SCHED_BARRIER();
        {
            register s32 color ASM_REG("$2") =
                ((value - 8) * 14) + 0x20;

            FIELD(dst, s8, 0xE) = color;
            FIELD(dst, s8, 0xD) = color;
            FIELD(dst, s8, 0xC) = color;
        }
        if (!(FIELD(part, u16, 0x14) & 0x8000) &&
            FIELD(part, u16, 4) == 0x104) {
            func_800A56E0(0x709);
        }
    }

    func_800478B8(dst);
    if (FIELD(owner, u16, 0x1E) & 0x8000) {
        FIELD(root, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

#ifdef __mips__
__asm__(
    ".globl func_81251000\n"
    ".type func_81251000,@function\n"
    ".size func_81251000,848\n");
#endif
