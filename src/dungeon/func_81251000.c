#include "common.h"
#include "shared/object_flags.h"

typedef struct S_81251000_0_pre {
    u16 unk_00;
} S_81251000_0_pre;   /* the 0x2 bytes before root in func_80170898, addressed as root[-1] */

typedef struct S_81251000_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
    s16 unk_B0;
    s16 unk_B2;
    s16 unk_B4;
    s16 unk_B6;
} S_81251000_0;   /* root in func_80170898 */

typedef struct S_81251000_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_81251000_1;   /* owner in func_80170898 */

typedef struct S_81251000_2 {
    u8 pad_00[0x4];
    union { s8 s8; u16 u16; } unk_04;   /* accessed as both */
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_81251000_2;   /* part in func_80170898 */

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
} S_81251000_3;   /* dst in func_80170898 */

typedef struct S_81251000_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81251000_4;   /* out in func_80170898 */

typedef struct S_81251000_5 {
    u8 pad_00[0x1];
    u8 unk_01;
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81251000_5;   /* copy in func_80170898 */

typedef struct S_81251000_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_81251000_6;   /* callee_part in func_80170898 */


extern s32 func_8003DE58(s32, void *, s16 *, s16);
extern void func_800478B8(void *);
extern void func_800A56E0(s32);




void func_80170898(void *root_data, void *position_out, void *part_out)
;
/* Copies part state, smooths position offsets, and applies phase-dependent brightness. */
void func_80170898(void *root_data, void *position_out, void *part_out)
{
    s16 offset[3];
    register void *output_pos = position_out;
    S_81251000_3 *output_part = part_out;
    S_81251000_2 *source_part;
    S_81251000_1 *owner;
    S_81251000_5 *transform;
    S_81251000_6 *motion_part;
    s8 phase;

    owner = ((S_81251000_0 *)root_data)->unk_AC;
    source_part = owner->unk_0C;
    transform = owner->unk_08;

    if (!(source_part->unk_14 & 0x80)) {
        output_part->unk_14 &= 0xFF7F;
    }

    ((S_81251000_4 *)output_pos)->unk_02 = transform->unk_02;
    ((S_81251000_4 *)output_pos)->unk_06 = transform->unk_06;
    ((S_81251000_4 *)output_pos)->unk_0A = transform->unk_0A;

    motion_part = owner->unk_0C;
    if (func_8003DE58(motion_part->unk_08, motion_part, offset,
                      ((S_81251000_0 *)root_data)->unk_B6) != 0) {
        ((S_81251000_4 *)output_pos)->unk_02 +=
            (offset[0] + ((S_81251000_0 *)root_data)->unk_B0) / 2;
        ((S_81251000_4 *)output_pos)->unk_06 +=
            (offset[1] + ((S_81251000_0 *)root_data)->unk_B2) / 2;
        ((S_81251000_4 *)output_pos)->unk_0A +=
            (offset[2] + ((S_81251000_0 *)root_data)->unk_B4) / 2;
        ((S_81251000_0 *)root_data)->unk_B0 = offset[0];
        ((S_81251000_0 *)root_data)->unk_B2 = offset[1];
        ((S_81251000_0 *)root_data)->unk_B4 = offset[2];
    }

    transform = output_part->unk_08;
    output_part->unk_1C = source_part->unk_1C;
    output_part->unk_1E = source_part->unk_1E;
    output_part->unk_14 = source_part->unk_14;
    transform->unk_01 &= 0xFE;

    if (((S_81251000_0 *)root_data)->unk_B6 == 1) {
        phase = source_part->unk_04.s8;
        if (phase < 8) {
            s32 brightness = (phase * 14) + 0x20;

            output_part->unk_0E = brightness;
            output_part->unk_0D = brightness;
            output_part->unk_0C = brightness;
        } else {
            s32 brightness = ((15 - phase) * 14) + 0x20;

            output_part->unk_0E = brightness;
            output_part->unk_0D = brightness;
            output_part->unk_0C = brightness;
        }
        if (!(source_part->unk_14 & 0x8000) &&
            source_part->unk_04.u16 == 0x10C) {
            func_800A56E0(0x709);
        }
    }

    if (((S_81251000_0 *)root_data)->unk_B6 == 2) {
        phase = source_part->unk_04.s8;
        if (phase < 8) {
            s32 brightness = ((7 - phase) * 14) + 0x20;

            output_part->unk_0E = brightness;
            output_part->unk_0D = brightness;
            output_part->unk_0C = brightness;
        } else {
            s32 brightness = ((phase - 8) * 14) + 0x20;

            output_part->unk_0E = brightness;
            output_part->unk_0D = brightness;
            output_part->unk_0C = brightness;
        }
        if (!(source_part->unk_14 & 0x8000) &&
            source_part->unk_04.u16 == 0x104) {
            func_800A56E0(0x709);
        }
    }

    func_800478B8(output_part);
    if (owner->unk_1E & 0x8000) {
        ((S_81251000_0_pre *)root_data)[-1].unk_00 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}


