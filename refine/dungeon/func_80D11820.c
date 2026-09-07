#include "common.h"
#include "m2c_compat.h"

typedef struct S_80171020_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80171020_4;   /* temp_v0 in func_80171020 */

typedef struct S_80171020_5 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80171020_5;   /* arg0 in func_80171020 */

typedef struct S_80171020_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80171020_6;   /* ((S_80171020_4 *)temp_v0)->unk_08 in func_80171020 */

typedef struct S_80171020_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80171020_7;   /* ((S_80171020_5 *)arg0)->unk_08 in func_80171020 */




void *func_8003FD64();
M2C_UNK func_8004491C();
s32 rand();
extern M2C_UNK D_80170D2C;
extern M2C_UNK D_80170F0C;

typedef struct S_80171020_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80171020_0;   /* temp_v0 in func_80171020 */

typedef struct S_80171020_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0xA];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x8];
    s32 unk_54;
} S_80171020_1;   /* temp_s0 in func_80171020 */

typedef struct S_80171020_2 {
    s32 unk_00;
} S_80171020_2;   /* temp_a2 in func_80171020 */

typedef struct S_80171020_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80171020_3;   /* temp_a2_2 in func_80171020 */

/* Spawns an effect at an offset from its parent with randomized velocity. */
void func_80171020(S_80171020_5 *parent, s16 effect_id, s32 effect_param, s32 unused, volatile s32 x_offset, volatile s32 y_offset, volatile s32 z_offset) {
    register s32 offset_x = x_offset;
    register s32 offset_y = y_offset;
    register s32 offset_z = z_offset;
    register s16 saved_effect_id = effect_id;
    register s32 saved_effect_param = effect_param;
    S_80171020_2 *position_x;
    S_80171020_3 *position_y;
    S_80171020_1 *effect_state;
    void *effect;

    effect = func_8003FD64(0x211, parent);
    if (effect == NULL) {
        return;
    }
    ((S_80171020_0 *)effect)->unk_10 = &D_80170F0C;
    ((S_80171020_6 *)(((S_80171020_4 *)effect)->unk_08))->unk_02 = (s16) (((S_80171020_7 *)(parent->unk_08))->unk_02 + offset_x);
    ((S_80171020_6 *)(((S_80171020_4 *)effect)->unk_08))->unk_06 = (s16) (((S_80171020_7 *)(parent->unk_08))->unk_06 + offset_y);
    ((S_80171020_6 *)(((S_80171020_4 *)effect)->unk_08))->unk_0A = (s16) (((S_80171020_7 *)(parent->unk_08))->unk_0A + offset_z);
    effect_state = effect + 0x20;
    effect_state->unk_40 = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
    effect_state->unk_44 = (s32) (((rand() & 0x7FFF) - 0x4000) * 0x10);
    effect_state->unk_48 = (s32) (((rand() & 0x3FFF) - 0x6000) * 0x10);
    position_x = ((S_80171020_0 *)effect)->unk_08;
    position_x->unk_00 = (s32) (position_x->unk_00 + (effect_state->unk_40 * 2));
    position_y = ((S_80171020_0 *)effect)->unk_08;
    position_y->unk_04 = (s32) (position_y->unk_04 + (effect_state->unk_44 * 2));
    effect_state->unk_54 = 0x8000;
    effect_state->unk_14 = saved_effect_id;
    effect_state->unk_32 = 0x14;
    effect_state->unk_34 = 0x14;
    func_8004491C(effect, &D_80170D2C, position_y);
    ((S_80171020_0 *)effect)->unk_20 = saved_effect_param;
    effect_state->unk_08 = saved_effect_param;
}
