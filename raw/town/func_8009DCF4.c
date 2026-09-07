#include "common.h"

extern s16 func_8008F170(void *, void *);
extern void func_8008F27C(void *, void *, s16);
extern void func_8008F294(void *, void *);
extern void func_8008F664(void *, void *);
extern void func_8009B2C4(void *, void *, void *, void *);
extern void func_8009B518(void *);
extern void func_8009C0C0(void *, void *, void *, void *);

extern u8 D_8009B454[];
extern u8 D_8009B594[];
extern u8 D_8009BDC0[];
extern u8 D_800FE488[];

void func_8009B454(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 result;
    void *state;
    s32 *value;

    result = func_8008F170(arg2, D_800FE488);
    func_8008F294(arg1, arg2);
    func_8008F664(arg1, arg2);
    if (*(u8 *)((u8 *)arg1 + 0x3B) == 0) {
        if (result - *(s16 *)((u8 *)arg2 + 0xA) >= 4) {
            func_8009C0C0(arg0, arg1, arg2, arg3);
            func_8009B518(arg0);
            return;
        }
        func_8008F27C(arg1, arg2, result);
        *(s32 *)((u8 *)arg2 + 0xC) = 0;
        *(s32 *)((u8 *)arg2 + 0x10) = 0;
        *(s32 *)((u8 *)arg2 + 0x14) = 0;
        *(void **)((u8 *)arg0 + 0x50) = D_8009B594;
    }
    func_8009B2C4(arg0, arg1, arg2, arg3);
    state = *(void **)((u8 *)arg0 + 0x50);
    if (state != D_8009B454 && state != D_8009B594 && state != D_8009BDC0) {
        value = *(s32 **)((u8 *)arg0 + 0x7C);
        if (value != 0)
            *(s32 *)((u8 *)arg3 + 8) = *value;
    }
}
