#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern unsigned char D_800717D0[16];
extern M2C_UNK D_800D42E4;

/* Appends D_800D42E4 to the linked list rooted at D_800717D0. */
void func_800C1A90(void) {
    func_8003AF58(D_800717D0, &D_800D42E4);
}
