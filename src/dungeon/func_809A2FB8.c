#include "common.h"


extern s32 D_800814A0[3];


typedef struct S_801747B8_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    u16 unk_14;
} S_801747B8_0;   /* arg2 in func_801747B8 */

typedef struct S_801747B8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801747B8_1;   /* arg1 in func_801747B8 */

typedef struct S_801747B8_2 {
    u8 pad_00[0x20];
    u16 unk_20;
    u8 pad_22[0x4];
    u16 unk_26;
    u8 pad_28[0x4];
    u16 unk_2C;
} S_801747B8_2;   /* dst in func_801747B8 */

typedef struct S_801747B8_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_801747B8_3;   /* (*(void * *)((u8 *)arg0 + 0x18)) in func_801747B8 */

typedef struct S_801747B8_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_801747B8_4;   /* (*(void * *)((u8 *)arg0 + 0x1C)) in func_801747B8 */

/* Updates an effect's color fade and delayed position history. */
void func_801747B8(void *effect, S_801747B8_1 *position, S_801747B8_0 *primitive)
{
    s16 trail_length;
    s32 sample_index;
    u8 *trail_tail;

    primitive->unk_08 = ((S_801747B8_3 *)((*(void * *)((u8 *)effect + 0x18))))->unk_08;
    primitive->unk_14 =
        ((S_801747B8_3 *)((*(void * *)((u8 *)effect + 0x18))))->unk_14 | 0xC;

    if ((*(u8 *)((u8 *)effect + 0x17)) == 0) {
        trail_length = (*(s16 *)((u8 *)effect + 0x34));
        if (primitive->unk_0C.u8 < (0x80 >> trail_length)) {
            primitive->unk_0C.s32 += 0x101010;
            goto update_history;
        }
        (*(u8 *)((u8 *)effect + 0x17))++;
        goto update_history;
    }

    if (primitive->unk_0C.u8 == 0) {
        goto mark_finished;
    }
    primitive->unk_0C.s32 += -0x80808;
    goto update_history;

mark_finished:
    (*(u16 *)((u8 *)effect + -2)) |= 0x8000;
    D_800814A0[0] |= 0x8000;

update_history:
    position->unk_02 = (*(u16 *)((u8 *)effect + 0x20));
    position->unk_06 = (*(u16 *)((u8 *)effect + 0x26));
    position->unk_0A = (*(u16 *)((u8 *)effect + 0x2C));

    sample_index = 0;
    if ((*(s16 *)((u8 *)effect + 0x34)) > 0) {
        do {
            (*(u16 *)((u8 *)effect + sample_index * 2 + 0x20)) = (*(u16 *)((u8 *)effect + sample_index * 2 + 0x22));
            (*(u16 *)((u8 *)effect + sample_index * 2 + 0x26)) = (*(u16 *)((u8 *)effect + sample_index * 2 + 0x28));
            (*(u16 *)((u8 *)effect + sample_index * 2 + 0x2C)) = (*(u16 *)((u8 *)effect + sample_index * 2 + 0x2E));
            sample_index++;
        } while (sample_index < (*(s16 *)((u8 *)effect + 0x34)));
    }

    trail_tail = (u8 *)(sample_index * 2 + (s32)(u32)effect);
    ((S_801747B8_2 *)trail_tail)->unk_20 = ((S_801747B8_4 *)((*(void * *)((u8 *)effect + 0x1C))))->unk_02;
    ((S_801747B8_2 *)trail_tail)->unk_26 = ((S_801747B8_4 *)((*(void * *)((u8 *)effect + 0x1C))))->unk_06;
    ((S_801747B8_2 *)trail_tail)->unk_2C = ((S_801747B8_4 *)((*(void * *)((u8 *)effect + 0x1C))))->unk_0A;
}
