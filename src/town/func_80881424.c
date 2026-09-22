/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

extern s32 D_80700630[];
extern s32 D_80700630_return[];
extern void func_80700868(s32);
extern s32 func_80700B4C(void);
extern void func_80700BCC(void);
extern void func_80700ED8(s32, s32);

__asm__(".set D_80700630_return, 0x80700630");

/* Devkit scene step: reset the cursor, rebuild the list, latch its length and redraw. */
s32 func_80881424(void) {
    s32 list_length;

    func_80700868(0);
    func_80700BCC();
    list_length = func_80700B4C();
    D_80700630[0] = list_length;
    func_80700ED8(list_length, D_80700630[1]);
    return D_80700630_return[0];
}
