#include "common.h"

/* Sets CD param byte D_800814D4=0x84 and retries CdControlB(CdlSetmode, &D_800814D4, 0)
 * up to 16 times; on total failure re-inits the CD via func_8003E70C(); always finishes
 * by waiting ~0x200 VSyncs via func_8003F5EC(). */
/* dual-access global: sb-store of D_800814D4 via $gp scalar, but address-of
 * (for CdControlB's param pointer) goes through a >8B neighbour symbol
 * D_800814D3[1] == &D_800814D4, forcing hi/lo codegen for the address-of. */
extern u8 D_800814D4;
extern u8 D_800814D3[8];

extern int CdControlB(u8 com, u8 *param, u8 *result);
extern void func_8003E70C(void);
extern void func_8003F5EC(void);

void func_8003F624(void) {
    int i;

    D_800814D4 = 0x84;
    for (i = 0x10; i != 0; i--) {
        if (CdControlB(0xE, &D_800814D3[1], 0) != 0) {
            goto done;
        }
    }
    func_8003E70C();
done:
    func_8003F5EC();
}
