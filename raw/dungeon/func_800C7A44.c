#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80099844(void *, void *);
extern void func_800A56E0(s32);
extern void func_800A6508(void);
extern void func_800C5BBC(s32, s32, s32, s32, s32, s32);
extern s32 func_800C8ABC(void *, s32, s32);
extern void func_800CD280(void);
extern void func_800DC1B8(s32);
extern s32 D_800DCF0C;
extern u8 D_800E1BF3[];
extern u8 D_800E3D40[];

s32 func_800CD1A4(void *arg0) {
    s32 var_a1;
    void *temp_v1;

    var_a1 = 0x40;
    if (D_800E3D40[0] != 0) {
        var_a1 = 0x400;
    }
    if (func_800C8ABC(arg0, var_a1, 0x10) == 0) {
        if (M2C_FIELD(arg0, u8 *, 0x13) == 0) {
            func_800A6508();
            func_800CD280();
            return 1;
        }
        return 1;
    }
    func_80099844(arg0, &D_800E1BF3);
    if (M2C_FIELD(arg0, u8 *, 0x13) == 0) {
        func_800DC1B8(D_800DCF0C);
    }
    temp_v1 = M2C_FIELD(arg0, void **, -0x14);
    if (!(M2C_FIELD(temp_v1, u16 *, 0x14) & 0x8000)) {
        func_800C5BBC((M2C_FIELD(temp_v1, u8 *, 0x24) << 6) | 0x20,
                      (M2C_FIELD(temp_v1, u8 *, 0x25) << 6) | 0x20,
                      M2C_FIELD(arg0, s16 *, 0x88), 0x808080, 0x20, 0);
        func_800A56E0(0x520);
    }
    return 1;
}
