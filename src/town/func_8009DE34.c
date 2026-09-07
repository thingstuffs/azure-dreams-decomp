#include "common.h"

extern void func_8008F664(void *, void *);
extern void func_8009B2C4(void *, void *, void *, void *);
extern void func_8009BFC0(void *, void *, void *, void *);

extern u8 D_8009B454[];
extern u8 D_8009B594[];
extern u8 D_8009BDC0[];
extern u8 D_800CFCB4[];

void func_8009B594(void *arg0, void *arg1, void *arg2, void *arg3) {
    s32 i;
    void *state;
    s32 *value;

    for (i = 0; i < 6; i++) {
        u8 *entry = D_800CFCB4 + i;

        if (entry[0x3A] != 0 || entry[0x40] != 0) {
            break;
        }
    }
    if (i < 6) {
        if (*(u8 *)((u8 *)arg1 + 0x3B) == 0) {
            func_8009BFC0(arg0, arg1, arg2, arg3);
        }
        func_8008F664(arg1, arg2);
        func_8009B2C4(arg0, arg1, arg2, arg3);
    }
    state = *(void **)((u8 *)arg0 + 0x50);
    if (state != D_8009B454 && state != D_8009B594 && state != D_8009BDC0) {
        value = *(s32 **)((u8 *)arg0 + 0x7C);
        if (value != 0) {
            *(s32 *)((u8 *)arg3 + 8) = *value;
        }
    }
}
