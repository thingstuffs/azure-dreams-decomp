#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(void *);

extern s32 func_80047FD8(void *arg0);
extern s32 func_8003C714(s32 arg0, void *arg1, s32 arg2);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern void func_8007BEF0(s32 arg0);
extern void func_80040560(s32 arg0, void *arg1);
extern s32 func_80403C78(void *arg0);
extern void func_80403D24(void *arg0);
extern void func_8007BFE0(void *arg0, s32 arg1);
extern void func_80403AC8(void *arg0, s32 arg1);
extern s32 func_80403AA0(void *arg0);
extern void func_80403B84(void *arg0, s32 arg1);
extern void func_804034D8(void *arg0);

extern u8 D_804005A0[];
extern u8 D_804005C8[];
extern u8 D_8040861C[];
extern u8 D_80409C90[];
extern u16 D_80409CAE;

s32 func_8001CBC4(s32 arg0) {
    s32 result;
    s32 status;
    u8 *object = D_80409C90;
    u8 *subobject;
    register u8 *callarg ASM_REG("$4");

    ASM_KEEP_NV(object);
    callarg = object;
    subobject = object + 0x20;
    status = func_80047FD8(callarg);
    if (status == 0) {
        result = func_8003C714(0, object, 0x118);
        if (result == 0) {
            func_8007C040(D_804005A0, D_804005C8, 0x151);
            func_8007BEF0(1);
        }
        func_80040560(result, D_8040861C);
        return func_80403C78(subobject);
    }
    func_80403D24(object);
    D_80409CAE &= 0x7FFF;
    func_8007BFE0(subobject, 0x440);
    func_80403AC8(subobject, 0x12);
    ASM_KEEP_NV(subobject);
    FIELD(object, void *, 0xC) = subobject + 0x1A8;
    FIELD(subobject, s32, 0x1B4) = func_80403AA0(subobject + 0x1B8);
    func_80403B84(subobject, arg0);
    FIELD(object, Callback, 0x10) = func_804034D8;
    func_804034D8(subobject);
    return (s32)object;
}
