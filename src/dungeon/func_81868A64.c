#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_8002418C;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEDB0;

typedef struct S_81868A64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_81868A64_0;   /* temp_v0 in func_81868A64 */

typedef struct S_81868A64_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81868A64_1;   /* temp_s0 in func_81868A64 */

typedef struct S_81868A64_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_81868A64_2;   /* temp_s0_2 in func_81868A64 */

typedef struct S_81868A64_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81868A64_3;   /* arg1 in func_81868A64 */

/* Creates a grayscale effect with a randomized offset from the supplied position. */
void func_81868A64(s32 user_data, S_81868A64_3 *source_pos, s8 intensity) {
    S_81868A64_1 *render_state;
    S_81868A64_2 *effect_pos;
    S_81868A64_0 *effect;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        render_state = effect->unk_0C;
        effect->unk_10 = &D_8002418C;
        effect->unk_20 = user_data;
        render_state->unk_0E = intensity;
        render_state->unk_0D = intensity;
        render_state->unk_0C = intensity;
        func_8003DB94(render_state, &D_800DEDB0, 0);
        render_state->unk_1E = 0x1800;
        render_state->unk_1C = 0x1800;
        render_state->unk_12 = 0x7E0B;
        render_state->unk_10 = (u16) (render_state->unk_10 | 0x60);
        render_state->unk_14 = (u16) (render_state->unk_14 | 0x10C);
        func_8004491C(effect, &D_80045340);
        effect_pos = effect->unk_08;
        effect_pos->unk_02 = (u16) source_pos->unk_02;
        effect_pos->unk_06 = (u16) source_pos->unk_06;
        effect_pos->unk_0A = (s16) ((source_pos->unk_0A + (rand() % 17)) - 8);
    }
}
