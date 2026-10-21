#include "common.h"
#include "frontend/card.h"
#include "main/data.h"

extern void func_8007BEF0(s32 value);
extern void func_8007C040(void *ptr, void *ptr2, s32 value);
extern s32 func_8007C9A8(s32 value);
extern void func_8007CA38(void);
extern void func_8007CA48(void);

/* Checks eight c_server entries and asserts on failed checks. */
void card_dev_close_events(void) {
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
