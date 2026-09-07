/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"

extern s32 D_80700630[];
extern s32 D_80700630_return[];
extern void func_80700868(s32);
extern s32 func_80700B4C(void);
extern void func_80700BCC(void);
extern void func_80700ED8(s32, s32);

__asm__(".set D_80700630_return, 0x80700630");

s32 func_80881424(void) {
    s32 temp_v0;

    func_80700868(0);
    func_80700BCC();
    temp_v0 = func_80700B4C();
    D_80700630[0] = temp_v0;
    func_80700ED8(temp_v0, D_80700630[1]);
    return D_80700630_return[0];
}
