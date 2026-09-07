#include "common.h"
typedef s32 M2C_UNK;

typedef struct S_800A5FC0_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800A5FC0_0;   /* temp_v1 in func_800A5FC0 */

typedef struct S_800A5FC0_1 {
    void * unk_00;
} S_800A5FC0_1;   /* &D_80083160 in func_800A5FC0 */

typedef struct S_800A5FC0_2 {
    s32 unk_00;
    s32 unk_04;
    u16 unk_08;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    s16 unk_0C;
} S_800A5FC0_2;   /* arg0 in func_800A5FC0 */

typedef struct S_800A5FC0_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u16 unk_0C;
    s16 unk_0E;
    s32 unk_10;
    u16 unk_14;
    s16 unk_16;
} S_800A5FC0_3;   /* temp_s0 in func_800A5FC0 */

typedef struct S_800A5FC0_4 {
    void * unk_00;
} S_800A5FC0_4;   /* temp_s3 in func_800A5FC0 */

typedef struct S_800A5FC0_5 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_800A5FC0_5;   /* ((S_800A5FC0_1 *)(&D_80083160))->unk_00 in func_800A5FC0 */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *D_80083160[];
extern M2C_UNK func_8006658C();
extern M2C_UNK func_80066640();
extern M2C_UNK func_800666E0();
extern M2C_UNK func_80067F20();

/* Advance a rectangle's right edge toward 320 and queue it for rendering. */
s32 func_800A5FC0(S_800A5FC0_2 *state) {
    u16 frames_left;
    u16 right_x;
    void *quad;
    void *draw_mode;
    S_800A5FC0_0 *render_ctx;
    void **render_ctx_ref;

    render_ctx = D_80083160[0];
    draw_mode = render_ctx->unk_8D0;
    render_ctx->unk_8D0 = (void *) (draw_mode + 0xC);
    quad = ((S_800A5FC0_5 *)(((S_800A5FC0_1 *)(&D_80083160))->unk_00))->unk_8D0;
    ((S_800A5FC0_5 *)(((S_800A5FC0_1 *)(&D_80083160))->unk_00))->unk_8D0 = (void *) (quad + 0x18);
    render_ctx_ref = (void **)&D_80083160;
    func_80067F20(draw_mode, 0, 0, state->unk_04, 0);
    ((S_800A5FC0_3 *)quad)->unk_04 = (s32) state->unk_00;
    func_800666E0(quad);
    func_80066640(quad, 1);
    ((S_800A5FC0_3 *)quad)->unk_10 = 0xE00000;
    ((S_800A5FC0_3 *)quad)->unk_08 = 0;
    ((S_800A5FC0_3 *)quad)->unk_0E = 0;
    ((S_800A5FC0_3 *)quad)->unk_16 = 0xE0;
    frames_left = state->unk_08 - 1;
    state->unk_08 = frames_left;
    if ((s16) frames_left <= 0)
        goto zero_case;
    {
        s32 x_delta = 0x140 - state->unk_0A.s;
        state->unk_0A.s = state->unk_0A.u + x_delta / (s16) frames_left;
    }
    goto common_case;
zero_case:
    state->unk_08 = 0U;
    state->unk_0A.s = 0x140;
common_case:
    right_x = (u16) state->unk_0A.s;
    ((S_800A5FC0_3 *)quad)->unk_14 = right_x;
    ((S_800A5FC0_3 *)quad)->unk_0C = right_x;
    func_8006658C((u8 *)((S_800A5FC0_4 *)render_ctx_ref)->unk_00 + ((state->unk_0C * 4) + 0x70), quad);
    func_8006658C((u8 *)((S_800A5FC0_4 *)render_ctx_ref)->unk_00 + ((state->unk_0C * 4) + 0x70), draw_mode);
    return 0;
}
