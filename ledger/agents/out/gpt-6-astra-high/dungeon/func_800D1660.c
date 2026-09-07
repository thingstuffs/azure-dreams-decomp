#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80083498[];
extern s16 D_80083228[5];
void *func_8003FD64(s32, void *);       /* extern */
void func_8004491C(void *, void *, void *, void *); /* extern */
s32 func_800644B8(s32);                           /* extern */
s32 func_80064584(s32);                           /* extern */
void func_80047784(void *, u8, s32);              /* extern */
extern M2C_UNK D_800D67B0;
extern M2C_UNK D_800D6C18[2];
extern M2C_UNK D_800E23D8;

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} CopyQuad;

typedef struct {
    u8 pad[8];
    void *field8;
    void *fieldc;
    void *field10;
} AllocBlock;

typedef struct S_800D6DC0_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u8 pad_18[0x2C];
    s16 unk_44;
    s16 unk_46;
    s16 unk_48;
    s16 unk_4A;
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
} S_800D6DC0_0;   /* temp_s2 in func_800D6DC0 */

typedef struct S_800D6DC0_1 {
    u8 pad_00[0xC];
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
    u8 pad_20[0xC];
    M2C_UNK * unk_2C;
} S_800D6DC0_1;   /* temp_s3 in func_800D6DC0 */

typedef struct S_800D6DC0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_800D6DC0_2;   /* temp_s0 in func_800D6DC0 */

typedef struct S_800D6DC0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D6DC0_3;   /* arg1 in func_800D6DC0 */

typedef struct S_800D6DC0_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_800D6DC0_4;   /* arg3 in func_800D6DC0 */

/* Creates eight radial effect segments using the source position and render data. */
void func_800D6DC0(void *unused, S_800D6DC0_3 *origin, void *render_template, S_800D6DC0_4 *orientation) {
    s32 end_y_scaled;
    s32 start_angle;
    s32 copy_end;
    s32 start_x;
    s32 end_x;
    s32 start_y;
    s32 end_y;
    s32 end_angle;
    s32 segment;
    S_800D6DC0_2 *position;
    S_800D6DC0_0 *effect_state;
    S_800D6DC0_1 *render_data;
    void *effect;
    void *copy_dst;
    void *copy_src;
    u8 *direction_table;
    s32 scale = 3;

    segment = 0;
    direction_table = (u8 *)&D_800E23D8;
    end_angle = 0x200;
    do {
        effect = func_8003FD64(0x112, D_80083498);
        effect_state = effect + 0x20;
        if (effect != NULL) {
            copy_src = render_template;
            effect_state->unk_0C = 0x1E;
            effect_state->unk_0E = 0x1E;
            effect_state->unk_14 = origin;
            effect_state->unk_10 = segment;
            render_data = ((AllocBlock *)effect)->fieldc;
            ((AllocBlock *)effect)->field10 = &D_800D6C18;
            copy_end = (s32)((u8 *)copy_src + 0x30);
            copy_dst = render_data;
            do {
                *(CopyQuad *)copy_dst = *(CopyQuad *)copy_src;
                copy_src += 0x10;
                copy_dst += 0x10;
            } while (copy_src != (void *)copy_end);
            render_data->unk_10 = 0x20;
            render_data->unk_14 = (u16) (render_data->unk_14 | 0xC);
            func_8004491C(effect, &D_800D67B0, copy_dst, copy_src);
            position = ((AllocBlock *)effect)->field8;
            position->unk_02 = (u16) origin->unk_02;
            start_angle = segment << 9;
            position->unk_06 = (u16) origin->unk_06;
            position->unk_0A = (s16) (origin->unk_0A + 0x28);
            render_data->unk_1E = 0x1000;
            render_data->unk_1C = 0x1000;
            render_data->unk_0E = 0xFA;
            render_data->unk_0D = 0xFA;
            render_data->unk_0C = 0xFA;
            start_x = (s32) (scale * func_80064584(start_angle)) >> 0xC;
            effect_state->unk_48 = (s16) start_x;
            effect_state->unk_44 = (s16) start_x;
            end_x = (s32) (scale * func_80064584(end_angle)) >> 0xC;
            effect_state->unk_4A = (s16) end_x;
            effect_state->unk_46 = (s16) end_x;
            start_y = (s32) (scale * func_800644B8(start_angle)) >> 0xC;
            effect_state->unk_50 = (s16) start_y;
            effect_state->unk_4C = (s16) start_y;
            end_y_scaled = scale * func_800644B8(end_angle);
            effect_state->unk_5A = 0;
            effect_state->unk_58 = 0;
            effect_state->unk_56 = 0;
            effect_state->unk_54 = 0;
            end_y = end_y_scaled >> 0xC;
            effect_state->unk_52 = (s16) end_y;
            effect_state->unk_4E = (s16) end_y;
            position->unk_16 = 0;
            render_data->unk_2C = direction_table;
            func_80047784(render_data, *((u8 *) (((((s32) (*D_80083228 + orientation->unk_2A + 0x100) >> 9) & 7) + (s32) direction_table))), 0);
        }
        segment += 1;
        end_angle += 0x200;
    } while (segment < 8);
    return;
}
