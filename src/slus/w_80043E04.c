#include "common.h"

/* Runs a per-frame update, then either primes D_80081500 with a new value
   and installs func_80043E60 as the next handler, or falls back to
   func_8003D92C, depending on D_80082E6E. */
/* only offset 0 of D_80082E6E is touched here; padded so the global is
   addressed via %hi/%lo rather than %gp_rel */
extern struct {
    u8 field_0;
    u8 pad[8];
} D_80082E6E;
extern s16 D_80081500;

extern void func_80043EB8(void);
extern s16 func_8003F794(s16 a0, s16 a1);
extern void func_80040A88(int a0);
extern void func_80043E60(void);
extern void func_8003D92C(void);

void func_80043E04(void) {
    func_80043EB8();
    if (D_80082E6E.field_0 != 0) {
        D_80081500 = func_8003F794(6, 8);
        func_80040A88((int) func_80043E60);
    } else {
        func_8003D92C();
    }
}
