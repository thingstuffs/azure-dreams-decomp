#include "common.h"

extern void func_800247D4(void);
extern void func_8002488C(void);
extern void func_800248D4(void);
extern void func_80024DF0(void);
extern void func_80024F30(void);
extern void func_80024FB0(void);
extern void func_80024FD8(void);
extern void func_800250E0(void);
extern void func_80025118(void);

extern s32 func_8009D218(void *, s32);
extern s32 func_800A6870(s32);
extern void func_800AD4D0(void *);
extern void func_800AD568(void *, s32);
extern void func_800B4C7C(s32, void *, s32, s32);

static void (*const callbacks[])(void) = {
    func_800247D4,
    0,
    func_8002488C,
    func_800248D4,
    func_80024DF0,
    func_80024F30,
    func_80024FB0,
    func_80024FD8,
    func_800250E0,
    func_80025118,
};

void func_818AA83C(void *arg0, s32 arg1) {
    register s32 amount ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register s32 adjusted;

    if (func_8009D218(arg0, 2) == 0) {
        amount = func_800A6870(arg1 & 0xFF) + 16;
        adjusted = amount;
        if (*(u8 *)((u8 *)arg0 + 0x28) & 2) {
            adjusted = amount + ((s32)(amount << 16) >> 19);
        }
        *(u16 *)((u8 *)arg0 + 0x64) += adjusted;
        func_800AD568(arg0, adjusted);
        func_800B4C7C(0x8004, arg0, (s16)*(u16 *)((u8 *)arg0 + 0x64), 1);
        func_800AD4D0(arg0);
    }
}

