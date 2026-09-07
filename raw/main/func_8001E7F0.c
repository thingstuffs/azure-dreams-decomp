#include "common.h"

extern s32 func_80047FD8(void *arg0);
extern void *func_8003C714(s32 arg0, void *arg1, s32 arg2);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_8007BEF0(s32 arg0);
extern void func_80040560(void *arg0, void *arg1);
extern void func_804058AC(void *arg0);
extern void func_804059A8(void *arg0);
extern void func_8007BFE0(void *arg0, s32 arg1);
extern void func_804056F4(void *arg0, s32 arg1);
extern s32 func_804056CC(void *arg0);
extern void func_804057B0(void *arg0, s32 arg1);
extern u8 D_8040861C[];
extern u8 D_80400738[];
extern u8 D_80400760[];

typedef struct {
    u8 pad_000[0x7C];
    s32 field_07C;
    u8 pad_080[0xA84];
    s32 field_B04;
    u8 field_B08[4];
} Obj;

typedef struct {
    u8 pad_00[0x0C];
    void *field_0C;
    s32 field_10;
    u8 pad_14[0x0A];
    u16 flags;
    Obj obj;
} Root;

extern Root D_8040B4F8;

void *func_8001E7F0(s32 arg0, s32 arg1) {
    u8 *base = (u8 *)&D_8040B4F8;
    Obj *obj = &D_8040B4F8.obj;

    if (func_80047FD8(base) == 0) {
        base = func_8003C714(0, base, 0x387);
        if (base == 0) {
            func_8007C040(D_80400738, D_80400760, 0x1A0);
            func_8007BEF0(1);
        }
        func_80040560(base, D_8040861C);
        func_804058AC(obj);
        return;
    }
    func_804059A8(base);
    D_8040B4F8.flags &= 0x7FFF;
    func_8007BFE0(obj, 0xDFC);
    obj->field_07C = arg1;
    func_804056F4(obj, 0x15);
    D_8040B4F8.field_0C = (u8 *)obj + 0xAF8;
    obj->field_B04 = func_804056CC(obj->field_B08);
    func_804057B0(obj, arg0);
    D_8040B4F8.field_10 = 0;
    return base;
}
