#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80100DB0[3];
/* Sets the first entry of D_80100DB0 to value. */
void func_800A4898(s32 value) {
    *D_80100DB0 = value;
}
