#include "common.h"

typedef struct S_8127B000_0_pre {
    u16 unk_00;
} S_8127B000_0_pre;   /* the 0x2 bytes before root in BODY_NAME, addressed as root[-1] */

typedef struct S_8127B000_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
    s16 unk_B0;
    s16 unk_B2;
    s16 unk_B4;
    s16 unk_B6;
} S_8127B000_0;   /* root in BODY_NAME */

typedef struct S_8127B000_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_8127B000_1;   /* owner in BODY_NAME */

typedef struct S_8127B000_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_8127B000_2;   /* part in BODY_NAME */

typedef struct S_8127B000_3 {
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
} S_8127B000_3;   /* dst in BODY_NAME */

typedef struct S_8127B000_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8127B000_4;   /* out in BODY_NAME */

typedef struct S_8127B000_5 {
    u8 pad_00[0x1];
    u8 unk_01;
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8127B000_5;   /* copy in BODY_NAME */

typedef struct S_8127B000_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8127B000_6;   /* callee_part in BODY_NAME */



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

void BODY_NAME(void *root_arg, void *output_transform, void *target_part)
    __attribute__((section(".text.func_8127B000")));
/* Copies part state and applies smoothed position offsets and phase-dependent shading. */
void BODY_NAME(void *root_arg, void *output_transform, void *target_part)
{
    s16 offset[3];
    void *root = root_arg;
    register void *transform ASM_REG("$17") = output_transform;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_8127B000_3 *render_part = target_part;
    S_8127B000_1 *owner;
    register void *source_part ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_8127B000_5 *part_transform;
    S_8127B000_6 *motion_part;
    s8 phase;

    owner = ((S_8127B000_0 *)root)->unk_AC;
    source_part = owner->unk_0C;
    part_transform = owner->unk_08;

    if (!(((S_8127B000_2 *)source_part)->unk_14 & 0x80)) {
        render_part->unk_14 &= 0xFF7F;
    }

    ((S_8127B000_4 *)transform)->unk_02 = part_transform->unk_02;
    ((S_8127B000_4 *)transform)->unk_06 = part_transform->unk_06;
    ((S_8127B000_4 *)transform)->unk_0A = part_transform->unk_0A;

    motion_part = owner->unk_0C;
    if (func_8003DA40(motion_part->unk_08, motion_part, offset,
                      ((S_8127B000_0 *)root)->unk_B6) != 0) {
        ((S_8127B000_4 *)transform)->unk_02 +=
            (offset[0] + ((S_8127B000_0 *)root)->unk_B0) / 2;
        ((S_8127B000_4 *)transform)->unk_06 +=
            (offset[1] + ((S_8127B000_0 *)root)->unk_B2) / 2;
        ((S_8127B000_4 *)transform)->unk_0A +=
            (offset[2] + ((S_8127B000_0 *)root)->unk_B4) / 2;
        ((S_8127B000_0 *)root)->unk_B0 = offset[0];
        ((S_8127B000_0 *)root)->unk_B2 = offset[1];
        ((S_8127B000_0 *)root)->unk_B4 = offset[2];
    }

    part_transform = render_part->unk_08;
    render_part->unk_1C = ((S_8127B000_2 *)source_part)->unk_1C;
    render_part->unk_1E = ((S_8127B000_2 *)source_part)->unk_1E;
    render_part->unk_14 = ((S_8127B000_2 *)source_part)->unk_14;
    part_transform->unk_01 &= 0xFE;

    if (((S_8127B000_0 *)root)->unk_B6 == 1) {
        phase = ((S_8127B000_2 *)source_part)->unk_04.s8;
        if (phase < 8) {
            s32 scaled_phase = phase * 7;

            ASM_TAILSLOT_PIN(scaled_phase);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_8016FA38(phase);
            return;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        {
            register s32 brightness ASM_REG("$2") =
                ((15 - phase) * 14) + 0x20;

            render_part->unk_0E = brightness;
            render_part->unk_0D = brightness;
            render_part->unk_0C = brightness;
        }
        if (!(((S_8127B000_2 *)source_part)->unk_14 & 0x8000) &&
            ((S_8127B000_2 *)source_part)->unk_04.u16 == 0x10C) {
            func_800A4398(0x709);
        }
    }

    if (((S_8127B000_0 *)root)->unk_B6 == 2) {
        phase = ((S_8127B000_2 *)source_part)->unk_04.s8;
        if (phase < 8) {
            register s32 reverse_phase ASM_REG("$3") = 7 - phase;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            ASM_TAILSLOT_PIN(reverse_phase);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            func_8016FAA8(phase);
            return;
        }
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        {
            register s32 brightness ASM_REG("$2") =
                ((phase - 8) * 14) + 0x20;

            render_part->unk_0E = brightness;
            render_part->unk_0D = brightness;
            render_part->unk_0C = brightness;
        }
        if (!(((S_8127B000_2 *)source_part)->unk_14 & 0x8000) &&
            ((S_8127B000_2 *)source_part)->unk_04.u16 == 0x104) {
            func_800A4398(0x709);
        }
    }

    func_80047454(render_part);
    if (owner->unk_1E & 0x8000) {
        ((S_8127B000_0_pre *)root)[-1].unk_00 |= 0x8000;
        D_800803D4[0] |= 0x8000;
    }
}

#ifdef __mips__
__asm__(
    ".globl func_8127B000\n"
    ".type func_8127B000,@function\n"
    ".size func_8127B000,848\n");
#endif
