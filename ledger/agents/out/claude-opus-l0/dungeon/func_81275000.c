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

extern s32 D_800814A0[3];

#ifdef __mips__

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

void BODY_NAME(void *root_data, void *position_data, void *render_data)
    __attribute__((section(".text.func_81275000")));
/* Updates part position, brightness, and flags from the owner and motion state. */
void BODY_NAME(void *root_data, void *position_data, void *render_data)
{
    s16 motion_offset[3];
    register void *out_pos = position_data;
    S_81275000_3 *render_part = render_data;
    S_81275000_2 *source_pos;
    S_81275000_1 *owner;
    S_81275000_5 *transform;
    S_81275000_6 *motion_part;
    s8 phase;

    owner = ((S_81275000_0 *)root_data)->unk_AC;
    source_pos = owner->unk_0C;
    transform = owner->unk_08;

    if (!(source_pos->unk_14 & 0x80)) {
        render_part->unk_14 &= 0xFF7F;
    }

    ((S_81275000_4 *)out_pos)->unk_02 = transform->unk_02;
    ((S_81275000_4 *)out_pos)->unk_06 = transform->unk_06;
    ((S_81275000_4 *)out_pos)->unk_0A = transform->unk_0A;

    motion_part = owner->unk_0C;
    if (func_8003DE58(motion_part->unk_08, motion_part, motion_offset,
                      ((S_81275000_0 *)root_data)->unk_B6) != 0) {
        ((S_81275000_4 *)out_pos)->unk_02 +=
            (motion_offset[0] + ((S_81275000_0 *)root_data)->unk_B0) / 2;
        ((S_81275000_4 *)out_pos)->unk_06 +=
            (motion_offset[1] + ((S_81275000_0 *)root_data)->unk_B2) / 2;
        ((S_81275000_4 *)out_pos)->unk_0A +=
            (motion_offset[2] + ((S_81275000_0 *)root_data)->unk_B4) / 2;
        ((S_81275000_0 *)root_data)->unk_B0 = motion_offset[0];
        ((S_81275000_0 *)root_data)->unk_B2 = motion_offset[1];
        ((S_81275000_0 *)root_data)->unk_B4 = motion_offset[2];
    }

    transform = render_part->unk_08;
    render_part->unk_1C = source_pos->unk_1C;
    render_part->unk_1E = source_pos->unk_1E;
    render_part->unk_14 = source_pos->unk_14;
    transform->unk_01 &= 0xFE;

    if (((S_81275000_0 *)root_data)->unk_B6 == 1) {
        phase = source_pos->unk_04.s8;
        {
            s32 intensity;

            if (phase < 8) {
                intensity = (phase * 14) + 0x20;
            } else {
                intensity = ((15 - phase) * 14) + 0x20;
            }
            render_part->unk_0E = intensity;
            render_part->unk_0D = intensity;
            render_part->unk_0C = intensity;
        }
        if (!(source_pos->unk_14 & 0x8000) &&
            source_pos->unk_04.u16 == 0x10C) {
            func_800A56E0(0x709);
        }
    }

    if (((S_81275000_0 *)root_data)->unk_B6 == 2) {
        phase = source_pos->unk_04.s8;
        {
            s32 intensity;

            if (phase < 8) {
                intensity = ((7 - phase) * 14) + 0x20;
            } else {
                intensity = ((phase - 8) * 14) + 0x20;
            }
            render_part->unk_0E = intensity;
            render_part->unk_0D = intensity;
            render_part->unk_0C = intensity;
        }
        if (!(source_pos->unk_14 & 0x8000) &&
            source_pos->unk_04.u16 == 0x104) {
            func_800A56E0(0x709);
        }
    }

    func_800478B8(render_part);
    if (owner->unk_1E & 0x8000) {
        ((S_81275000_0_pre *)root_data)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}

#ifdef __mips__
__asm__(
    ".globl func_81275000\n"
    ".type func_81275000,@function\n"
    ".size func_81275000,848\n");
#endif
