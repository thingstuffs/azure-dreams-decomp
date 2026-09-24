#include "common.h"
#include "m2c_compat.h"

extern u8 D_80045340[];
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern M2C_UNK D_800249E0;
extern M2C_UNK D_80025FE8;

typedef struct S_81971760_0 {
    u8 pad_00[0x38];
    s16 unk_38;
    s16 unk_3A;
    u8 pad_3C[0x4];
    void * unk_40;
    u16 unk_44;
    u16 unk_46;
    u16 unk_48;
} S_81971760_0;   /* temp_s0 in func_81971760 */

typedef struct S_81971760_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_81971760_1;   /* temp_v0 in func_81971760 */

typedef struct S_81971760_2 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81971760_2;   /* temp_a3 in func_81971760 */

typedef struct S_81971760_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81971760_3;   /* temp_s1 in func_81971760 */

typedef struct S_81971760_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_81971760_4;   /* temp_arg1 in func_81971760 */

typedef struct {
    s32 y;
    s32 z;
} OffsetYZ;

/* Creates an effect at a randomized offset from the origin and initializes its rendering data. */
void func_81971760(void *unused_0, void *origin_data, s32 unused_2, s32 offset_x, OffsetYZ offset_yz) {
    u16 jittered_x;
    void *effect_arg;
    u16 coord;
    s32 random_value;
    S_81971760_2 *render_data;
    S_81971760_0 *effect_state;
    void *effect;
    S_81971760_4 *origin = origin_data;
    s32 initial_y = offset_yz.y;
    s32 initial_z = offset_yz.z;
    effect = func_8003FC64(0x212);
    if (effect != NULL) {
        effect_arg = effect;
        effect_state = effect + 0x20;
        effect_state->unk_38 = 0x1E;
        effect_state->unk_3A = 0x1E;
        effect_state->unk_44 = offset_x;
        effect_state->unk_46 = (u16) initial_y;
        effect_state->unk_48 = (u16) initial_z;
        effect_state->unk_40 = origin;
        ((S_81971760_1 *)effect)->unk_10 = &D_800249E0;
        func_8004491C(effect_arg, D_80045340);
        render_data = ((S_81971760_1 *)effect)->unk_0C;
        render_data->unk_10 = 0x20;
        render_data->unk_06 = 6;
        render_data->unk_14 = (u16) (render_data->unk_14 | 0xC);
        offset_x = (s32)((S_81971760_1 *)effect)->unk_08;
        random_value = func_80069EF8();
        coord = effect_state->unk_44;
        coord -= 0x10;
        effect_state->unk_44 = coord + (random_value & 0x1F);
        random_value = func_80069EF8();
        coord = effect_state->unk_46;
        coord -= 0x10;
        effect_state->unk_46 = coord + (random_value & 0x1F);
        random_value = func_80069EF8();
        coord = effect_state->unk_48;
        jittered_x = effect_state->unk_44;
        coord -= 0x10;
        effect_state->unk_48 = coord + (random_value & 0x1F);
        ((S_81971760_3 *)offset_x)->unk_02 = jittered_x;
        ((S_81971760_3 *)offset_x)->unk_06 = (u16) effect_state->unk_46;
        ((S_81971760_3 *)offset_x)->unk_0A = (u16) effect_state->unk_48;
        ((S_81971760_3 *)offset_x)->unk_02 = (u16) (((S_81971760_3 *)offset_x)->unk_02 + origin->unk_02);
        ((S_81971760_3 *)offset_x)->unk_06 = (u16) (((S_81971760_3 *)offset_x)->unk_06 + origin->unk_06);
        ((S_81971760_3 *)offset_x)->unk_0A = (u16) (((S_81971760_3 *)offset_x)->unk_0A + origin->unk_0A);
        render_data = ((S_81971760_1 *)effect)->unk_0C;
        render_data->unk_1E = 0x800;
        render_data->unk_1C = 0x800;
        render_data->unk_0E = 0x80;
        render_data->unk_0D = 0x80;
        render_data->unk_0C = 0x80;
        memcpy((u8 *) effect + 0xA2, (u8 *) &D_80025FE8, 12);
        render_data->unk_08 = (void *) (effect + 0xA2);
    }
}
