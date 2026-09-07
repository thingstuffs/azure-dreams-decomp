#include "common.h"

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
    void *temp_v1;

    var_a1 = 0x40;
    if (D_800E3D40 != 0) {
        var_a1 = 0x400;
    }
    if (func_800C8844(arg0, var_a1, 8) == 0) {
        if (M2C_FIELD(arg0, s32 *, 0x14) & 0x4000) {
            func_800A6508();
            func_800CD460();
            return 1;
        }
        return 1;
    }
    func_80099844(arg0, &D_800E1C14);
    if (M2C_FIELD(arg0, u8 *, 0x13) == 0) {
        func_800DC1B8(D_800DCF1C);
    }
    temp_v1 = M2C_FIELD(arg0, void **, -0x14);
    if (!(M2C_FIELD(temp_v1, u16 *, 0x14) & 0x8000)) {
        func_800C5BBC((M2C_FIELD(temp_v1, u8 *, 0x24) << 6) | 0x20,
                      (M2C_FIELD(temp_v1, u8 *, 0x25) << 6) | 0x20,
                      M2C_FIELD(arg0, s16 *, 0x88), 0x802080, 0x20, 1);
    }
    return 1;
}
