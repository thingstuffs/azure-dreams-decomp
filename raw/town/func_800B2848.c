#include "common.h"

typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern int func_80049490();
extern M2C_UNK func_800AF254();
extern M2C_UNK func_800AF448();
extern M2C_UNK func_800AF520();
extern M2C_UNK func_800AF674();
extern M2C_UNK func_800AF784();
extern M2C_UNK func_800AF858();

void func_800AFFA8(void *arg0) {
    void *temp_v1;

    func_800AF448();
    func_800AF520(arg0);
    func_800AF674(arg0);
    func_800AF784(arg0);
    func_800AF254(M2C_FIELD(arg0, s32 *, 0xA8), arg0);
    func_800AF858(M2C_FIELD(arg0, s32 *, 0xA8), arg0);
    temp_v1 = M2C_FIELD(arg0, void **, 0);
    func_80049490(M2C_FIELD(temp_v1, s32 **, 0x20)[M2C_FIELD(temp_v1, s32 *, 0x18)]);
}
