#include "common.h"

typedef struct S_80171A38_0_pre {
    u16 unk_00;
} S_80171A38_0_pre;   /* the 0x2 bytes before arg0 in func_80171A38, addressed as arg0[-1] */

typedef struct S_80171A38_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80171A38_0;   /* arg0 in func_80171A38 */

typedef struct S_80171A38_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80171A38_1;   /* record in func_80171A38 */

typedef struct S_80171A38_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x1];
    u16 unk_06;
    u8 pad_08[0x24];
    void * unk_2C;
} S_80171A38_2;   /* part in func_80171A38 */

typedef struct S_80171A38_3 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x14];
    s16 unk_1C;
    s16 unk_1E;
} S_80171A38_3;   /* arg2 in func_80171A38 */

typedef struct S_80171A38_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80171A38_4;   /* arg1 in func_80171A38 */

typedef struct S_80171A38_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80171A38_5;   /* source in func_80171A38 */

typedef struct S_80171A38_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80171A38_6;   /* ((S_80171A38_1 *)record)->unk_0C in func_80171A38 */



typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern s32 func_8003DE58(void *, void *, Vec3s *, s32);

extern s32 D_800814A0[3];
extern u8 D_80175E54[];
extern u8 D_80175E5C[];
extern u8 D_80175E64[];

/* Update position and part state, then mark the object used unless its part is exempt. */
void func_80171A38(void *object, S_80171A38_4 *position, S_80171A38_3 *part_state)
{
    S_80171A38_1 *record;
    S_80171A38_2 *part;
    S_80171A38_5 *base_position;
    u16 part_value;
    Vec3s position_delta;

    record = (u8 *)((S_80171A38_0 *)object)->unk_20 - 0x20;
    if ((record->unk_1E & 0x8000) != 0) {
        goto mark_used;
    }

    do { part = record->unk_0C; } while (0);
    part_value = part->unk_06;
    base_position = record->unk_08;
    part_state->unk_06 = part_value + 1;

    if (part->unk_04 == 0) {
        part_state->unk_1E = 0x400;
        part_state->unk_1C = 0x400;
    }
    if (part->unk_04 == 1) {
        part_state->unk_1E = 0x700;
        part_state->unk_1C = 0x700;
    }
    if (part->unk_04 == 2) {
        part_state->unk_1E = 0xa00;
        part_state->unk_1C = 0xa00;
    }
    if (part->unk_04 == 3) {
        part_state->unk_1E = 0x700;
        part_state->unk_1C = 0x700;
    }
    if (part->unk_04 == 4) {
        part_state->unk_1E = 0x400;
        part_state->unk_1C = 0x400;
    }

    position->unk_02 = base_position->unk_02;
    position->unk_06 = base_position->unk_06;
    position->unk_0A = base_position->unk_0A;

    if (func_8003DE58(
            ((S_80171A38_6 *)(record->unk_0C))->unk_08,
            record->unk_0C, &position_delta, 0) != 0) {
        position->unk_02 += position_delta.x;
        position->unk_06 += position_delta.y;
        position->unk_0A += position_delta.z;
    }

    if (part->unk_2C == D_80175E54 ||
        part->unk_2C == D_80175E5C ||
        part->unk_2C == D_80175E64) {
        return;
    }

mark_used:
    ((S_80171A38_0_pre *)object)[-1].unk_00 |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
