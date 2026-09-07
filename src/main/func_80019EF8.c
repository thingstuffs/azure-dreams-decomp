#include "common.h"

extern void func_8007BEF0(s32 arg0);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern s32 func_8007C9A8(s32 arg0);
extern void func_8007CA38(void);
extern void func_8007CA48(void);

extern s32 D_80400004[];
extern s32 D_8040002C[];

void func_80019EF8(void) {
    func_8007CA38();
    if (func_8007C9A8(*(s32 *)0x80409270) == 0) {
        func_8007C040(D_80400004, D_8040002C, 0xFD);
        func_8007BEF0(1);
    }
    if (func_8007C9A8(*(s32 *)0x80409274) == 0) {
        func_8007C040(D_80400004, D_8040002C, 0xFF);
        func_8007BEF0(1);
    }
    if (func_8007C9A8(*(s32 *)0x80409278) == 0) {
        func_8007C040(D_80400004, D_8040002C, 0x101);
        func_8007BEF0(1);
    }
    if (func_8007C9A8(*(s32 *)0x8040927C) == 0) {
        func_8007C040(D_80400004, D_8040002C, 0x103);
        func_8007BEF0(1);
    }
    if (func_8007C9A8(*(s32 *)0x80409280) == 0) {
        func_8007C040(D_80400004, D_8040002C, 0x105);
        func_8007BEF0(1);
    }
    if (func_8007C9A8(*(s32 *)0x80409284) == 0) {
        func_8007C040(D_80400004, D_8040002C, 0x107);
        func_8007BEF0(1);
    }
    if (func_8007C9A8(*(s32 *)0x80409288) == 0) {
        func_8007C040(D_80400004, D_8040002C, 0x109);
        func_8007BEF0(1);
    }
    if (func_8007C9A8(*(s32 *)0x8040928C) == 0) {
        func_8007C040(D_80400004, D_8040002C, 0x10B);
        func_8007BEF0(1);
    }
    func_8007CA48();
}
