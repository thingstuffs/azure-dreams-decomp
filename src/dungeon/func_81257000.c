#include "common.h"
#include "shared/object_flags.h"

typedef struct S_81257000_0_pre {
    u16 unk_00;
} S_81257000_0_pre;   /* the 0x2 bytes before root in func_8016A898, addressed as root[-1] */

typedef struct S_81257000_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
    s16 unk_B0;
    s16 unk_B2;
    s16 unk_B4;
    s16 unk_B6;
} S_81257000_0;   /* root in func_8016A898 */

typedef struct S_81257000_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_81257000_1;   /* owner in func_8016A898 */

typedef struct S_81257000_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_81257000_2;   /* part in func_8016A898 */

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
} S_81257000_3;   /* dst in func_8016A898 */

typedef struct S_81257000_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81257000_4;   /* out in func_8016A898 */

typedef struct S_81257000_5 {
    u8 pad_00[0x1];
    u8 unk_01;
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81257000_5;   /* copy in func_8016A898 */

typedef struct S_81257000_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_81257000_6;   /* callee_part in func_8016A898 */

extern s32 func_8003DE58(s32, void *, s16 *, s16);
extern void func_800478B8(void *);
extern void func_800A56E0(s32);




void func_8016A898(void *root_arg, void *out_pos_arg, void *dst_part_arg)
;
/* Copies part state, applies averaged position offsets, and updates phase-based shading. */
void func_8016A898(void *root_arg, void *out_pos_arg, void *dst_part_arg)
{
    s16 pos_offset[3];
    void *root = root_arg;
    void *out_pos = out_pos_arg;
    S_81257000_3 *dst_part = dst_part_arg;
    S_81257000_1 *owner;
    S_81257000_5 *part_data;
    S_81257000_6 *motion_part;
    s8 phase;

    owner = ((S_81257000_0 *)root)->unk_AC;
    out_pos_arg = owner->unk_0C;
    part_data = owner->unk_08;

    if (!(((S_81257000_2 *)out_pos_arg)->unk_14 & 0x80)) {
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
    dst_part->unk_1C = ((S_81257000_2 *)out_pos_arg)->unk_1C;
    dst_part->unk_1E = ((S_81257000_2 *)out_pos_arg)->unk_1E;
    dst_part->unk_14 = ((S_81257000_2 *)out_pos_arg)->unk_14;
    part_data->unk_01 &= 0xFE;

    if (((S_81257000_0 *)root)->unk_B6 == 1) {
        phase = ((S_81257000_2 *)out_pos_arg)->unk_04.s8;
        if (phase < 8) {
            s32 brightness = (phase * 14) + 0x20;

            dst_part->unk_0E = brightness;
            dst_part->unk_0D = brightness;
            dst_part->unk_0C = brightness;
        } else {
            s32 brightness = ((15 - phase) * 14) + 0x20;

            dst_part->unk_0E = brightness;
            dst_part->unk_0D = brightness;
            dst_part->unk_0C = brightness;
        }
        if (!(((S_81257000_2 *)out_pos_arg)->unk_14 & 0x8000) &&
            ((S_81257000_2 *)out_pos_arg)->unk_04.u16 == 0x10C) {
            func_800A56E0(0x709);
        }
    }

    if (((S_81257000_0 *)root)->unk_B6 == 2) {
        phase = ((S_81257000_2 *)out_pos_arg)->unk_04.s8;
        if (phase < 8) {
            s32 brightness = ((7 - phase) * 14) + 0x20;

            dst_part->unk_0E = brightness;
            dst_part->unk_0D = brightness;
            dst_part->unk_0C = brightness;
        } else {
            s32 brightness = ((phase - 8) * 14) + 0x20;

            dst_part->unk_0E = brightness;
            dst_part->unk_0D = brightness;
            dst_part->unk_0C = brightness;
        }
        if (!(((S_81257000_2 *)out_pos_arg)->unk_14 & 0x8000) &&
            ((S_81257000_2 *)out_pos_arg)->unk_04.u16 == 0x104) {
            func_800A56E0(0x709);
        }
    }

    func_800478B8(dst_part);
    if (owner->unk_1E & 0x8000) {
        ((S_81257000_0_pre *)root)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}


