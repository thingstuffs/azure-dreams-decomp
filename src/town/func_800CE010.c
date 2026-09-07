#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_800C3050();
M2C_UNK func_800CB8CC();
extern M2C_UNK D_800D69DC;
extern M2C_UNK D_800D69E4;
extern M2C_UNK D_800D6A0C;
extern M2C_UNK D_800D6A10;

typedef struct S_800CB770_0 {
    u8 pad_00[0x96];
    u8 unk_96;
} S_800CB770_0;   /* arg0 in func_800CB770 */

void func_800CB770(S_800CB770_0 *arg0) {
    func_800C3050(arg0, 8, &D_800D6A0C, &D_800D6A10, &D_800D69DC, &D_800D69E4);
    func_800CB8CC(arg0, arg0->unk_96);
}
