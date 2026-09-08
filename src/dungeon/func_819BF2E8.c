#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_800247C0;
extern M2C_UNK D_80045340;

typedef struct S_80024AE8_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s16 unk_28;
    s16 unk_2A;
} S_80024AE8_0;   /* temp_v0_2 in func_80024AE8 */

typedef struct S_80024AE8_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80024AE8_1;   /* temp_v0 in func_80024AE8 */

typedef struct S_80024AE8_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80024AE8_2;   /* temp_v1 in func_80024AE8 */

typedef struct S_80024AE8_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80024AE8_3;   /* arg1 in func_80024AE8 */

typedef struct S_80024AE8_4 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80024AE8_4;   /* temp_v1_2 in func_80024AE8 */

/* Create and initialize an effect at the supplied position. */
void func_80024AE8(s32 effect_value, S_80024AE8_3 *position) {
    void *effect;
    S_80024AE8_0 *effect_state;
    S_80024AE8_2 *effect_position;
    S_80024AE8_4 *render_state;

    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        effect_state = effect + 0x20;
        effect_state->unk_28 = 0x1E;
        effect_state->unk_2A = 0x1E;
        effect_state->unk_20 = effect_value;
        ((S_80024AE8_1 *)effect)->unk_10 = &D_800247C0;
        func_8004491C(effect, &D_80045340);
        effect_position = ((S_80024AE8_1 *)effect)->unk_08;
        effect_position->unk_00 = (s32) position->unk_00;
        effect_position->unk_04 = (s32) position->unk_04;
        effect_position->unk_08 = (s32) position->unk_08;
        render_state = ((S_80024AE8_1 *)effect)->unk_0C;
        render_state->unk_14 = (u16) (render_state->unk_14 | 0x80);
    }
}
