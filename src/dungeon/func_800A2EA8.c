#include "common.h"
#ifndef NULL
#define NULL 0
#endif
#define F(e,t,o) (*(t)((s8 *)(e)+(o)))
extern u8 D_80045340[];
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern s32 func_800A7A38(void *);
extern void func_800BC26C(void *, s32, s32, s32);

void *func_800A8608(s32 a0, s32 a1, s16 a2, s32 a3, volatile s32 a4) {
    s32 a4w = a4;
    void *v0;
    void *s0;
    void *v02;

    v0 = func_8003FD64(0x12, (void *)a0);
    if (v0 != NULL) {
        v02 = F(v0, void **, 8);
        s0 = F(v0, void **, 0xC);
        F(v02, s16 *, 2) = a2;
        F(v02, s16 *, 6) = a3;
        F(v02, s16 *, 0xA) = (s16)a4w;
        func_8004491C(v0, D_80045340);
        F(s0, u8 *, 0xE) = 0x80;
        F(s0, u8 *, 0xD) = 0x80;
        F(s0, u8 *, 0xC) = 0x80;
        F(s0, s16 *, 0x1E) = 0x1000;
        F(s0, s16 *, 0x1C) = 0x1000;
        F(s0, s32 *, 8) = func_800A7A38((void *)a1);
        func_800BC26C(v0, 0, 0, 0);
    }
    return v0;
}
