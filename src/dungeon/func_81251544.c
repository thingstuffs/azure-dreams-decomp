#include "common.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_80170D44_0_pre {
    u16 unk_00;
} S_80170D44_0_pre;   /* the 0x2 bytes before arg0 in func_80170D44, addressed as arg0[-1] */

typedef struct S_80170D44_0 {
    u8 pad_00[0x96];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x10];
    s16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
} S_80170D44_0;   /* arg0 in func_80170D44 */

typedef struct S_80170D44_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170D44_1;   /* arg1 in func_80170D44 */

typedef struct S_80170D44_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170D44_2;   /* src in func_80170D44 */



extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];


/* Copy the effect position, expand and fade its primitive, and flag expiration. */
void func_80170D44(void *effect, S_80170D44_1 *position, Rec_D_80082E80 *primitive)
{
    s16 ticks_left;
    s32 shade;
    u16 extent;
    S_80170D44_2 *source_position;

    source_position = ((S_80170D44_0 *)effect)->unk_AC;
    position->unk_02 = source_position->unk_02;
    position->unk_06 = source_position->unk_06;
    position->unk_0A = source_position->unk_0A;

    extent = primitive->unk_1C.at02_u16.v + 0x320;
    primitive->unk_1C.at02_u16.v = extent;
    primitive->unk_1C.at00_u16.v = extent;

    ticks_left = ((S_80170D44_0 *)effect)->unk_96.s - 1;
    shade = (s32)(ticks_left * 0x50) / (s16)((S_80170D44_0 *)effect)->unk_A8;
    ((S_80170D44_0 *)effect)->unk_96.s = (u16)ticks_left;
    primitive->unk_0C.at02_s8.v = (s8)shade;
    primitive->unk_0C.at01_s8.v = (s8)shade;
    primitive->unk_0C.at00_s8.v = (s8)shade;
    func_800478B8(primitive);

    if (((S_80170D44_0 *)effect)->unk_96.u <= 0) {
        ((S_80170D44_0_pre *)effect)[-1].unk_00 = (u16)(((S_80170D44_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}
