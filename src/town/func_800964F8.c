#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 *D_800FE5D8[3];
extern s32 D_800947CC;

/* Sets the first pointer in D_800FE5D8 to D_800947CC. */
s32 townSetReturnItemCallback(void) {
    *D_800FE5D8 = &D_800947CC;
    return 0;
}
