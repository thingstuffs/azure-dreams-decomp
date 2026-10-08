#include "common.h"
#include "shared/object_flags.h"

typedef struct S_81263000_0_pre {
    u16 unk_00;
} S_81263000_0_pre;   /* the 0x2 bytes before root in func_8015E898, addressed as root[-1] */

typedef struct S_81263000_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
    s16 unk_B0;
    s16 unk_B2;
    s16 unk_B4;
    s16 unk_B6;
} S_81263000_0;   /* root in func_8015E898 */

typedef struct S_81263000_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_81263000_1;   /* owner in func_8015E898 */

typedef struct S_81263000_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_81263000_2;   /* part in func_8015E898 */

typedef struct S_81263000_3 {
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
} S_81263000_3;   /* dst in func_8015E898 */

typedef struct S_81263000_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81263000_4;   /* out in func_8015E898 */

typedef struct S_81263000_5 {
    u8 pad_00[0x1];
    u8 unk_01;
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81263000_5;   /* copy in func_8015E898 */

typedef struct S_81263000_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_81263000_6;   /* callee_part in func_8015E898 */

extern s32 func_8003DE58(s32, void *, s16 *, s16);
extern void func_800478B8(void *);
extern void func_800A56E0(s32);




void func_8015E898(void *root, void *output_pos, void *target_data)
;
/* Update part position, shading, and flags from its owner. */
void func_8015E898(void *root, void *output_pos, void *target_data)
{
    s16 offset[3];
    void *position_data;
    S_81263000_3 *target_part = target_data;
    S_81263000_1 *owner;
    S_81263000_5 *pos_data;
    S_81263000_6 *motion_part;
    s8 phase;
    s16 shade_a;
    s32 reverse_phase;

    owner = ((S_81263000_0 *)root)->unk_AC;
    position_data = owner->unk_0C;
    pos_data = owner->unk_08;

    if (!(((S_81263000_2 *)position_data)->unk_14 & 0x80)) {
        target_part->unk_14 &= 0xFF7F;
    }

    ((S_81263000_4 *)output_pos)->unk_02 = pos_data->unk_02;
    ((S_81263000_4 *)output_pos)->unk_06 = pos_data->unk_06;
    ((S_81263000_4 *)output_pos)->unk_0A = pos_data->unk_0A;

    motion_part = owner->unk_0C;
    if (func_8003DE58(motion_part->unk_08, motion_part, offset,
                      ((S_81263000_0 *)root)->unk_B6) != 0) {
        ((S_81263000_4 *)output_pos)->unk_02 +=
            (offset[0] + ((S_81263000_0 *)root)->unk_B0) / 2;
        ((S_81263000_4 *)output_pos)->unk_06 +=
            (offset[1] + ((S_81263000_0 *)root)->unk_B2) / 2;
        ((S_81263000_4 *)output_pos)->unk_0A +=
            (offset[2] + ((S_81263000_0 *)root)->unk_B4) / 2;
        ((S_81263000_0 *)root)->unk_B0 = offset[0];
        ((S_81263000_0 *)root)->unk_B2 = offset[1];
        ((S_81263000_0 *)root)->unk_B4 = offset[2];
    }

    pos_data = target_part->unk_08;
    target_part->unk_1C = ((S_81263000_2 *)position_data)->unk_1C;
    target_part->unk_1E = ((S_81263000_2 *)position_data)->unk_1E;
    target_part->unk_14 = ((S_81263000_2 *)position_data)->unk_14;
    pos_data->unk_01 &= 0xFE;

    if (((S_81263000_0 *)root)->unk_B6 == 1) {
        phase = ((S_81263000_2 *)position_data)->unk_04.s8;
        if (phase < 8) {
            shade_a = (phase * 14) + 0x20;
            target_part->unk_0E = shade_a;
            target_part->unk_0D = shade_a;
            target_part->unk_0C = shade_a;
        } else {
            shade_a = ((15 - phase) * 14) + 0x20;
            target_part->unk_0E = shade_a;
            target_part->unk_0D = shade_a;
            target_part->unk_0C = shade_a;
        }
        if (!(((S_81263000_2 *)position_data)->unk_14 & 0x8000) &&
            ((S_81263000_2 *)position_data)->unk_04.u16 == 0x10C) {
            func_800A56E0(0x709);
        }
    }

    if (((S_81263000_0 *)root)->unk_B6 == 2) {
        phase = ((S_81263000_2 *)position_data)->unk_04.s8;
        if (phase < 8) {
            reverse_phase = 7;
            reverse_phase -= phase;
        } else {
            reverse_phase = phase - 8;
        }
        {
            s32 shade =
                ((reverse_phase * 7) * 2) + 0x20;

            target_part->unk_0E = shade;
            target_part->unk_0D = shade;
            target_part->unk_0C = shade;
        }
        if (!(((S_81263000_2 *)position_data)->unk_14 & 0x8000) &&
            ((S_81263000_2 *)position_data)->unk_04.u16 == 0x104) {
            func_800A56E0(0x709);
        }
    }

    func_800478B8(target_part);
    if (owner->unk_1E & 0x8000) {
        ((S_81263000_0_pre *)root)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}


