#include "common.h"

typedef struct S_800CD384_0 {
    void * unk_00;
    u8 pad_04[0x23];
    u8 unk_27;
    s32 unk_28;
    u8 pad_2C[0x70];
    s16 unk_9C;
} S_800CD384_0;   /* arg0 in func_800CD384; pointer addresses record offset 0x14 */

typedef struct S_800CD384_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800CD384_1;   /* temp_v1 in func_800CD384 */


typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80099844();
extern void func_800A6508(void);
extern M2C_UNK func_800C5BBC();
extern s32 func_800C8844();
extern void func_800CD460(void);
extern M2C_UNK func_800DC1B8();
extern s32 D_800DCF1C;
extern M2C_UNK D_800E1C14;
extern u8 D_800E3D40;

s32 func_800CD384(void *arg0) {
    M2C_UNK var_a1;
    S_800CD384_1 *temp_v1;

    var_a1 = 0x40;
    if (D_800E3D40 != 0) {
        var_a1 = 0x400;
    }
    if (func_800C8844(arg0, var_a1, 8) == 0) {
        if (((S_800CD384_0 *)((u8 *)arg0 - 0x14))->unk_28 & 0x4000) {
            func_800A6508();
            return 1;
        }
        return 1;
    }
    func_80099844(arg0, &D_800E1C14);
    if (((S_800CD384_0 *)((u8 *)arg0 - 0x14))->unk_27 == 0) {
        func_800DC1B8(D_800DCF1C);
    }
    temp_v1 = ((S_800CD384_0 *)((u8 *)arg0 - 0x14))->unk_00;
    if (!(temp_v1->unk_14 & 0x8000)) {
        func_800C5BBC((temp_v1->unk_24 << 6) | 0x20,
                      (temp_v1->unk_25 << 6) | 0x20,
                      ((S_800CD384_0 *)((u8 *)arg0 - 0x14))->unk_9C, 0x802080, 0x20, 1);
    }
    return 1;
}
