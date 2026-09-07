#include "common.h"

typedef struct S_80024550_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80024550_0;   /* temp_v0 in func_80024550 */

typedef struct S_80024550_1 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_80024550_1;   /* temp_s2 in func_80024550 */

typedef struct S_80024550_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024550_2;   /* temp_s0 in func_80024550 */

typedef struct S_80024550_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024550_3;   /* temp_s0_2 in func_80024550 */

typedef struct S_80024550_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024550_4;   /* arg0 in func_80024550 */



extern void *func_8003FC64(s32);
extern s32 rand(void);
extern void func_8003DB94(void *, void *, s32);
extern s32 func_80064584(s32);
extern s32 func_800644B8(s32);
extern void func_8004491C(void *, void *);

extern u8 D_800244A4[];
extern u8 D_80045340[];
extern u8 D_80083160[];
extern u8 D_800DE870[];

/* Spawn an effect at a random radial offset from the given position. */
void func_80024550(S_80024550_4 *origin)
{
    s16 *scene_state;
    s32 random_value;
    s32 adjusted_random;
    S_80024550_2 *render_data;
    S_80024550_3 *position;
    S_80024550_1 *effect_state;
    void *effect;

    scene_state = (s16 *)D_80083160;
    effect = func_8003FC64(0x212);
    if (effect != 0) {
        ((S_80024550_0 *)effect)->unk_10 = D_800244A4;
        adjusted_random = rand();
        random_value = adjusted_random;
        effect_state = (u8 *)effect + 0x20;
        if (random_value < 0) {
            adjusted_random = random_value + 0xFFF;
        }
        effect_state->unk_08 = random_value - ((adjusted_random >> 12) << 12);
        render_data = ((S_80024550_0 *)effect)->unk_0C;
        render_data->unk_0E = 0x80;
        render_data->unk_0D = 0x80;
        render_data->unk_0C = 0x80;
        func_8003DB94(render_data, D_800DE870, 0);
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        render_data->unk_10 |= 0x20;
        render_data->unk_14 |= 0xC;
        render_data->unk_1A =
            (s32)(0 - ((func_80064584(effect_state->unk_08 -
                                      scene_state[0x64]) >> 4) << 8)) >> 8;
        func_8004491C(effect, D_80045340);
        position = ((S_80024550_0 *)effect)->unk_08;
        position->unk_02 = origin->unk_02 +
            ((func_800644B8(effect_state->unk_08) * 2) >> 8);
        position->unk_06 = origin->unk_06 +
            ((func_80064584(effect_state->unk_08) * 2) >> 8);
        position->unk_0A = origin->unk_0A;
    }
}
