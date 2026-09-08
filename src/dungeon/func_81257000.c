#include "common.h"

typedef struct S_81257000_0_pre {
    u16 unk_00;
} S_81257000_0_pre;   /* the 0x2 bytes before root in BODY_NAME, addressed as root[-1] */

typedef struct S_81257000_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
    s16 unk_B0;
    s16 unk_B2;
    s16 unk_B4;
    s16 unk_B6;
} S_81257000_0;   /* root in BODY_NAME */

typedef struct S_81257000_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_81257000_1;   /* owner in BODY_NAME */

typedef struct S_81257000_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_81257000_2;   /* part in BODY_NAME */

typedef struct S_81257000_3 {
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
} S_81257000_3;   /* dst in BODY_NAME */

typedef struct S_81257000_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81257000_4;   /* out in BODY_NAME */

typedef struct S_81257000_5 {
    u8 pad_00[0x1];
    u8 unk_01;
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81257000_5;   /* copy in BODY_NAME */

typedef struct S_81257000_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_81257000_6;   /* callee_part in BODY_NAME */



extern s32 func_8003DE58(s32, void *, s16 *, s16);
extern void func_800478B8(void *);
extern void func_800A56E0(s32);
extern void func_8016AA38() __attribute__((noreturn));
extern void func_8016AAA8() __attribute__((noreturn));

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

static const u32 bank_words[] __asm__("func_81257000")
    __attribute__((section(".text.func_81257000"), aligned(4))) = {
    0x8016AF84, 0x8016B12C, 0x8016B8C0, 0x8016B8C0,
    0x8016B8C0, 0x8016B8E8, 0x8016B894, 0x8016B894,
    0x8016B894, 0x8016B894, 0x8016B894, 0x8016B8E8,
    0x8016B8E8, 0x8016B884, 0x8016C5D0, 0x8016C814,
    0x8016C85C, 0x8016C89C, 0x8016C93C, 0x8016C9A8,
    0x8016CA10, 0x8016CA30, 0x8016CAC4, 0x00000000,
    0x8016C680, 0x8016C678, 0x8016C670, 0x8016C688,
    0x8016C62C, 0x8016C624, 0x8016C61C, 0x00000000,
    0x8016CF20, 0x8016CF90, 0x8016CFA8, 0x8016CFD4,
    0x8016D250, 0x8016D2C0,
};

#define BODY_NAME func_81257098
#else
#define BODY_NAME func_81257000
#endif

void BODY_NAME(void *root_arg, void *out_pos_arg, void *dst_part_arg)
    __attribute__((section(".text.func_81257000")));
/* Copies part state, applies averaged position offsets, and updates phase-based shading. */
void BODY_NAME(void *root_arg, void *out_pos_arg, void *dst_part_arg)
{
    s16 pos_offset[3];
    void *root = root_arg;
    register void *out_pos ASM_REG("$17") = out_pos_arg;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_81257000_3 *dst_part = dst_part_arg;
    S_81257000_1 *owner;
    register void *src_part ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_81257000_5 *part_data;
    S_81257000_6 *motion_part;
    s8 phase;

    owner = ((S_81257000_0 *)root)->unk_AC;
    src_part = owner->unk_0C;
    part_data = owner->unk_08;

    if (!(((S_81257000_2 *)src_part)->unk_14 & 0x80)) {
        dst_part->unk_14 &= 0xFF7F;
    }

    ((S_81257000_4 *)out_pos)->unk_02 = part_data->unk_02;
    ((S_81257000_4 *)out_pos)->unk_06 = part_data->unk_06;
    ((S_81257000_4 *)out_pos)->unk_0A = part_data->unk_0A;

    motion_part = owner->unk_0C;
    if (func_8003DE58(motion_part->unk_08, motion_part, pos_offset,
                      ((S_81257000_0 *)root)->unk_B6) != 0) {
        ((S_81257000_4 *)out_pos)->unk_02 +=
            (pos_offset[0] + ((S_81257000_0 *)root)->unk_B0) / 2;
        ((S_81257000_4 *)out_pos)->unk_06 +=
            (pos_offset[1] + ((S_81257000_0 *)root)->unk_B2) / 2;
        ((S_81257000_4 *)out_pos)->unk_0A +=
            (pos_offset[2] + ((S_81257000_0 *)root)->unk_B4) / 2;
        ((S_81257000_0 *)root)->unk_B0 = pos_offset[0];
        ((S_81257000_0 *)root)->unk_B2 = pos_offset[1];
        ((S_81257000_0 *)root)->unk_B4 = pos_offset[2];
    }

    part_data = dst_part->unk_08;
    dst_part->unk_1C = ((S_81257000_2 *)src_part)->unk_1C;
    dst_part->unk_1E = ((S_81257000_2 *)src_part)->unk_1E;
    dst_part->unk_14 = ((S_81257000_2 *)src_part)->unk_14;
    part_data->unk_01 &= 0xFE;

    if (((S_81257000_0 *)root)->unk_B6 == 1) {
        phase = ((S_81257000_2 *)src_part)->unk_04.s8;
        if (phase < 8) {
            s32 scaled_phase = phase * 7;

            ASM_TAILSLOT_PIN(scaled_phase);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_8016AA38(phase);
            return;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        {
            register s32 brightness ASM_REG("$2") =
                ((15 - phase) * 14) + 0x20;

            dst_part->unk_0E = brightness;
            dst_part->unk_0D = brightness;
            dst_part->unk_0C = brightness;
        }
        if (!(((S_81257000_2 *)src_part)->unk_14 & 0x8000) &&
            ((S_81257000_2 *)src_part)->unk_04.u16 == 0x10C) {
            func_800A56E0(0x709);
        }
    }

    if (((S_81257000_0 *)root)->unk_B6 == 2) {
        phase = ((S_81257000_2 *)src_part)->unk_04.s8;
        if (phase < 8) {
            register s32 reverse_phase ASM_REG("$3") = 7 - phase;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            ASM_TAILSLOT_PIN(reverse_phase);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_8016AAA8(phase);
            return;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        {
            register s32 brightness ASM_REG("$2") =
                ((phase - 8) * 14) + 0x20;

            dst_part->unk_0E = brightness;
            dst_part->unk_0D = brightness;
            dst_part->unk_0C = brightness;
        }
        if (!(((S_81257000_2 *)src_part)->unk_14 & 0x8000) &&
            ((S_81257000_2 *)src_part)->unk_04.u16 == 0x104) {
            func_800A56E0(0x709);
        }
    }

    func_800478B8(dst_part);
    if (owner->unk_1E & 0x8000) {
        ((S_81257000_0_pre *)root)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

#ifdef __mips__
__asm__(
    ".globl func_81257000\n"
    ".type func_81257000,@function\n"
    ".size func_81257000,848\n");
#endif
