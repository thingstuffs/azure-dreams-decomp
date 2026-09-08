#include "common.h"

typedef struct S_80024FD8_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80024FD8_0;   /* temp_v0 in func_80024FD8 */

typedef struct S_80024FD8_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024FD8_1;   /* temp_v1 in func_80024FD8 */

typedef struct S_80024FD8_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024FD8_2;   /* arg0 in func_80024FD8 */

typedef struct S_80024FD8_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x4];
    s16 unk_16;
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    s16 unk_1E;
} S_80024FD8_3;   /* temp_s0 in func_80024FD8 */

typedef struct S_80024FD8_4 {
    u8 pad_00[0x14];
    s16 unk_14;
    u8 pad_16[0x8];
    s16 unk_1E;
    u8 pad_20[0x4];
    s16 unk_24;
} S_80024FD8_4;   /* temp_v1_2 in func_80024FD8 */



extern void *func_8003FC64();
extern void func_8004491C();
extern void func_8003DB94();

extern u8 D_80024EE0[];
extern u8 D_80025854[];
extern u8 D_80045C34[];
extern u16 D_800257CC;

/* Creates a render object at the supplied position and initializes its effect state. */
void *func_80024FD8(S_80024FD8_2 *source_pos, s16 effect_param, s16 size)
{
    s32 signed_size;
    s32 render_code;
    u16 object_count;
    S_80024FD8_3 *render_state;
    void *object;
    S_80024FD8_1 *position;
    S_80024FD8_4 *effect_state;

    object = func_8003FC64(0x202);
    if (object != 0) {
        ((S_80024FD8_0 *)object)->unk_10 = D_80024EE0;
        func_8004491C(object, D_80045C34);
        position = ((S_80024FD8_0 *)object)->unk_08;
        position->unk_02 = source_pos->unk_02;
        position->unk_06 = source_pos->unk_06;
        position->unk_0A = source_pos->unk_0A;
        render_state = ((S_80024FD8_0 *)object)->unk_0C;
        render_state->unk_0C = 0x808080;
        render_state->unk_1C = 0x400;
        render_state->unk_1E = 0x1CCC;
        func_8003DB94(render_state, D_80025854, 0);
        signed_size = (s16)size;
        render_state->unk_18 = (signed_size << 8) - 0x400;
        render_code = 0x60;
           /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        effect_state = (u8 *)object + 0x20;
           /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        render_state->unk_10 = render_code;
        object_count = D_800257CC;
        render_state->unk_16 = 0x400;
        effect_state->unk_24 = size;
        effect_state->unk_14 = effect_param;
        effect_state->unk_1E = signed_size * 2;
        D_800257CC = object_count + 1;
    }
    return object;
}

/* MECHANISM: Natural argument liveness preserves the retail 0x28 frame and s0-s4 save contract.
   The guarded a0/v1 roles share one signed arg2 conversion and hold the three-store destination base.
   An unpinned 0x60 local plus ordered keeps yields the exact li/addiu/lui/sh/lhu counter schedule. */
