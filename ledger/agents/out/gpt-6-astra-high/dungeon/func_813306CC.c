#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_80167540[3];
extern u8 D_80045340[];
extern u8 D_800DEAE0[];
extern void *func_8003FC64(s32);
extern M2C_UNK func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);

typedef struct S_801676CC_0 {
    u8 pad_00[0x18];
    s16 unk_18;
    s16 unk_1A;
} S_801676CC_0;   /* temp_v0_2 in func_801676CC */

typedef struct S_801676CC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_801676CC_1;   /* temp_v0 in func_801676CC */

typedef struct S_801676CC_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_801676CC_2;   /* temp_a0 in func_801676CC */

typedef struct S_801676CC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801676CC_3;   /* temp_a0_2 in func_801676CC */

typedef struct S_801676CC_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801676CC_4;   /* arg0 in func_801676CC */

typedef struct S_801676CC_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_801676CC_5;   /* temp_a0_3 in func_801676CC */

/* Creates sixteen effects at the given position with increasing sprite scales. */
void func_801676CC(S_801676CC_4 *origin) {
    s16 scale_x;
    s16 scale_y;
    s32 effect_index;
    s16 initial_ticks;
    void *effect_data;
    S_801676CC_2 *render_params;
    S_801676CC_3 *position;
    S_801676CC_5 *sprite;
    void *effect;
    S_801676CC_0 *effect_state;

    effect_index = 0;
    initial_ticks = 0xE;
    effect_data = &D_80167540;
    scale_y = 0x1000;
    scale_x = 0x1400;
    do {
        effect = func_8003FC64(0x212);
        if (effect != NULL) {
            effect_state = effect + 0x20;
            effect_state->unk_18 = initial_ticks;
            effect_state->unk_1A = initial_ticks;
            ((S_801676CC_1 *)effect)->unk_10 = effect_data;
            func_8004491C(effect, D_80045340);
            render_params = ((S_801676CC_1 *)effect)->unk_0C;
            render_params->unk_10 = 0x60;
            render_params->unk_14 = (u16) (render_params->unk_14 | 0xC);
            position = ((S_801676CC_1 *)effect)->unk_08;
            position->unk_00 = (s32) origin->unk_00;
            position->unk_04 = (s32) origin->unk_04;
            position->unk_08 = (s32) (origin->unk_08 + 0xFFC00000);
            sprite = ((S_801676CC_1 *)effect)->unk_0C;
            sprite->unk_1C = scale_x;
            sprite->unk_1E = scale_y;
            sprite->unk_0E = 0;
            sprite->unk_0D = 0;
            sprite->unk_0C = 0;
            sprite->unk_06 = 0;
            sprite->unk_12 = 0x7DCF;
            sprite->unk_14 = (u16) (sprite->unk_14 | 0x100);
            func_8003DB94(sprite, D_800DEAE0, 0);
        }
        scale_y += 0x200;
        effect_index += 1;
        scale_x += 0x200;
    } while (effect_index < 0x10);
}
