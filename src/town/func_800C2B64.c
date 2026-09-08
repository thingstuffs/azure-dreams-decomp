#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C02C4_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x1C];
    s16 unk_20;
    s16 unk_22;
    u8 pad_24[0x4];
    s16 unk_28;
} S_800C02C4_0;   /* arg0 in func_800C02C4; pointer addresses record offset 0x10 */

typedef struct S_800C02C4_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    M2C_UNK * unk_2C;
} S_800C02C4_1;   /* arg2 in func_800C02C4 */


M2C_UNK func_80033D08();                      /* extern */
M2C_UNK func_80094A38();           /* extern */
M2C_UNK func_800A643C();          /* extern */
M2C_UNK func_800A647C();          /* extern */
extern M2C_UNK D_800A62E8;
extern M2C_UNK D_800A630C;
extern M2C_UNK D_800C035C;
extern M2C_UNK D_800D0C58;

/* Initializes object and rendering data and registers its resources. */
void func_800C02C4(void *object_data, void *unused, S_800C02C4_1 *render_data) {
    ((S_800C02C4_0 *)((u8 *)object_data - 0x10))->unk_00 = &D_800C035C;
    ((S_800C02C4_0 *)((u8 *)object_data - 0x10))->unk_22 = -1;
    ((S_800C02C4_0 *)((u8 *)object_data - 0x10))->unk_20 = 0xC00;
    ((S_800C02C4_0 *)((u8 *)object_data - 0x10))->unk_28 = 0xC00;
    render_data->unk_1E = 0x1000;
    render_data->unk_1C = 0x1000;
    render_data->unk_0C = 0x808080;
    render_data->unk_2C = &D_800D0C58;
    func_80094A38(&D_800D0C58, object_data);
    func_80033D08(object_data);
    func_800A647C(0x24, &D_800A62E8);
    func_800A643C(0xE4, &D_800A630C);
}
