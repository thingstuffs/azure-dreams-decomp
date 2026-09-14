#include "common.h"

extern s8 D_80080A84[];
extern s8 D_80080A88[];
extern u8 D_80082E60[];
extern u8 D_80082E6A[];

extern void func_80020F18(void);
extern void func_800585A0(void);
extern void SD_Call(s32 arg0);

/* Set state 2, run setup, select sound behavior, and clear the high flag bit. */
void func_80027BF4(void) {
    D_80080A84[0] = 2;
    func_80020F18();
    func_800585A0();
    if (D_80082E6A[0] == 1) {
        SD_Call(0x200);
    } else {
        D_80080A88[0] = 0;
    }
    D_80082E60[0xF] &= 0x7F;
}
