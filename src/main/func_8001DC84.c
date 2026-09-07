#include "common.h"

extern u8 D_8040062C[];
extern u8 D_80400654[];
extern u8 D_8040861C[];
extern u8 D_804F281B[];
extern u8 D_805030EF[];

extern void *func_8003C714(s32 arg0, void *arg1, s32 arg2);
extern void func_80040560(void *arg0, void *arg1);
extern s32 func_80047FD8(void *arg0);
extern void func_8007BEF0(s32 arg0);
extern void func_8007BFE0(void *arg0, s32 arg1);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern s32 func_804046C8(void *arg0);
extern s32 func_80404B5C(s32 arg0);
extern void func_80404B84(void *arg0, s32 arg1);
extern void func_80404C44(void *arg0, s32 arg1);
extern s32 func_80404D40(void *arg0);
extern void func_80404DBC(void *arg0);

typedef struct {
    u8 pad_00[4];
    s32 field_04;
    u8 pad_08[0x214];
    s32 field_21C;
    s32 field_220;
} Obj;

typedef struct {
    u8 pad_00[0x0C];
    u8 *field_0C;
    void *field_10;
    u8 pad_14[0x0A];
    u16 flags;
    Obj obj;
} Root;

extern Root D_8040B1D0;

s32 func_8001DC84(s32 arg0, s32 arg1) {
    Root *base;
    Obj *obj;
    register Obj *tail_obj ASM_REG("$17");   /* MATCH pin: retail keeps a computation the compiler would drop */

    base = &D_8040B1D0;
    obj = &base->obj;

    if (func_80047FD8(base) == 0) {
        base = (Root *)func_8003C714(0, base, 0xC9);
        if (base == 0) {
            func_8007C040(D_8040062C, D_80400654, 0x17A);
            func_8007BEF0(1);
        }
        func_80040560(base, D_8040861C);
        return func_80404D40(obj);
    }
    func_80404DBC(base);
    {
        u16 flags = D_8040B1D0.flags;
        flags &= 0x7FFF;
        D_8040B1D0.flags = flags;
    }
    func_8007BFE0(obj, 0x304);
    D_804F281B[0] = 8;
    D_805030EF[0] = 8;
    func_80404B84(obj, 7);
    tail_obj = obj;
    ASM_KEEP(tail_obj);   /* MATCH pin: retail immediate-load split depends on it */
    ASM_KEEP(base);   /* MATCH pin: keeps a constant in a register as retail does */
    base->field_0C = (u8 *)tail_obj + 0x210;
    tail_obj->field_21C = func_80404B5C(tail_obj->field_220);
    func_80404C44(tail_obj, (tail_obj->field_04 = arg1, arg0));
    func_804046C8((base->field_10 = func_804046C8, tail_obj));
    return (s32)base;
}
