#include "common.h"
#include "records/Rec_D_80082E80.h"
typedef long long M2C_S64;

typedef struct S_8102F0D4_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8102F0D4_0;   /* arg1 in func_8102F0D4 */

typedef struct S_8102F0D4_1_pre {
    u16 unk_00;
} S_8102F0D4_1_pre;   /* the 0x2 bytes before arg0 in func_8102F0D4, addressed as arg0[-1] */

typedef struct S_8102F0D4_1 {
    u8 pad_00[0x94];
    s16 unk_94;
    u16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
} S_8102F0D4_1;   /* arg0 in func_8102F0D4 */

typedef struct S_8102F0D4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8102F0D4_2;   /* temp_v1 in func_8102F0D4 */



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s8 D_800DCECC[];
extern s16 D_80083228[5];
extern s32 D_800814A0[3];
s32 func_80065420();
extern s32 func_800478B8();

/* Updates relative depth with a direction offset and flags expiration when the countdown ends. */
void func_8102F0D4(void *state, S_8102F0D4_0 *position, Rec_D_80082E80 *entity) {
    u16 coords[3];
    M2C_S64 transform_result;
    s16 transform_aux;
    M2C_UNK transform_flags;
    s32 position_depth;
    s32 reference_depth;
    s8 *direction_offset;
    u16 ticks_left;
    S_8102F0D4_2 *reference_pos;

    coords[0] = position->unk_02;
    coords[1] = position->unk_06;
    coords[2] = position->unk_0A;
    position_depth = func_80065420(coords, &transform_result, &transform_aux, &transform_flags);
    reference_pos = ((S_8102F0D4_1 *)state)->unk_A8;
    coords[0] = reference_pos->unk_02;
    coords[1] = reference_pos->unk_06;
    coords[2] = reference_pos->unk_0A;
    reference_depth = func_80065420(coords, &transform_result, &transform_aux, &transform_flags);
    direction_offset = &D_800DCECC[((s32) (*D_80083228 + ((S_8102F0D4_1 *)state)->unk_94 + 0x100) >> 9) & 7];
    entity->unk_06.as_s16 = (s16) ((position_depth - reference_depth) - (*direction_offset * 2));
    func_800478B8(entity, direction_offset);
    ticks_left = ((S_8102F0D4_1 *)state)->unk_96 - 1;
    ((S_8102F0D4_1 *)state)->unk_96 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        ((S_8102F0D4_1_pre *)state)[-1].unk_00 = (u16) (((S_8102F0D4_1_pre *)state)[-1].unk_00 | 0x8000);
        D_800814A0[0] = D_800814A0[0] | 0x8000;
    }
}
