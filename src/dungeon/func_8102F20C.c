#include "common.h"
#include "m2c_compat.h"

typedef struct S_8102F20C_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8102F20C_0;   /* arg1 in func_8102F20C */

typedef struct S_8102F20C_1_pre {
    u16 unk_00;
} S_8102F20C_1_pre;   /* the 0x2 bytes before arg0 in func_8102F20C, addressed as arg0[-1] */

typedef struct S_8102F20C_1 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    u8 pad_1E[0xA];
    void * unk_28;
} S_8102F20C_1;   /* arg0 in func_8102F20C */

typedef struct S_8102F20C_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8102F20C_2;   /* temp_v1 in func_8102F20C */

typedef struct S_8102F20C_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0xC];
    u16 unk_14;
} S_8102F20C_3;   /* out in func_8102F20C */


typedef struct {
    u16 x0;
    u16 x1;
    u16 x2;
} Stack3;

extern s8 D_800DCECC[];
extern s16 D_80083228[5];
extern s32 D_800814A0[3];
extern s32 func_80065420(void *, void *, void *, void *);
extern void func_800478B8(void *, s32);

/* Apply a relative projected depth with a direction bias and propagate output status flags. */
void func_8102F20C(void *entity, S_8102F20C_0 *position, void *output) {
    Stack3 coords;
    M2C_UNK projection_flags;
    M2C_UNK depth_cue;
    M2C_UNK screen_xy[2];
    s16 depth_delta;
    s32 depth_bias;
    S_8102F20C_2 *base_position;
    S_8102F20C_3 *result;

    result = output;
    coords.x0 = position->unk_02;
    coords.x1 = position->unk_06;
    coords.x2 = position->unk_0A;
    depth_delta = func_80065420(&coords.x0, &screen_xy, &depth_cue, &projection_flags);
    base_position = ((S_8102F20C_1 *)entity)->unk_28;
    coords.x0 = base_position->unk_02;
    coords.x1 = base_position->unk_06;
    coords.x2 = base_position->unk_0A;
    depth_delta = depth_delta - func_80065420(&coords.x0, &screen_xy, &depth_cue, &projection_flags);
    depth_bias = D_800DCECC[((s32) (*D_80083228 + ((S_8102F20C_1 *)entity)->unk_1C + 0x100) >> 9) & 7] * 2;
    depth_delta = depth_delta + depth_bias;
    result->unk_14 = (u16) (result->unk_14 & 0xFF7F);
    result->unk_06 = depth_delta;
    func_800478B8(result, depth_bias);
    if (result->unk_14 & 0x6000) {
        ((S_8102F20C_1_pre *)entity)[-1].unk_00 = (u16) (((S_8102F20C_1_pre *)entity)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
