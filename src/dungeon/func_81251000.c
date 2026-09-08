#include "common.h"

typedef struct S_81251000_0_pre {
    u16 unk_00;
} S_81251000_0_pre;   /* the 0x2 bytes before root in BODY_NAME, addressed as root[-1] */

typedef struct S_81251000_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
    s16 unk_B0;
    s16 unk_B2;
    s16 unk_B4;
    s16 unk_B6;
} S_81251000_0;   /* root in BODY_NAME */

typedef struct S_81251000_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_81251000_1;   /* owner in BODY_NAME */

typedef struct S_81251000_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_81251000_2;   /* part in BODY_NAME */

typedef struct S_81251000_3 {
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
} S_81251000_3;   /* dst in BODY_NAME */

typedef struct S_81251000_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81251000_4;   /* out in BODY_NAME */

typedef struct S_81251000_5 {
    u8 pad_00[0x1];
    u8 unk_01;
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81251000_5;   /* copy in BODY_NAME */

typedef struct S_81251000_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_81251000_6;   /* callee_part in BODY_NAME */



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

void BODY_NAME(void *root_data, void *position_out, void *part_out)
    __attribute__((section(".text.func_81251000")));
/* Copies part state, smooths position offsets, and applies phase-dependent brightness. */
void BODY_NAME(void *root_data, void *position_out, void *part_out)
{
    s16 offset[3];
    void *root = root_data;
    register void *output_pos ASM_REG("$17") = position_out;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_81251000_3 *output_part = part_out;
    S_81251000_1 *owner;
    register void *source_part ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_81251000_5 *transform;
    S_81251000_6 *motion_part;
    s8 phase;

    owner = ((S_81251000_0 *)root)->unk_AC;
    source_part = owner->unk_0C;
    transform = owner->unk_08;

    if (!(((S_81251000_2 *)source_part)->unk_14 & 0x80)) {
        output_part->unk_14 &= 0xFF7F;
    }

    ((S_81251000_4 *)output_pos)->unk_02 = transform->unk_02;
    ((S_81251000_4 *)output_pos)->unk_06 = transform->unk_06;
    ((S_81251000_4 *)output_pos)->unk_0A = transform->unk_0A;

    motion_part = owner->unk_0C;
    if (func_8003DE58(motion_part->unk_08, motion_part, offset,
                      ((S_81251000_0 *)root)->unk_B6) != 0) {
        ((S_81251000_4 *)output_pos)->unk_02 +=
            (offset[0] + ((S_81251000_0 *)root)->unk_B0) / 2;
        ((S_81251000_4 *)output_pos)->unk_06 +=
            (offset[1] + ((S_81251000_0 *)root)->unk_B2) / 2;
        ((S_81251000_4 *)output_pos)->unk_0A +=
            (offset[2] + ((S_81251000_0 *)root)->unk_B4) / 2;
        ((S_81251000_0 *)root)->unk_B0 = offset[0];
        ((S_81251000_0 *)root)->unk_B2 = offset[1];
        ((S_81251000_0 *)root)->unk_B4 = offset[2];
    }

    transform = output_part->unk_08;
    output_part->unk_1C = ((S_81251000_2 *)source_part)->unk_1C;
    output_part->unk_1E = ((S_81251000_2 *)source_part)->unk_1E;
    output_part->unk_14 = ((S_81251000_2 *)source_part)->unk_14;
    transform->unk_01 &= 0xFE;

    if (((S_81251000_0 *)root)->unk_B6 == 1) {
        phase = ((S_81251000_2 *)source_part)->unk_04.s8;
        if (phase < 8) {
            s32 scaled_phase = phase * 7;

            ASM_TAILSLOT_PIN(scaled_phase);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_80170A38(phase);
            return;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        {
            register s32 brightness ASM_REG("$2") =
                ((15 - phase) * 14) + 0x20;

            output_part->unk_0E = brightness;
            output_part->unk_0D = brightness;
            output_part->unk_0C = brightness;
        }
        if (!(((S_81251000_2 *)source_part)->unk_14 & 0x8000) &&
            ((S_81251000_2 *)source_part)->unk_04.u16 == 0x10C) {
            func_800A56E0(0x709);
        }
    }

    if (((S_81251000_0 *)root)->unk_B6 == 2) {
        phase = ((S_81251000_2 *)source_part)->unk_04.s8;
        if (phase < 8) {
            register s32 reverse_phase ASM_REG("$3") = 7 - phase;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            ASM_TAILSLOT_PIN(reverse_phase);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_80170AA8(phase);
            return;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        {
            register s32 brightness ASM_REG("$2") =
                ((phase - 8) * 14) + 0x20;

            output_part->unk_0E = brightness;
            output_part->unk_0D = brightness;
            output_part->unk_0C = brightness;
        }
        if (!(((S_81251000_2 *)source_part)->unk_14 & 0x8000) &&
            ((S_81251000_2 *)source_part)->unk_04.u16 == 0x104) {
            func_800A56E0(0x709);
        }
    }

    func_800478B8(output_part);
    if (owner->unk_1E & 0x8000) {
        ((S_81251000_0_pre *)root)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

#ifdef __mips__
__asm__(
    ".globl func_81251000\n"
    ".type func_81251000,@function\n"
    ".size func_81251000,848\n");
#endif
