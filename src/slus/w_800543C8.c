#include "common.h"

/* Dispatcher: if top byte of D_800847D4 is set, call func_80055CF4() first,
 * then unconditionally call func_800544A4() and func_8005440C(). */
extern int D_800847D4[3]; /* size > 8 to force %hi/%lo addressing (see gp-vs-hilo notes) */

extern void func_80055CF4(void);
extern void func_800544A4(void);
extern void func_8005440C(void);

void func_800543C8(void)
{
    if (D_800847D4[0] & 0xFF000000) {
        func_80055CF4();
    }
    func_800544A4();
    func_8005440C();
}
