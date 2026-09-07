#include "common.h"

#define FIELD(p, t, o) (*(t *)((u8 *)(p) + (o)))

extern s32 func_8003DA40(s32, void *, s16 *, s16);
extern void func_80047454(void *);
extern void func_800A4398(s32);
extern void func_8016FA38() __attribute__((noreturn));
extern void func_8016FAA8() __attribute__((noreturn));

extern s32 D_800803D4[3];

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

static const u32 bank_words[] __asm__("func_8127B000")
    __attribute__((section(".text.func_8127B000"), aligned(4))) = {
    0x8016FF84, 0x8017012C, 0x801708C0, 0x801708C0,
    0x801708C0, 0x801708E8, 0x80170894, 0x80170894,
    0x80170894, 0x80170894, 0x80170894, 0x801708E8,
    0x801708E8, 0x80170884, 0x801715D0, 0x80171814,
    0x8017185C, 0x8017189C, 0x8017193C, 0x801719A8,
    0x80171A10, 0x80171A30, 0x80171AC4, 0x00000000,
    0x80171680, 0x80171678, 0x80171670, 0x80171688,
    0x8017162C, 0x80171624, 0x8017161C, 0x00000000,
    0x80171F20, 0x80171F90, 0x80171FA8, 0x80171FD4,
    0x80172250, 0x801722C0,
};

#define BODY_NAME func_8127B098
#else
#define BODY_NAME func_8127B000
#endif

void BODY_NAME(void *arg0, void *arg1, void *arg2)
    __attribute__((section(".text.func_8127B000")));
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
    if (func_8003DA40(FIELD(callee_part, s32, 8), callee_part, pos,
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
            func_8016FA38(value);
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
            func_800A4398(0x709);
        }
    }

    if (FIELD(root, s16, 0xB6) == 2) {
        value = FIELD(part, s8, 4);
        if (value < 8) {
            register s32 tail_value ASM_REG("$3") = 7 - value;

            ASM_TAILSLOT_PIN(tail_value);
            func_8016FAA8(value);
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
            func_800A4398(0x709);
        }
    }

    func_80047454(dst);
    if (FIELD(owner, u16, 0x1E) & 0x8000) {
        FIELD(root, u16, -2) |= 0x8000;
        D_800803D4[0] |= 0x8000;
    }
}

#ifdef __mips__
__asm__(
    ".globl func_8127B000\n"
    ".type func_8127B000,@function\n"
    ".size func_8127B000,848\n");
#endif
