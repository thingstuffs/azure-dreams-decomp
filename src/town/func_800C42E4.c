#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern unsigned char D_800717D0[16];
extern M2C_UNK D_800D42CC;

/* Passes the global buffer and data address to appendTownMovieListNode. */
void func_800C1A44(void) {
    appendTownMovieListNode(D_800717D0, &D_800D42CC);
}
