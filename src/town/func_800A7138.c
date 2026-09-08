#include "common.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80100DB0[3];
/* p_came_rotset: Set the first camera rotation component. */
void func_800A4898(s32 rotation) {
    *D_80100DB0 = rotation;
}
