#include "common.h"

typedef struct S_80975170_0_pre {
    u16 unk_00;
} S_80975170_0_pre;   /* the 0x2 bytes before arg0 in func_80975170, addressed as arg0[-1] */

typedef struct S_80975170_0 {
    u8 pad_00[0x96];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x12];
    s16 unk_AA;
    u8 pad_AC[0x4];
    void * unk_B0;
} S_80975170_0;   /* arg0 in func_80975170 */

typedef struct S_80975170_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80975170_1;   /* arg1 in func_80975170 */

typedef struct S_80975170_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80975170_2;   /* src in func_80975170 */

typedef struct S_80975170_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
} S_80975170_3;   /* arg2 in func_80975170 */


extern void func_800478B8(void *arg0);
extern s32 D_800814A0[3];


/* Copy the source transform, advance and fade the effect, and flag completion when its timer expires. */
void func_80975170(void *effect, S_80975170_1 *transform, S_80975170_3 *render_state)
{
    s16 ticks_left;
    s32 brightness;
    u16 render_offset;
    S_80975170_2 *source_transform;

    source_transform = ((S_80975170_0 *)effect)->unk_B0;
    transform->unk_02 = source_transform->unk_02;
    transform->unk_06 = source_transform->unk_06;
    transform->unk_0A = source_transform->unk_0A;

    render_offset = render_state->unk_1E + 0x320;
    render_state->unk_1E = render_offset;
    render_state->unk_1C = render_offset;

    ticks_left = ((S_80975170_0 *)effect)->unk_96.s - 1;
    brightness = (s32)(ticks_left * 0x50) / (s16)((S_80975170_0 *)effect)->unk_AA;
    ((S_80975170_0 *)effect)->unk_96.s = (u16)ticks_left;
    render_state->unk_0E = (s8)brightness;
    render_state->unk_0D = (s8)brightness;
    render_state->unk_0C = (s8)brightness;
    func_800478B8(render_state);

    if (((S_80975170_0 *)effect)->unk_96.u <= 0) {
        ((S_80975170_0_pre *)effect)[-1].unk_00 = (u16)(((S_80975170_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0[0] = (s32)(D_800814A0[0] | 0x8000);
    }
}
