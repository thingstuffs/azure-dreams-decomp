#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C52D0_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800C52D0_6;   /* temp_a0 in func_800C52D0 */

typedef struct S_800C52D0_7 {
    u8 pad_00[0x3];
    s8 unk_03;
} S_800C52D0_7;   /* ((S_800C52D0_6 *)temp_a0)->unk_08 in func_800C52D0 */




extern const s32 D_800D5138;
extern s32 D_800D513C;

typedef struct S_800C52D0_0 {
    u8 pad_00[0x9C];
    void * unk_9C;
} S_800C52D0_0;   /* arg0 in func_800C52D0 */

typedef struct S_800C52D0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800C52D0_1;   /* temp_v0 in func_800C52D0 */

typedef struct S_800C52D0_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800C52D0_2;   /* arg1 in func_800C52D0 */

typedef struct S_800C52D0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800C52D0_3;   /* temp_a3 in func_800C52D0 */

typedef struct S_800C52D0_4 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800C52D0_4;   /* temp_a0 in func_800C52D0 */

typedef struct S_800C52D0_5 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_800C52D0_5;   /* arg2 in func_800C52D0 */

/* Computes an offset position and subtracts 0x20 from the output state. */
void func_800C52D0(S_800C52D0_0 *object, S_800C52D0_2 *out_pos, S_800C52D0_5 *state) {
    s32 z_product;
    S_800C52D0_4 *offsets;
    S_800C52D0_3 *base_pos;
    S_800C52D0_1 *object_data;

    object_data = object->unk_9C;
    base_pos = object_data->unk_08;
    offsets = object_data->unk_0C;
    out_pos->unk_04 = (s32) base_pos->unk_04;
    out_pos->unk_00 = (s32) (base_pos->unk_00 + (offsets->unk_1C * D_800D5138));
    z_product = ((S_800C52D0_7 *)(((S_800C52D0_6 *)offsets)->unk_08))->unk_03 * offsets->unk_1E;
    if (z_product < 0) {
        z_product += 0xFFF;
    }
    out_pos->unk_08 = (s32) (base_pos->unk_08 + ((z_product >> 0xC) * D_800D513C));
    state->unk_1A = (u16) (state->unk_1A - 0x20);
}
