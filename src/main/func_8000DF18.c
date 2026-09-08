#include "common.h"

extern void func_8006A084(void);
extern s32 CloseEvent(void *arg0);
extern void printf(void *arg0, void *arg1, s32 arg2);
extern void exit(s32 arg0) __attribute__((noreturn));
extern void func_8006A094(void);

extern void *D_80028550;
extern void *D_80028554;
extern void *D_80028558;
extern void *D_8002855C;
extern void *D_80028560;
extern void *D_80028564;
extern void *D_80028568;
extern void *D_8002856C;
extern u8 D_80020000[];
extern u8 D_80020028[];

/* Closes memory card events, exiting if any close fails. */
void func_80020F18(void)
{
    func_8006A084();
    if (CloseEvent(D_80028550) == 0) {
        printf(D_80020000, D_80020028, 0x107);
        exit(1);
    }
    if (CloseEvent(D_80028554) == 0) {
        printf(D_80020000, D_80020028, 0x109);
        exit(1);
    }
    if (CloseEvent(D_80028558) == 0) {
        printf(D_80020000, D_80020028, 0x10B);
        exit(1);
    }
    if (CloseEvent(D_8002855C) == 0) {
        printf(D_80020000, D_80020028, 0x10D);
        exit(1);
    }
    if (CloseEvent(D_80028560) == 0) {
        printf(D_80020000, D_80020028, 0x10F);
        exit(1);
    }
    if (CloseEvent(D_80028564) == 0) {
        printf(D_80020000, D_80020028, 0x111);
        exit(1);
    }
    if (CloseEvent(D_80028568) == 0) {
        printf(D_80020000, D_80020028, 0x113);
        exit(1);
    }
    if (CloseEvent(D_8002856C) == 0) {
        printf(D_80020000, D_80020028, 0x115);
        exit(1);
    }
    func_8006A094();
}
