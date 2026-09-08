#include "common.h"

extern u8 D_80082E6B;
extern s16 D_8008146C;
extern u8 D_800DCF4E[];
extern u8 D_800DF3CC[];

extern s32 func_80033BC0(s32);
extern void func_80040AA0(s32);
extern void func_8003E4FC();
extern void func_8003F320(void);

void func_800BCFC4(void) {
    s32 *p;

    if (D_80082E6B == 0x11) {
        p = (s32 *)0x80010000;
        if (p[0x824] == 0 && D_8008146C == 0x28 &&
            func_80033BC0(0xa2) == 0 && p[0x823] == 0) {
            p[0x823] = 1;
            func_80040AA0(0x21);
            D_800DCF4E[0] = 0;
            return;
        }
    }
    func_8003E4FC(6, &D_800DF3CC, 0);
    func_8003F320();
}

/* MECHANISM: The 0x18 frame naturally saves only ra and s0; s0 holds the lazy 0x80010000 page.
   func_80033BC0 and func_80040AA0 each take one argument; a1's page loads feed the shared tail.
   Removing the phantom second arguments eliminated two rematerialized lui words and closed exact. */
