#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800247B8_arg1.h"

typedef struct {
    u8 bytes[12];
} U12;

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80045340[];
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();                /* extern */
extern M2C_UNK D_800249FC;
extern M2C_UNK D_80025B48;

typedef struct S_80024AEC_0 {
    u8 pad_00[0x5A];
    s16 unk_5A;
    s16 unk_5C;
    u8 pad_5E[0x2A];
    s32 unk_88;
} S_80024AEC_0;   /* temp_v1 in func_80024AEC */

typedef struct S_80024AEC_1 {
    u8 pad_00[0x88];
    s32 unk_88;
} S_80024AEC_1;   /* arg0 in func_80024AEC */

typedef struct S_80024AEC_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80024AEC_2;   /* temp_v0 in func_80024AEC */

typedef struct S_80024AEC_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024AEC_3;   /* temp_a3 in func_80024AEC */

typedef struct S_80024AEC_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024AEC_4;   /* temp_v1_2 in func_80024AEC */


/* Create an effect at the supplied position and initialize its rendering state. */
void func_80024AEC(S_80024AEC_1 *source, Rec_func_800247B8_arg1 *position) {
    S_80024AEC_3 *render_state;
    void *effect;
    S_80024AEC_0 *effect_state;
    S_80024AEC_4 *effect_position;

    effect = func_8003FC64(0x12);
    effect_state = effect + 0x20;
    if (effect != NULL) {
        effect_state->unk_5A = 0x3C;
        effect_state->unk_5C = 0x3C;
        effect_state->unk_88 = (s32) source->unk_88;
        ((S_80024AEC_2 *)effect)->unk_10 = &D_800249FC;
        func_8004491C(effect, D_80045340);
        render_state = ((S_80024AEC_2 *)effect)->unk_0C;
        render_state->unk_10 = 0x40;
        render_state->unk_06 = 0xA;
        render_state->unk_14 = (u16) (render_state->unk_14 | 0xC);
        effect_position = ((S_80024AEC_2 *)effect)->unk_08;
        effect_position->unk_02 = (u16) position->unk_02;
        effect_position->unk_06 = (u16) position->unk_06;
        effect_position->unk_0A = (u16) position->unk_0A;
        render_state = ((S_80024AEC_2 *)effect)->unk_0C;
        render_state->unk_0E = 0x50;
        render_state->unk_0D = 0x50;
        render_state->unk_0C = 0x50;
        render_state->unk_1E = 0;
        render_state->unk_1C = 0;
        *(U12 *)((u8 *)effect + 0x96) = *(U12 *)&D_80025B48;
        render_state->unk_08 = (void *) (effect + 0x96);
    }
}
