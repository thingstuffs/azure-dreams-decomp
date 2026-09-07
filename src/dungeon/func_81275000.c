#include "common.h"

typedef struct S_81275000_0_pre {
    u16 unk_00;
} S_81275000_0_pre;   /* the 0x2 bytes before root in BODY_NAME, addressed as root[-1] */

typedef struct S_81275000_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
    s16 unk_B0;
    s16 unk_B2;
    s16 unk_B4;
    s16 unk_B6;
} S_81275000_0;   /* root in BODY_NAME */

typedef struct S_81275000_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_81275000_1;   /* owner in BODY_NAME */

typedef struct S_81275000_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_81275000_2;   /* part in BODY_NAME */

typedef struct S_81275000_3 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_81275000_3;   /* dst in BODY_NAME */

typedef struct S_81275000_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81275000_4;   /* out in BODY_NAME */

typedef struct S_81275000_5 {
    u8 pad_00[0x1];
    u8 unk_01;
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81275000_5;   /* copy in BODY_NAME */

typedef struct S_81275000_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_81275000_6;   /* callee_part in BODY_NAME */



extern s32 func_8003DE58(s32, void *, s16 *, s16);
extern void func_800478B8(void *);
extern void func_800A56E0(s32);
extern void func_8014CA38() __attribute__((noreturn));
extern void func_8014CAA8() __attribute__((noreturn));

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

static const u32 bank_words[] __asm__("func_81275000")
    __attribute__((section(".text.func_81275000"), aligned(4))) = {
    0x8014CF84, 0x8014D12C, 0x8014D8C0, 0x8014D8C0,
    0x8014D8C0, 0x8014D8E8, 0x8014D894, 0x8014D894,
    0x8014D894, 0x8014D894, 0x8014D894, 0x8014D8E8,
    0x8014D8E8, 0x8014D884, 0x8014E5D0, 0x8014E814,
    0x8014E85C, 0x8014E89C, 0x8014E93C, 0x8014E9A8,
    0x8014EA10, 0x8014EA30, 0x8014EAC4, 0x00000000,
    0x8014E680, 0x8014E678, 0x8014E670, 0x8014E688,
    0x8014E62C, 0x8014E624, 0x8014E61C, 0x00000000,
    0x8014EF20, 0x8014EF90, 0x8014EFA8, 0x8014EFD4,
    0x8014F250, 0x8014F2C0,
};

#define BODY_NAME func_81275098
#else
#define BODY_NAME func_81275000
#endif

void BODY_NAME(void *arg0, void *arg1, void *arg2)
    __attribute__((section(".text.func_81275000")));
void BODY_NAME(void *arg0, void *arg1, void *arg2)
{
    s16 pos[3];
    void *root = arg0;
    register void *out ASM_REG("$17") = arg1;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_81275000_3 *dst = arg2;
    S_81275000_1 *owner;
    register void *part ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    S_81275000_5 *copy;
    S_81275000_6 *callee_part;
    s8 value;

    owner = ((S_81275000_0 *)root)->unk_AC;
    part = owner->unk_0C;
    copy = owner->unk_08;

    if (!(((S_81275000_2 *)part)->unk_14 & 0x80)) {
        dst->unk_14 &= 0xFF7F;
    }

    ((S_81275000_4 *)out)->unk_02 = copy->unk_02;
    ((S_81275000_4 *)out)->unk_06 = copy->unk_06;
    ((S_81275000_4 *)out)->unk_0A = copy->unk_0A;

    callee_part = owner->unk_0C;
    if (func_8003DE58(callee_part->unk_08, callee_part, pos,
                      ((S_81275000_0 *)root)->unk_B6) != 0) {
        ((S_81275000_4 *)out)->unk_02 +=
            (pos[0] + ((S_81275000_0 *)root)->unk_B0) / 2;
        ((S_81275000_4 *)out)->unk_06 +=
            (pos[1] + ((S_81275000_0 *)root)->unk_B2) / 2;
        ((S_81275000_4 *)out)->unk_0A +=
            (pos[2] + ((S_81275000_0 *)root)->unk_B4) / 2;
        ((S_81275000_0 *)root)->unk_B0 = pos[0];
        ((S_81275000_0 *)root)->unk_B2 = pos[1];
        ((S_81275000_0 *)root)->unk_B4 = pos[2];
    }

    copy = dst->unk_08;
    dst->unk_1C = ((S_81275000_2 *)part)->unk_1C;
    dst->unk_1E = ((S_81275000_2 *)part)->unk_1E;
    dst->unk_14 = ((S_81275000_2 *)part)->unk_14;
    copy->unk_01 &= 0xFE;

    if (((S_81275000_0 *)root)->unk_B6 == 1) {
        value = ((S_81275000_2 *)part)->unk_04.s8;
        if (value < 8) {
            s32 tail_value = value * 7;

            ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail delay-slot contents depend on it */
            func_8014CA38(value);
            return;
        }
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        {
            register s32 color ASM_REG("$2") =
                ((15 - value) * 14) + 0x20;

            dst->unk_0E = color;
            dst->unk_0D = color;
            dst->unk_0C = color;
        }
        if (!(((S_81275000_2 *)part)->unk_14 & 0x8000) &&
            ((S_81275000_2 *)part)->unk_04.u16 == 0x10C) {
            func_800A56E0(0x709);
        }
    }

    if (((S_81275000_0 *)root)->unk_B6 == 2) {
        value = ((S_81275000_2 *)part)->unk_04.s8;
        if (value < 8) {
            register s32 tail_value ASM_REG("$3") = 7 - value;   /* MATCH pin: retail register colouring depends on it */

            ASM_TAILSLOT_PIN(tail_value);   /* MATCH pin: retail delay-slot contents depend on it */
            func_8014CAA8(value);
            return;
        }
        ASM_SCHED_BARRIER();   /* MATCH pin: retail basic-block layout depends on it */
        {
            register s32 color ASM_REG("$2") =
                ((value - 8) * 14) + 0x20;

            dst->unk_0E = color;
            dst->unk_0D = color;
            dst->unk_0C = color;
        }
        if (!(((S_81275000_2 *)part)->unk_14 & 0x8000) &&
            ((S_81275000_2 *)part)->unk_04.u16 == 0x104) {
            func_800A56E0(0x709);
        }
    }

    func_800478B8(dst);
    if (owner->unk_1E & 0x8000) {
        ((S_81275000_0_pre *)root)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

#ifdef __mips__
__asm__(
    ".globl func_81275000\n"
    ".type func_81275000,@function\n"
    ".size func_81275000,848\n");
#endif
