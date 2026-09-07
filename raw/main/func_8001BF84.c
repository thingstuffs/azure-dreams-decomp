#include "common.h"

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80409508[];
extern u8 D_80400548[];
extern u8 D_80400570[];
extern u8 D_8040861C[];
extern u8 D_80402F04[];
extern u16 D_80409526;
__asm__(".set D_80409526, 0x80409526");

s32 func_8003C714(s32, u8 *, s32);
s32 func_80040560(s32, u8 *);
s32 func_80047FD8(u8 *);
s32 func_8007BEF0(s32);
s32 func_8007BFE0(u8 *, s32);
s32 func_8007C040(u8 *, u8 *, s32);
void *func_80402DC8(u8 *);
s32 func_80402DF0(u8 *, s32);
void func_80402EBC(u8 *, s32, s32, s32, s32);
u8 *func_80403060(u8 *);
s32 func_8040343C(s32, u8 *);

u8 *func_8001BF84(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 result;
    register u8 *store_base ASM_REG("$4");
    u8 *root = D_80409508;
    u8 *child = D_80409508 + 0x20;

    if (func_80047FD8(root) == 0) {
        result = func_8003C714(0, root, 0x1E1);
        if (result == 0) {
            func_8007C040(D_80400548, D_80400570, 0x299);
            func_8007BEF0(1);
        }
        func_80040560(result, D_8040861C);
        return func_80403060(child);
    }

    func_8040343C(*(s32 *)0x80409534 != 2, root);
    D_80409526 &= 0x7FFF;
    func_8007BFE0(child, 0x764);
    func_80402DF0(child, 6);
    ASM_KEEP_NV(root);
    M2C_FIELD(root, s32 *, 0xC) = (s32)(child + 0x67C);
    result = (s32)func_80402DC8(child + 0x68C);
    store_base = child;
    ASM_KEEP_NV(store_base);
    M2C_FIELD(store_base, s32 *, 0x688) = result;
    func_80402EBC(store_base, arg0, arg1, arg2, arg3);
    M2C_FIELD(root, s32 *, 0x10) = (s32)D_80402F04;
    return root;
}
