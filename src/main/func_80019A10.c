#include "common.h"

extern void func_8007BEF0(s32 arg0) __attribute__((noreturn));
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern s32 func_8007C998(s32 arg0, s32 arg1, s32 arg2, void *arg3);
extern s32 func_8007C9D8(s32 arg0);
extern void func_8007CA38(void);
extern void func_8007CA48(void);

extern s32 D_80400004[];
extern s32 D_8040002C[];
extern s32 D_80409270[];
extern s32 D_80409274[];
extern s32 D_80409278[];
extern s32 D_8040927C[];
extern s32 D_80409280[];
extern s32 D_80409284[];
extern s32 D_80409288[];
extern s32 D_8040928C[];
extern s32 D_804009C0[];
extern s32 D_804009D4[];
extern s32 D_804009E8[];
extern s32 D_804009FC[];

/* Opens and enables memory card events, asserting that each operation succeeds. */
void func_80019A10(void) {
    s32 event_handle;
    func_8007CA38();
    event_handle = func_8007C998(0xF4000001, 4, 0x2000, 0);
    *(s32 *)0x80409270 = event_handle;
    if (event_handle == -1) { func_8007C040(D_80400004, D_8040002C, 0xB4); func_8007BEF0(1); }
    event_handle = func_8007C998(0xF4000001, 0x8000, 0x2000, 0);
    *(s32 *)0x80409274 = event_handle;
    if (event_handle == -1) { func_8007C040(D_80400004, D_8040002C, 0xB6); func_8007BEF0(1); }
    event_handle = func_8007C998(0xF4000001, 0x100, 0x2000, 0);
    *(s32 *)0x80409278 = event_handle;
    if (event_handle == -1) { func_8007C040(D_80400004, D_8040002C, 0xB8); func_8007BEF0(1); }
    event_handle = func_8007C998(0xF4000001, 0x2000, 0x2000, 0);
    *(s32 *)0x8040927C = event_handle;
    if (event_handle == -1) { func_8007C040(D_80400004, D_8040002C, 0xBA); func_8007BEF0(1); }
    event_handle = func_8007C998(0xF0000011, 4, 0x1000, D_804009C0);
    *(s32 *)0x80409280 = event_handle;
    if (event_handle == -1) { func_8007C040(D_80400004, D_8040002C, 0xBD); func_8007BEF0(1); }
    event_handle = func_8007C998(0xF0000011, 0x8000, 0x1000, D_804009D4);
    *(s32 *)0x80409284 = event_handle;
    if (event_handle == -1) { func_8007C040(D_80400004, D_8040002C, 0xBF); func_8007BEF0(1); }
    event_handle = func_8007C998(0xF0000011, 0x100, 0x1000, D_804009E8);
    *(s32 *)0x80409288 = event_handle;
    if (event_handle == -1) { func_8007C040(D_80400004, D_8040002C, 0xC1); func_8007BEF0(1); }
    event_handle = func_8007C998(0xF0000011, 0x2000, 0x1000, D_804009FC);
    *(s32 *)0x8040928C = event_handle;
    if (event_handle == -1) { func_8007C040(D_80400004, D_8040002C, 0xC3); func_8007BEF0(1); }
    func_8007CA48();
    if (func_8007C9D8(D_80409270[0]) == 0) { func_8007C040(D_80400004, D_8040002C, 0xCF); func_8007BEF0(1); }
    if (func_8007C9D8(D_80409274[0]) == 0) { func_8007C040(D_80400004, D_8040002C, 0xD1); func_8007BEF0(1); }
    if (func_8007C9D8(D_80409278[0]) == 0) { func_8007C040(D_80400004, D_8040002C, 0xD3); func_8007BEF0(1); }
    if (func_8007C9D8(D_8040927C[0]) == 0) { func_8007C040(D_80400004, D_8040002C, 0xD5); func_8007BEF0(1); }
    if (func_8007C9D8(D_80409280[0]) == 0) { func_8007C040(D_80400004, D_8040002C, 0xD7); func_8007BEF0(1); }
    if (func_8007C9D8(D_80409284[0]) == 0) { func_8007C040(D_80400004, D_8040002C, 0xD9); func_8007BEF0(1); }
    if (func_8007C9D8(D_80409288[0]) == 0) { func_8007C040(D_80400004, D_8040002C, 0xDB); func_8007BEF0(1); }
    if (func_8007C9D8(D_8040928C[0]) == 0) { func_8007C040(D_80400004, D_8040002C, 0xDD); func_8007BEF0(1); }
}
