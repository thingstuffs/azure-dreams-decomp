#include "common.h"

/* dual-access global: sb-store of D_800814D4 via $gp scalar, but address-of
 * (for CdControlB's param pointer) goes through a >8B neighbour symbol
 * D_800814D3[1] == &D_800814D4, forcing hi/lo codegen for the address-of. */
extern u8 D_800814D4;
extern u8 D_800814D3[8];

extern int CdControlB(u8 com, u8 *param, u8 *result);
extern void func_8003E70C(void);
extern void func_8003F5EC(void);

/* Tries CD mode 0x84 up to 16 times, increments retry counters on failure, then waits. */
void func_8003F624(void) {
    int attempts_left;

    D_800814D4 = 0x84;
    for (attempts_left = 0x10; attempts_left != 0; attempts_left--) {
        if (CdControlB(0xE, &D_800814D3[1], 0) != 0) {
            goto done;
        }
    }
    func_8003E70C();
done:
    func_8003F5EC();
}
